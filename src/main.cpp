#include <iostream>
#include <unistd.h>
#include <signal.h>

#include <behavior_tree.h>
#include "parser.h"

std::string agent;

void signal_callback_handler(int signum)
{
    printf("Caught signal %d\n", signum);
    // Cleanup and close up stuff here
    // Terminate program
    exit(signum);
}

int main(int argc, char **argv)
{
    try
    {
        int TickPeriod_milliseconds = 1000;
        std::cout << "Hello, world!" << std::endl;

        // initialize the behavior tree client node
        agent = "test";
        ros::init(argc, argv, std::string("behavior_tree") + "_" + agent);

        // create the bt from the file bt.txt (put on the path)
        std::cout << "----------------- PARSE FILE -----------------" << std::endl;
        std::string filename;

        if (ros::param::has("/apc/bt/file"))
        {
            ros::param::get("/apc/bt/file", filename);
        }
        else
        {
            filename = std::string("bt") + "_" + agent;
        }

        parse_file(filename + ".txt");

        // print the data parsed from the specification file
        std::cout << "----------------- PRINT TREE -----------------" << std::endl;
    }
    catch (BT::BehaviorTreeException& Exception)
    {
        std::cout << Exception.what() << std::endl;
    }
}
