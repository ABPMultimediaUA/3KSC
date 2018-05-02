 
#ifndef CERESOURCETEXTURE
#define CERESOURCETEXTURE

#include "stb_image.h"

#include "CEresource.hpp"

class CEResourceTexture: public CEResource{
public:
	CEResourceTexture();
	~CEResourceTexture();

	bool loadFile(const char* p_name);
	void draw(GLuint p_shaderProgram);

	GLint getTextureId(){return m_textureId;}
	void setTextureId(GLint p_id){m_textureId = p_id;}

	std::string getTextureType(){return m_type;}
	void setTextureType(std::string p_type){m_type = p_type;}

	std::string getTexturePath(){return m_path;}
	void setTexturePath(std::string p_path){m_path = p_path;}

	std::string getTextureDirectory(){return m_directory;}
	void setTextureDirectory(std::string p_directory){m_directory = p_directory;}

private:

	GLint m_textureId;
    std::string m_type;
    std::string m_path;
    std::string m_directory;
	GLint TextureFromFile(const char* p_path);
};

#endif