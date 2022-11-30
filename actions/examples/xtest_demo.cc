
#include "xcb/xcb.h"
#include "xcb/xtest.h"
#include "xcb/xcbext.h"
#include "xcb/xcb_keysyms.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void send_str(xcb_connection_t* connection, xcb_key_symbols_t* syms, const char* str) {
    xcb_window_t none = { XCB_NONE };

    while(str[0] != 0) {
        xcb_keysym_t  ks = str[0];
        uint8_t code = *xcb_key_symbols_get_keycode(syms, ks);

        xcb_test_fake_input(connection, XCB_KEY_PRESS, code, 0, none, 0, 0, 0);
        xcb_test_fake_input(connection, XCB_KEY_RELEASE, code, 0, none, 0, 0, 0);
        // xcb_wait_for_reply(connection, xcb_test_fake_input(connection, XCB_KEY_PRESS, code, 0, none, 0, 0, 0).sequence, NULL);
        // xcb_wait_for_reply(connection, xcb_test_fake_input(connection, XCB_KEY_RELEASE, code, 0, none, 0, 0, 0).sequence, NULL);

        str++;
    }
}

int main() {
    xcb_connection_t *connection = xcb_connect(NULL, NULL);
    xcb_key_symbols_t* syms;

    xcb_test_get_version_cookie_t version_cookie = xcb_test_get_version(connection, 2, 1);

    xcb_generic_error_t* error = NULL;
    xcb_test_get_version_reply_t* version_reply = xcb_test_get_version_reply(connection, version_cookie, &error);

    if (version_reply){
        fprintf( stderr, "XTest version %u.%u\n",
        (unsigned int)version_reply->major_version,
        (unsigned int)version_reply->minor_version );
        free(version_reply);
    }
    if (error) {
        fprintf( stderr, "XTest version error: %d", (int)error->error_code );
        free(error);
    }

    syms = xcb_key_symbols_alloc(connection);

    char* buf = (char*)malloc(128);
    while (fgets(buf, 128, stdin)) {
        buf[strlen(buf)-1] = '\0';
        send_str(connection, syms, buf);
        xcb_flush(connection);
    }

    xcb_key_symbols_free(syms);
    xcb_disconnect(connection);

    exit(0);
}