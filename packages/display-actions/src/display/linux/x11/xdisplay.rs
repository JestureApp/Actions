use super::XWindow;
use crate::display::{Error, Key};
use crate::util::Cached;
use libc::{c_int, c_long, c_uint, c_ulong};
use std::cell::Cell;
use x11::xlib;

pub struct XDisplay {
    disp: *mut xlib::Display,
    root_id: Cached<c_ulong>,
}

impl XDisplay {
    pub fn new() -> Result<Self, Error> {
        let disp = unsafe { xlib::XOpenDisplay(std::ptr::null()) };

        if disp.is_null() {
            Err("Failed to connection to X11".to_string())
        } else {
            Ok(XDisplay {
                disp,
                root_id: Cached::new(),
            })
        }
    }

    /// Returns the root window of the display
    pub fn default_root_window(&self) -> Result<XWindow, Error> {
        let id = self
            .root_id
            .get_or_init(|| unsafe { xlib::XDefaultRootWindow(self.disp) });

        Ok(XWindow::new(*id, self))
    }

    pub fn send_key<E>(
        &self,
        key: &Key,
        pressed: bool,
        modifiers: c_uint,
        window: &XWindow,
        propagate: bool,
    ) -> Result<(), Error> {
        let (mask, type_) = if pressed {
            (xlib::KeyPressMask, xlib::KeyPress)
        } else {
            (xlib::KeyReleaseMask, xlib::KeyRelease)
        };

        let event: xlib::XKeyEvent = xlib::XKeyEvent {
            type_,
            serial: 0, // Set by X server
            send_event: true as c_int,
            display: self.disp,
            window: window.id(), // CHECKME: Should this be the same window
            root: 0,             // CHECKME: Should I set this?
            subwindow: 0,        // None (see X.h)
            time: xlib::CurrentTime,
            x: 0,
            y: 0,
            x_root: 0,
            y_root: 0,
            state: modifiers,
            keycode: todo!(),
            same_screen: true as c_int,
        };

        self.send_event(window, propagate, mask, event)
    }

    pub fn send_event<E>(
        &self,
        window: &XWindow,
        propagate: bool,
        mask: c_long,
        event: E,
    ) -> Result<(), Error>
    where
        E: Into<xlib::XEvent>,
    {
        let mut event = event.into();

        // WARNING: Can generate exceptions
        let ret =
            unsafe { xlib::XSendEvent(self.disp, window.id(), propagate as i32, mask, &mut event) };

        // Yes this is weird, but according to https://x.org/releases/current/doc/libX11/libX11/libX11.html#XSendEvent
        // XSendEvent returns 0 on failure, and non-zero on success
        if ret == 0 {
            Err("Failed to send event".to_string())
        } else {
            Ok(())
        }
    }
}

impl Drop for XDisplay {
    fn drop(&mut self) {
        // WARNING: Can generate exceptions
        unsafe { xlib::XCloseDisplay(self.disp) };
    }
}
