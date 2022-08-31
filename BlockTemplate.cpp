#include "BlockTemplate.h"
void BlockTemplate::BuildFace(std::vector<Vertex>& vertices, Faces Direction, glm::vec3 Pos)
{
	/*glm::vec3(0.0f, 0.0, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0, 1)*/
	 
	switch (Direction)	//https://upload.wikimedia.org/wikipedia/commons/e/ec/Cube_coords.png Based on that, anticlockwise (from left bottm)
	{
	case Up:
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(0, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(1, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(0, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(0, 0)));
		break;
	case Down:
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(0, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 0.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(1, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 1.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 1.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(0, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec2(0, 0)));
		break;
	case North:
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 0)));
		break;
	case East:
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 0.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(0, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 1.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(1, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 1.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 0.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(0, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 0.0f),
				glm::vec3(0.6f, 0.6f, 0.6f),
				glm::vec2(0, 0)));
		break;
	case South:
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 0.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(1.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 0)));

		break;
	case West:
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 0)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 0.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(1, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 1.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 1)));
		vertices.push_back(
			Vertex(Pos + glm::vec3(0.0f, 0.0, 1.0f),
				glm::vec3(0.7f, 0.7f, 0.7f),
				glm::vec2(0, 0)));
		break;
	default:
		break;
	}

}