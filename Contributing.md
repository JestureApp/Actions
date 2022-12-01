# Development Requirements
* [Bazel](https://bazel.build/)
* [Clang](https://clang.llvm.org/)
* [GCC](https://gcc.gnu.org/)

# Code Organization
An overview of some important files and organization of the code. If it's not 
listed here you probably don't need to worry about it.
```
Actions
├── actions         # Top level directory for source, platform-independent 
│   │               # implementation goes here.
│   │
│   ├── examples        # Some code examples that use Actions.
│   │
│   └── linux           # Linux specific implementation
│
├── third_party     # Contains build configuration for non-bazel repositories, 
│                   # in our case local dependencies. 
│
├── .bazelrc        # Can be used to specify default command-line args for bazel.
│
├── deps.bzl        # A script that installs all the dependencies for actions,
│                   # if you need to add or change a dependency do it here.
│
└── WORKSPACE       # Bazel workspace configuration
```

# IDE setup
For any IDEs using some form of `clangd` for IntelliSense run
```
bazel run //.vscode:compile_commands
```
to generate a `compile_commands.json` file.

## VSCode
VSCode is the preferred IDE as we have setup some tooling to make working in this
code base easier.

### Tasks
* Build All
* Test All
* Refresh compile_commands.json