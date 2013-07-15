#!/usr/bin/env python
# vim:set ts=4 sw=4 et

import sys
import imuproto as ipr


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


def usage():
    print "pktshow.py <tty dev> [+-mpu] [+-mag] [+-bar]"


def main():
    baud = 115200

    if len(sys.argv) < 2:
        usage()

    dev = sys.argv[1]

    ser = ipr.serial.Serial(dev, baud)
    reader = ipr.PktReader(ser)

    kq = reader.getQueue()
    reader.start()

    pv = ipr.Pt_Version()
    st = ipr.Pt_SensTest()

    reader.send(pv)
    reader.send(st)

    if len(sys.argv) > 2:
        me = ipr.Pt_MesgEn()
        for a in sys.argv[2:]:
            if a == '+mpu':
                me.mpu_dat_en = True
            elif a == '-mpu':
                me.mpu_dat_en = False
            elif a == '+mag':
                me.mag_dat_en = True
            elif a == '-mag':
                me.mag_dat_en = False
            elif a == '+bar':
                me.bar_dat_en = True
            elif a == '-bar':
                me.bar_dat_en = False

        reader.send(me)

    while True:
        kq.join()
        p = kq.get()
        update_stat(p)
        print p

if __name__ == "__main__":
    try:
        main()
    except:
        print_stat()

