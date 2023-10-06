#ifndef FILE_PROCESSING_H
    #define FILE_PROCESSING_H

    typedef int Buffer_t;

    long get_file_size(FILE * fp);
    FILE * file_open(const char * file_name, const char * mode);
    Buffer_t * read_file(Buffer_t * buffer, const size_t buffer_size, FILE * fp);

#endif // FILE_PROCESSING_H
