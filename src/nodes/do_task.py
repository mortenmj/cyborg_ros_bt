#!/usr/bin/env python

import rospy
from BTTask import BTAction

class BTDoTask(BTAction):
    def __init__(self, name):
        super(BTDoTask, self).__init__(name)

if __name__ == '__main__':
    rospy.init_node('do_task')
    BTAction(rospy.get_name())
    rospy.spin()
