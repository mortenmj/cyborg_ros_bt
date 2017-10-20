/* Copyright (C) 2015-2017 Michele Colledanchise - All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <behavior_tree.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "BehaviorTree");
    try
    {
        int TickPeriod_milliseconds = 1000;

        BT::SequenceNode *root = new BT::SequenceNode("root");

        /* Recharge if not busy.
         * If battery level somewhat low, finish current task and then recharge
         * If battery level very low, recharge immediately
         */
        BT::FallbackNode *fb1 = new BT::FallbackNode("fb1");
        BT::FallbackNode *fb2 = new BT::FallbackNode("fb2");
        BT::FallbackNode *fb3 = new BT::FallbackNode("fb3");
        BT::FallbackNode *fb4 = new BT::FallbackNode("fb4");

        BT::SequenceNode *sq1 = new BT::SequenceNode("sq1");
        BT::SequenceNode *sq2 = new BT::SequenceNode("sq2");
        BT::SequenceNode *sq3 = new BT::SequenceNode("sq3");
        BT::SequenceNode *sq4 = new BT::SequenceNode("sq4");

        BT::ROSCondition *check_if_have_task        = new BT::ROSCondition("check_if_have_task");
        BT::ROSCondition *check_if_have_urgent_task = new BT::ROSCondition("check_if_have_urgent_task");
        BT::ROSCondition *check_if_battery_low      = new BT::ROSCondition("check_if_battery_low");
        BT::ROSCondition *check_if_battery_very_low = new BT::ROSCondition("check_if_battery_very_low");

        BT::ROSAction    *do_recharge1 = new BT::ROSAction("do_recharge");
        BT::ROSAction    *do_recharge2 = new BT::ROSAction("do_recharge");
        BT::ROSAction    *do_recharge3 = new BT::ROSAction("do_recharge");
        BT::ROSAction    *do_task1     = new BT::ROSAction("do_task");
        BT::ROSAction    *do_task2     = new BT::ROSAction("do_task");

        root->AddChild(fb1);

        fb1->AddChild(sq1);
        fb1->AddChild(do_recharge1);

        sq1->AddChild(check_if_have_task);
        sq1->AddChild(fb2);

        fb2->AddChild(sq2);
        fb2->AddChild(fb4);

        sq2->AddChild(check_if_have_urgent_task);
        sq2->AddChild(fb3);

        fb3->AddChild(sq3);
        fb3->AddChild(do_recharge2);

        sq3->AddChild(check_if_battery_very_low);
        sq3->AddChild(do_task1);

        fb4->AddChild(sq4);
        fb4->AddChild(do_recharge3);

        sq4->AddChild(check_if_battery_low);
        sq4->AddChild(do_task2);

        Execute(root, TickPeriod_milliseconds);  // from BehaviorTree.cpp
    }
    catch (BT::BehaviorTreeException& Exception)
    {
        std::cout << Exception.what() << std::endl;
    }

    return 0;
}
