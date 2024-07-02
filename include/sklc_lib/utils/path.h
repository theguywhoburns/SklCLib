#ifndef _SKLC_DATALANG_PATH_H_
#define _SKLC_DATALANG_PATH_H_

#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>

bool PathExists(string path);
bool PathEndsWithDirectorySeparator(string path);
const string PathGetInvalidFileNameChars();

string PathCombine(string path1, string path2);
string PathCombineArr(string* paths, uint64_t len);

string PathGetFullPath(string path);

string PathGetFileName(string path);
string PathGetFileExtension(string path);

#define PathExistsCCP(ccp) PathExists(STRING_VIEW(ccp, StringLength(ccp)))
#define PathGetFullPathCCP(ccp) PathGetFullPath(STRING_VIEW(ccp, StringLength(ccp)))

#endif//_SKLC_DATALANG_PATH_H_