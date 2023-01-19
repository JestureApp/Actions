# Actions

Actions is a platform agnostic API for interacting with your operating systems Display Server with the purpose of performing various actions on the behave of the user.

As of right now these actions include:
* Sending Keystrokes [See Example](#example-sending-keystrokes-to-applications).

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

# Examples

## Example: Sending Keystrokes to Applications
TODO

# Documentation
Please refer to the [docs](docs/Index.md) for more information.

# Contributing
See [Contributing](Contributing.md) for instruction on contributing