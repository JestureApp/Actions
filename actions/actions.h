#ifndef __H_ACTIONS__
#define __H_ACTIONS__

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/utility/utility.h"
#include "actions/connection.h"
#include "actions/keystroke.h"
#include "map"

namespace actions {
using Action = absl::variant<Keystrokes>;

template <class ActionId>
class Actions {
   public:
    static absl::StatusOr<std::shared_ptr<Actions<ActionId>>> Create() {
        absl::StatusOr<std::unique_ptr<Connection>> conn = Connection::Open();

        if (!conn.ok()) {
            return conn.status();
        }

        Actions* actions = new Actions();
        actions->conn = std::move(conn).value();

        return std::shared_ptr<Actions>(actions);
    };

    ~Actions(){};

    void Add(ActionId id, Action action) { actions[id] = action; }

    absl::Status Perform(ActionId id) {
        if (actions.find(id) == actions.end()) {
            return absl::NotFoundError("Action not found");
        }

        Action& action = actions[id];

        if (absl::holds_alternative<Keystrokes>(action)) {
            return conn->SendKeystroke(absl::get<Keystrokes>(action));
        }

        return absl::UnimplementedError("Not implemented");
    }

   private:
    Actions(){};

    std::unique_ptr<Connection> conn;
    std::map<ActionId, Action> actions;
};

}  // namespace actions

#endif  // __H_ACTIONS__