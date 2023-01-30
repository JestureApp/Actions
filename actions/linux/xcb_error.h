#ifndef __H_LINUX_XCB_ERROR__
#define __H_LINUX_XCB_ERROR__

#include "absl/status/status.h"

namespace actions {
/**
 * Converts an xcb error code into a status
 *
 * @param code the code to convert.
 * @return the status.
 */
absl::Status XcbError(int code) noexcept;
}  // namespace actions

#endif  // __H_LINUX_XCB_ERROR__