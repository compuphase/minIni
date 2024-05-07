#include "minGlue-SPIFFS.h"
#include "spiffs.h"

char *fs_gets(char *s, int size, spiffs_file *file)
{
    char    *ptr;
    int32_t numBytes;
    int32_t pos;

    if ((s == 0) || (size <= 0))
    {
        return(NULL);
    }
    /* See the current position before reading */
    pos = SPIFFS_lseek(FS_HDL, *(file), 0, SPIFFS_SEEK_CUR);
    /* Read from the current position */
    numBytes = SPIFFS_read(FS_HDL, *(file), (s), (size - 1));
    if (numBytes > 0)
    {
        /* Find the first/next new line */
        ptr = strchr(s, '\n');
        if (ptr)
        {
            ptr++;
            *ptr     = 0;
            numBytes = strlen(s);
        }
    }
    else
    {
        return(NULL);
    }
    assert(numBytes <= size);
    /* Set the new position for the next read */
    SPIFFS_lseek(FS_HDL, *(file), (pos + numBytes), SPIFFS_SEEK_SET);
    return(s);
}
