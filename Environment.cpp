#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <shlwapi.h>
#include "Environment.h"


Environment::Environment() {

}

Environment ::~Environment() {

}

int Environment::GetFolderPath(SpecialFolder Folder, char* Buffer) {
	int Result = 1;
	int CLSIDL = 0;
	switch (Folder) {
	case MyComputer: {CLSIDL = CSIDL_DRIVES; break; }
	case MyDocuments: {CLSIDL = CSIDL_MYDOCUMENTS; break; }
	case MyMusic: {CLSIDL = CSIDL_MYMUSIC; break; }
	case MyPictures: {CLSIDL = CSIDL_MYPICTURES; break; }
	case MyVideos: {CLSIDL = CSIDL_MYVIDEO; break; }
	}
	if (SHGetFolderPathA(0, CLSIDL, NULL, SHGFP_TYPE_CURRENT, Buffer) == S_OK) {
		Result = 0;
	}
	return Result;
}

int Environment::getCurrentDirectory(char* Path, int Length) {
	int Result = 1;
	if (GetCurrentDirectoryA(Length, Path) != 0) {
		Result = 0;
	}
	return Result;
};

void Environment::setCurrentDirectory(char* Path) {
	SetCurrentDirectoryA(Path);
};

