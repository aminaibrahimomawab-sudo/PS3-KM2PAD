/*
 * PS3-KM-HEN
 * USB Keyboard + USB Mouse only
 */

#include <stdint.h>
#include <string.h>

typedef struct
{
    uint8_t modifier;
    uint8_t reserved;
    uint8_t keys[6];
} KeyboardReport;

typedef struct
{
    uint8_t buttons;
    int8_t x;
    int8_t y;
} MouseReport;

typedef struct
{
    uint8_t buttons[2];
    int8_t lx;
    int8_t ly;
    int8_t rx;
    int8_t ry;
    uint8_t l2;
    uint8_t r2;
} PadState;

static PadState pad;

static int key_pressed(const KeyboardReport *r, uint8_t key)
{
    int i;

    for (i = 0; i < 6; i++)
    {
        if (r->keys[i] == key)
            return 1;
    }

    return 0;
}

static void keyboard_update(const KeyboardReport *r)
{
    memset(&pad, 0, sizeof(pad));

    /* WASD -> Left Stick */
    if (key_pressed(r, 0x04))
        pad.lx = -127; /* A */

    if (key_pressed(r, 0x07))
        pad.lx = 127;  /* D */

    if (key_pressed(r, 0x1A))
        pad.ly = -127; /* W */

    if (key_pressed(r, 0x16))
        pad.ly = 127;  /* S */

    /* Space -> Cross */
    if (key_pressed(r, 0x2C))
        pad.buttons[0] |= 0x02;

    /* C -> Circle */
    if (key_pressed(r, 0x06))
        pad.buttons[0] |= 0x04;

    /* R -> Square */
    if (key_pressed(r, 0x15))
        pad.buttons[0] |= 0x01;

    /* 1 -> Triangle */
    if (key_pressed(r, 0x1E))
        pad.buttons[0] |= 0x08;

    /* Q -> L1 */
    if (key_pressed(r, 0x14))
        pad.buttons[0] |= 0x10;

    /* G -> R1 */
    if (key_pressed(r, 0x0A))
        pad.buttons[0] |= 0x20;

    /* Tab -> Select */
    if (key_pressed(r, 0x2B))
        pad.buttons[0] |= 0x80;

    /* Enter -> Start */
    if (key_pressed(r, 0x28))
        pad.buttons[1] |= 0x08;

    /* Escape -> PS */
    if (key_pressed(r, 0x29))
        pad.buttons[1] |= 0x10;
}

static void mouse_update(const MouseReport *m)
{
    /* Mouse movement -> Right Stick */
    pad.rx = m->x;
    pad.ry = m->y;

    /* Left mouse -> R2 */
    if (m->buttons & 0x01)
        pad.r2 = 255;

    /* Right mouse -> L2 */
    if (m->buttons & 0x02)
        pad.l2 = 255;
}
