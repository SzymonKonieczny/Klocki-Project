#include "Camera.h"
Camera::Camera(glm::vec3 position) {
	Position = position;


}
void Camera::UpdateView()
{
	view = glm::lookAt(Position, Position + LookingAtDir, glm::vec3(0.0f, 1.0f, 0.0f));
	

	proj = glm::perspective(90.0f, float(Window::GetInstance()->WinWidth)/ Window::GetInstance()->WinHeight,0.01f, 500.0f);


	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

}
void Camera::GetUniformLocations(Shader & shaderProgram)
{
	shaderProgram.Activate();
	 modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	 viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	 projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	std::cout << "Chunk Shader \n proj : " << projLoc << "view: " << viewLoc << "model: " << modelLoc << std::endl;

}
void Camera::UpdateUniformsTransparent()
{

	glUniformMatrix4fv(TranslucentmodelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(TranslucentviewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(TranslucentprojLoc, 1, GL_FALSE, glm::value_ptr(proj));

}
void Camera::UpdateUniformsEntity()
{
	glUniformMatrix4fv(EntitymodelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(EntityviewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(EntityprojLoc, 1, GL_FALSE, glm::value_ptr(proj));

}
void Camera::GetUniformLocationsForTransparent(Shader& shaderProgram)
{
	shaderProgram.Activate();
	TranslucentmodelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	TranslucentviewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	TranslucentprojLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	std::cout << "Transparent Shader \n proj : " << TranslucentprojLoc << "view: " << TranslucentviewLoc << "model: " << TranslucentmodelLoc << std::endl;

}
void Camera::GetUniformLocationsForEntity(Shader& shaderProgram)
{
	shaderProgram.Activate();
	EntitymodelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	EntityviewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	EntityprojLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	std::cout << "Entity Shader \n proj : " << EntityprojLoc << "view: " << EntityviewLoc << "model: " << EntitymodelLoc << std::endl;

}
int  Camera::GetModelUniformLocation()
{
	return modelLoc;
}



