#include "actions/linux/error.h"

#include "absl/status/status.h"
#include "xcb/xcb.h"

namespace actions {
absl::Status XcbErrorToStatus(int error) {
    switch (error) {
        case 0:
            return absl::OkStatus();

        case XCB_CONN_ERROR:
            return absl::InternalError("XCB_CONN_ERROR");

        case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
            return absl::InternalError("XCB_CONN_CLOSED_EXT_NOTSUPPORTED");

        case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
            return absl::InternalError("XCB_CONN_CLOSED_MEM_INSUFFICIENT");

        case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
            return absl::InternalError("XCB_CONN_CLOSED_REQ_LEN_EXCEED");

        case XCB_CONN_CLOSED_PARSE_ERR:
            return absl::InternalError("XCB_CONN_CLOSED_PARSE_ERR");

        case XCB_CONN_CLOSED_INVALID_SCREEN:
            return absl::InternalError("XCB_CONN_CLOSED_INVALID_SCREEN");

        case XCB_CONN_CLOSED_FDPASSING_FAILED:
            return absl::InternalError("XCB_CONN_CLOSED_FDPASSING_FAILED");

        default:
            break;
    }

    return absl::UnknownError("Unknown XCB error: " + std::to_string(error));
}
}  // namespace actions
