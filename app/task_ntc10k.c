
#include "task_ntc10k.h"
#include "protocol.h"
#include <math.h>

#ifdef HAS_DEV_NTC10K

/* Thread */
static WORKING_AREA(wa_ntc10k, 256);
static msg_t thd_ntc10k(void *arg UNUSED);

/* local data */
#define OVERSAMPLING 4
static adcsample_t adc_samples[OVERSAMPLING];

static const ADCConversionGroup adc_trm_group = {
	FALSE,
	1,
	NULL,
	NULL,
	0, /* CR1 */
	ADC_CR2_SWSTART, /* CR2 */
	ADC_SMPR1_SMP_AN15(ADC_SAMPLE_144),
	0, /* SMPR2 */
	ADC_SQR1_NUM_CH(1),
	0, /* SQR2 */
	ADC_SQR3_SQ1_N(ADC_CHANNEL_IN15)
};

void ntc10k_init(void)
{
	chThdCreateStatic(wa_ntc10k, sizeof(wa_ntc10k), HIGHPRIO, thd_ntc10k, NULL);
}

static msg_t thd_ntc10k(void *arg UNUSED)
{
	msg_t ret;
	uint32_t adc_raw;

	chRegSetThreadName("ntc10k");

	palSetPadMode(NTC10K_GPIO, NTC10K_PIN, PAL_MODE_INPUT_ANALOG);

	while (!chThdShouldTerminate()) {
		chThdSleepMilliseconds(50);

		adcAcquireBus(&ADCD1);
		ret = adcConvert(&ADCD1, &adc_trm_group, adc_samples, OVERSAMPLING);
		adcReleaseBus(&ADCD1);

		if (ret != RDY_OK)
			continue;

		adc_raw = 0;
		for (int i = 0; i < OVERSAMPLING; i++)
			adc_raw += adc_samples[i];
		adc_raw /= OVERSAMPLING;

		/* See notes at
		 * @href http://en.wikipedia.org/wiki/Voltage_divider
		 * @href http://en.wikipedia.org/wiki/Thermistor
		 */

		const float Vin = 5.0; /* V divider refrence */
		const float Vref = 3.3; /* V ADC refrence */
		const float R1 = 10e3; /* Ohm divider R1 */

		float Vout = adc_raw * Vref / 4096.0f;
		float R2 = R1 / (Vin / Vout - 1);

		/* Shteinhart form */
		//const float a = 1.40e-3;
		//const float b = 2.37e-4;
		//const float c = 9.90e-8;

		//float lnR = log(R2);
		//float T = 1 / (a + b * lnR + c * lnR * lnR * lnR);
		//T -= 273.15;

		/* B-form */
		const float T0 = 298.15; /* 25 C in Kelvin */
		//const float R0 = 10e3; /* R for T0 */
		const float R0 = 8.6e3; /* R for T0 */
		const float B = 3988.0; /* from DS for B57861S0103F40 */
		float T = 1 / (1 / T0 + 1 / B * log(R2 / R0));
		T -= 273.15;

		pt_send_trm_dat((int)(T * 100.0));
		//debug("Temp: ADC=%d, V=%f, R2=%f, T=%f\n", adc_raw, Vout, R2, T);
	}

	return 0;
}

#endif /* HAS_DEV_NTC10K */
