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

#include "../include/menu_screens/MapScreen.hpp"

//Returns the only instance of this class
MapScreen& MapScreen::instance(){
    static MapScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
MapScreen::MapScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    
    m_Fusfus        = new sf::Sprite(*(m_menu->m_spritesheet));
    m_Sakura        = new sf::Sprite(*(m_menu->m_spritesheet));
    m_Kawaiisaki    = new sf::Sprite(*(m_menu->m_spritesheet));

    clipElements();
    setElementsOrigins();
    placeElements();
    initializeNodes();

    m_prev          = Screen::CharacterLocal;
    m_next          = Screen::Undefined;

    createControlsBar(2);
}

//Destructor
MapScreen::~MapScreen(){
    std::cout << "~MapScreen" << std::endl;
    if (m_Fusfus){
        delete m_Fusfus;
        m_Fusfus = nullptr;
    }

    if (m_Sakura){
        delete m_Sakura;
        m_Sakura = nullptr;
    }

    if (m_Kawaiisaki){
        delete m_Kawaiisaki;
        m_Kawaiisaki = nullptr;
    }
}

//Clips the texture for each element
void MapScreen::clipElements(){
    m_Fusfus->setTextureRect(sf::IntRect(1280, 840, 640, 140));
    m_Sakura->setTextureRect(sf::IntRect(1280, 980, 640, 140));
    m_Kawaiisaki->setTextureRect(sf::IntRect(1280, 1120, 640, 140));
}

//Sets the origin of transformation for each element
void MapScreen::setElementsOrigins(){
    setOriginIndex(m_Fusfus, 4);
    setOriginIndex(m_Sakura, 4);
    setOriginIndex(m_Kawaiisaki, 4);
}

//Places each element
void MapScreen::placeElements(){
    m_Fusfus->setPosition(getViewportWidth(0.5), getViewportHeight(0.5) + 70);
    m_Sakura->setPosition(m_Fusfus->getPosition());
    m_Kawaiisaki->setPosition(m_Fusfus->getPosition());

    m_Fusfus->move(0, -150);
    m_Kawaiisaki->move(0, 150);
}

//Initializes the menu nodes
void MapScreen::initializeNodes(){
    m_FusfusNode        = new MenuNode(Screen::Undefined, m_Fusfus);
    m_SakuraNode        = new MenuNode(Screen::Undefined, m_Sakura);
    m_KawaiisakiNode    = new MenuNode(Screen::Undefined, m_Kawaiisaki);

    m_FusfusNode->setDown(m_SakuraNode);
    m_SakuraNode->setDown(m_KawaiisakiNode);
    m_KawaiisakiNode->setDown(m_FusfusNode);

    m_selectedNode = m_FusfusNode;
    createSelectionRect();
}

//Draws to the screen
void MapScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));

    m_menu->m_texture->draw(*m_Fusfus);
    m_menu->m_texture->draw(*m_Sakura);
    m_menu->m_texture->draw(*m_Kawaiisaki);

    m_menu->m_texture->draw(*m_selectedRect);

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    m_menu->m_texture->display();
}