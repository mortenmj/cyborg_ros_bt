#!/usr/bin/env python

import rospy
from BTTask import BTAction

class BTDoRecharge(BTAction):
    def __init__(self, name):
        super(BTDoTask, self).__init__(name)

if __name__ == '__main__':
    rospy.init_node('do_recharge')
    BTAction(rospy.get_name())
    rospy.spin()
