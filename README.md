# Actions

## Prerequisites
### Linux
* [libx11](https://x.org/releases/current/doc/libX11/libX11/libX11.html)
  
  On ubuntu:
  ```bash
  apt-get install libx11-dev
  ```

  On Arch:
  ```
  pacman -S libx11
  ```

## Getting started

Follow the instructions [here](https://capstone-cs.eng.utah.edu/groups/jesture/-/wikis/Infrastructure/NPM#authenticating-with-gitlab-package-registry) to be able to install the package.

Then install the package
```
npm i @jesture/actions
```

## TODO
- [ ] How do I handle exceptions across FFI boundary
- [ ] Implement keystroke actions
- [ ] Setup CI/CD
