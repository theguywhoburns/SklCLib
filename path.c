#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/path.h>

//WARNING: OUT POINTER WILL BE REALLOCATED
bool Path_Combine_2(Path* out, Path* path1, Path* path2) {
    if (!out || !path1 || !path2) return false;

    // Create a temporary wstring to hold the result.
    Path temp = wstring_create();

    // Append the first path to temp.
    wstring_add_wstr_wstr(&temp, temp, *path1);
    if (!Path_EndsWithDirectorySeparator(path1)) {
        wstring_add_wstr_wcp(&temp, temp, L"\\");
    }

    // Append the second path to temp.
    wstring_add_wstr_wstr(&temp, temp, *path2);

    // Safely transfer the result to out, taking care of potential overlap.
    wstring_destroy(out);
    *out = temp;

    return true;
}

//WARNING: OUT POINTER WILL BE REALLOCATED
bool Path_Combine_3(Path* out, Path* path1, Path* path2, Path* path3) {
    if (!out || !path1 || !path2 || !path3) return false;

    // Use Path_Combine_2 to combine the first two paths into a temporary variable.
    Path temp = wstring_create();
    if (!Path_Combine_2(&temp, path1, path2)) {
        wstring_destroy(&temp);
        return false;
    }

    // Ensure the combined path ends with a directory separator before adding path3.
    if (!Path_EndsWithDirectorySeparator(&temp)) {
        wstring_add_wstr_wcp(&temp, temp, L"\\");
    }

    // Append the third path.
    wstring_add_wstr_wstr(&temp, temp, *path3);

    // Safely transfer the result to out.
    wstring_destroy(out);
    *out = temp;

    return true;
}

//WARNING: OUT POINTER WILL BE REALLOCATED
bool Path_Combine_4(Path* out, Path* path1, Path* path2, Path* path3, Path* path4) {
    if (!out || !path1 || !path2 || !path3 || !path4) return false;

    // Use Path_Combine_3 to combine the first three paths into a temporary variable.
    Path temp = wstring_create();
    if (!Path_Combine_3(&temp, path1, path2, path3)) {
        wstring_destroy(&temp);
        return false;
    }

    // Ensure the combined path ends with a directory separator before adding path4.
    if (!Path_EndsWithDirectorySeparator(&temp)) {
        wstring_add_wstr_wcp(&temp, temp, L"\\");
    }

    // Append the fourth path.
    wstring_add_wstr_wstr(&temp, temp, *path4);

    // Safely transfer the result to out.
    wstring_destroy(out);
    *out = temp;

    return true;
}

///@brief WARNING: IF YOU ARE USING PATH FROM AN ARRAY AS AN OUTPUT IT WILL BE REALLOCATED AT THE END
bool Path_Combine_ARRAY(Path* out, Path** path_array, uint64_t path_array_size) {
    if (!out || !path_array || path_array_size == 0) return false;

    // Create a temporary wstring to hold the result, ensuring we don't prematurely modify 'out'.
    Path temp = wstring_create();

    // Iterate through the array, stopping before the last element.
    for (uint64_t i = 0; i < path_array_size - 1; ++i) {
        if (path_array[i] == NULL) {
            // Clean up and return false on error.
            wstring_destroy(&temp);
            return false;
        }

        // Append each path to 'temp' and ensure it ends with a directory separator.
        wstring_add_wstr_wstr(&temp, temp, *path_array[i]);
        if (!Path_EndsWithDirectorySeparator(path_array[i])) {
            wstring_add_wstr_wcp(&temp, temp, L"\\");
        }
    }

    // Handle the last element separately to avoid adding an unnecessary directory separator.
    if (path_array[path_array_size - 1] == NULL) {
        wstring_destroy(&temp);
        return false;
    }
    wstring_add_wstr_wstr(&temp, temp, *path_array[path_array_size - 1]);

    // Safely transfer the result to 'out', ensuring any overlap is handled correctly.
    wstring_destroy(out);
    *out = temp;

    return true;
}

/// @brief Returns a pointer to a string representing FULL path, don't forget to deallocate before/after using
Path* Path_Get(FILE* f) {
    return NULL;    
}


//WARNING: OUT POINTER WILL BE REALLOCATED
bool Path_GetFullPath(Path* out, Path* path) {
    return false;
}  

/// @returns true if ends with / or \\
/// @returns false if not true lol
bool Path_EndsWithDirectorySeparator(Path* path) {
    return false;
}

/// @brief Checks if the file or folder exists at the specified path
/// @param path the PATH
/// @returns true if exists
/// @returns false if not
bool Path_Exists(Path* path) {
    return false;
}

/// @returns false and NULL If not found or path is invalid
/// @returns true and Allocated String pointer if found, this pointer has to be freed manually
bool Path_GetExstension(Path* path) {
    return false;
}

bool Path_GetFileName(wstring* out, Path* path) {
    return false;
}

bool Path_GetFileNameWithoutExstension(wstring* out, Path* path) {
    return false;
}

wstring_view* Path_GetInvalidFileNameChars() {
    return NULL;
}

wstring* Path_GetInvalidPathChars() {
    return NULL;
}

wstring* Path_GetRandomFileName(bool no_random_exstension, wstring* ext) {
    return NULL;
}
