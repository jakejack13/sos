/** Collection of constants used to draw text and shapes to the screen */
#ifndef _FONT_H_
#define _FONT_H_

enum screen_colors {
    WHITE = (unsigned int) 0x00FFFFFF,
    BLACK = (unsigned int) 0x00000000,
};

/** Data structure for holding font data */
struct font {
    /** Mapping of character value to character glyph */
    unsigned char map[224][8];
    /** Number of glyphs */
    const unsigned int numglyphs;
    /** Bytes per glyph */
    const unsigned int bpg;
    /** Bytes per line */
    const unsigned int bpl;
    /** Width of each glyph */
    const unsigned int width;
    /** Height of each glyph */
    const unsigned int height;
    /** Foreground color of glyphs */
    const unsigned int fore_color;
    /** Background color of glphs */
    const unsigned int back_color;
};

extern struct font default_font;

#endif //_FONT_H_