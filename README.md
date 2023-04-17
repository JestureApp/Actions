# Actions

Actions is a platform agnostic API for interacting with your operating systems Display Server with the purpose of performing various actions on the behave of the user.

As of right now these actions include:
* Sending Keystrokes [See Example](#example-sending-keystrokes-to-applications).
* Sending Mouse button presses [See Example](#example-sending-mouse-button-presses)

## Prerequisites
Actions has various dependencies depending on our platform. Please see the related subsections for your platform's dependencies.

### Linux
Currently Actions only supports linux systems using the X11 display server.
* [libx11](https://x.org/releases/current/doc/libX11/libX11/libX11.html)
  
  On ubuntu:
  ```bash
  apt-get install libx11-dev
  ```

  On Arch:
  ```
  pacman -S libx11
  ```

# Bazel setup
Include the following in your `WORKSPACE` file
```
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "actions",
    strip_prefix = "Actions-1.0.0",
    url = "https://github.com/JestureApp/Actions/archive/refs/tags/v1.0.0.zip",
)

load("@actions//:repositories.bzl", "actions_repositories")

actions_repositories()

load("@actions//display:display_configure.bzl", "display_configure")

display_configure()

load("@display//:local_display.bzl", "display_repositories")

display_repositories()
```

# Examples

## Example: Sending Keystrokes to Applications
```c++
// Create connection to display server and setup actions API
auto actions = Actions::Create();

if (! actions.ok()) {
    std::cout << "Failed to create actions: " << actions.status() << std::endl;
    std::exit(1);
}

// Create a key sequence
auto keysequence = action::ParseKeystroke("Ctrl+Shift+D");

if (! keysequence.ok()) {
    std::cout << "Failed to parse keysequence: " << keysequence.status() << std::endl;
    std::exit(1);
}

// Send a keystroke event to the focused window
absl::Status status = actions->Perform(action::Keystroke{keysequence.value()}, action::target::Focused()).get();

if (! status.ok()) {
    std::cout << "Failed to send keystroke: " << status << std::endl;
    std::exit(1);
}
```

## Example: Sending Mouse button presses
```c++
// Create connection to display server and setup actions API
auto actions = Actions::Create();

if (! actions.ok()) {
    std::cout << "Failed to create actions: " << actions.status() << std::endl;
    std::exit(1);
}

// Send a cursor move event to the focused window
absl::Status status = actions->Perform(action::CursorMove{.x = 0.1, .y = 0.1}, action::target::Focused()).get();

if (! status.ok()) {
    std::cout << "Failed to send keystroke: " << status << std::endl;
    std::exit(1);
}

// Send a mouse click event to the focused window
status = actions->Perform(action::MouseClick::LeftClick, action::target::Focused()).get();

if (! status.ok()) {
    std::cout << "Failed to send keystroke: " << status << std::endl;
    std::exit(1);
}
```

# Contributing
See [Contributing](Contributing.md) for instruction on contributing