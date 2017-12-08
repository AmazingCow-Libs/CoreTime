#pragma once

//----------------------------------------------------------------------------//
// Namespaces                                                                 //
//----------------------------------------------------------------------------//
// All classes of this core is placed inside this namespace.
// We use MACROS so is easier to change if needed.
// Is (in our opinion) more explicit.
// And finally the editors will not reformat the code.
#define NS_CORETIME_BEGIN namespace CoreTime {
#define NS_CORETIME_END   }
#define USING_NS_CORETIME using namespace CoreTime


//----------------------------------------------------------------------------//
// Version                                                                    //
//----------------------------------------------------------------------------//
#define COW_CORETIME_VERSION_MAJOR    "0"
#define COW_CORETIME_VERSION_MINOR    "1"
#define COW_CORETIME_VERSION_REVISION "0"

#define COW_CORETIME_VERSION       \
        COW_CORETIME_VERSION_MAJOR "." \
        COW_CORETIME_VERSION_MINOR "." \
        COW_CORETIME_VERSION_REVISION
