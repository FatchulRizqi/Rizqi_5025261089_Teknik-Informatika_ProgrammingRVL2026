#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to custom_message__msg__Controller

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Controller {

    // This member is not documented.
    #[allow(missing_docs)]
    pub velx: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vely: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub angvel: f32,

}



impl Default for Controller {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Controller::default())
  }
}

impl rosidl_runtime_rs::Message for Controller {
  type RmwMsg = super::msg::rmw::Controller;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        velx: msg.velx,
        vely: msg.vely,
        angvel: msg.angvel,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      velx: msg.velx,
      vely: msg.vely,
      angvel: msg.angvel,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      velx: msg.velx,
      vely: msg.vely,
      angvel: msg.angvel,
    }
  }
}


