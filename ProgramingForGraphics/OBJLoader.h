#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "Vertex.h"


using namespace std;

class OBJLoader
{
public:
	static vector<Vertex> LoadOBJ(const string& FolderLocation, const string& FileName, string& AmbiantLoc,
		string& DiffLoc, string& specLoc, string& NormalLoc, vector<uint32_t>& indices);

	static void LoadMaterial(const string& MatLibLoc, string& AmbiantLoc, string& DiffLoc, string& specLoc,
		string& NormalLoc);
};
