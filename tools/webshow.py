#!/usr/bin/env python
# vim:set ts=4 sw=4 et:

import sys
import imuproto
import argparse
import web
import web.template
import time
from webreader import current_data
from rrdlog import RRDEngineLog

#try:
#    import cjson as json
#except:
#    import json
import json

urls = (
    '/api/get/(rpm|bar|trm|all)', 'JsonGetCurrent',
    '/api/set/servo', 'JsonSetServo',
    '/api/set/engine-stop', 'JsonSetStop',
    '/api/set/engine-release', 'JsonSetRelease',
    '/', 'Index',
)

render = web.template.render('tpl/', cache=False, globals=globals())


class Index(object):
    def GET(self):
        return render.index(current_data.get_all(), time.time())


class JsonGetCurrent(object):
    def GET(self, element):
        if element == 'rpm':
            return json.dumps({'timestamp': time.time(), 'rpm': current_data.rpm_dat})
        elif element == 'bar':
            return json.dumps({'timestamp': time.time(), 'bar': current_data.bar_dat})
        elif element == 'trm':
            return json.dumps({'timestamp': time.time(), 'trm': current_data.trm_dat})
        elif element == 'all':
            all_ = current_data.get_all()
            all_.update(timestamp=time.time())
            return json.dumps(all_)
        else:
            return json.dumps({'error': 'unknown request'})


class JsonSetServo(object):
    def GET(self):
        return json.dumps({'error': 'use /api/get/all for servo state'})

    def POST(self):
        i = web.input()
        if i.has_key('json'):
            try:
                js = json.loads(i['json'])
            except ValueError as e:
                web.debug(e)
                return json.dumps({'error': repr(e)})

            for chan, pulse in js.iteritems():
                try:
                    c = int(chan)
                    p = int(pulse)
                except ValueError as e:
                    web.debug(e)
                    return json.dumps({'error': repr(e)})

                current_data.set_servo(c, p)

        elif i.has_key('channel') and i.has_key('pulse'):
            try:
                c = int(i['channel'])
                p = int(i['pulse'])
            except ValueError as e:
                web.debug(e)
                return json.dumps({'error': repr(e)})

            current_data.set_servo(c, p)

        else:
            return json.dumps({'error': 'unknown input', 'post_data': repr(i)})

        return json.dumps({'servo': 'ok'})


class JsonSetStop(object):
    def GET(self):
        return json.dumps({'error': 'use POST here secret=emergency'})

    def POST(self):
        i = web.input()
        if i.has_key('secret') and i['secret'] == 'emergency':
                current_data.stop_engine()
                pass
        else:
            return json.dumps({'error': 'unknown input', 'post_data': repr(i)})

        return json.dumps({'engine-stop': 'ok'})


class JsonSetRelease(object):
    def GET(self):
        return json.dumps({'error': 'use POST here secret=release'})

    def POST(self):
        i = web.input()
        if i.has_key('secret') and i['secret'] == 'release':
                current_data.stop_engine(False)
                pass
        else:
            return json.dumps({'error': 'unknown input', 'post_data': repr(i)})

        return json.dumps({'engine-release': 'ok'})




def main():
    parser = argparse.ArgumentParser(prefix_chars='-+')
    parser.add_argument("device", help="com port device file")
    parser.add_argument("baudrate", help="com port baudrate", type=int, nargs='?', default=230400)
    parser.add_argument("-p", dest="webport", help="server port", type=str, default='8080')

    args = parser.parse_args();

    ser = imuproto.serial.Serial(args.device, args.baudrate)
    reader = imuproto.PktReader(ser)

    current_data.set_reader(reader)
    current_data.start()

    log = RRDEngineLog()
    log.start()

    # hack
    app = web.application(urls, globals())
    sys.argv[1] = args.webport
    app.run()


if __name__ == "__main__":
    main()
