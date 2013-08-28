
#include "task_rpm.h"
#include "protocol.h"
#include <math.h>

#ifdef HAS_DEV_RPM

#define EVT_TIMEOUT	MS2ST(500)
#define IRQ_EVTMASK	EVENT_MASK(3)

/* Thread */
static WORKING_AREA(wa_rpm, 256);
static msg_t thd_rpm(void *arg UNUSED);
static Thread *thdp_rpm = NULL;

/* local data */

void rpm_init(void)
{
	thdp_rpm = chThdCreateStatic(wa_rpm, sizeof(wa_rpm), HIGHPRIO, thd_rpm, NULL);
}

static msg_t thd_rpm(void *arg UNUSED)
{
	msg_t ret;
	TimeMeasurement rpm_tm;
	//uint16_t rpm;
	float rpm;
	uint32_t period;

	chRegSetThreadName("rpm");

	tmInit();
	tmObjectInit(&rpm_tm);

	rpm_stop_engine(0);

	while (!chThdShouldTerminate()) {
		eventmask_t mask = chEvtWaitOneTimeout(ALL_EVENTS, EVT_TIMEOUT);

		if (!(mask & IRQ_EVTMASK)) {
			pt_send_rpm_dat(0);
			continue;
		}

		tmStopMeasurement(&rpm_tm);
		period = rpm_tm.last;
		tmStartMeasurement(&rpm_tm);

		period = RTT2US(period);

		if (period < 1000) {
			/* noise */
			continue;
		}

		rpm = 10e6f / period * 60.0f;
		pt_send_rpm_dat(rpm);
	}

	return 0;
}

void rpm_stop_engine(bool en)
{
	if (en) {
		palSetPadMode(RPM_GPIO, RPM_PIN, PAL_MODE_OUTPUT_OPENDRAIN);
		palClearPad(RPM_GPIO, RPM_PIN);
	}
	else {
		palSetPadMode(RPM_GPIO, RPM_PIN, PAL_MODE_INPUT_PULLUP);
		//palClearPad(RDM_GPIO, RPM_PIN);
	}
}

void rpm_exti_handler(EXTDriver *extp UNUSED, expchannel_t channel UNUSED)
{
	if (thdp_rpm == NULL)
		return;

	chSysLockFromIsr();
	chEvtSignalI(thdp_rpm, IRQ_EVTMASK);
	chSysUnlockFromIsr();
}

#endif /* HAS_DEV_NTC10K */
