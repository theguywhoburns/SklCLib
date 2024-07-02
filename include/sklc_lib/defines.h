// took it from sklc core(my local project that im working on right now) and modified it
#ifndef _SKLC_LIB_DEFINES_H_
#define _SKLC_LIB_DEFINES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Inlining
#ifdef _MSC_VER
#define INLINE __forceinline
#define NOINLINE __declspec(noinline)
#else
#define INLINE static inline
#define NOINLINE
#endif

#if defined(_MSC_VER)
#define STATIC_ASSERT(statement) static_assert(statement, #statement)
#else
#define STATIC_ASSERT(statement) _Static_assert(statement, #statement)
#endif

#if defined(_WIN32) || defined(_WIN64) 
    #define SKLC_PLATFORM_WINDOWS
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define SKLC_PLATFORM_WINDOWS_CYGWIN
#elif defined(__ANDROID__)
    #define SKLC_PLATFORM_ANDROID
#elif defined(__linux__)
    // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
    #define SKLC_PLATFORM_LINUX
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
        #define SKLC_PLATFORM_BSD
    #endif
#elif defined(__hpux)
    #define SKLC_PLATFORM_HP_UX
#elif defined(_AIX)
    // IBM AIX
    #define SKLC_PLATFORM_AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        // Apple IOS
        #define SKLC_PLATFORM_APPLE_IOS
    #elif TARGET_OS_IPHONE == 1
        // Apple IOS
        #define SKLC_PLATFORM_APPLE_IOS
    #elif TARGET_OS_MAC == 1
        // Apple OSX
        #define SKLC_PLATFORM_APPLE_OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    // Oracle(the ones that created java) Solaris, Open Indiana
    #define SKLC_PLATFORM_SOLARIS
#else
    #error UNKNOWN OR UNSUPPORTED PLATFORM... PEASE USE SUPPORTED ONE 
#endif

#endif//_SKLC_LIB_DEFINES_H_