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
  if(file_exists(path)) {
    file->handle = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  } else {
    file->handle = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
  }
  StringCreate(&file->name, path);
  file->size = GetFileSize(file->handle, NULL);
  file->data.data = (char*)malloc(file->size + 1);
	file->data.len = file->size;
  DWORD read;
  ReadFile(file->handle, file->data.data, file->size, &read, NULL);
  file->data.data[file->size] = 0;
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
  StringDestroy(&file->data);
	StringDestroy(&file->name);
  free(file);
}

void delete_file(const char *path) {
  DeleteFileA(path);
}

void delete_file_str(string path) {
  delete_file(path.data);
}
