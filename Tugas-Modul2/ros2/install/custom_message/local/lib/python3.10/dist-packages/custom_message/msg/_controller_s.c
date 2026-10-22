// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from custom_message:msg/Controller.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "custom_message/msg/detail/controller__struct.h"
#include "custom_message/msg/detail/controller__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool custom_message__msg__controller__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[42];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("custom_message.msg._controller.Controller", full_classname_dest, 41) == 0);
  }
  custom_message__msg__Controller * ros_message = _ros_message;
  {  // velx
    PyObject * field = PyObject_GetAttrString(_pymsg, "velx");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->velx = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // vely
    PyObject * field = PyObject_GetAttrString(_pymsg, "vely");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->vely = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // angvel
    PyObject * field = PyObject_GetAttrString(_pymsg, "angvel");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->angvel = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * custom_message__msg__controller__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Controller */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("custom_message.msg._controller");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Controller");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  custom_message__msg__Controller * ros_message = (custom_message__msg__Controller *)raw_ros_message;
  {  // velx
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->velx);
    {
      int rc = PyObject_SetAttrString(_pymessage, "velx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vely
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->vely);
    {
      int rc = PyObject_SetAttrString(_pymessage, "vely", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // angvel
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->angvel);
    {
      int rc = PyObject_SetAttrString(_pymessage, "angvel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
