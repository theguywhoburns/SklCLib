#ifndef _SKLC_LIB_UTILS_FILESYSTEM_H_
#define _SKLC_LIB_UTILS_FILESYSTEM_H_
#include <sklc_lib/defines.h>
#include <sklc_lib/utils/tinyvec.h>
#include <sklc_lib/utils/string.h>

typedef struct _folder {
    string name;
    /** Folders tinyvec */
    struct _folder *folders;
    /** Files tinyvec */
    struct _file *files;
    Date modified;
} Folder;

bool folder_exists(const char *path);
bool folder_exists_str(string  path);

typedef enum file_flags {
    FILE_FLAG_OPEN_IF_EXIST_ELSE_CREATE = 0x0,
    FILE_FLAG_MAX_FLAGS = 0xFF
} file_flags;

/// @brief File struct compatible with std file io functions(cuz FILE* is a handle)
typedef struct _file {
    /**
     * Placed handle first for compatibility with default 
     * functions like fopen, so you can just 
     * pass the struct without re-cating
     */
    void *handle;
    u64 size;
    string name;
    string data;
    Date modified;
} File;

bool file_exists(const char *path);
bool file_exists_str(string  path);

File* file_open(const char *path);
File* file_open_str(string path);
File* file_open_ex(const char *path);
File* file_open_ex_str(string path);

void file_close(File *file);
void delete_file(const char *path);
void delete_file_str(string path);

#endif//_SKLC_LIB_UTILS_FILESYSTEM_H_