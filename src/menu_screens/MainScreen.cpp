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

#include "../include/menu_screens/MainScreen.hpp"
#include <iostream>

//Returns the only instance of this class
MainScreen& MainScreen::instance(){
    static MainScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
MainScreen::MainScreen(MenuState* p_menu)
    : MenuScreen(p_menu){

    m_title         = new sf::Sprite(*(m_menu->m_spritesheet));
    m_settings      = new sf::Sprite(*(m_menu->m_spritesheet));
    m_playLocal     = new sf::Sprite(*(m_menu->m_spritesheet));
    m_playOnline    = new sf::Sprite(*(m_menu->m_spritesheet));
    m_quit          = new sf::Sprite(*(m_menu->m_spritesheet));

    clipElements();
    setElementsOrigins();
    placeElements();
    initializeNodes();

    m_settingsScreen = Screen::GameSettings;

    createControlsBar(1);
}

//Destructor
MainScreen::~MainScreen(){
    std::cout << "~MainScreen" << std::endl;
    if(m_playLocalNode){
        delete m_playLocalNode;
        m_playLocalNode = nullptr;
    }

    if(m_playOnlineNode){
        delete m_playOnlineNode;
        m_playOnlineNode = nullptr;
    }

    if(m_quitNode){
        delete m_quitNode;
        m_quitNode = nullptr;
    }

    if(m_title){
        delete m_title;
        m_title = nullptr;
    }

    if(m_settings){
        delete m_settings;
        m_settings = nullptr;
    }

    if(m_playLocal){
        delete m_playLocal;
        m_playLocal = nullptr;
    }

    if(m_playOnline){
        delete m_playOnline;
        m_playOnline = nullptr;
    }

    if(m_quit){
        delete m_quit;
        m_quit = nullptr;
    }
}

//Clips the texture for each element
void MainScreen::clipElements(){
    m_title->setTextureRect(sf::IntRect(0, 0, 640, 140));
    m_settings->setTextureRect(sf::IntRect(1920, 0, 128, 128));
    m_playLocal->setTextureRect(sf::IntRect(0, 140, 1280, 140));
    m_playOnline->setTextureRect(sf::IntRect(0, 280, 1280, 140));
    m_quit->setTextureRect(sf::IntRect(0, 420, 1280, 140));
}

//Sets the origin of transformation for each element
void MainScreen::setElementsOrigins(){
    setOriginIndex(m_playLocal, 4);
    setOriginIndex(m_playOnline, 4);
    setOriginIndex(m_quit, 4);
}

//Places each element
void MainScreen::placeElements(){
    m_title->setPosition(0, 0);
    m_settings->setPosition(getViewportWidth() - 128, 0);
    m_playLocal->setPosition(getViewportWidth(0.5), getViewportHeight(0.5));
    m_playOnline->setPosition(m_playLocal->getPosition());
    m_quit->setPosition(m_playLocal->getPosition());
}

//Initializes the menu nodes
void MainScreen::initializeNodes(){
    m_playLocalNode     = new MenuNode(Screen::CharacterLocal, m_playLocal);
    m_playOnlineNode    = new MenuNode(Screen::OnlineMode, m_playOnline);
    m_quitNode          = new MenuNode(Screen::Undefined, m_quit);

    m_playLocalNode->setRight(m_playOnlineNode);
    m_playOnlineNode->setRight(m_quitNode);
    m_quitNode->setRight(m_playLocalNode);

    m_selectedNode = m_playLocalNode;
}

//Draws to the screen
void MainScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));
    m_menu->m_texture->draw(*m_title);
    m_menu->m_texture->draw(*m_settings);
    m_menu->m_texture->draw(*(m_selectedNode->element));

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    m_menu->m_texture->display();
}