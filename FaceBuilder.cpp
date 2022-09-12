#include "FaceBuilder.h"
#include "Mesh.h"

void FaceBuilder::BuildFace(Mesh& vertices, Faces Direction, glm::vec3 Pos, BlockTypes block)
{
	/*glm::vec3(0.0f, 0.0, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0, 1)*/
	Util* instance = Util::GetInstance();
	int x = Pos.x;
	int y = Pos.y;
	int z = Pos.z;
	unsigned int a;
	switch (Direction)	//https://upload.wikimedia.org/wikipedia/commons/e/ec/Cube_coords.png Based on that, anticlockwise (from left bottm)
	{
	case Up:
				/*vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 1.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));
		*/
		a = (x | (y << 4) | (z << 14) | (00 << 18) | (00 << 20) | (block << 22));

		//								x:5		y:10		z:5							corner:2	color:2		textureNr:10
		vertices.AddToVerticies(Vertex((x | ((y+1) << 5) | (z << 15)					| (0 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x+1) | ((y+1) << 5) | (z << 15)				| (1 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | ((z + 1) << 15)		| (3 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y + 1) << 5) | ((z + 1) << 15)		| (3 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y+1) << 5) | ((z + 1) << 15)				| (2 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y + 1) << 5) | (z << 15)					| (0 << 20) | (00 << 22) | (block << 24))));

		

		break;
	case Down:
		
		vertices.AddToVerticies(Vertex((x | (y << 5) | (z << 15)						 | (0 << 20) | (10 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | (z << 15)					 | (1 << 20) | (10 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | ((z + 1) << 15)			 | (3 << 20) | (10 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y  << 5) | ((z + 1) << 15)			 | (3 << 20) | (10 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y  << 5) | ((z + 1) << 15)					 | (2 << 20) | (10 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y << 5) | (z << 15)						 | (0 << 20) | (10 << 22) | (block << 24))));
	/*	vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 0.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 1.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 1.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));*/
		break;
	case North:
		vertices.AddToVerticies(Vertex((x | (y << 5) | ((z+1) << 15)						 | (0 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | ((z + 1) << 15)				 | (1 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | ((z + 1) << 15)			 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1)  << 5) | ((z + 1) << 15)			 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y+1)  << 5) | ((z + 1) << 15)					 | (2 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y << 5) | ((z + 1) << 15)					     | (0 << 20) | (01 << 22) | (block << 24))));
		/*vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));*/
		break;
	case East:
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | (z << 15)						 | (0 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | ((z + 1) << 15)				 | (1 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | ((z + 1) << 15)			 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1)  << 5) | ((z + 1) << 15)			 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x+1) | ((y+1)  << 5) | (z << 15)					 | (2 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | (z << 15)					     | (0 << 20) | (01 << 22) | (block << 24))));

		/*vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 0.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 1.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 0.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 0.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));*/
		break;
	case South:
		vertices.AddToVerticies(Vertex((x | (y << 5) | (z << 15)							 | (0 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | (z << 15)						 | (1 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | (z << 15)					 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | (z << 15)					 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y+1)  << 5) | (z << 15)						 | (2 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x| (y << 5) | (z << 15)							     | (0 << 20) | (01 << 22) | (block << 24))));


		/*vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));*/

		break;
	case West:
		vertices.AddToVerticies(Vertex((x | (y << 5) | ((z+1) << 15)							| (0 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y << 5) | (z << 15)								| (1 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x| ((y + 1) << 5) | (z << 15)							| (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x| ((y + 1) << 5) | (z << 15)							| (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y + 1) << 5) | ((z+1) << 15)						| (2 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y << 5) | ((z+1) << 15)							| (0 << 20) | (01 << 22) | (block << 24))));


	/*	vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.x)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.y, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.y)));
		vertices.AddToVerticies(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(instance->BLOCKS[block].textureCoordinatesX.x, instance->BLOCKS[block].textureCoordinatesY.x)));
		break;*/
	default:
		break;
	}

}