// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_message:msg/Controller.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__BUILDER_HPP_
#define CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_message/msg/detail/controller__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_message
{

namespace msg
{

namespace builder
{

class Init_Controller_angvel
{
public:
  explicit Init_Controller_angvel(::custom_message::msg::Controller & msg)
  : msg_(msg)
  {}
  ::custom_message::msg::Controller angvel(::custom_message::msg::Controller::_angvel_type arg)
  {
    msg_.angvel = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_message::msg::Controller msg_;
};

class Init_Controller_vely
{
public:
  explicit Init_Controller_vely(::custom_message::msg::Controller & msg)
  : msg_(msg)
  {}
  Init_Controller_angvel vely(::custom_message::msg::Controller::_vely_type arg)
  {
    msg_.vely = std::move(arg);
    return Init_Controller_angvel(msg_);
  }

private:
  ::custom_message::msg::Controller msg_;
};

class Init_Controller_velx
{
public:
  Init_Controller_velx()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Controller_vely velx(::custom_message::msg::Controller::_velx_type arg)
  {
    msg_.velx = std::move(arg);
    return Init_Controller_vely(msg_);
  }

private:
  ::custom_message::msg::Controller msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_message::msg::Controller>()
{
  return custom_message::msg::builder::Init_Controller_velx();
}

}  // namespace custom_message

#endif  // CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__BUILDER_HPP_
