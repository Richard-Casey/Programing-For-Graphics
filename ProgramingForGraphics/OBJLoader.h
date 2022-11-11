#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "Vertex.h"
#include <map>

using namespace std;

class OBJLoader
{
public:
	static vector<Vertex> LoadOBJ(const string& FolderLocation, const string& FileLoc, string& AmbiantLoc,
		string& DiffLoc, string& specLoc, string& NormalLoc, vector<uint32_t>& indices);

	static void LoadMaterial(const string& MatLibLoc, string& AmbiantLoc, string& DiffLoc, string& specLoc,
		string& NormalLoc);
};

#endif