// Copyright (c) 2017 Franka Emika GmbH
// Use of this source code is governed by the Apache-2.0 license, see LICENSE
#pragma once

#include <memory>
#include <string>

#include <controller_interface/multi_interface_controller.h>
#include <franka_hw/franka_cartesian_command_interface.h>
#include <franka_hw/franka_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <ros/node_handle.h>
#include <ros/time.h>

#include "custom_panda_controllers/CartesianVelocityTarget.h"


namespace custom_panda_controllers {

class CartesianVelocityCustomController : public controller_interface::MultiInterfaceController<
                                               franka_hw::FrankaVelocityCartesianInterface,
                                               franka_hw::FrankaStateInterface> {
 public:
  bool init(hardware_interface::RobotHW* robot_hardware, ros::NodeHandle& node_handle) override;
  void update(const ros::Time&, const ros::Duration& period) override;
  void starting(const ros::Time&) override;
  void stopping(const ros::Time&) override;

 private:
  franka_hw::FrankaVelocityCartesianInterface* velocity_cartesian_interface_;
  std::unique_ptr<franka_hw::FrankaCartesianVelocityHandle> velocity_cartesian_handle_;
  ros::Duration elapsed_time_;
  std::array<double, 6> velocity_old = {0, 0, 0, 0, 0, 0};
  std::array<double, 6> velocity_out = {0, 0, 0, 0, 0, 0};
  std::array<double, 6> velocity_goal = {0, 0, 0, 0, 0, 0};
  std::array<double, 6> max_acceleration;
  std::array<double, 6> max_velocity;
  std::array<double, 6> max_jerk;
  std::array<double, 6> last_acc = {0, 0, 0, 0, 0, 0};



  ros::Subscriber sub_vel;
  
  // void velocity_callback(stud_hee::MyVelocity);
  void velocity_callback(custom_panda_controllers::CartesianVelocityTarget);

};

}  // namespace custom_panda_controllers
