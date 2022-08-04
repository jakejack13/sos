#include "io/framebuffer.h"

#include "io/mmio.h"

//MAILBOX

// The buffer must be 16-byte aligned as only the upper 28 bits of the address can be passed via the mailbox
volatile unsigned int __attribute__((aligned(16))) mbox[36];

enum {
    VIDEOCORE_MBOX = (PERIPHERAL_BASE + 0x0000B880),
    MBOX_READ      = (VIDEOCORE_MBOX + 0x0),
    MBOX_POLL      = (VIDEOCORE_MBOX + 0x10),
    MBOX_SENDER    = (VIDEOCORE_MBOX + 0x14),
    MBOX_STATUS    = (VIDEOCORE_MBOX + 0x18),
    MBOX_CONFIG    = (VIDEOCORE_MBOX + 0x1C),
    MBOX_WRITE     = (VIDEOCORE_MBOX + 0x20),
    MBOX_RESPONSE  = 0x80000000,
    MBOX_FULL      = 0x80000000,
    MBOX_EMPTY     = 0x40000000
};

enum {
    MBOX_REQUEST  = 0
};

enum {
    MBOX_CH_POWER = 0,
    MBOX_CH_FB    = 1,
    MBOX_CH_VUART = 2,
    MBOX_CH_VCHIQ = 3,
    MBOX_CH_LEDS  = 4,
    MBOX_CH_BTNS  = 5,
    MBOX_CH_TOUCH = 6,
    MBOX_CH_COUNT = 7,
    MBOX_CH_PROP  = 8 // Request from ARM for response by VideoCore
};

enum {
    MBOX_TAG_SETPOWER   = 0x28001,
    MBOX_TAG_SETCLKRATE = 0x38002,

    MBOX_TAG_SETPHYWH   = 0x48003,
    MBOX_TAG_SETVIRTWH  = 0x48004,
    MBOX_TAG_SETVIRTOFF = 0x48009,
    MBOX_TAG_SETDEPTH   = 0x48005,
    MBOX_TAG_SETPXLORDR = 0x48006,
    MBOX_TAG_GETFB      = 0x40001,
    MBOX_TAG_GETPITCH   = 0x40008,

    MBOX_TAG_LAST       = 0
};

static unsigned int mbox_call(unsigned char ch) {
    // 28-bit address (MSB) and 4-bit value (LSB)
    unsigned int r = ((unsigned int)((long) &mbox) &~ 0xF) | (ch & 0xF);

    // Wait until we can write
    while (mmio_read(MBOX_STATUS) & MBOX_FULL);
    
    // Write the address of our buffer to the mailbox with the channel appended
    mmio_write(MBOX_WRITE, r);

    while (1) {
        // Is there a reply?
        while (mmio_read(MBOX_STATUS) & MBOX_EMPTY);

        // Is it a reply to our message?
        if (r == mmio_read(MBOX_READ)) return mbox[1]==MBOX_RESPONSE; // Is it successful?
           
    }
    return 0;
}

//FRAMEBUFFER

unsigned int width, height, pitch, isrgb;
static unsigned char *fb;

void fb_init() {
    mbox[0] = 35*4; // Length of message in bytes
    mbox[1] = MBOX_REQUEST;

    mbox[2] = MBOX_TAG_SETPHYWH; // Tag identifier
    mbox[3] = 8; // Value size in bytes
    mbox[4] = 0;
    mbox[5] = 1920; // Value(width)
    mbox[6] = 1080; // Value(height)

    mbox[7] = MBOX_TAG_SETVIRTWH;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 1920;
    mbox[11] = 1080;

    mbox[12] = MBOX_TAG_SETVIRTOFF;
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0; // Value(x)
    mbox[16] = 0; // Value(y)

    mbox[17] = MBOX_TAG_SETDEPTH;
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = 32; // Bits per pixel

    mbox[21] = MBOX_TAG_SETPXLORDR;
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1; // RGB

    mbox[25] = MBOX_TAG_GETFB;
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096; // FrameBufferInfo.pointer
    mbox[29] = 0;    // FrameBufferInfo.size

    mbox[30] = MBOX_TAG_GETPITCH;
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0; // Bytes per line

    mbox[34] = MBOX_TAG_LAST;

    // Check call is successful and we have a pointer with depth 32
    if (mbox_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
        mbox[28] &= 0x3FFFFFFF; // Convert GPU address to ARM address
        width = mbox[10];       // Actual physical width
        height = mbox[11];      // Actual physical height
        pitch = mbox[33];       // Number of bytes per line
        isrgb = mbox[24];       // Pixel order
        fb = (unsigned char *)((long)mbox[28]);
    }
}

void fb_draw_pixel(int x, int y, unsigned int color) {
    int offs = (y * pitch) + (x * 4);
    *((unsigned int*)(fb + offs)) = color;
}

void fb_draw_char(int x, int y, char c, struct font font) {
    unsigned char ch = (unsigned char) c;
    unsigned char *glyph = (unsigned char *)&font.map + (ch < font.numglyphs ? ch : 0) * font.bpg;

    for (int i=0;i<font.height;i++) {
        for (int j=0;j<font.width;j++) {
            unsigned int mask = 1 << j;
            unsigned int col = (*glyph & mask) ? font.fore_color : font.back_color;

            fb_draw_pixel(x+j, y+i, col);
        }
        glyph += font.bpl;
    }
}

void fb_draw_string(int x, int y, const char *s, struct font font) {
    while (*s) {
        if (*s == '\r') {
            x = 0;
        } else if(*s == '\n') {
            x = 0; y += font.height;
        } else {
	        fb_draw_char(x,y,*s,font);
            x += font.width;
        }
       s++;
    }
}

void fb_paint_screen(unsigned int color) {
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            fb_draw_pixel(i,j,color);
        }
    }
}
