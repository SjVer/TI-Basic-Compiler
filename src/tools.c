#include "common.h"
#include "tools.h"

// reallocates memory of size newSize for pointer
// if newSize is 0, pointer is freed
void *reallocate(void *pointer, size_t oldSize, size_t newSize)
{
    if (newSize == 0)
    {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL)
    {
        // exit if we have no more memory available
        fprintf(stderr, "MEMORY ALLOCATION FAILED! (From %d to %d)\n",
            oldSize, newSize);
        exit(1);
    }
    return result;
}

// formats a string
char *fstr(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int smallSize = sizeof(char) * 1024;
    char *smallBuffer = malloc(smallSize);

    int size = vsnprintf(smallBuffer, smallSize, format, args);

    va_end(args);

    if (size < sizeof smallBuffer)
        return smallBuffer;

    int bigSize = sizeof(char) * (size + 1);
    char *buffer = malloc(bigSize);

    va_start(args, format);
    vsnprintf(buffer, bigSize, format, args);
    va_end(args);

    return buffer;
}

char *readFile(const char *path)
{
    FILE *file = fopen(path, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "Could not open file \"%s\".\n", path);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char *buffer = (char *)malloc(fileSize + 1);
	if (buffer == NULL)
	{
		fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
		exit(74);
	}
	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	if (bytesRead < fileSize)
	{
		fprintf(stderr, "Could not read file \"%s\".\n", path);
		exit(74);
	}
	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}