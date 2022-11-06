use super::XWindow;
use crate::display::{Error, Key};
use crate::util::Cached;
use libc::{c_char, c_int, c_long, c_uint, c_ulong};
use std::cell::Cell;
use x11::xlib;

const XKB_SUCCESS: c_int = 0;
const XKB_BAD_LIBRARY_VERSION: c_int = 1;
const XKB_CONNECTION_REFUSED: c_int = 2;
const XKB_NONXKB_SERVER: c_int = 3;
const XKB_BAD_SERVER_VERSION: c_int = 4;

pub struct XDisplay {
    pub(super) disp: *mut xlib::Display,
    root_id: c_ulong,
}

impl XDisplay {
    /// Construct a new `XDisplay`. Returns a `XDisplay` if successful or an `Error`
    /// if there was some problem opening the display
    ///
    /// Will open a connection to the default X server, as well as obtaining some
    /// necessary information about the server.
    ///
    /// # Examples
    /// ```
    /// use display_actions::display::linux::x11::XDisplay;
    ///
    /// let disp = XDisplay::new().unwrap();
    ///
    /// let root = disp.get_root_window();
    /// ```
    pub fn new() -> Result<Self, Error> {
        let disp = {
            let mut event_ret = 0;
            let mut error_ret = 0;
            let mut reason_ret = 0;

            let disp = unsafe {
                xlib::XkbOpenDisplay(
                    std::ptr::null::<c_char>() as *mut c_char, // display_name
                    std::ptr::null::<c_int>() as *mut c_int,   // event_rtrn
                    std::ptr::null::<c_int>() as *mut c_int,   // error_rtrn
                    std::ptr::null::<c_int>() as *mut c_int,   // major_in_out
                    std::ptr::null::<c_int>() as *mut c_int,   // minor_in_out
                    &mut reason_ret,
                )
            };

            if disp.is_null() {
                return match reason_ret {
                    XKB_BAD_LIBRARY_VERSION | XKB_BAD_SERVER_VERSION => {
                        Err("Incompatible XKeyboard version".into())
                    }
                    XKB_CONNECTION_REFUSED => Err("Connection refused".into()),
                    XKB_NONXKB_SERVER => {
                        Err("The server does not support the XKEYBOARD extension".into())
                    }

                    _ => Err("XkbOpenDisplay returned an unknown reason".into()),
                };
            }

            disp
        };

        let root_id = unsafe { xlib::XDefaultRootWindow(disp) };

        Ok(XDisplay { disp, root_id })
    }

    /// Returns the root window of the display
    pub fn default_root_window(&self) -> XWindow {
        // Cheap, just need to wrap the ID
        XWindow::new(self.root_id, self)
    }

    pub fn send_key<E>(
        &self,
        key: &Key,
        pressed: bool,
        modifiers: u32,
        window: &XWindow,
        propagate: bool,
    ) -> Result<(), Error> {
        let (mask, type_) = if pressed {
            (xlib::KeyPressMask, xlib::KeyPress)
        } else {
            (xlib::KeyReleaseMask, xlib::KeyRelease)
        };

        let event: xlib::XKeyEvent = xlib::XKeyEvent {
            type_: type_,
            serial: 0,
            send_event: 0,
            display: self.disp,
            window: window.id(),
            root: self.root_id,
            subwindow: 0,
            time: 0,
            x: 0,
            y: 0,
            x_root: 0,
            y_root: 0,
            state: modifiers,
            keycode: todo!(),
            same_screen: 0,
        };

        unsafe {
            xlib::XSendEvent(
                self.disp,
                window.id(),
                propagate as c_int,
                mask,
                &event as *const xlib::XKeyEvent as *mut xlib::XEvent,
            );
        }

        Ok(())
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

        let ret =
            unsafe { xlib::XSendEvent(self.disp, window.id(), propagate as i32, mask, &mut event) };

        // Yes this is weird, but according to https://x.org/releases/current/doc/libX11/libX11/libX11.html#XSendEvent
        // XSendEvent returns 0 on failure, and non-zero on success
        if ret == 0 {
            Err("Failed to send event".into())
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_new() -> Result<(), Error> {
        let display = XDisplay::new()?;
        let root = display.default_root_window();

        Ok(())
    }
}
