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

#include "../include/menu_screens/OnlineCreateScreen.hpp"

//Returns the only instance of this class
OnlineCreateScreen& OnlineCreateScreen::instance(){
    static OnlineCreateScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
OnlineCreateScreen::OnlineCreateScreen(MenuState* p_menu)
    : MenuScreen(p_menu){

    m_yourIP    = new sf::Sprite(*(m_menu->m_spritesheet));
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
OnlineCreateScreen::~OnlineCreateScreen(){
    std::cout << "~OnlineCreateScreen" << std::endl;
    if(m_yourIP){
        delete m_yourIP;
        m_yourIP = nullptr;
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
void OnlineCreateScreen::clipElements(){
    m_yourIP->setTextureRect(sf::IntRect(1280, 420, 640, 140));
    m_IPBox->setTextureRect(sf::IntRect(1280, 700, 640, 140));
}

//Sets the origin of transformation for each element
void OnlineCreateScreen::setElementsOrigins(){
    setOriginIndex(m_yourIP, 4);
    setOriginIndex(m_IPBox, 4);
    setOriginIndex(m_IP, 4);
}

//Places each element
void OnlineCreateScreen::placeElements(){
    m_yourIP->setPosition(getViewportWidth(0.5), getViewportHeight(0.333));
    m_IPBox->setPosition(getViewportWidth(0.5), getViewportHeight(0.666));
    m_IP->setPosition(m_IPBox->getPosition());
}

//Initializes the menu nodes
void OnlineCreateScreen::initializeNodes(){
    
}

//Draws to the screen
void OnlineCreateScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));

    m_menu->m_texture->draw(*m_yourIP);
    m_menu->m_texture->draw(*m_IPBox);
    m_menu->m_texture->draw(*m_IP);

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    m_menu->m_texture->display();
}










/* ****************************** ACTIONS ****************************** */
void OnlineCreateScreen::select(){
    save();
}