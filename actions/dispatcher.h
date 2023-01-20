#ifndef __H_DISPATCHER__
#define __H_DISPATCHER__

#if defined(__linux__)
#include "actions/linux/dispatcher.h"
#endif

namespace actions {
#if defined(__linux__)
using Dispatcher = LinuxDispatcher;
#endif
}  // namespace actions

#endif  // __H_DISPATCHER__