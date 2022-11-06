// TODO: docs
pub enum ModKey {
    // TODO: add left and right variants?
    Shift,
    Ctrl,
    Alt,
    CapsLock,
}

// TODO: docs
pub enum NormalKey {
    // System Keys
    PrtSc,
    Escape,

    // Editing or Navigational Keys
    Tab,
    Enter,
    Backspace,
    Insert,
    Delete,
    Home,
    End,
    PageUp,
    PageDown,
    UpArrow,
    RightArrow,
    LeftArrow,
    DownArrow,

    // Function Keys
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,

    // Multimedia Keys
    // TODO: Skipped some keys
    // VolumeMute,
    // VolumeUp,
    // VolumeDown,
    // MediaNext,
    // MediaPrevious,
    // MediaStop,
    // MediaPausePlay,

    // Character Keys
    Char(char),
}

// TODO: docs
pub enum Key {
    Mod(ModKey),
    Normal(NormalKey),
}

pub struct KeyStroke {}
