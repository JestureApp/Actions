#include <iostream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/status/status.h"
#include "actions/action.h"
#include "actions/actions.h"

ABSL_FLAG(std::string, keystroke, "shift+a", "The keystroke to send");

using namespace actions;

absl::Status run() {
    auto actions = Actions::Create();

    if (!actions.ok()) return actions.status();

    auto keysequence = action::ParseKeystroke(FLAGS_keystroke.CurrentValue());

    if (!keysequence.ok()) return keysequence.status();

    return actions
        ->Perform(action::Keystroke{keysequence.value()},
                  action::target::Focused())
        .get();
}

int main(int argc, char** argv) {
    absl::ParseCommandLine(argc, argv);

    std::cout << "Running Example" << std::endl;
    absl::Status status = run();

    if (!status.ok()) {
        std::cout << status << std::endl;
        return 1;
    }

    return 0;
}