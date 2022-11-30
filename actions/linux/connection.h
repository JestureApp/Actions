#ifndef __H_LINUX_CONNECTION__
#define __H_LINUX_CONNECTION__

#include "absl/status/statusor.h"
#include "actions/connection_base.h"
#include "actions/keystroke.h"
#include "xcb/xcb.h"
#include "xcb/xcb_keysyms.h"

namespace actions {
class Connection : public ConnectionBase {
 public:
  /**
   * @brief Open a connection to the X server
   * @return A valid connection to the server or an error status
   */
  static absl::StatusOr<std::unique_ptr<Connection>> Open();

  absl::Status SendKeystroke(Keystrokes &keystroke) override;

  ~Connection();

 private:
  absl::Status Flush();

  Connection(xcb_connection_t *conn, xcb_screen_t *screen,
             xcb_key_symbols_t *symbols);

  xcb_connection_t *conn;
  xcb_screen_t *screen;

  xcb_key_symbols_t *key_symbols;
};
}  // namespace actions

#endif  // __H_LINUX_CONNECTION__