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
	switch (Direction)	//https://upload.wikimedia.org/wikipedia/commons/e/ec/Cube_coords.png Based on that, anticlockwise (from left bottm)
	{
	case Up:

		//						x:5		y:10		z:5							corner:2	color:2		textureNr:10
		vertices.AddToVerticies(Vertex((x | ((y+1) << 5) | (z << 15)					| (0 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x+1) | ((y+1) << 5) | (z << 15)				| (1 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | ((z + 1) << 15)		| (3 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y + 1) << 5) | ((z + 1) << 15)		| (3 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y+1) << 5) | ((z + 1) << 15)				| (2 << 20) | (00 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y + 1) << 5) | (z << 15)					| (0 << 20) | (00 << 22) | (block << 24))));


		break;
	case Down:
		
		vertices.AddToVerticies(Vertex((x | (y << 5) | (z << 15)						 | (0 << 20) | (2 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | (z << 15)					 | (1 << 20) | (2 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | ((z + 1) << 15)			 | (3 << 20) | (2 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y  << 5) | ((z + 1) << 15)			 | (3 << 20) | (2 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y  << 5) | ((z + 1) << 15)					 | (2 << 20) | (2 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y << 5) | (z << 15)						 | (0 << 20) | (2 << 22) | (block << 24))));

		break;
	case North:
		vertices.AddToVerticies(Vertex((x | (y << 5) | ((z+1) << 15)						 | (0 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | ((z + 1) << 15)				 | (1 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | ((z + 1) << 15)			 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1)  << 5) | ((z + 1) << 15)			 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y+1)  << 5) | ((z + 1) << 15)					 | (2 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y << 5) | ((z + 1) << 15)					     | (0 << 20) | (01 << 22) | (block << 24))));
	
		break;
	case East:
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | (z << 15)						 | (0 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | ((z + 1) << 15)				 | (1 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | ((z + 1) << 15)			 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1)  << 5) | ((z + 1) << 15)			 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x+1) | ((y+1)  << 5) | (z << 15)					 | (2 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | (z << 15)					     | (0 << 20) | (01 << 22) | (block << 24))));


		break;
	case South:
		vertices.AddToVerticies(Vertex((x | (y << 5) | (z << 15)							 | (0 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | (y << 5) | (z << 15)						 | (1 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | (z << 15)					 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex(((x + 1) | ((y+1) << 5) | (z << 15)					 | (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y+1)  << 5) | (z << 15)						 | (2 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x| (y << 5) | (z << 15)							     | (0 << 20) | (01 << 22) | (block << 24))));


		break;
	case West:
		vertices.AddToVerticies(Vertex((x | (y << 5) | ((z+1) << 15)							| (0 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y << 5) | (z << 15)								| (1 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x| ((y + 1) << 5) | (z << 15)							| (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x| ((y + 1) << 5) | (z << 15)							| (3 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | ((y + 1) << 5) | ((z+1) << 15)						| (2 << 20) | (01 << 22) | (block << 24))));
		vertices.AddToVerticies(Vertex((x | (y << 5) | ((z+1) << 15)							| (0 << 20) | (01 << 22) | (block << 24))));
		break;

		default:
		break;
	}

}