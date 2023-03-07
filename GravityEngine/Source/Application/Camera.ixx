module;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

export module Camera;

export class Camera
{
private:
	glm::mat4 ProjectionMatrix;
	glm::mat4 TranslationMatrix;
	glm::mat4 CameraMatrix;

public:
	Camera(glm::vec3 pos, glm::vec3 center, float aspectRatio, float FOV)
	{
		TranslationMatrix = glm::lookAt(pos, center, glm::vec3(0.0f, 0.0f, -1.0f));
		ProjectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, 0.001f, 100000.0f);

		CameraMatrix = ProjectionMatrix * TranslationMatrix;
	}

	void SetProjectionMatrix(float aspectRatio, float FOV)
	{
		ProjectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, 0.001f, 100000.0f);
		CameraMatrix = ProjectionMatrix * TranslationMatrix;
	}

	void SetTranslationMatrix(glm::vec3 pos, glm::vec3 center)
	{
		TranslationMatrix = glm::lookAt(pos, center, glm::vec3(0.0f, 0.0f, 1.0f));
		CameraMatrix = ProjectionMatrix * TranslationMatrix;
	}


	glm::mat4 GetCameraMatrix() const { return CameraMatrix; }
};
