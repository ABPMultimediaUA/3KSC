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

#include "../include/menu_screens/OnlineJoinScreen.hpp"

//Returns the only instance of this class
OnlineJoinScreen& OnlineJoinScreen::instance(){
    static OnlineJoinScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
OnlineJoinScreen::OnlineJoinScreen(MenuState* p_menu)
    : MenuScreen(p_menu){

    m_enterIP   = new sf::Sprite(*(m_menu->m_spritesheet));
    m_IPBox     = new sf::Sprite(*(m_menu->m_spritesheet));
    m_IP        = new sf::Text("0.0.0.0", *(m_menu->m_font), 60);

    stylizeText(m_IP);

    clipElements();
    setElementsOrigins();
    placeElements();
    initializeNodes();

    m_prev      = Screen::OnlineMode;
    m_next      = Screen::CharacterOnline;

    createControlsBar(2);
}

//Destructor
OnlineJoinScreen::~OnlineJoinScreen(){
    std::cout << "~OnlineJoinScreen" << std::endl;

    if(m_enterIP){
        delete m_enterIP;
        m_enterIP = nullptr;
    }

    if(m_IPBox){
        delete m_IPBox;
        m_IPBox = nullptr;
    }
    
    if(m_IP){
        delete m_IP;
        m_IP = nullptr;
    }
}

//Clips the texture for each element
void OnlineJoinScreen::clipElements(){
    m_enterIP->setTextureRect(sf::IntRect(1280, 560, 640, 140));
    m_IPBox->setTextureRect(sf::IntRect(1280, 700, 640, 140));
}

//Sets the origin of transformation for each element
void OnlineJoinScreen::setElementsOrigins(){
    setOriginIndex(m_enterIP, 4);
    setOriginIndex(m_IPBox, 4);
    setOriginIndex(m_IP, 4);
}

//Places each element
void OnlineJoinScreen::placeElements(){
    m_enterIP->setPosition(getViewportWidth(0.5), getViewportHeight(0.333));
    m_IPBox->setPosition(getViewportWidth(0.5), getViewportHeight(0.666));
    m_IP->setPosition(m_IPBox->getPosition());
}

//Initializes the menu nodes
void OnlineJoinScreen::initializeNodes(){
    
}

//Draws to the screen
void OnlineJoinScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));

    m_menu->m_texture->draw(*m_enterIP);
    m_menu->m_texture->draw(*m_IPBox);
    m_menu->m_texture->draw(*m_IP);

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    m_menu->m_texture->display();
}










/* ****************************** ACTIONS ****************************** */
void OnlineJoinScreen::select(){
    save();
}