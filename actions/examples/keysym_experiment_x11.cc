#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <assert.h>
#include <unistd.h>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xcb_util.h>
#include <xcb/xtest.h>

#include <iostream>
#include <vector>

xcb_keycode_t find_modifier_keycode(uint8_t keycodes_per_mod, int length,
                                    xcb_keycode_t* keycodes, int index) {
    assert(length > (index + 1) * keycodes_per_mod);
    for (int i = 0; i < keycodes_per_mod; i++) {
        xcb_keycode_t code = keycodes[index * keycodes_per_mod + 1];

        if (code) return code;
    }

    return 0;
}

int main() {
    int screen_num;
    xcb_connection_t* conn = xcb_connect(nullptr, &screen_num);

    const xcb_setup_t* setup = xcb_get_setup(conn);
    xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(setup);

    if (xcb_setup_roots_length(setup) <= screen_num) {
        xcb_disconnect(conn);
        return 1;
    }

    for (int i = 0; i < screen_num; i++) {
        xcb_screen_next(&screen_iter);
    }

    xcb_screen_t* screen = screen_iter.data;

    xcb_key_symbols_t* key_symbols = xcb_key_symbols_alloc(conn);
    KeySym super_sym = XStringToKeysym("Super_R");
    KeySym enter_sym = XStringToKeysym("Return");

    xcb_keycode_t code_super =
        xcb_key_symbols_get_keycode(key_symbols, super_sym)[0];
    xcb_keycode_t code_enter =
        xcb_key_symbols_get_keycode(key_symbols, enter_sym)[0];

    std::cout << "super: " << (int)code_super << std::endl;
    std::cout << "enter: " << (int)code_enter << std::endl;

    std::vector<xcb_void_cookie_t> cookies;
    // sleep(3);

    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_PRESS, ctrl, 0,
    //                                       screen->root, 0, 0, 0));
    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_PRESS, super, 0,
    //                                       screen->root, 0, 0, 0));
    // // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_PRESS, meta1, 0,
    // //                                       screen->root, 0, 0, 0));
    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_PRESS, 0x8d, 0,
    //                                       screen->root, 0, 0, 0));

    // // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_RELEASE, ctrl, 0,
    // //                                       screen->root, 0, 0, 0));
    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_RELEASE, super, 0,
    //                                       screen->root, 0, 0, 0));
    // // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_RELEASE, meta1, 0,
    // //                                       screen->root, 0, 0, 0));
    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_RELEASE, 0x8d, 0,
    //                                       screen->root, 0, 0, 0));

    xcb_flush(conn);

    for (xcb_void_cookie_t cookie : cookies) {
        xcb_generic_error_t* error = xcb_request_check(conn, cookie);

        if (error != NULL) {
            return 1;
        }
    }

    xcb_disconnect(conn);

    return 0;
}