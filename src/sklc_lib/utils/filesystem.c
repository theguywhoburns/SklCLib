#include <sklc_lib/utils/filesystem.h>
#include <Windows.h>

bool folder_exists(const char *path) {
	DWORD attribs = GetFileAttributesA(path);
	return (attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY));
}

bool folder_exists_str(string path) {
	return folder_exists(path.data);
}

bool file_exists(const char *path) {
  return GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES;
}

bool file_exists_str(string path) {
  return file_exists(path.data);
}

File* file_open(const char *path) {
  File *file = (File*)malloc(sizeof(File));
  
  return file;
}

File* file_open_str(string path) {
  return file_open(path.data);
}

File* file_open_ex(const char *path) {
  return file_open(path);
}

void file_close(File *file) {
  CloseHandle(file->handle);
  free(file);
}

void delete_file(const char *path) {
  DeleteFileA(path);
}

void delete_file_str(string path) {
  delete_file(path.data);
}
