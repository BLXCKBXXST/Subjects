#ifndef CP866_H
#define CP866_H

static void cp866_to_utf8(const char *src, char *dst) {
    unsigned char c;
    while ((c = (unsigned char)*src++) != 0) {
        if (c >= 0x80 && c <= 0x9F) {
            *dst++ = (char)0xD0;
            *dst++ = (char)(c - 0x80 + 0x90);
        } else if (c >= 0xA0 && c <= 0xAF) {
            *dst++ = (char)0xD0;
            *dst++ = (char)(c - 0xA0 + 0xB0);
        } else if (c >= 0xE0 && c <= 0xEF) {
            *dst++ = (char)0xD1;
            *dst++ = (char)(c - 0xE0 + 0x80);
        } else if (c == 0xF0) {
            *dst++ = (char)0xD0;
            *dst++ = (char)0x81;
        } else if (c == 0xF1) {
            *dst++ = (char)0xD1;
            *dst++ = (char)0x91;
        } else {
            *dst++ = (char)c;
        }
    }
    *dst = 0;
}

#endif
