#ifndef _SKLC_DATALANG_PATH_H_
#define _SKLC_DATALANG_PATH_H_

#include <util/string.h>

typedef struct _iobuf FILE;

typedef wstring Path;

//WARNING: OUT POINTER WILL BE REALLOCATED
bool Path_Combine_2(Path* out, Path* path1, Path* path2);
//WARNING: OUT POINTER WILL BE REALLOCATED
bool Path_Combine_3(Path* out, Path* path1, Path* path2, Path* path3);
//WARNING: OUT POINTER WILL BE REALLOCATED
bool Path_Combine_4(Path* out, Path* path1, Path* path2, Path* path3, Path* path4);
///@brief WARNING: IF YOU ARE USING PATH FROM AN ARRAY AS AN OUTPUT IT WILL BE REALLOCATED AT THE END
///@brief \n AND IT'S SLOOOW
bool Path_Combine_ARRAY(Path* out, Path** path_array, uint64_t path_array_size);
/// @brief Returns a pointer to a string representing FULL path, don't forget to deallocate before/after using
Path* Path_Get(FILE* f);
//WARNING: OUT POINTER WILL BE REALLOCATED
bool Path_GetFullPath(Path* out, Path* path);  
/// @returns true if ends with / or \\
/// @returns false if not true lol
bool Path_EndsWithDirectorySeparator(Path* path);
/// @brief Checks if the file or folder exists at the specified path
/// @param path the PATH
/// @returns true if exists
/// @returns false if not
bool Path_Exists(Path* path);
/// @returns false and NULL If not found or path is invalid
/// @returns true and Allocated String pointer if found, this pointer has to be freed manually
bool Path_GetExstension(Path* path);
bool Path_GetFileName(wstring* out, Path* path);
bool Path_GetFileNameWithoutExstension(wstring* out, Path* path);
wstring_view* Path_GetInvalidFileNameChars();
wstring* Path_GetInvalidPathChars();
wstring* Path_GetRandomFileName(bool no_random_exstension, wstring* ext);


#endif//_SKLC_DATALANG_PATH_H_