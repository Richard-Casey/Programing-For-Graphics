#include "OBJLoader.h"

vector<Vertex> OBJLoader::LoadOBJ(const string& FolderLocation, const string& FileName, string& AmbiantLoc,
	string& DiffLoc, string& specLoc, string& NormalLoc, vector<uint32_t>& indices)
{
	string line;			// the next line of text from the file
	string MatLibName;		// the name of the mtl lib
	string MaterialOfMesh;	// the name of the mtl to use
	string MeshName;		// the name of the mesh / object
	vector <glm::vec3> VertPositions;		// temp storage for the vertex position
	vector <glm::vec3> VertNormals;			// temp storage for the vertex normals
	vector <glm::vec3> VertTextureCoords;	// temp storage for vertex TexCoords
	vector <Vertex> FinalVerts; // the list of verts, normal and tex coords

	std::ifstream file;
	string FileLoc = FolderLocation + "/" + FileName;
	const char* fileNameChar = FileLoc.c_str();
	file.open(fileNameChar, ifstream::in);

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			if (line[0] != '#')
			{
				string FirstWord = line.substr(0, line.find(' '));

				if (FirstWord == "mtllib")
				{
					MatLibName = line.substr(line.find(' ') + 1, line.find('\n'));
				}
	//if this line is the mtllib line, get the data after the first space and save it in the MatLibName var

				else if (FirstWord == "o") //Object name
				{
					MeshName = line.substr(line.find(' '), line.find('\n'));
				}

				else if (FirstWord == "v") // Vert Pos
				{
					string VertValues = line.substr(line.find(' '), line.find('\n'));
					float x, y, z;
					sscanf_s(VertValues.c_str(), "%f %f %f", &x, &y, &z);
					VertPositions.push_back(glm::vec3(x, y, z));
				}

				else if (FirstWord == "vn") // Vert normal
				{
					string VertNormValues = line.substr(line.find(' '), line.find('\n'));
					float x, y, z;
					sscanf_s(VertNormValues.c_str(), "%f %f %f", &x, &y, &z);
					VertNormals.push_back(glm::vec3(x, y, z));
				}

				else if (FirstWord == "vt") // Vert texture Coordinates
				{
					string VertTexValues = line.substr(line.find(' '), line.find('\n'));
					float x, y, z;
					sscanf_s(VertTexValues.c_str(), "%f %f %f", &x, &y, &z);
					VertTextureCoords.push_back(glm::vec3(x, y, z));
				}

				else if (FirstWord == "usemtl") // which Mtl to use in .mtl
				{
					MaterialOfMesh = line.substr(line.find(' ') + 1, line.find('\n'));
					LoadMaterial(FolderLocation + "/" + MatLibName, AmbiantLoc, DiffLoc, specLoc, NormalLoc);
				}

			}
		}
	}
	else
	{
		cerr << "Unablle to load text file: " << FolderLocation + "/" + FileLoc << endl;
	}

	return FinalVerts; // to shut it up!!
}
void OBJLoader::LoadMaterial(const string& MatLibLoc, string& AmbiantLoc, string& DiffLoc, string& specLoc, string& NormalLoc)
{
}
;