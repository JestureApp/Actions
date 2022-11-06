mod error;
pub use error::Error;

mod keys;
pub use keys::{Key, KeyStroke};

#[cfg(target_os = "linux")]
mod linux;

// Should be implemented for each platform
pub(self) trait DisplayActionsImpl: Sized {
    /// Initialize the connection to the display server
    fn init() -> Result<Self, Error>;
}

/// Provides actions to be dispatched to the display server
pub struct DisplayActions {
    #[cfg(target_os = "linux")]
    inner: linux::LinuxActions,
}

impl DisplayActions {
    pub fn new() -> Result<Self, Error> {
        #[cfg(target_os = "linux")]
        let inner = linux::LinuxActions::init()?;

        Ok(Self { inner })
    }
}
