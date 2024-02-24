// took it from sklc core(my local project that im working on right now) and modified it
#ifndef _SKLC_LIB_DEFINES_H_
#define _SKLC_LIB_DEFINES_H_

#ifndef __cplusplus
    #define bool _Bool
    #define true 1
    #define false 0
#endif


/*----IMPORTANT----

if you want to use X Window system, define USE_X_WINDOW_SYS before including any of the folowing headers:
    #include <sklc_lib/internal/glad/glad_glx.h>

-----------------*/



// May be needed for library user to check the library version
#define __SKLC_VERSION 1
#define __SKLC_WNDCLASSNAME L"SKLCWND01"

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

typedef union _reg16 {
    u16 full;
    struct {
        u8 low;
        u8 high;
    } bytes;
    struct {
        union {
            u8 small_reg;
            struct {
                u8 bit0 : 1;
                u8 bit1 : 1;
                u8 bit2 : 1;
                u8 bit3 : 1;
                u8 bit4 : 1;
                u8 bit5 : 1;
                u8 bit6 : 1;
                u8 bit7 : 1;
            } bits;
        } low_byte;
        u8 high_byte;
    } nested;
} reg16;

typedef union _reg32 {
    u32 full;
    struct {
        u16 low;
        u16 high;
    } words;
    struct {
        u8 byte0;
        u8 byte1;
        u8 byte2;
        u8 byte3;
    } bytes;
    struct {
        union {
            u16 small_reg;
            struct {
                u8 low_byte;
                u8 high_byte;
            } bytes;
        } low_word;
        u16 high_word;
    } nested;
} reg32;

typedef union _reg64 {
    u64 full;
    struct {
        u32 low;
        u32 high;
    } dwords;
    struct {
        u16 word0;
        u16 word1;
        u16 word2;
        u16 word3;
    } words;
    struct {
        u8 byte0;
        u8 byte1;
        u8 byte2;
        u8 byte3;
        u8 byte4;
        u8 byte5;
        u8 byte6;
        u8 byte7;
    } bytes;
    struct {
        union {
            u32 small_reg;
            struct {
                u16 low_word;
                u16 high_word;
            } words;
            struct {
                u8 byte0;
                u8 byte1;
                u8 byte2;
                u8 byte3;
            } bytes;
        } low_dword;
        u32 high_dword;
    } nested;
} reg64;

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