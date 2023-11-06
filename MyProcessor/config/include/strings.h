#ifndef STRINGS_H
    #define STRINGS_H

    #include <stdio.h>

    void show_text(const char * text5, const size_t size);
    size_t get_strings_num(char * buffer);
    void get_pointers(const char * buffer, const char * pointers[], const size_t strings_num);
    void show_strings(const char * const * strings, const size_t strings_num);
    char * skip_word(const char * buffer);
    char * next_word(const char * buffer);
    char * skip_spaces(const char * buffer);

#endif // STRINGS_H
