//============================================================================
// Name        : utils.cpp
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

bool sortOp(std::string i, std::string j);
bool sortOpReverse(std::string i, std::string j);

int listFiles();

void loadFiles(const char *path);

std::string getExtension(std::string str);
std::string getFileName(std::string str);

int renameFiles(std::string oldname, std::string newname);
int renameSmiFiles();
int renameAviFiles();

int swapVector(bool down);
