#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef void(*OnFoundFile)(char* FileName);

class Directory {
public:
	static int CreateDir(const char* DirectoryName);
	static bool Exists(const char* Path);
	static int Delete(const char* DirectoryName);
	static int EnumerateFiles(const char* Mask, OnFoundFile OnFound = NULL);
	static int EnumerateDirectories(const char* Mask, OnFoundFile OnFound = NULL);
	static bool Combine(char* SourcePath, const char* AppendPath);
};

#endif