#!/usr/bin/env python

import rospy
from BTTask import BTCondition

class BTCheckIfBatteryLow(BTCondition):
    def __init__(self, name):
        super(BTCheckIfBatteryLow, self).__init__(name)

if __name__ == '__main__':
    rospy.init_node('check_if_battery_low')
    BTCondition(rospy.get_name())
    rospy.spin()
