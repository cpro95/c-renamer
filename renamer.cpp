//============================================================================
// Name        : avi_smi_namer.cpp
// Author      : cpro95
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : AVI, SMI Namer by cpro95
//============================================================================

#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <algorithm>

// global variables
std::vector<std::string> vMovieFiles;
std::vector<std::string> vSmiFiles;

bool sortOp(std::string i, std::string j)
{
	return (i<j);
}

bool sortOpReverse(std::string i, std::string j)
{
	return (i>j);
}

int listFiles()
{
	int size1, size2;
	size1 = vMovieFiles.size();
	size2 = vSmiFiles.size();
	if(size1 != size2)
		std::cout << "error : Count does not match " <<
		"size1 : " << size1 << " size2 : " << size2 << std::endl;



	for(int i=0; i< size1; i++)
		std::cout << vMovieFiles[i] << '\n' << vSmiFiles[i] << std::endl;
		
	if(size1==0 | size2==0)
	{
		return 0;
	}
	else {
		return 1;
	}
	
}


void loadFiles(const char* path)
{
	DIR* dirFile = opendir(path);
	if (dirFile)
	{
		struct dirent* hFile;
		while ((hFile = readdir(dirFile)) != NULL)
		{
			if (!strcmp(hFile->d_name, "."))
				continue;
			if (!strcmp(hFile->d_name, ".."))
				continue;

			if(hFile->d_name[0] == '.') continue;

			if (strstr(hFile->d_name, ".mkv") || strstr(hFile->d_name, ".mp4") || strstr(hFile->d_name, ".avi"))
				{
				std::string str(hFile->d_name);
				vMovieFiles.push_back(str);
				}
			else
				if(strstr(hFile->d_name, ".smi") || strstr(hFile->d_name, ".smil") || strstr(hFile->d_name, ".srt"))
				{
					std::string str2(hFile->d_name);
					vSmiFiles.push_back(str2);
				}
		}
	}
	closedir (dirFile);

	std::cout << "We found " << vMovieFiles.size() << " files.\n" << std::endl;
}


std::string getExtension(std::string str)
{
	unsigned found = str.find_last_of(".");
	return str.substr(found);
}

std::string getFileName(std::string str)
{
	unsigned found = str.find_last_of(".");
	return str.substr(0,found);
}


int renameFiles(std::string oldname, std::string newname)
{
	int result = rename(oldname.c_str(), newname.c_str());

	if (result != 0)
		perror("Error renaming file");

	return 0;
}

void renameSmiFiles()
{
	int size = vMovieFiles.size();

	for(int i = 0; i<size ; i++)
		renameFiles(vSmiFiles[i], getFileName(vMovieFiles[i]) + getExtension(vSmiFiles[i]));

	std::cout << "\nRename Operation has been done." << std::endl;
}

void renameAviFiles()
{
	int size = vMovieFiles.size();
	
	for(int i=0; i<size; i++)
	{
		renameFiles(vMovieFiles[i], getFileName(vSmiFiles[i]) + getExtension(vMovieFiles[i]));
	}
	
	std::cout << "\nRename Operation has been done." << std::endl;
}

int main()
{

	loadFiles(".");
	//listFiles();
	
	std::sort(vMovieFiles.begin(), vMovieFiles.end(), sortOp);
	std::sort(vSmiFiles.begin(), vSmiFiles.end(), sortOp);
	
	if(listFiles()!=0)
	{
		std::cout << "Do you want to rename it by movie names(M) or subtitle names(S)? (M/S), otherwise it'll quit." << std::endl;
		char c = std::cin.get();
		
		if(c=='M' || c=='m')
			renameSmiFiles();
		else if(c=='S' || c=='s')
			renameAviFiles();
			
	}
	else{
		std::cout << "quit" << std::endl;
	}
	return 0;
}
