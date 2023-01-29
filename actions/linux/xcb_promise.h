#ifndef __H_LINUX_XCB_PROMISE__
#define __H_LINUX_XCB_PROMISE__

#include <xcb/xcb.h>
#include <xcb/xcbext.h>

#include <list>

#include "absl/status/status.h"
#include "actions/promise.h"

namespace actions {
class XcbPromise : public Promise<absl::Status> {
   public:
    XcbPromise(xcb_connection_t *conn, std::list<unsigned int> &&seqnums);

    XcbPromise(XcbPromise &&) noexcept;
    XcbPromise &operator=(XcbPromise &&) noexcept;

    bool Poll() noexcept override;

   private:
    void handle_error(xcb_generic_error_t *_error);

    xcb_connection_t *conn;
    xcb_generic_error_t *error = nullptr;
    std::list<unsigned int> seqnums;
};
}  // namespace actions

#endif  // __H_LINUX_XCB_PROMISE