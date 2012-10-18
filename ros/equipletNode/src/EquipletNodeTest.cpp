/**
 * @file EquipletNodeTest.cpp
 * @brief Node to test the EquipletNode
 * @date Created: 2012-10-17
 *
 * @author Dennis Koole
 *
 * @section LICENSE
 * License: newBSD
 *  
 * Copyright © 2012, HU University of Applied Sciences Utrecht.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "rosMast/StateMachine.h"
#include "rosMast/StateChanged.h"

/**
 * Callback that is called when a message is received
 * @param msg the message that is received
 **/
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("%s", msg->data.c_str());
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "EquipletNodeTest");
	ros::NodeHandle nodeHandle;

	/**
	 * Subscribe to the topic published by the EquipletNode
	 **/
	ros::Publisher pub = nodeHandle.advertise<rosMast::StateChanged>("equiplet_statechanged", 1);

	sleep(2);

	rosMast::StateChanged msg;	
	msg.equipletID = 1;
	msg.moduleID = 1;
	msg.state = rosMast::standby;

	pub.publish(msg);	

	ros::spin();

	return 0;
}