#ifndef __H_LINUX_XCB_CONNECTION__
#define __H_LINUX_XCB_CONNECTION__

#include <xcb/xcb.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "actions/connection.h"
#include "actions/linux/xcb_promise.h"
#include "actions/promise.h"

namespace actions {
/**
 * A connection to a X server, this object manages the lifecycle of the
 * connection and acts as a middle man to the xcb api.
 */
class XcbConnection : public Connection {
   public:
    /**
     * Opens a connection to the default X server.
     *
     * @return A `absl::Status` in the case of a failure or an `XcbConnection`
     * in the case of a success.
     */
    static absl::StatusOr<std::unique_ptr<XcbConnection>> Open();

    virtual ~XcbConnection();

    XcbConnection(XcbConnection& other) = delete;
    XcbConnection& operator=(XcbConnection& other) = delete;

    XcbConnection(XcbConnection&& other) noexcept;
    XcbConnection& operator=(XcbConnection&& other) noexcept;

    std::unique_ptr<Promise<absl::Status>> SendKeystroke(
        Keystroke& keystroke) noexcept override;

   protected:
    /// Not apart of public interface. DO NOT USE outside of testing.
    XcbConnection(xcb_connection_t* conn);

   private:
    xcb_connection_t* conn;
};
}  // namespace actions
#endif