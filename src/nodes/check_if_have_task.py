#!/usr/bin/env python

import rospy
from BTTask import BTCondition

class BTCheckIfHaveTask(BTCondition):
    def __init__(self, name):
        super(BTCheckIfHaveTask, self).__init__(name)

if __name__ == '__main__':
    rospy.init_node('check_if_have_task')
    BTCondition(rospy.get_name())
    rospy.spin()
