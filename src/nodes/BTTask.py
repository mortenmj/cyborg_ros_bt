#!/usr/bin/env python

import actionlib
import behavior_tree_core.msg
from enum import Enum

class BTStatus(Enum):
    Running = 0
    Success = 1
    Failure = 2

class BTTask(object):
    # Messages that are used to publish feedback/result
    _feedback = behavior_tree_core.msg.BTFeedback()
    _result   = behavior_tree_core.msg.BTResult()

    def __init__(self, name):
        self._action_name = name
        self._as = actionlib.SimpleActionServer(self._action_name, behavior_tree_core.msg.BTAction, execute_cb=self.execute_cb, auto_start = False)
        self._as.start()

    # Called immediately before execution. Can be used to reset state from previous execution.
    def on_start(self):
        pass

    # Called to run the actual task
    def on_update(self, goal=None):
        pass

    # Called after execution success or failure
    def on_end(self):
        pass

    # Called when the behavior tree finishes
    def on_complete(self):
        pass

    # Called when behavior is paused and resumed
    def on_pause(self, paused):
        pass

    # Get this tasks priority of running
    def get_priority(self):
        pass

    def set_status(self, status):
        if status is BTStatus.Success:
            self._feedback.status = 1
            self._result.status = self._feedback.status
            rospy.loginfo('Action %s: Succeeded' % self._action_name)
            self._as.set_succeeded(self._result)
        elif status is BTStatus.Failure:
            self._feedback.status = 2
            self._result.status = self._feedback.status
            rospy.loginfo('Action %s: Failed' % self._action_name)
            self._as.set_succeeded(self._result)
        else:
            rospy.logerr('Action %s: has a wrong return status' % self._action_name)

    def execute_cb(self, goal):
        self.on_start()
        running = True
        while self.on_update(goal) is 'running':
            running = self.on_update(self)
        self.on_end()

class BTAction(BTTask):
    def __init__(self, name):
        super(BTAction, self).__init__(name)

class BTCondition(BTTask):
    def __init__(self, name):
        super(BTCondition, self).__init__(name)
