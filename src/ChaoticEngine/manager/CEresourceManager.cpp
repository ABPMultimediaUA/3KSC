
#include <iostream>

#include "../../include/ChaoticEngine/manager/CEresourceManager.hpp"
#include "../../include/ChaoticEngine/manager/CEresourceAnimation.hpp"

//Instance initialization
CEResourceManager* CEResourceManager::m_instance = 0;

//Returns the only instance of this class
CEResourceManager* CEResourceManager::instance(){
    if (!m_instance){
        m_instance = new CEResourceManager();
    }

    return m_instance;
}

CEResourceManager::CEResourceManager(){}

CEResourceManager::~CEResourceManager(){}

CEResource& CEResourceManager::getResource(const char* p_name){
	//Creamos un recurso vacio y comprobamos si ya tenemos guardado algun recurso con esa ruta
	CEResource* t_resource = NULL;
	std::string t_path = p_name;
	for(size_t i = 0; i < m_resources.size(); i++){
		if(m_resources[i]!=nullptr && t_path.compare(m_resources[i]->getName()) == 0){
			t_resource = m_resources[i];
			return *t_resource;
		}
	}
	//Si no lo hemos encontrado entonces lo leemos desde disco
	if(t_resource == NULL){
		//comprobamos el formato del recurso
		t_resource = &checkFormat(p_name);
		if(t_resource->loadFile(p_name)){
			t_resource->setName(p_name);
			m_resources.push_back(t_resource);
		}
	}
	return *t_resource;
}

//Este metodo sustrae el formato de la ruta que le pasan por parametro y lo compara con un vector en el que
//hay guardados varios tipos de formatos
CEResource& CEResourceManager::checkFormat(const char* p_name){
	
	std::string t_path   = p_name;
	std::string t_format = t_path.substr(t_path.find_last_of('.')+1, t_path.size());

	//Default NULL
	CEResource* t_resourceObject = NULL; 
	
	//Remember even = format, odd = type
	size_t i = 0;
	//Una vez que encuentra en formato apropiado crea un recurso de ese tipo y lo devuelve
	while (i < m_types.size() && t_resourceObject == NULL) {
		if (!m_types[i].compare(t_format)) {
			if (!m_types[i + 1].compare("mesh")) { //file contains a mesh			
				t_resourceObject = new CEResourceMesh();
			}
			else if (!m_types[i + 1].compare("tex")) {//file contains a texture
				t_resourceObject = new CEResourceTexture();
			}
			else if (!m_types[i + 1].compare("animation")) {//file contains a texture
				t_resourceObject = new CEResourceAnimation();
			}
		}
		i += 2;
	}

	return *t_resourceObject;
}

//Borramos todos los recursos almacenados en el gestor
void CEResourceManager::deleteResources(){
	showResources();
	for(int i = 0; i < m_resources.size(); i++){
		delete(m_resources[i]);
		m_resources[i] = nullptr;
    }
    
	m_resources.clear();
}

void CEResourceManager::showResources(){
	std::cout<<std::endl;
	std::cout<<" - LISTA DE RECURSOS -"<<std::endl;
	for(int i = 0; i < m_resources.size(); i++){
		std::cout<<"recurso: " << m_resources[i]->getName() <<std::endl;
	}
}