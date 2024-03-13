#ifndef _SKLC_LIB_EMU_H_
#define _SKLC_LIB_EMU_H_
#include <sklc_lib/defines.h>

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

#endif//_SKLC_LIB_EMU_H_