#ifndef EML_MUSIC_STYLE_HELPERS_H
#define EML_MUSIC_STYLE_HELPERS_H

enum class MUSIC_STYLE {
    BLUES = 0,
    CLASSICAL = 1,
    COUNTRY = 2,
    DISCO = 3,
    HIPHOP = 4,
    JAZZ = 5,
    METAL = 6,
    POP = 7,
    REGGAE = 8,
    ROCK = 9
};

std::string music_style_to_string(const MUSIC_STYLE &s);

MUSIC_STYLE music_style_from_string(std::string str);

MUSIC_STYLE music_style_from_int(unsigned int s);


std::ostream &operator<<(std::ostream &os, MUSIC_STYLE music_style);


#endif //EML_MUSIC_STYLE_HELPERS_H
