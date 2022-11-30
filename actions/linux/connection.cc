#include "actions/linux/connection.h"

#include "absl/status/statusor.h"
#include "actions/keystroke.h"
#include "actions/linux/error.h"
#include "xcb/xcb.h"
#include "xcb/xcb_keysyms.h"
#include "xcb/xtest.h"

namespace actions {
absl::StatusOr<std::unique_ptr<Connection>> Connection::Open() {
  // Setup connection
  absl::Status status = absl::OkStatus();
  int screen_num;
  xcb_connection_t *conn = xcb_connect(NULL, &screen_num);

  if (conn == NULL) {
    return absl::UnavailableError("Failed to open connection to X server");
  }

  status.Update(actions::XcbErrorToStatus(xcb_connection_has_error(conn)));

  if (!status.ok()) {
    xcb_disconnect(conn);
    return status;
  }

  // Get primary screen
  const xcb_setup_t *setup = xcb_get_setup(conn);
  xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(setup);

  if (xcb_setup_roots_length(setup) <= screen_num) {
    xcb_disconnect(conn);
    return absl::OutOfRangeError("Invalid screen number");
  }

  for (int i = 0; i < screen_num; i++) {
    xcb_screen_next(&screen_iter);
  }

  xcb_screen_t *screen = screen_iter.data;

  // Ensure necessary extensions are present
  const xcb_query_extension_reply_t *xtest_data =
      xcb_get_extension_data(conn, &xcb_test_id);

  status.Update(actions::XcbErrorToStatus(xcb_connection_has_error(conn)));

  if (!status.ok()) {
    xcb_disconnect(conn);
    return status;
  }

  if (!xtest_data->present) {
    xcb_disconnect(conn);
    return absl::UnavailableError("XTest extension not present");
  }

  // Get key symbols
  xcb_key_symbols_t *key_symbols = xcb_key_symbols_alloc(conn);

  return std::unique_ptr<Connection>(new Connection(conn, screen, key_symbols));
}

absl::Status Connection::SendKeystroke(Keystrokes &keystrokes) {
  // if (key_symbols == NULL) {
  //     key_symbols = xcb_key_symbols_alloc(conn);
  // }

  // while(str[0] != 0) {
  //     xcb_keysym_t  ks = str[0];
  //     uint8_t code = *xcb_key_symbols_get_keycode(key_symbols, ks);

  //     xcb_test_fake_input(conn, XCB_KEY_PRESS, code, 0, screen->root, 0, 0,
  //     0); xcb_test_fake_input(conn, XCB_KEY_RELEASE, code, 0, screen->root,
  //     0, 0, 0);

  //     str++;
  // }

  // return Flush();

  std::vector<xcb_void_cookie_t> cookies;

  for (Keystroke keystroke : keystrokes) {
    uint8_t code = *xcb_key_symbols_get_keycode(key_symbols, keystroke.key);

    cookies.push_back(xcb_test_fake_input_checked(conn, XCB_KEY_PRESS, code, 0,
                                                  screen->root, 0, 0, 0));
    cookies.push_back(xcb_test_fake_input_checked(conn, XCB_KEY_RELEASE, code,
                                                  0, screen->root, 0, 0, 0));
  }

  for (xcb_void_cookie_t cookie : cookies) {
    xcb_generic_error_t *error = xcb_request_check(conn, cookie);

    if (error != NULL) {
      return absl::InternalError("Failed to send keystroke");
    }
  }

  return absl::OkStatus();
}

absl::Status Connection::Flush() {
  xcb_flush(conn);

  return actions::XcbErrorToStatus(xcb_connection_has_error(conn));
}

Connection::~Connection() {
  xcb_key_symbols_free(key_symbols);
  xcb_disconnect(conn);
}

Connection::Connection(xcb_connection_t *conn, xcb_screen_t *screen,
                       xcb_key_symbols_t *key_symbols)
    : conn(conn), screen(screen), key_symbols(key_symbols) {}
}  // namespace actions
