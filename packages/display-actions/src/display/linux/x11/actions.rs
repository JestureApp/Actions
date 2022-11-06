use super::XDisplay;
use crate::display::{DisplayActionsImpl, Error};

pub struct X11Actions {
    display: XDisplay,
}

impl DisplayActionsImpl for X11Actions {
    fn init() -> Result<Self, Error> {
        Ok(Self {
            display: XDisplay::new()?,
        })
    }
}
