#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment {
public:
	enum SpecialFolder {
		MyComputer
		, MyDocuments
		, MyMusic
		, MyPictures
		, MyVideos
	};

public:
	Environment();
	~Environment();
	static int GetFolderPath(SpecialFolder Folder, char* Buffer);
	static int getCurrentDirectory(char* Path, int Length);
	static void setCurrentDirectory(char* Path);
private:

};


#endif