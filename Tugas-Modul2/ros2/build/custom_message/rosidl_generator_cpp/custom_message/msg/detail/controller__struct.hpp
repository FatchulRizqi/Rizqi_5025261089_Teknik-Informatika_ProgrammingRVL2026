// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_message:msg/Controller.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__STRUCT_HPP_
#define CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_message__msg__Controller __attribute__((deprecated))
#else
# define DEPRECATED__custom_message__msg__Controller __declspec(deprecated)
#endif

namespace custom_message
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Controller_
{
  using Type = Controller_<ContainerAllocator>;

  explicit Controller_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velx = 0.0f;
      this->vely = 0.0f;
      this->angvel = 0.0f;
    }
  }

  explicit Controller_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velx = 0.0f;
      this->vely = 0.0f;
      this->angvel = 0.0f;
    }
  }

  // field types and members
  using _velx_type =
    float;
  _velx_type velx;
  using _vely_type =
    float;
  _vely_type vely;
  using _angvel_type =
    float;
  _angvel_type angvel;

  // setters for named parameter idiom
  Type & set__velx(
    const float & _arg)
  {
    this->velx = _arg;
    return *this;
  }
  Type & set__vely(
    const float & _arg)
  {
    this->vely = _arg;
    return *this;
  }
  Type & set__angvel(
    const float & _arg)
  {
    this->angvel = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_message::msg::Controller_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_message::msg::Controller_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_message::msg::Controller_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_message::msg::Controller_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_message::msg::Controller_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_message::msg::Controller_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_message::msg::Controller_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_message::msg::Controller_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_message::msg::Controller_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_message::msg::Controller_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_message__msg__Controller
    std::shared_ptr<custom_message::msg::Controller_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_message__msg__Controller
    std::shared_ptr<custom_message::msg::Controller_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Controller_ & other) const
  {
    if (this->velx != other.velx) {
      return false;
    }
    if (this->vely != other.vely) {
      return false;
    }
    if (this->angvel != other.angvel) {
      return false;
    }
    return true;
  }
  bool operator!=(const Controller_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Controller_

// alias to use template instance with default allocator
using Controller =
  custom_message::msg::Controller_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_message

#endif  // CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__STRUCT_HPP_
