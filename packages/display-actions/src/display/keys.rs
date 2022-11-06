// TODO: docs
pub enum Key {
    // List of keys found from https://www.autohotkey.com/docs/KeyList.htm

    // General
    CapsLock,
    Space,
    Tab,
    Enter,
    Escape,
    Backspace,

    // Cursor Control
    ScrollLock,
    Delete,
    Insert,
    Home,
    End,
    PageUp,
    PageDown,
    UpArrow,
    DownArrow,
    LeftArrow,
    RightArrow,

    // Number Pad
    // TODO

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
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,

    // Modifier Keys
    // TODO: add left and right variants?
    Alt,
    Shift,
    Control,
    Meta,

    // Multimedia Keys
    // TODO: Skipped some keys
    VolumeMute,
    VolumeUp,
    VolumeDown,
    MediaNext,
    MediaPrevious,
    MediaStop,
    MediaPausePlay,

    // Other
    // TODO

    // Characters
    Layout(char),
}

pub type KeyStroke = [Key];
