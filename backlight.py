#!/usr/bin/env python3

import argparse
import os

class BacklightController:
    def __init__(self, device_string):
        self.device_string = device_string
        with open(os.path.join(device_string,'max_brightness')) as f:
            self.max_brightness = int(f.read().strip())
        with open(os.path.join(device_string,'brightness')) as f:
            self.brightness = int(f.read().strip())
        print('brightness before change: {} of {}'.format(self.brightness, self.max_brightness))

    def apply_change(self, change):
        brightness = min(self.brightness + change, self.max_brightness)
        brightness = max(0, brightness)
        print('Writing {} into {}'.format(
            brightness,
            os.path.join(self.device_string, 'brightness')))
        with open(os.path.join(self.device_string, 'brightness'), 'w') as f:
            f.write('{}'.format(brightness))


def backlight_control(args):
    ctrl = BacklightController(args.device)
    ctrl.apply_change(args.change)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-d',
                        '--device',
                        help='Backlight device',
                        default='/sys/class/backlight/intel_backlight/')
    parser.add_argument('change',
                        help='''Relative change spec, e.g. -10 to reduce by 10 points,
                        +10 to increase by 10 points''',
                        type=int,
                        default='0')
    args = parser.parse_args()

    backlight_control(args)
