#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <sklc_lib/utils/path.h>

string PathGetFileName(string path) {
	int id = StringFind(path, STRING_VIEW_("\\", 1), STRING_FIND_LAST);
	if(id == -1) {
		string str = {0};
		StringCreate(&str, "");
		return str;
	}
	string tmp = {0};
	StringCreateEx(&tmp, path.data + id + 1, StringLength(path.data + id + 1), false);
	id = StringFind(tmp, STRING_VIEW_(".", 1), 0);
	if(id == -1) {
		string ret = {0};
		StringDuplicate(&ret, tmp);
		return ret;
	}
	string ret = {0};
	StringSlice(&ret, tmp, 0, id);
	return ret;
}

string PathGetFileExtension(string path) {
	int id = StringFind(path, STRING_VIEW_(".", 1), STRING_FIND_LAST);
	if(id == -1) {
		string str = {0};
		StringCreate(&str, "");
		return str;
	}

	string ret = {0};
	StringCreate(&ret, path.data + id + 1);
	return ret;
}

bool PathEndsWithDirectorySeparator(string path) {
	#ifdef SKLC_PLATFORM_WINDOWS
		return StringEndsWith(path, STRING_VIEW_("\\", 1));
	#endif
	#ifdef SKLC_PLATFORM_LINUX
		return StringEndsWith(path, STRING_VIEW_("/", 1)) || StringEndsWith(path, STRING_VIEW_("\\", 1));
	#endif
}

const string PathGetInvalidFileNameChars() {
	return (string){.data = "\\/:*?\"<>|", .len = 47, .own = false};
}

#ifdef SKLC_PLATFORM_WINDOWS

#include <Windows.h>

bool PathExists(string path) {
  DWORD attrs = GetFileAttributesA(path.data);
  return (attrs != INVALID_FILE_ATTRIBUTES);
}

string PathCombine(string path1, string path2);

string PathCombineArr(string* paths, uint64_t len);

string PathGetFullPath(string path) {
  char fullPath[MAX_PATH];
  GetFullPathNameA(path.data, MAX_PATH, fullPath, NULL);
  string ret = {0};
	StringCreate(&ret, fullPath);
	return ret;
}

#endif