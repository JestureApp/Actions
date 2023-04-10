#include <iostream>

#include "absl/status/status.h"
#include "actions/action.h"
#include "actions/actions.h"

using namespace actions;

absl::Status run() {
    auto actions = Actions::Create();

    if (!actions.ok()) return actions.status();

    absl::Status status = actions
                              ->Perform(action::CursorMove{.x = 0.1, .y = 0.1},
                                        action::target::Focused())
                              .get();

    if (!status.ok()) return status;

    return actions
        ->Perform(action::MouseClick::LeftClick, action::target::Focused())
        .get();
}

int main(int argc, char** argv) {
    std::cout << "Running Example" << std::endl;
    absl::Status status = run();

    if (!status.ok()) {
        std::cout << status << std::endl;
        return 1;
    }

    return 0;
}