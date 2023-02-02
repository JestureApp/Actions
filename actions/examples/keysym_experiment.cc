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

    xcb_get_modifier_mapping_cookie_t cookie = xcb_get_modifier_mapping(conn);
    xcb_flush(conn);

    xcb_generic_error_t* error = nullptr;

    auto reply = xcb_get_modifier_mapping_reply(conn, cookie, &error);

    if (error) return 1;

    uint8_t keycodes_per_mod = reply->keycodes_per_modifier;
    int length = xcb_get_modifier_mapping_keycodes_length(reply);
    xcb_keycode_t* keycodes = xcb_get_modifier_mapping_keycodes(reply);

    std::cout << "keycodes per modifier: " << (int)keycodes_per_mod
              << " length: " << length << std::endl;

    uint8_t shift = find_modifier_keycode(keycodes_per_mod, length, keycodes,
                                          XCB_MAP_INDEX_SHIFT);

    uint8_t ctrl = find_modifier_keycode(keycodes_per_mod, length, keycodes,
                                         XCB_MAP_INDEX_CONTROL);

    uint8_t lock = find_modifier_keycode(keycodes_per_mod, length, keycodes,
                                         XCB_MAP_INDEX_LOCK);

    uint8_t meta1 = find_modifier_keycode(keycodes_per_mod, length, keycodes,
                                          XCB_MAP_INDEX_1);

    uint8_t meta2 = find_modifier_keycode(keycodes_per_mod, length, keycodes,
                                          XCB_MAP_INDEX_2);

    uint8_t meta3 = find_modifier_keycode(keycodes_per_mod, length, keycodes,
                                          XCB_MAP_INDEX_3);

    uint8_t super = find_modifier_keycode(keycodes_per_mod, length, keycodes,
                                          XCB_MAP_INDEX_4);

    // uint8_t meta5 = find_modifier_keycode(keycodes_per_mod, length, keycodes,
    //                                       XCB_MAP_INDEX_5);

    std::cout << "Shift: " << (int)shift << std::endl;
    std::cout << "Ctrl: " << (int)ctrl << std::endl;
    std::cout << "Lock: " << (int)lock << std::endl;
    std::cout << "Meta1: " << (int)meta1 << std::endl;
    std::cout << "Meta2: " << (int)meta2 << std::endl;
    std::cout << "Meta3: " << (int)meta3 << std::endl;
    std::cout << "super: " << (int)super << std::endl;

    xcb_key_symbols_t* key_symbols = xcb_key_symbols_alloc(conn);

    xcb_keycode_t code_a = xcb_key_symbols_get_keycode(key_symbols, 'a')[0];
    xcb_keycode_t code_d = xcb_key_symbols_get_keycode(key_symbols, 'd')[0];
    xcb_keycode_t code_n = xcb_key_symbols_get_keycode(key_symbols, 'n')[0];
    xcb_keycode_t code_1 = xcb_key_symbols_get_keycode(key_symbols, '1')[0];

    std::cout << "a: " << (int)code_a << std::endl;
    std::cout << "d: " << (int)code_d << std::endl;
    std::cout << "1: " << (int)code_1 << std::endl;
    std::cout << "n: " << (int)code_n << std::endl;

    std::vector<xcb_void_cookie_t> cookies;

    sleep(3);

    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_PRESS, ctrl, 0,
    //                                       screen->root, 0, 0, 0));
    cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_PRESS, super, 0,
                                          screen->root, 0, 0, 0));
    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_PRESS, meta1, 0,
    //                                       screen->root, 0, 0, 0));
    cookies.push_back(
        xcb_test_fake_input(conn, XCB_KEY_PRESS, 36, 0, screen->root, 0, 0, 0));

    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_RELEASE, ctrl, 0,
    //                                       screen->root, 0, 0, 0));
    cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_RELEASE, super, 0,
                                          screen->root, 0, 0, 0));
    // cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_RELEASE, meta1, 0,
    //                                       screen->root, 0, 0, 0));
    cookies.push_back(xcb_test_fake_input(conn, XCB_KEY_RELEASE, 36, 0,
                                          screen->root, 0, 0, 0));

    xcb_flush(conn);

    for (xcb_void_cookie_t cookie : cookies) {
        xcb_generic_error_t* error = xcb_request_check(conn, cookie);

        if (error != NULL) {
            return 1;
        }
    }

    free(reply);

    xcb_disconnect(conn);

    return 0;
}