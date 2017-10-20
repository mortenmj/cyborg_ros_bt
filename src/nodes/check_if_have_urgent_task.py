#!/usr/bin/env python

import rospy
from BTTask import BTCondition

class BTCheckIfHaveUrgentTask(BTCondition):
    def __init__(self, name):
        super(BTCheckIfHaveUrgentTask, self).__init__(name)

if __name__ == '__main__':
    rospy.init_node('check_if_have_urgent_task')
    BTCondition(rospy.get_name())
    rospy.spin()
