 
#ifndef CE_SCENE
#define CE_SCENE

#include <vector>

#include "../CEscenenode.hpp"
#include "../manager/CEresourceManager.hpp"

class CESceneCamera;
class CESceneLight;
class CESceneMesh;
class CESceneQuad;
class CESceneSprite;
class CESceneParticleSystem;
class CESceneSkybox;
class CEShaderProgram;

class CEScene{
public:
	CEScene();
	~CEScene();

	CESceneCamera*			createCamera(bool p_isActive = false);
	CESceneLight*			createLight(float p_lightIntensity[3], float p_lightAtenuation);
	CESceneMesh*			createMesh(const char* p_path);
	CESceneQuad*			createQuad(float p_vertex[4][2]);
	CESceneSprite*			createSprite(const char* p_path, float p_width, float p_height);
	CESceneParticleSystem*	createParticleSystem(const char* p_path, int p_amount);
	CESceneSkybox*			createSkybox(const char* p_path[6]);

	void			setActiveCamera(CESceneCamera* p_camera);

	void 			draw();
	void			release();

private:
	CESceneNode*		m_root;
	CEResourceManager*	m_resourceManager;
	CEShaderProgram* 	m_shaderProgram;

	CESceneCamera*		m_activeCamera;

	std::vector<CESceneCamera*>	m_cameras;
	std::vector<CESceneLight*>	m_lights;
};

#endif
