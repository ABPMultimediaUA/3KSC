/*
    3KSC: A fighting game
    Copyright (C) 2018  Chaotic Games

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*/

#include "../headers/managers/UIManager.hpp"

#include <SFML/OpenGL.hpp>
#include <iostream>

//Instance initialization
UIManager* UIManager::m_instance = 0;

//Returns the only instance of this class
UIManager* UIManager::instance(){
    if (!m_instance){
        m_instance = new UIManager();
    }

    return m_instance;
}

//Constructor
UIManager::UIManager(){
    //this->m_buttons = 0;
    //this->m_menus = 0;
    //this->m_callbacks = 0;
/*
    m_renderTexture = new sf::RenderTexture();

    if (!m_renderTexture->create(640, 480, true)){
        std::cout << "Error creando textura" << std::endl;
    }

//    const sf::Context* t_gameContext = sf::Context::getActiveContext();
//    m_gameContext = const_cast<sf::Context*>(t_gameContext);
//    std::cout << "Game Context: " << m_gameContext << std::endl;
//    
//    sf::Context t_context;
//    const sf::Context* t_SFMLContext = &t_context;
//    m_SFMLContext = const_cast<sf::Context*>(t_SFMLContext);
//    std::cout << "SFML Context: " << m_SFMLContext << std::endl;

    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    ////gluPerspective((GLdouble) 45.0, (GLdouble) 640/480, (GLdouble) 1.0, (GLdouble) 500.0);
    //glMatrixMode(GL_MODELVIEW);

    
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(100, 50));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(10, 20);
    m_renderTexture = new sf::RenderTexture();
    m_renderTexture->create(360, 480, true);
    m_renderTexture->draw(rectangle);
    m_renderTexture->display();
*/
}

//Destructor
UIManager::~UIManager(){}

//Updates the render target
void UIManager::update(){
    
}

//Displays the texture
void UIManager::render(){
/*
    //std::cout << "Context GAME: " <<m_gameContext << std::endl;
    //std::cout << "Context SFML: " <<m_SFMLContext << std::endl;
    //std::cout << "Context 1: " <<sf::Context::getActiveContext() << std::endl;
    //sf::Context* t_context = new sf::Context();
    //std::cout << "Context 2: " <<sf::Context::getActiveContext() << std::endl;
    //m_SFMLContext->setActive(true);

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);

    m_texture = &m_renderTexture->getTexture();
    sf::Texture::bind(m_texture);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (0, 1, 1, 0, -1, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(0.f, 1.f);
        glVertex2f(0.0f, 0.5f);
        glTexCoord2f(1.f, 1.f);
        glVertex2f(0.5f, 0.5f);
        glTexCoord2f(1.f, 0.f);
        glVertex2f(0.5f, 0.0f);
        glTexCoord2f(0.f, 0.f);
        glVertex2f(0.0f, 0.0f);
    glEnd();

    //delete t_context;
    //m_gameContext->setActive(true);
*/
}

//Starts a game
void UIManager::start(){

}

//Pauses the game
void UIManager::pause(){

}

//Shows a menu
void UIManager::showMenu(){

}

//Hides a menu
void UIManager::hideMenu(){

}