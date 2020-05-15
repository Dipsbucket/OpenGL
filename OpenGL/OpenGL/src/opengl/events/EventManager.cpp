#include "EventManager.h"

EventManager::EventManager()
{
	// OpenGL
	this->currentRenderingMode = 0;
	this->enableDepthTest = true;
	this->enableMultiSampling = true;

	// Camera
	this->currentCameraIndex = 0;

	// Object
	this->currentObject = 0;
}

EventManager::~EventManager()
{
}

void EventManager::createShaderManager()
{
	// TODO JT : Try catch Créer le cameraManager en 1er
	// Création et compilation des shaders
	this->shaderManager = new ShaderManager();
	this->shaderManager->loadShaders();
	this->shaderManager->compileShaders();
	this->shaderManager->setMVPUniforms(cameraManager->getCurrentCamera()->model, cameraManager->getCurrentCamera()->view, cameraManager->getCurrentCamera()->projection);
}

void EventManager::createCameraManager(int width, int height)
{
	// Création des caméras
	this->cameraManager = new CameraManager(width, height);
}

void EventManager::createSceneManager()
{
	this->sceneManager = new SceneManager();
}

void EventManager::switchRenderingMode(int rmIndex)
{
	if (rmIndex != this->currentRenderingMode)
	{
		switch (rmIndex)
		{
			case 0:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			case 1:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;
			case 2:
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				break;
			default:
				break;
		}

		this->currentRenderingMode = rmIndex;
	}
}

void EventManager::switchDepthTest(bool enable)
{
	if (enable != this->enableDepthTest)
	{
		if (enable)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}

		this->enableDepthTest = enable;
	}
}

void EventManager::switchMultiSampling(bool enable)
{
	if (enable != this->enableMultiSampling)
	{
		if (enable)
		{
			glEnable(GL_MULTISAMPLE);
		}
		else
		{
			glDisable(GL_MULTISAMPLE);
		}

		this->enableMultiSampling = enable;
	}
}

void EventManager::switchShaders(int vsIndex, int fsIndex)
{
	shaderManager->getShaderProgram()->clear();
	shaderManager->setCurrentVsIndex(vsIndex);
	shaderManager->setCurrentFsIndex(fsIndex);
	shaderManager->compileShaders();
	this->shaderManager->setMVPUniforms(cameraManager->getCurrentCamera()->model, cameraManager->getCurrentCamera()->view, cameraManager->getCurrentCamera()->projection);
}

void EventManager::switchCamera(int cameraIndex)
{
	if (cameraIndex != this->currentCameraIndex)
	{
		cameraManager->setCurrentCamera(cameraIndex);
		this->shaderManager->setMVPUniforms(cameraManager->getCurrentCamera()->model, cameraManager->getCurrentCamera()->view, cameraManager->getCurrentCamera()->projection);

		this->currentCameraIndex = cameraIndex;
	}
}

void EventManager::switchObject(int objectIndex)
{
	if (this->currentObject != objectIndex)
	{
		this->currentObject = objectIndex;
	}
}

void EventManager::manageScroll(double offset)
{
	if (shaderManager->hasMVP())
	{
		cameraManager->getCurrentCamera()->zoom(offset > 0);
		this->shaderManager->setMVPUniforms(cameraManager->getCurrentCamera()->model, cameraManager->getCurrentCamera()->view, cameraManager->getCurrentCamera()->projection);
	}
}

void EventManager::manageRotateCamera(double xOffset, double yOffset)
{
	if (shaderManager->hasMVP())
	{
		// TODO JT : TEST
		//cameraManager->getCurrentCamera()->rotate(xOffset, yOffset);
		//this->shaderManager->setMVPUniforms(cameraManager->getCurrentCamera()->model, cameraManager->getCurrentCamera()->view, cameraManager->getCurrentCamera()->projection);
	}
}

void EventManager::manageRotateCameraArcBall(float viewportWidth, float viewportHeight, float x, float y, float z)
{
	if (shaderManager->hasMVP())
	{
		cameraManager->getCurrentCamera()->test(viewportWidth, viewportHeight, x, y, z);
		this->shaderManager->setMVPUniforms(cameraManager->getCurrentCamera()->model, cameraManager->getCurrentCamera()->view, cameraManager->getCurrentCamera()->projection);
	}
}

void EventManager::translateObject(unsigned int objectIndex, glm::vec3 translation, bool reset)
{
	if (glm::length(translation) > 0)
	{
		this->sceneManager->getObject(objectIndex)->translate(translation, reset);
	}
}

void EventManager::rotateObject(unsigned int objectIndex, glm::vec3 rotation)
{
	if (glm::length(rotation) > 0)
	{
		this->sceneManager->getObject(objectIndex)->rotate(rotation);
	}
}

void EventManager::saveTransforms()
{
	this->sceneManager->saveTransforms();
}

void EventManager::clearTransform(unsigned int id)
{
	this->sceneManager->clearTransform(id);
}

void EventManager::clearTransforms()
{
	this->sceneManager->clearTransforms();
}