#pragma once
#ifndef BLOCK_TEMPLATE_H
#define BLOCK_TEMPLATE_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "VBO.h" //For Vertex struct
struct BlockType
{
	enum BlockTypes
	{
		Grass,
		ShubiumOre,
		Stone,
		Dirt,
		Log,
		Leaves,
		Sand,
		Water,
		Air,
		ShubiumCrystal
	};

};
enum Faces
{
	Up, //+y
	Down, //-y
	North,//+z
	East,//+x
	South,//-z
	West//-x
};
struct BlockTemplate
{

	glm::vec2 textureCoordinatesX;  //x mininmum, y maximim 
	glm::vec2 textureCoordinatesY;
	bool Collidable;
	std::string name;
	BlockType::BlockTypes drops;

	static void BuildFace(std::vector<Vertex>& vertices, Faces Direction, glm::vec3 Pos);
};

#endif // !BLOCK_TEMPLATE_H


