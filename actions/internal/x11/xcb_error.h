#ifndef ACTIONS_INTERNAL_X11_XCB_ERROR_H
#define ACTIONS_INTERNAL_X11_XCB_ERROR_H

#include <xcb/xcb.h>

#include "absl/status/status.h"

namespace actions::internal::x11 {
/// @brief Converts an xcb status code to an `absl::Status`.
/// @param code The xcb status code.
/// @return The associated status.
absl::Status XcbStatus(int code) noexcept;

/// @brief Converts an `xcb_generic_error_t` to an `absl::Status`.
/// @param conn The connection to the X server (borrow). Used to determine which
/// extension if any produced the error.
/// @param error The error to convert.
/// @return The associated status.
absl::Status XcbErrorToStatus(xcb_connection_t *conn,
                              xcb_generic_error_t *error) noexcept;
}  // namespace actions::internal::x11

#endif  // ACTIONS_INTERNAL_X11_XCB_ERROR_H