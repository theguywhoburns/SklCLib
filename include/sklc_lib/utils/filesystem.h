#ifndef _SKLC_LIB_UTILS_FILESYSTEM_H_
#define _SKLC_LIB_UTILS_FILESYSTEM_H_
#include <sklc_lib/defines.h>
#include <sklc_lib/utils/tinyvec.h>
#include <sklc_lib/utils/string.h>

typedef struct FileEntry {
    string name;
    /** Folders tinyvec */
    struct FileEntry *children;
    uint64_t size;
    uint64_t last_modified;
} FileEntry;

typedef struct File {
    FileEntry entry;
    void* handle;
} File;

bool folder_exists(const char *path);
bool folder_exists_str(string  path);

bool file_exists(const char *path);
bool file_exists_str(string  path);

File* file_open(const char *path);
File* file_open_str(string path);

void file_close(File *file);
void delete_file(const char *path);
void delete_file_str(string path);

FileEntry* get_file_entry(const char *path);

#endif//_SKLC_LIB_UTILS_FILESYSTEM_H_