/*  Glue functions for the minIni library, based on the C/C++ stdio library
 *
 *  Or better said: this file contains macros that maps the function interface
 *  used by minIni to the standard C/C++ file I/O functions.
 *
 *  By CompuPhase, 2008-2014
 *  This "glue file" is in the public domain. It is distributed without
 *  warranties or conditions of any kind, either express or implied.
 */

/* map required file I/O types and functions to the standard C library */
#include <stdio.h>
#include "spiffs.h"

char *fs_gets(char *s, int size, spiffs_file *file);

#ifndef FS_HDL
extern spiffs *fs_gethandle(void);
/* Macro to return the handle to the SPIFFS file system */
#define FS_HDL (fs_gethandle())
#endif /* FS_HDL */

#define PORTABLE_STRNICMP

#define INI_FILETYPE                    spiffs_file
#define ini_openread(filename,file)     ((*(file) = SPIFFS_open(FS_HDL, (filename), SPIFFS_RDONLY, 0)) != NULL)
#define ini_openwrite(filename,file)    ((*(file) = SPIFFS_open(FS_HDL, (filename), (SPIFFS_WRONLY | SPIFFS_APPEND | SPIFFS_CREAT), 0)) != NULL)
#define ini_openrewrite(filename,file)  ((*(file) = SPIFFS_open(FS_HDL, (filename), (SPIFFS_WRONLY | SPIFFS_DIRECT), 0)) != NULL)
#define ini_close(file)                 (SPIFFS_close(FS_HDL, *(file)) == 0)
#define ini_read(buffer,size,file)      (fs_gets((buffer), (size), (file)) != NULL)
#define ini_write(buffer,file)          (SPIFFS_write(FS_HDL, *(file), (buffer), strlen(buffer)) >= 0)
#define ini_rename(source,dest)         (SPIFFS_rename(FS_HDL, (source), (dest)) == 0)
#define ini_remove(filename)            (SPIFFS_remove(FS_HDL, filename) == 0)

#define INI_FILEPOS                     int
#define ini_tell(file,pos)              (*(pos) = SPIFFS_lseek(FS_HDL, *(file), 0, SPIFFS_SEEK_CUR))
#define ini_seek(file,pos)              (SPIFFS_lseek(FS_HDL, *(file), *(pos), SPIFFS_SEEK_SET) == 0)

/* for floating-point support, define additional types and functions */
#define INI_REAL                        float
#define ini_ftoa(string,value)          sprintf((string),"%f",(value))
#define ini_atof(string)                (INI_REAL)strtod((string),NULL)
