# -*- python -*-
# vim:set ts=4 sw=4 et:

from pyrrd.rrd import *
from webreader import current_data
import threading
import time


ENGINE_SERVO = 0


class RRDEngineLog(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self, name='imu data storage')
        self.daemon = True
        self.fname = time.strftime('./static/log/engine_log_%Y-%m-%d-%H:%M.rrd')
        self.create()
        self.terminate = threading.Event()

    def create(self):
        e_rpm_ds = DataSource(dsName='engine_rpm', dsType='GAUGE', heartbeat=1)
        e_trm_ds = DataSource(dsName='engine_temp', dsType='GAUGE', heartbeat=1)
        e_servo_ds = DataSource(dsName='engine_servo', dsType='ABSOLUTE', heartbeat=1)

        avg1 = RRA(cf='AVERAGE', xff=0.5, steps=1, rows=3600*2)
        avg2 = RRA(cf='AVERAGE', xff=0.5, steps=5, rows=3600)
        min_ = RRA(cf='MIN', xff=0.5, steps=5, rows=3600)
        max_ = RRA(cf='MAX', xff=0.5, steps=5, rows=3600)

        self.rrdfile = RRD(self.fname, ds=(e_rpm_ds, e_trm_ds, e_servo_ds, ), rra=(avg1, avg2, min_, max_, ), step=1)
        self.rrdfile.create()

    def run(self):
        while not self.terminate.is_set():
            rpm = current_data.rpm_dat
            trm = current_data.trm_dat
            servo = current_data._servo_state[ENGINE_SERVO]

            self.rrdfile.bufferValue(time.time(), rpm, trm, servo)
            self.rrdfile.update()

            self.terminate.wait(1.0)

    def stop(self):
        self.terminate.set()
