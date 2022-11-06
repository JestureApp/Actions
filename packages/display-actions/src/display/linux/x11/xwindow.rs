use super::XDisplay;
use libc::c_ulong;
use x11::xlib;

pub struct XWindow<'d> {
    id: c_ulong,
    display: &'d XDisplay,
}

impl<'d> XWindow<'d> {
    pub fn new(id: c_ulong, display: &'d XDisplay) -> Self {
        Self { id, display }
    }

    pub fn id(&self) -> c_ulong {
        self.id
    }
}
