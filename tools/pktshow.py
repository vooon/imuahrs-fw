#!/usr/bin/env python
# vim:set ts=4 sw=4 et

import sys
import imuproto as ipr
import argparse


class UpdStat(object):
    msgid = 0

    minup = 0x10000 - 1
    avgup = 0
    maxup = 0

    last_time = 0
    MAX_TIME = 0x10000 - 1

    dt_acc = 0
    dt_count = 0

    def __init__(self, msgid, start_time):
        self.msgid = msgid
        self.last_time = start_time
        self.dt_acc = 0.0
        self.dt_count = 0

    def _timediff(self, time):
        if (time < self.last_time):
            dt = self.MAX_TIME - self.last_time
            return dt + time
        else:
            return time - self.last_time

    def update(self, time):
        dt = self._timediff(time)

        self.minup = min(self.minup, dt)
        self.maxup = max(self.maxup, dt)

        self.dt_acc += dt
        self.dt_count += 1

        self.avgup = int(self.dt_acc / self.dt_count)
        self.last_time = time


PKT_STAT = {}

def update_stat(pkt):
    if PKT_STAT.has_key(pkt.msgid):
        PKT_STAT[pkt.msgid].update(pkt.time)
    else:
        PKT_STAT[pkt.msgid] = UpdStat(pkt.msgid, pkt.time)


def print_stat():
    print " Update time int millis "
    print "ID:    min    avg    max    pkt cnt"
    print "-----------------------------------"
    for s in PKT_STAT.values():
        print "{msgid:02x}: {min:6d} {avg:6d} {max:6d} {cnt:10d}".format(
            msgid=s.msgid, min=s.minup, avg=s.avgup, max=s.maxup, cnt=s.dt_count)


def main():
    def anyint(string):
        return int(string, 0)

    parser = argparse.ArgumentParser(prefix_chars='-+')
    parser.add_argument("device", help="com port device file")
    parser.add_argument("baudrate", help="com port baudrate", type=int, nargs='?', default=230400)

    parser.add_argument("+mpu", dest="mpu_en", action="store_true", default=None,
                        help="enable mpu_dat messages")
    parser.add_argument("-mpu", dest="mpu_en", action="store_false", default=None,
                        help="disable mpu_dat messages")

    parser.add_argument("+mag", dest="mag_en", action="store_true", default=None,
                        help="enable mag_dat messages")
    parser.add_argument("-mag", dest="mag_en", action="store_false", default=None,
                        help="disable mag_dat messages")

    parser.add_argument("+bar", dest="bar_en", action="store_true", default=None,
                        help="enable bar_dat messages")
    parser.add_argument("-bar", dest="bar_en", action="store_false", default=None,
                        help="disable bar_dat messages")

    parser.add_argument("+mpucfg", dest="mpu_cfg", default=None, type=anyint, nargs=3,
                        help="send mpu_cfg message (default: 0x18 0x10 0x00)")

    args = parser.parse_args();

    ser = ipr.serial.Serial(args.device, args.baudrate)
    reader = ipr.PktReader(ser)

    kq = reader.getQueue()
    reader.start()

    pv = ipr.Pt_Version()
    st = ipr.Pt_SensTest()

    reader.send(pv)
    reader.send(st)

    if args.mpu_en is not None or args.mag_en is not None or args.bar_en is not None:
        me = ipr.Pt_MesgEn()
        me.mpu_dat_en = args.mpu_en or False
        me.mag_dat_en = args.mag_en or False
        me.bar_dat_en = args.bar_en or False
        reader.send(me)

    if args.mpu_cfg is not None:
        mcf = ipr.Pt_MpuCfg()
        mcf.gyro_scale = args.mpu_cfg[0]
        mcf.accel_scale = args.mpu_cfg[1]
        mcf.filter_scale = args.mpu_cfg[2]
        reader.send(mcf)

    while True:
        kq.join()
        p = kq.get()
        update_stat(p)
        print p

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print_stat()

