#include "absl/status/status.h"
#include "actions/actions.h"

absl::Status run() {
  auto maybe_actions = actions::Actions<int>::Create();

  if (!maybe_actions.ok()) {
    return maybe_actions.status();
  }

  absl::Status status = absl::OkStatus();
  auto actions = maybe_actions.value();

  actions->Add(0, actions::Keystrokes({{'a', 0}}));
  status.Update(actions->Perform(0));

  if (!status.ok()) {
    return status;
  }

  return status;
}

int main() {
  absl::Status status = run();

  if (!status.ok()) {
    std::cerr << "Error: " << status.message() << std::endl;
    return 1;
  }

  return 0;
}