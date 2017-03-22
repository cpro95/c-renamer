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
#include "utils.h"

// global variables in main.cpp
extern std::vector<std::string> vMovieFiles;
extern std::vector<std::string> vSmiFiles;

extern int index1;
extern int index2;
extern bool index_inside_movie;

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
	int size1 = vMovieFiles.size();
	int size2 = vSmiFiles.size();

	if(size1 > 0 || size2 > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
	
}


void loadFiles(const char* path)
{
	// clear vectors
	vMovieFiles.clear();	
	vSmiFiles.clear();
	
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

			if (strstr(hFile->d_name, ".mkv") ||
				strstr(hFile->d_name, ".mp4") ||
				strstr(hFile->d_name, ".avi")
				)
				{
					std::string str(hFile->d_name);
					vMovieFiles.push_back(str);
				}
			else
				if(
				   strstr(hFile->d_name, ".smi") ||
			 	   strstr(hFile->d_name, ".smil") ||
				   strstr(hFile->d_name, ".srt") ||
				   strstr(hFile->d_name, ".ass")
				)
				{
					std::string str2(hFile->d_name);
					vSmiFiles.push_back(str2);
				}
		}
	}
	closedir (dirFile);
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
	{
		perror("Error renaming file");
		return 1;
	}
	else return 0;
}

int renameSmiFiles()
{
	int size = vMovieFiles.size();
	int error;

	for(int i = 0; i<size ; i++)
		error += renameFiles(vSmiFiles[i],
				getFileName(vMovieFiles[i])	+ getExtension(vSmiFiles[i]));

	if (error > 0)
	{	
		perror("Error renaming file");
		return 1;
	}
	else
	{
		return 0;
	}
}
int renameAviFiles()
{
	int size = vMovieFiles.size();
	int error;
	
	for(int i=0; i<size; i++)
	{
		error += renameFiles(vMovieFiles[i],
				getFileName(vSmiFiles[i]) + getExtension(vMovieFiles[i]));
	}
	
	if (error > 0)
	{	
		perror("Error renaming file");
		return 1;
	}
	else
	{
		return 0;
	}
}


int swapVector(bool down) 
{
	// bool down is direction
	// true is down direction
	// false is up direction

	std::string imsi;
	std::string imsi2;

	if(down==true) // going down
	{
			if(index_inside_movie==true)
			{
				if(index1 != vMovieFiles.size()-1)
				{
						imsi=vMovieFiles[index1];
						imsi2=vMovieFiles[index1+1];
						vMovieFiles[index1+1] =imsi;
						vMovieFiles[index1] = imsi2;
						index1++;
				}
			}
			else
			{
				if(index2 != vSmiFiles.size()-1)
				{

						imsi=vSmiFiles[index2];
						imsi2=vSmiFiles[index2+1];
						vSmiFiles[index2+1] =imsi;
						vSmiFiles[index2] = imsi2;
						index2++;
				}
			}

	}

	if(down==false) // going up
	{
			if(index_inside_movie==true)
			{
				if(index1 != 0)
				{
					imsi=vMovieFiles[index1];
					imsi2=vMovieFiles[index1-1];
					vMovieFiles[index1-1] =imsi;
					vMovieFiles[index1] = imsi2;
					index1--;
				}
			}
			else
			{
				if(index2 != 0)
				{
					imsi=vSmiFiles[index2];
					imsi2=vSmiFiles[index2-1];
					vSmiFiles[index2-1] =imsi;
					vSmiFiles[index2] = imsi2;
					index2--;
				}

			}

	}

}

