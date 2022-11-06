use libc::c_int;
use std::{
    error::Error,
    fmt::{self, Display},
};

// TODO: docs
#[derive(Debug)]
pub enum X11ProtocolError {
    BadAccess,
    BadAlloc,
    BadAtom,
    BadColor,
    BadCursor,
    BadDrawable,
    BadFont,
    BadGC,
    BadIDChoice,
    BadImplementation,
    BadLength,
    BadMatch,
    BadName,
    BadPixmap,
    BadValue,
    BadWindow,

    Unknown(c_int),
}

impl X11ProtocolError {
    const BAD_VALUE: c_int = 2;
    const BAD_WINDOW: c_int = 3;
    const BAD_PIXMAP: c_int = 4;
    const BAD_ATOM: c_int = 5;
    const BAD_CURSOR: c_int = 6;
    const BAD_FONT: c_int = 7;
    const BAD_MATCH: c_int = 8;
    const BAD_DRAWABLE: c_int = 9;
    const BAD_ACCESS: c_int = 10;
    const BAD_ALLOC: c_int = 11;
    const BAD_COLOR: c_int = 12;
    const BAD_GC: c_int = 13;
    const BAD_ID_CHOICE: c_int = 14;
    const BAD_NAME: c_int = 15;
    const BAD_LENGTH: c_int = 16;
    const BAD_IMPLEMENTATION: c_int = 17;

    pub fn from_code(code: c_int) -> X11ProtocolError {
        match code {
            Self::BAD_VALUE => Self::BadValue,
            Self::BAD_WINDOW => Self::BadWindow,
            Self::BAD_PIXMAP => Self::BadPixmap,
            Self::BAD_ATOM => Self::BadAtom,
            Self::BAD_CURSOR => Self::BadCursor,
            Self::BAD_FONT => Self::BadFont,
            Self::BAD_MATCH => Self::BadMatch,
            Self::BAD_DRAWABLE => Self::BadDrawable,
            Self::BAD_ACCESS => Self::BadAccess,
            Self::BAD_ALLOC => Self::BadAlloc,
            Self::BAD_COLOR => Self::BadColor,
            Self::BAD_GC => Self::BadGC,
            Self::BAD_ID_CHOICE => Self::BadIDChoice,
            Self::BAD_NAME => Self::BadName,
            Self::BAD_LENGTH => Self::BadLength,
            Self::BAD_IMPLEMENTATION => Self::BadImplementation,

            _ => Self::Unknown(code),
        }
    }

    pub fn check_status(status: c_int) -> Result<(), X11ProtocolError> {
        if status == 0 {
            Ok(())
        } else {
            Err(Self::from_code(status))
        }
    }
}

impl Display for X11ProtocolError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::BadAccess => write!(f, "X11 BadAccess error"),
            Self::BadAlloc => write!(f, "X11 BadAlloc error"),
            Self::BadAtom => write!(f, "X11 BadAtom error"),
            Self::BadColor => write!(f, "X11 BadColor error"),
            Self::BadCursor => write!(f, "X11 BadCursor error"),
            Self::BadDrawable => write!(f, "X11 BadDrawable error"),
            Self::BadFont => write!(f, "X11 BadFont error"),
            Self::BadGC => write!(f, "X11 BadGC error"),
            Self::BadIDChoice => write!(f, "X11 BadIDChoice error"),
            Self::BadImplementation => write!(f, "X11 BadImplementation error"),
            Self::BadLength => write!(f, "X11 BadLength error"),
            Self::BadMatch => write!(f, "X11 BadMatch error"),
            Self::BadName => write!(f, "X11 BadName error"),
            Self::BadPixmap => write!(f, "X11 BadPixmap error"),
            Self::BadValue => write!(f, "X11 BadValue error"),
            Self::BadWindow => write!(f, "X11 BadWindow error"),

            Self::Unknown(code) => write!(f, "Unknown X11 error code: {}", code),
        }
    }
}

impl Error for X11ProtocolError {}

pub enum XkbError {}
