// took it from sklc core(my local project that im working on right now) and modified it
#ifndef _SKLC_LIB_DEFINES_H_
#define _SKLC_LIB_DEFINES_H_

#ifndef __cplusplus
    #define bool _Bool
    #define true 1
    #define false 0
#endif



#ifndef NULL
#define NULL ((void*)0)
#endif

//TODO: Static assert every type equals to the specified size
typedef char    b8; 
typedef int     b32;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef signed char         i8;
typedef signed short        i16;
typedef signed int          i32;
typedef signed long long    i64;

typedef float   f32;
typedef double  f64;

typedef unsigned short wchar;

#define BIT(x) (1 << x)

typedef u8  Byte; // Byte  = 1 Byte
typedef u16 Word; // Word  = 2 Bytes
typedef u32 DWord;// DWord = 4 Bytes
typedef u64 QWord;// QWord = 8 Bytes

// Inlining
#ifdef _MSC_VER
#define INLINE __forceinline
#define NOINLINE __declspec(noinline)
#else
#define INLINE static inline
#define NOINLINE
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