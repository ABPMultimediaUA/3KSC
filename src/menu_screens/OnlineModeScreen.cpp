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

#include "../include/menu_screens/OnlineModeScreen.hpp"

//Returns the only instance of this class
OnlineModeScreen& OnlineModeScreen::instance(){
    static OnlineModeScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
OnlineModeScreen::OnlineModeScreen(MenuState* p_menu)
    : MenuScreen(p_menu){

    m_create    = new sf::Sprite(*(m_menu->m_spritesheet));
    m_join      = new sf::Sprite(*(m_menu->m_spritesheet));

    clipElements();
    setElementsOrigins();
    placeElements();
    initializeNodes();

    m_prev      = Screen::Main;

    createControlsBar(0);
}

//Destructor
OnlineModeScreen::~OnlineModeScreen(){
    std::cout << "~OnlineModeScreen" << std::endl;

    if (m_create){
        delete m_create;
        m_create = nullptr;
    }

    if (m_join){
        delete m_join;
        m_join = nullptr;
    }
}

//Clips the texture for each element
void OnlineModeScreen::clipElements(){
    m_create->setTextureRect(sf::IntRect(1280, 140, 640, 140));
    m_join->setTextureRect(sf::IntRect(1280, 280, 640, 140));
}

//Sets the origin of transformation for each element
void OnlineModeScreen::setElementsOrigins(){
    setOriginIndex(m_create, 4);
    setOriginIndex(m_join, 4);
}

//Places each element
void OnlineModeScreen::placeElements(){
    m_create->setPosition(getViewportWidth(0.5), getViewportHeight(0.5));
    m_join->setPosition(m_create->getPosition());

    m_create->move(0, -80);
    m_join->move(0, 80);
}

//Initializes the menu nodes
void OnlineModeScreen::initializeNodes(){
    m_createNode        = new MenuNode(Screen::OnlineCreate, m_create);
    m_joinNode          = new MenuNode(Screen::OnlineJoin, m_join);

    m_createNode->setDown(m_joinNode);
    m_joinNode->setDown(m_createNode);

    m_selectedNode = m_createNode;
    createSelectionRect();
}

//Draws to the screen
void OnlineModeScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));

    m_menu->m_texture->draw(*m_create);
    m_menu->m_texture->draw(*m_join);

    m_menu->m_texture->draw(*m_selectedRect);

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    m_menu->m_texture->display();
}