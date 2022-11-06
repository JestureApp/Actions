mod x11;
use self::x11::X11Actions;

// Allows for implementation on other display servers later
pub type LinuxActions = X11Actions;
