
#include "xcb/xcb.h"
#include "xcb/xtest.h"
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

        // xcb_test_fake_input(connection, XCB_KEY_PRESS, code, 0, none, 0, 0, 0);
        // xcb_test_fake_input(connection, XCB_KEY_RELEASE, code, 0, none, 0, 0, 0);

        xcb_key_press_event_t press_event;
        memset(&press_event, 0, sizeof(press_event));
        press_event.response_type = XCB_KEY_PRESS;
        press_event.time = XCB_CURRENT_TIME;
        press_event.root = none;
        press_event.event = none;
        press_event.state = 0;
        press_event.same_screen = 1;

        press_event.detail = code;

        xcb_send_event(connection, 1, none, XCB_EVENT_MASK_KEY_PRESS, (const char*)&press_event);

        xcb_key_release_event_t release_event;
        memset(&release_event, 0, sizeof(release_event));
        release_event.response_type = XCB_KEY_RELEASE;
        release_event.time = XCB_CURRENT_TIME;
        release_event.root = none;
        release_event.event = none;
        release_event.state = 0;
        release_event.same_screen = 1;

        release_event.detail = code;

        xcb_send_event(connection, 1, none, XCB_EVENT_MASK_KEY_RELEASE, (const char*)&release_event);

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