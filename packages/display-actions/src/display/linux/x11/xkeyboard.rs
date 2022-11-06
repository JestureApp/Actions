use super::{XDisplay, XWindow};
use crate::display::{Error, Key, NormalKey};
use libc::{c_int, c_long, c_uint, c_ulong};
use std::collections::HashMap;
use x11::xlib;

pub struct XKeyboard {
    keycodes: HashMap<NormalKey, c_uint>,
}

impl XKeyboard {
    pub fn new(display: &XDisplay) -> Self {
        // Get keycode range
        let mut keycode_high = 0;
        let mut keycode_low = 0;

        unsafe {
            xlib::XDisplayKeycodes(display.disp, &mut keycode_low, &mut keycode_high);
        }

        let mut keycodes = HashMap::new();

        XKeyboard { keycodes }
    }
}
