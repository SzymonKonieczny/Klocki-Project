#pragma once
#ifndef BLOCK_TEMPLATE_H
#define BLOCK_TEMPLATE_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "GLOBAL.h"

#include "BlockTypes.h"
#include "VBO.h" //For Vertex struct





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
	glm::vec2 textureCoordinatesY; //x mininmum, y maximim 
	bool Collidable;
	std::string name;
	BlockTypes drops;

};

#endif // !BLOCK_TEMPLATE_H


