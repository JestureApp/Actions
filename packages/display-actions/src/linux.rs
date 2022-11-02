use libc::{c_char, c_int, c_void, useconds_t};

type Xdo = *const c_void;
type Window = c_int;

#[link(name = "xdo")]
extern "C" {
    fn xdo_free(xdo: Xdo);
    fn xdo_new(display: *const c_char) -> Xdo;

    fn xdo_send_keysequence_window(
        xdo: Xdo,
        window: Window,
        keysequence: *const c_char,
        delay: useconds_t,
    ) -> c_int;

    fn xdo_send_keysequence_window_down(
        xdo: Xdo,
        window: Window,
        keysequence: *const c_char,
        delay: useconds_t,
    ) -> c_int;

    fn xdo_send_keysequence_window_up(
        xdo: Xdo,
        window: Window,
        keysequence: *const c_char,
        delay: useconds_t,
    ) -> c_int;
}
