// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_message:msg/Controller.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__STRUCT_H_
#define CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Controller in the package custom_message.
typedef struct custom_message__msg__Controller
{
  float velx;
  float vely;
  float angvel;
} custom_message__msg__Controller;

// Struct for a sequence of custom_message__msg__Controller.
typedef struct custom_message__msg__Controller__Sequence
{
  custom_message__msg__Controller * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_message__msg__Controller__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_MESSAGE__MSG__DETAIL__CONTROLLER__STRUCT_H_
