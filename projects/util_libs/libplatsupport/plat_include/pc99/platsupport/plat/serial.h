/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#pragma once

#define SERIAL_CONSOLE_COM1_PORT  0x3f8
#define SERIAL_CONSOLE_COM2_PORT  0x2f8
#define SERIAL_CONSOLE_COM3_PORT  0x3e8
#define SERIAL_CONSOLE_COM4_PORT  0x2e8

#define SERIAL_CONSOLE_COM1_PORT_END (SERIAL_CONSOLE_COM1_PORT + 7)
#define SERIAL_CONSOLE_COM2_PORT_END (SERIAL_CONSOLE_COM2_PORT + 7)
#define SERIAL_CONSOLE_COM3_PORT_END (SERIAL_CONSOLE_COM3_PORT + 7)
#define SERIAL_CONSOLE_COM4_PORT_END (SERIAL_CONSOLE_COM4_PORT + 7)

#define SERIAL_CONSOLE_COM1_IRQ   4
#define SERIAL_CONSOLE_COM2_IRQ   3
#define SERIAL_CONSOLE_COM3_IRQ   4
#define SERIAL_CONSOLE_COM4_IRQ   3

#define EGA_TEXT_FB_BASE          0xB8000

enum chardev_id {
    PC99_SERIAL_COM1,
    PC99_SERIAL_COM2,
    PC99_SERIAL_COM3,
    PC99_SERIAL_COM4,
    PC99_TEXT_EGA,
    PC99_KEYBOARD_PS2,
    /* Aliases */
    PS_SERIAL0 = PC99_SERIAL_COM1,
    PS_SERIAL1 = PC99_SERIAL_COM2,
    PS_SERIAL2 = PC99_SERIAL_COM3,
    PS_SERIAL3 = PC99_SERIAL_COM4,
    /* defaults */
#if defined(CONFIG_LIB_PLAT_SUPPORT_SERIAL_PORT_X86_COM1)
    PS_SERIAL_DEFAULT = PC99_SERIAL_COM1
#elif defined(CONFIG_LIB_PLAT_SUPPORT_SERIAL_PORT_X86_COM2)
    PS_SERIAL_DEFAULT = PC99_SERIAL_COM2
#elif defined(CONFIG_LIB_PLAT_SUPPORT_SERIAL_PORT_X86_COM3)
    PS_SERIAL_DEFAULT = PC99_SERIAL_COM3
#elif defined(CONFIG_LIB_PLAT_SUPPORT_SERIAL_PORT_X86_COM4)
    PS_SERIAL_DEFAULT = PC99_SERIAL_COM4
#elif defined(CONFIG_LIB_PLAT_SUPPORT_SERIAL_TEXT_EGA)
    PS_SERIAL_DEFAULT = PC99_TEXT_EGA
#else
    PS_SERIAL_DEFAULT = PC99_SERIAL_COM1
#endif

};

