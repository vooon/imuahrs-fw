# -*- python -*-
# vim:ser ts=4 sw=4 et:

import web
import imuproto
import threading


class CurrentDataThread(threading.Thread):

    def __init__(self):
        threading.Thread.__init__(self, name='imu data logger')
        self.daemon = True
        self._lock = threading.Lock()
        self._terminate = threading.Event()

        self._last_update = 0
        self._version = ''
        self._sens_test = { 'accel': False, 'gyro': False, 'mag': False, 'baro': False }
        self._trm_dat = -99
        self._rpy_dat = 0
        self._bar_dat = { 'pressure': 0, 'temperature': -99 }
        self._servo_state = [ 0 ] * 8

        self._reader = None

    @property
    def last_update(self):
        with self._lock:
            return self._last_update

    @property
    def version(self):
        with self._lock:
            return self._version

    def _set_version(self, ver):
        web.debug("FW version: {}".format(ver))
        with self._lock:
            self._last_update_ms = ver.time
            self._version = ver.version_str

    @property
    def sens_test(self):
        with self._lock:
            return self._sens_test

    def _set_sens_test(self, pkt):
        web.debug("FW status: {}".format(pkt))
        with self._lock:
            self._last_update_ms = pkt.time
            self._sens_test = {
                'accel': pkt.accel_ok,
                'gyro': pkt.gyro_ok,
                'mag': pkt.mag_ok,
                'baro': pkt.baro_ok,
            }

    @property
    def trm_dat(self):
        with self._lock:
            return self._trm_dat

    def _set_trm_dat(self, trm):
        with self._lock:
            self._last_update_ms = trm.time
            self._trm_dat = trm.temperature / 100.0

    @property
    def rpy_dat(self):
        with self._lock:
            return self._rpy_dat

    def _set_rpy_dat(self, rpy):
        with self._lock:
            self._last_update_ms = rpy.time
            self._rpy_dat = rpy.rpy

    @property
    def bar_dat(self):
        with self._lock:
            return self._bar_dat

    def _set_bar_dat(self, bar):
        with self._lock:
            self._last_update_ms = bar.time
            self._bar_dat = {
                'pressure': bar.pressure / 1000.0,
                'temperature': bar.temperature / 100.0
            }

    def get_all(self):
        with self._lock:
            return {
                'last_update': self._last_update,
                'version': self._version,
                'sens_test': self._sens_test,
                'trm': self._trm_dat,
                'rpy': self._rpy_dat,
                'bar': self._bar_dat,
                'servo_state': self._servo_state,
            }

    def set_reader(self, reader):
        self._reader = reader

    def stop(self):
        self._terminate.set()

    def run(self):
        # init
        version_rq = imuproto.Pt_Version()
        sens_test_rq = imuproto.Pt_SensTest()

        mesg_en = imuproto.Pt_MesgEn()
        #mesg_en.mpu_dat_en = True
        #mesg_en.mag_dat_en = True
        mesg_en.bar_dat_en = True
        mesg_en.trm_dat_en = True
        #mesg_en.rpy_dat_en = True

        self._reader.start()
        self._reader.send(version_rq)
        self._reader.send(sens_test_rq)
        self._reader.send(mesg_en)

        kq = self._reader.getQueue()

        while not self._terminate.is_set():
            kq.join()
            pkt = kq.get()

            if isinstance(pkt, imuproto.Pt_Version):
                self._set_version(pkt)
            elif isinstance(pkt, imuproto.Pt_SensTest):
                self._set_sens_test(pkt)
            elif isinstance(pkt, imuproto.Pt_BarDat):
                self._set_bar_dat(pkt)
            elif isinstance(pkt, imuproto.Pt_TrmDat):
                self._set_trm_dat(pkt)
            elif False: # isinstance(pkt, imuproto.Pt_RpyDat):
                self._set_rpy_dat(pkt)
            else:
                web.debug("warn: unhandled packet {}".format(pkt))

    def set_servo(self, channel, pulse):
        with self._lock:
            servo_set = imuproto.Pt_ServoSet()
            servo_set.channel = channel
            servo_set.pulse = pulse

            self._servo_state[channel] = pulse
            self._reader.send(servo_set)


current_data = CurrentDataThread()

