# -*- Python -*-
# vim:set ts=4 ws=4 et

import serial
import threading
import struct
from Queue import Queue

class DesError(Exception):
    pass

class SerError(Exception):
    pass


PROTO_START = 0x79

CRC_TABLE = (
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
)

def _crc8(crc, buf):
    crc8 = crc
    for b in buf:
        crc8 = CRC_TABLE[crc8 ^ b]

    return crc8


class PacketBase(object):
    msgid = 0
    time = 0

    def __init__(self, time=0, bytestream=None):
        if bytestream is not None:
            self.deserialize(time, bytestream)

    def serialize(self):
        time = 0
        payload = self.serialize_payload()

        buf = bytearray((PROTO_START, self.msgid, time & 0xff, (time >> 8) & 0xff, len(payload)))
        buf += payload
        buf.append(_crc8(0, buf[1:]))

        return buf

    def serialize_payload(self):
        return bytearray()

    def deserialize(self, time, buf):
        self.time = time
        self.deserialize_payload(buf)

    def deserialize_payload(self, buf):
        pass


class Pt_Version(PacketBase):
    msgid = 0x00
    version_str = ""

    def deserialize_payload(self, buf):
        self.version_str = str(buf)

    def __repr__(self):
        return "<Pt_Version: ({} ms) '{}'>".format(self.time, self.version_str)


class Pt_SensTest(PacketBase):
    msgid = 0x01
    gyro_ok = False
    accel_ok = False
    mag_ok = False
    baro_ok = False

    def deserialize_payload(self, buf):
        if len(buf) != 1:
            raise DesError

        b = buf[0]

        self.gyro_ok = bool(b & 0x01)
        self.accel_ok = bool(b & 0x02)
        self.mag_ok = bool(b & 0x04)
        self.baro_ok = bool(b & 0x08)

    def __repr__(self):
        return "<Pt_SensTest: ({} ms) gyro_ok={} accel_ok={} mag_ok={} baro_ok={}>".format(
            self.time, self.gyro_ok, self.accel_ok, self.mag_ok, self.baro_ok)


class Pt_Heartbeat(PacketBase):
    msgid = 0x02

    def __repr__(self):
        return "<Pt_Heartbeat: ({} ms)>".format(self.time)


class Pt_MesgEn(PacketBase):
    msgid = 0xc0
    mpu_dat_en = False
    mag_dat_en = False
    bar_dat_en = False

    def serialize_payload(self):
        b = 0
        if self.mpu_dat_en:
            b |= 0x01
        if self.mag_dat_en:
            b |= 0x02
        if self.bar_dat_en:
            b |= 0x04
        return bytearray((b, ))

    def __repr__(self):
        return "<Pt_MesgEn: ({} ms) mpu_dat_en={} mag_dat_en={} bar_dat_en={}>".format(
            self.time, self.mpu_dat_en, self.mag_dat_en, self.bar_dat_en)


class Pt_MpuCfg(PacketBase):
    msgid = 0xc1
    gyro_scale = 0
    accel_scale = 0
    filter_scale = 0

    def serialize_payload(self):
        return bytearray(struct.pack('<BBB', self.gyro_scale, self.accel_scale, self.filter_scale))

    def __repr__(self):
        return "<Pt_MpuCfg: ({} ms) gyro_scale={} accel_scale={} filter_scale={}>".format(
            self.time, self.gyro_scale, self.accel_scale, self.filter_scale)


class Pt_HmcCfg(PacketBase):
    msgid = 0xc2

    def __repr__(self):
        return "<Pt_HmcCfg: ({} ms)>".format(self.time)

class Pt_BmpCfg(PacketBase):
    msgid = 0xc3

    def __repr__(self):
        return "<Pt_BmpCfg: ({} ms)>".format(self.time)


class Pt_MpuDat(PacketBase):
    msgid = 0xd0
    gyro_x = 0
    gyro_y = 0
    gyro_z = 0
    accle_x = 0
    accle_y = 0
    accle_z = 0
    temperature = 0

    def deserialize_payload(self, buf):
        if len(buf) != 14:
                raise DesError

        self.gyro_x, self.gyro_y, self.gyro_z, \
        self.accel_x, self.accel_y, self.accel_z, \
        self.temperature = struct.unpack('<hhhhhhh', buf)

    def __repr__(self):
        return "<Pt_MpuDat: ({} ms) gyro=[{}, {}, {}] accel=[{}, {}, {}] temp={}>".format(
                self.time,
                self.gyro_x, self.gyro_y, self.gyro_z,
                self.accel_x, self.accel_y, self.accel_z,
                self.temperature)


class Pt_MagDat(PacketBase):
    msgid = 0xd1
    mag_x = 0
    mag_y = 0
    mag_z = 0

    def deserialize_payload(self, buf):
        if len(buf) != 6:
            raise DesError

        self.mag_x, self.mag_y, self.mag_z = struct.unpack('<hhh', buf)

    def __repr__(self):
        return "<Pt_MagDat: ({} ms) mag=[{}, {}, {}]>".format(
            self.time, self.mag_x, self.mag_y, self.mag_z)


class Pt_BarDat(PacketBase):
    msgid = 0xd2

    pressure = 0
    temperature = 0

    def deserialize_payload(self, buf):
        if len(buf) != 6:
            raise DesError

        self.pressure, self.temperature = struct.unpack('<ih', buf)

    def __repr__(self):
        return "<Pt_BarDat: ({} ms) pressure={} temperature={}>".format(
            self.time, self.pressure, self.temperature)


PKT_TYPES = {
    0x00: Pt_Version,
    0x01: Pt_SensTest,
    0x02: Pt_Heartbeat,
    0xc0: Pt_MesgEn,
    0xc1: Pt_MpuCfg,
    0xc2: Pt_HmcCfg,
    0xc3: Pt_BmpCfg,
    0xd0: Pt_MpuDat,
    0xd1: Pt_MagDat,
    0xd2: Pt_BarDat,
}


class PktReader(threading.Thread):
    def __init__(self, serdev):
        threading.Thread.__init__(self, name='imuahrs reader')

        self.ser = serdev
        self.terminate = threading.Event()
        self.pkt_in_queue = Queue()
        self.ser.setTimeout(2.0)
        self.daemon = True

    def stop(self):
        self.terminate.set()

    def getQueue(self):
        return self.pkt_in_queue

    def send(self, pkt):
        if isinstance(pkt, PacketBase):
            self.ser.write(pkt.serialize())
        else:
            raise DesError

    def run(self):
        state = 'S'
        msgid = 0
        time = 0
        len_ = 0
        crc = 0
        payload = bytearray()

        while not self.terminate.is_set():
            c = self.ser.read(1)
            if len(c) == 0:
                continue

            b = bytearray(c)

            if state == 'S':
                if b[0] != PROTO_START:
                    continue
                state = 'M'

            elif state == 'M':
                msgid = b[0]
                crc = _crc8(0, b)
                state = 'TL'

            elif state == 'TL':
                time = b[0]
                crc = _crc8(crc, b)
                state = 'TH'

            elif state == 'TH':
                time |= b[0] << 8
                crc = _crc8(crc, b)
                state = 'L'

            elif state == 'L':
                len_ = b[0]
                crc = _crc8(crc, b)
                if len_ > 0:
                    state = 'P'
                else:
                    state = 'C'

            elif state == 'C':
                if crc == b[0]:
                    self._insert_packet(msgid, time, payload)
                else:
                    print "crc error: MSGID: {} TIME: {} LEN: {} CRC: {} = {} {} {}".format(
                        msgid, time, len_, b, crc, c, len(c))

                state = 'S'

            if state == 'P': # pass thrugh payload receive from 'L'
                buf = self.ser.read(len_)
                if (len(buf) != len_):
                    state = 'S'
                    print "short read"
                    continue

                payload = bytearray(buf)
                crc = _crc8(crc, payload)
                state = 'C'

    def _insert_packet(self, msgid, time, payload):
        if PKT_TYPES.has_key(msgid):
            try:
                pkt = PKT_TYPES[msgid](time, payload)
                self.pkt_in_queue.put(pkt)
                self.pkt_in_queue.task_done()
            except DesError:
                print "bad packet"
        else:
            print "unknown msgid", msgid

