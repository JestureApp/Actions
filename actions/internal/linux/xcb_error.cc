#include "actions/internal/linux/xcb_error.h"

#include <xcb/xcb.h>

#include "absl/status/status.h"

namespace actions::internal::linux {
absl::Status XcbStatus(int code) noexcept {
    switch (code) {
        case 0:
            return absl::OkStatus();

        case XCB_CONN_ERROR:
            return absl::InternalError(
                "xcb connection errors because of socket, pipe "
                "and other stream errors. (code: XCB_CONN_ERROR)");

        case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
            return absl::InternalError(
                "xcb connection shutdown because of extension not supported. "
                "(code: XCB_CONN_CLOSED_EXT_NOTSUPPORTED)");

        case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
            return absl::ResourceExhaustedError(
                "Insufficient memory. (code: "
                "XCB_CONN_CLOSED_MEM_INSUFFICIENT)");

        case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
            return absl::InternalError(
                "Connection closed, exceeding request length that server "
                "accepts. (code: XCB_CONN_CLOSED_REQ_LEN_EXCEED)");

        case XCB_CONN_CLOSED_PARSE_ERR:
            return absl::InternalError(
                "Connection closed, error during parsing display string. "
                "(code: XCB_CONN_CLOSED_PARSE_ERR)");

        case XCB_CONN_CLOSED_INVALID_SCREEN:
            return absl::InternalError(
                "Connection closed because the server does not have a screen "
                "matching the display. (code: XCB_CONN_CLOSED_INVALID_SCREEN)");

        case XCB_CONN_CLOSED_FDPASSING_FAILED:
            return absl::InternalError(
                "Connection closed because some FD passing operation failed. "
                "(code: XCB_CONN_CLOSED_FDPASSING_FAILED)");

        default:
            return absl::UnknownError(
                "Unrecognized Xcb error. (code: " + std::to_string(code) + ")");
    }
}

absl::Status XcbErrorToStatus(xcb_connection_t *conn,
                              xcb_generic_error_t *error) noexcept {
    // TODO: Determine extension.
    return absl::UnknownError("XCB error with code " +
                              std::to_string(error->major_code) + "." +
                              std::to_string(error->minor_code));
}
}  // namespace actions::internal::linux