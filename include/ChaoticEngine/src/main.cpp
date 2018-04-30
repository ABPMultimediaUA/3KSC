
#include <../include/main.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/manager/stb_image.h"

int main(){
	std::cout << "*************************\n* TEST DE CHAOTICENGINE *\n*************************" << std::endl;

	CEWindow* window = new CEWindow(640, 480, "3KSC", false);

	CEScene* scene = new CEScene();
	CESceneCamera* m_camera	= scene->createCamera(true);
	CESceneLight*  m_light	= scene->createLight();
	CESceneMesh*   m_mesh	= scene->createMesh("resources/pelota/pelota.obj");
	m_mesh->setScale(0.25, 0.25, 0.25);

	while(window->isOpen()){
		window->processInput();
		
		window->clear(0.5f, 0.0f, 0.0f, 1.0f);

		m_light->processInput(window->getWindow());
		m_mesh->processInput(window->getWindow());
		m_light->getPosition();

		scene->draw();

    	window->swapBuffers();
		window->pollEvents();
	}
	scene->release();
	window->close();
	return 0;
}
