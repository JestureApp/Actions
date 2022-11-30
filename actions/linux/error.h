#ifndef __H_LINUX_ERROR__
#define __H_LINUX_ERROR__

#include "absl/status/status.h"

namespace actions {
absl::Status XcbErrorToStatus(int error);
}

#endif  // __H_LINUX_ERROR__