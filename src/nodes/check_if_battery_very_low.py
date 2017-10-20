#!/usr/bin/env python

import rospy
from BTTask import BTCondition

class BTCheckIfBatteryVeryLow(BTCondition):
    def __init__(self, name):
        super(BTCheckIfBatteryVeryLow, self).__init__(name)

if __name__ == '__main__':
    rospy.init_node('check_if_battery_very_low')
    BTCondition(rospy.get_name())
    rospy.spin()
