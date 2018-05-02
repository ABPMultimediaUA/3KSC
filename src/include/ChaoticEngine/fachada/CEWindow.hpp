 
#ifndef CE_WINDOW
#define CE_WINDOW

//OpenGL
#include <glew.h>
#include <glfw3.h>
#include <gl.h>

class CEWindow{
public:
	CEWindow(int p_width, int p_height, const char* p_title, bool p_fullscreen);
	~CEWindow();

	bool 		isOpen();
	
	void 		close();
	void 		clear(float p_red = 0, float p_green = 0, float p_blue = 0, float p_alpha = 0);
	void		swapBuffers();
	void		pollEvents();
	void 		processInput();

	GLFWwindow* getWindow();

	/*  CALLBACKS  */
	static void windows_size_callback(GLFWwindow* p_window, int p_width, int p_height);

private:
	GLFWwindow*	m_window;

	void 		enableCulling();
	void 		enableZBuffer();
};

#endif
