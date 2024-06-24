#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <rvo2_ros/RVO.h>

int main(int argc, char **argv){
    
    ros::init(argc, argv, "wp_loader_node");
    ros::NodeHandle n;

    const int loop_rate_=20;
    ros::Rate loop_rate(loop_rate_);

    //param setting
    ros::NodeHandle pn("~");

    auto markers_pub = n.advertise<visualization_msgs::MarkerArray>("agent_markers", 1);
    visualization_msgs::MarkerArray marker_array;

    const float RVO_TWO_PI = 6.28318530717958647692F;

    RVO::RVOSimulator simulator;
    /* Specify the global time step of the simulation. */
    simulator.setTimeStep(1.0/loop_rate_);

    /* Specify the default parameters for agents that are subsequently added. */
    simulator.setAgentDefaults(1.0F, 4U, 5.0F, 5.0F, 0.1F, 0.2F);

    std::vector<RVO::Vector2> goals;
    const int agent_num=2;
    for (std::size_t i = 0U; i < agent_num; ++i) {
        simulator.addAgent(
            1.0F *
            RVO::Vector2(std::cos(static_cast<float>(i) * RVO_TWO_PI * 1.0/(agent_num+0)),
                            std::sin(static_cast<float>(i) * RVO_TWO_PI * 1.0/agent_num)));
        goals.push_back(-simulator.getAgentPosition(i));
    }

    while (n.ok())  {
        visualization_msgs::MarkerArray marker_array;
        for (int i = 0; i < static_cast<int>(simulator.getNumAgents()); ++i) {
            RVO::Vector2 goalVector = goals[i] - simulator.getAgentPosition(i);

            if (RVO::absSq(goalVector) > 1.0F) {
                goalVector = RVO::normalize(goalVector);
            }          

            simulator.setAgentPrefVelocity(i, goalVector);

            visualization_msgs::Marker marker;
            marker.header.frame_id = "map";
            marker.header.stamp = ros::Time::now();
            marker.ns = std::string("agent_marker");
            marker.id = i;
            marker.type = visualization_msgs::Marker::CYLINDER;
            marker.action = visualization_msgs::Marker::ADD;
            marker.pose.position.x = simulator.getAgentPosition(i).x();
            marker.pose.position.y = simulator.getAgentPosition(i).y();
            marker.pose.position.z = 0.0;
            marker.pose.orientation.w = 1.0;
            marker.pose.orientation.x = 0.0;
            marker.pose.orientation.y = 0.0;
            marker.pose.orientation.z = 0.0;
            marker.scale.x = 0.1;
            marker.scale.y = 0.1;
            marker.scale.z = 0.1;
            marker.color.r = 1.0;
            marker.color.g = 0.0;
            marker.color.b = 0.0;
            marker.color.a = 1.0;
            marker_array.markers.emplace_back(marker);
        }

        simulator.doStep();

        markers_pub.publish(marker_array);
        
        ros::spinOnce();
        loop_rate.sleep();
        
    }
    
    return 0;
}