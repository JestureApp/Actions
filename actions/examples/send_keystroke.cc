
#include "xcb/xcb.h"
#include "absl/status/status.h"

#define RETURN_IF_ERROR(expr) \
  do { \
    absl::Status _status = (expr); \
    if (!_status.ok()) { \
      return _status; \
    } \
  } while (0)

absl::Status setup_display_and_screen(
    const char* display_name,
    xcb_connection_t** connection,
    xcb_screen_t** screen) 
{
    int screen_n;

    *connection = xcb_connect(display_name, &screen_n);

    if (xcb_connection_has_error(*connection)) {
        return absl::InternalError("Failed to connect to X server");
    }

    const xcb_setup_t* setup = xcb_get_setup(*connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    int screen_count = xcb_setup_roots_length(setup);
    
    if (screen_count <= screen_n) {
        std::cerr << "Screen number " << screen_n << " is out of range (0-" << screen_count << ")" << std::endl;
        return absl::InternalError("Failed to get screen");
    }

    for (int i = 0; i < screen_n; i++) {
        xcb_screen_next(&iter);
    }

    *screen = iter.data;

    return absl::OkStatus();
}

absl::Status ensure_ext(const char* ext_name, xcb_connection_t* connection) 
{
    xcb_query_extension_cookie_t cookie = xcb_query_extension(connection, strlen(ext_name), ext_name);
    xcb_query_extension_reply_t* reply = xcb_query_extension_reply(connection, cookie, NULL);

    if (!reply) {
        return absl::InternalError("Failed to query extension");
    }

    if (!reply->present) {
        return absl::InternalError("Extension not present");
    }

    free(reply);

    return absl::OkStatus();
}

absl::Status get_focused_window(xcb_connection_t* connection, xcb_window_t* focus)
{
    xcb_generic_error_t* error;

    xcb_get_input_focus_cookie_t cookie = xcb_get_input_focus(connection);
    xcb_get_input_focus_reply_t* reply = xcb_get_input_focus_reply(connection, cookie, &error);

    if (error) {
        return absl::InternalError("Failed to get focused window");
    }

    *focus = reply->focus;

    free(reply);

    return absl::OkStatus();
}

absl::Status send_keystroke(xcb_connection_t* connection, 
    xcb_window_t root,
    xcb_window_t window, 
    uint32_t keycode, 
    uint16_t modifiers) 
{
    xcb_key_press_event_t* event = (xcb_key_press_event_t*) calloc(32, 1);
    event->response_type = XCB_KEY_PRESS;
    event->detail = keycode;
    event->time = XCB_CURRENT_TIME;
    event->root = root;
    event->state = modifiers;
    event->event = window;
    event->same_screen = 1;

    xcb_send_event(connection, 0, window, XCB_EVENT_MASK_NO_EVENT, (const char*)&event);

    if (xcb_connection_has_error(connection)) {
        return absl::InternalError("Failed to send event");
    }

    xcb_flush(connection);

    return absl::OkStatus();
}

absl::Status run() {
    xcb_connection_t *connection;
    xcb_screen_t *screen;

    RETURN_IF_ERROR(setup_display_and_screen(nullptr, &connection, &screen));

    std::cout << "Screen " << screen->root << " selected" << std::endl;

    // RETURN_IF_ERROR(ensure_ext("XKEYBOARD", connection));

    // std::cout << "XKEYBOARD extension present" << std::endl;

    xcb_window_t focus;

    RETURN_IF_ERROR(get_focused_window(connection, &focus));

    std::cout << "Focused window: " << focus << std::endl;

    RETURN_IF_ERROR(send_keystroke(connection, screen->root, focus, 0x26, 0));

    xcb_disconnect(connection);

    return absl::OkStatus();
}

int main() 
{
    absl::Status status = run();

    if (!status.ok()) {
        std::cerr << status.message() << std::endl;
        return 1;
    }

    return 0;
}