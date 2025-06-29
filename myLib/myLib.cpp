<<<<<<< HEAD
#include "myLib.hpp"

size_t getFileSize(FILE* file)
{
    ASSERT(file, "file = NULL, it is impossible to work with null ptr", stderr);

    long currentPos = ftell(file);
    fseek(file, 0, SEEK_END);
    size_t size = (size_t)ftell(file);
    fseek(file, currentPos, SEEK_SET);

    return size;
}

char* readFileToBuffer(FILE* file, size_t size_file)
{
    ASSERT(file, "file = NULL, it is impossible to work with null ptr", stderr);
    ASSERT(size_file, "size_file should not be null", stderr);

    char* buffer = (char*)calloc(size_file, sizeof(char));    // СОЗДАНИЕ БУФФЕРА
    ASSERT(buffer, "buffer = NULL, it is impossible to work with null ptr", stderr);

    size_file = fread(buffer, sizeof(char), size_file, file); // ЗАПОЛЕНИЕ БУФФЕРА

    return buffer;
}
=======
#include "myLib.h"

size_t getSizeOfFile(FILE* file, const char* const nameFile)
{
    assert(file);
    assert(nameFile);

    struct stat st;     
    stat(nameFile, &st);                                                                             
    size_t size = st.st_size;
    assert(size);

    return size;
}
>>>>>>> bd16e690d2e5ded0d14e349537736a45217249a6
