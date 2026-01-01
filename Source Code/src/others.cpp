#include <kamek.hpp>
#include <profileid.hpp>
#include <profile.hpp>
#include <utils.hpp>

// This is something related to LH files
kmWriteNop(0x801D7884);

void WriteUtf8ToTextBox(nw4r::lyt::TextBox *tb, const char *source) {
    int size = sizeof(source) / sizeof(char);
    OSReport("%d\n", size);

    wchar_t buffer[1024];
    int j = 0;

    for (int i = 0; source[i] && j < 1023; ) {
        unsigned char c = source[i];
        if (c < 0x80) {
            // 7 bits, which should be ascii
            buffer[j++] = c;
            i += 1;
        }
        else if ((c & 0xE0) == 0xC0 && (source[i+1] & 0xC0) == 0x80) {
            // 2 bytes
            buffer[j++] = ((c & 0x1F) << 6) | (source[i+1] & 0x3F);
            i += 2;
        }
        else if ((c & 0xF0) == 0xE0 && (source[i+1] & 0xC0) == 0x80 && (source[i+2] & 0xC0) == 0x80) {
            // 3 bytes
            buffer[j++] = ((c & 0x0F) << 12) | ((source[i+1] & 0x3F) << 6) | (source[i+2] & 0x3F);
            i += 3;
        }
        else {
            // invalid type, skip
            i += 1;
        }
    }
    buffer[j] = 0;
    tb->SetString(buffer);
}