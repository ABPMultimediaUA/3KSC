
#include <iostream>

#include "../../include/ChaoticEngine/fachada/CEWindow.hpp"

CEWindow::CEWindow(int p_width, int p_height, const char* p_title, bool p_fullscreen){
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(p_width, p_height, p_title, NULL, NULL);
	if (m_window == NULL){
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
	
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(GLEW_OK != err){
		//Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	//fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glfwSetFramebufferSizeCallback(m_window, windows_size_callback);

	std::cout << "VERSION OPENGL: " << glGetString(GL_VERSION) << std::endl;

	enableCulling();
	enableZBuffer();
}

CEWindow::~CEWindow(){}

void CEWindow::enableCulling(){
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void CEWindow::enableZBuffer(){
	glEnable(GL_DEPTH_TEST);	
}

bool CEWindow::isOpen(){
	if(glfwWindowShouldClose(m_window) == GL_FALSE)
		return true;
	
	return false;
}

void CEWindow::close(){
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void CEWindow::clear(float p_red, float p_green, float p_blue, float p_alpha){
	glClearColor(p_red, p_green, p_blue, p_alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CEWindow::swapBuffers(){
	glfwSwapBuffers(m_window);
}

void CEWindow::pollEvents(){
	glfwPollEvents();
}

void CEWindow::processInput(){
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}

GLFWwindow* CEWindow::getWindow(){
	return m_window;
}


/*  CALLBACKS  */
void CEWindow::windows_size_callback(GLFWwindow* p_window, int p_width, int p_height){
	glViewport(0, 0, p_width, p_height);
}