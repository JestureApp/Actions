#include <iostream>

#include "absl/status/status.h"
#include "actions/action.h"
#include "actions/actions.h"

using namespace actions;

absl::Status run() {
    auto keysequence = action::ParseKeystroke("shift");

    if (!keysequence.ok()) return keysequence.status();

    auto actions = Actions::Create();

    if (!actions.ok()) return actions.status();

    absl::Status status = actions
                              ->Perform(action::KeysPress{keysequence.value()},
                                        action::target::Focused())
                              .get();

    if (!status.ok()) return status;

    status =
        actions
            ->Perform(action::MousePress::LeftPress, action::target::Focused())
            .get();

    if (!status.ok()) return status;

    status = actions
                 ->Perform(action::CursorMove{.x = 0.1, .y = 0},
                           action::target::Focused())
                 .get();

    if (!status.ok()) return status;

    status = actions
                 ->Perform(action::KeysRelease{keysequence.value()},
                           action::target::Focused())
                 .get();

    if (!status.ok()) return status;

    return actions
        ->Perform(action::MouseRelease::LeftRelease, action::target::Focused())
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