#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <shlwapi.h>
#include "Directory.h"

#pragma comment(lib, "Shlwapi.lib")

int Directory::CreateDir(const char* DirectoryName) {
	if (CreateDirectoryA(DirectoryName, NULL)) {
		return 0;
	}
	else {
		return 1;
	}
}

bool Directory::Exists(const char* Path) {
	if (PathFileExistsA(Path)) {
		return true;
	}
	else {
		return false;
	}
}

int Directory::Delete(const char* DirectoryName) {
	return (RemoveDirectoryA(DirectoryName) == TRUE);
}

int Directory::EnumerateFiles(const char* Mask, OnFoundFile OnFound) {
	int Result = 0;

	LPWIN32_FIND_DATAA Founded = (LPWIN32_FIND_DATAA)malloc(sizeof(WIN32_FIND_DATAA));

	HANDLE searchHandle = FindFirstFileA(Mask, Founded);
	if (INVALID_HANDLE_VALUE != searchHandle) {
		do {
			if ((Founded->dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY) != Founded->dwFileAttributes) {
				if (NULL != OnFound) {
					OnFound(Founded->cFileName);
				}
				Result++;
			}
		} while (FindNextFileA(searchHandle, Founded));
		FindClose(searchHandle);
	}
	free(Founded);

	return Result;
};

int Directory::EnumerateDirectories(const char* Mask, OnFoundFile OnFound) {
	int Result = 0;

	LPWIN32_FIND_DATAA Founded = (LPWIN32_FIND_DATAA)malloc(sizeof(WIN32_FIND_DATAA));

	HANDLE searchHandle = FindFirstFileA(Mask, Founded);
	if (INVALID_HANDLE_VALUE != searchHandle) {
		do {
			if ((Founded->dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY) == Founded->dwFileAttributes) {
				if (NULL != OnFound) {
					OnFound(Founded->cFileName);
				}
				Result++;
			}
		} while (FindNextFileA(searchHandle, Founded));
		FindClose(searchHandle);
	}
	free(Founded);

	return Result;
};

bool Directory::Combine(char* SourcePath, const char* AppendPath) {
	return (PathAppendA(SourcePath, AppendPath) == TRUE);
};
