#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "Mesh.h"

class OBJModelLoader {

public:
	static void LoadModelToMesh(Mesh<UncompressedVertex>& mesh, std::string fileName)
	{

		std::ifstream file(fileName);
		std::string line = "";
		std::string prefix = "";
		std::vector<glm::fvec3> positions;
		std::vector<glm::fvec2> UV_coords;
		std::vector<GLuint> positions_indicies;
		std::vector<GLuint> UV_indicies;
		std::stringstream ss;
		if(!file.is_open()) std::cout << " Couldnt read " + fileName + '\n';
		while (std::getline(file, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;
			if (ss.fail())
				std::cout << "OBJModelLoader: String stream fail \n";
			if (prefix == "v")
			{
				glm::fvec3 v;
				ss >> v.x >>  v.y >> v.z;

				positions.push_back(v);
				
			}
			if (prefix == "vt")
			{
				glm::fvec2 v;
				ss >> v.x >> v.y;

				UV_coords.push_back(v);
			}
			if (prefix == "f")
			{
				int counter = 0;
				int temp_int;
				while (ss >> temp_int)
				{

					if (counter == 0)
						positions_indicies.push_back(temp_int);
					else if (counter == 1)
						UV_indicies.push_back(temp_int);
					else if (counter == 2) {}
						// we dont care for normals for now, so nothing

					if (ss.peek() == '/')
					{
						++counter;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ')
					{
						//++counter;
						counter = 0;
						ss.ignore(1, ' ');
					}

					if (counter > 2)
						counter = 0;
				}
			}

		}
		//Build final vertex array (mesh)
		//vertices.resize(vertex_position_indicies.size(), Vertex());
		mesh.ClearVerticies();
		//Load in all indices
		for (size_t i = 0; i < positions_indicies.size(); ++i)
		{
			UncompressedVertex temp_vert;
			temp_vert.position = positions[positions_indicies[i]-1]; //in the .OBJ format, they start indexing with 1 (xD)
			
			temp_vert.texturePos = glm::vec2(1, 1);//UV_coords[UV_indicies[i]-1];
			temp_vert.color = glm::vec3(1.0f, 1.0f, 1.0f);
			
			mesh.AddToVerticies(temp_vert);
			mesh.AddToElements(positions_indicies[i]-1);

		}
		std::cout << " Loaded " << positions_indicies.size() << "verticies for " + fileName + '\n';

	}

};