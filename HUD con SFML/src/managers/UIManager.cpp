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
#include <string> //For std::to_string()
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
    m_window = new sf::RenderWindow(sf::VideoMode(640, 480), "HUD 3KSC");
    m_window->setFramerateLimit(60);

    initializeHUDSprites();
    initializeHUDTexts();
}

//Destructor
UIManager::~UIManager(){}

void UIManager::initializeHUDSprites(){
    sf::Texture* t_texture = new sf::Texture();

    //Load texture
    if (!t_texture->loadFromFile("assets/UI/HUD/Spritesheet.png")){
        std::cerr << "Error loading HUD sprites" << std::endl;
    }

    //Create sprites from texture
    m_magicBarBackground    = new sf::Sprite(*t_texture);
    m_magicBarForeground    = new sf::Sprite(*t_texture);
    m_player                = new sf::Sprite(*t_texture); 

    //Clip specific sections
    m_magicBarBackground->setTextureRect(sf::IntRect(0, 0, 256, 256));
    m_magicBarForeground->setTextureRect(sf::IntRect(385, (128 - 15), 1, (10 + 68 + 15)));
    m_player->setTextureRect(sf::IntRect(0, 256, 256, 256));

    //Place transformation origin at center of sprites
    m_magicBarBackground->setOrigin(m_magicBarBackground->getGlobalBounds().width / 2, m_magicBarBackground->getGlobalBounds().height / 2);
    m_player->setOrigin(m_player->getGlobalBounds().width / 2, m_player->getGlobalBounds().height / 2);

    //Place sprites
    m_magicBarBackground->setPosition(m_window->getSize().x / 2, m_window->getSize().y / 2);
    m_magicBarForeground->setPosition(m_magicBarBackground->getPosition().x, m_magicBarBackground->getPosition().y - 15);
    m_player->setPosition(m_magicBarBackground->getPosition().x, m_magicBarBackground->getPosition().y);

    //Initial rotation for magic bar
    m_magicBarForeground->rotate(-135);
    m_magicBarFragments = 579;
}


void UIManager::initializeHUDTexts(){
    sf::Font* t_font = new sf::Font;

    //Load font
    if (!t_font->loadFromFile("assets/fonts/Ubuntu-R.ttf")){
        std::cerr << "Error loading HUD font" << std::endl;
    }

    //Create texts
    m_life = new sf::Text("100%", *t_font, 35);
    m_lifeShield = new sf::Text("0%", *t_font, 23);
    m_magic = new sf::Text("100%", *t_font, 23);

    //Color texts
    m_life->setFillColor(sf::Color::White);
    m_lifeShield->setFillColor(sf::Color(118,255,3));
    m_magic->setFillColor(sf::Color(41,79,254));

    //Make an outline for texts
    m_life->setOutlineThickness(2);
    m_lifeShield->setOutlineThickness(2);
    m_magic->setOutlineThickness(2);

    m_life->setOutlineColor(sf::Color::Black);
    m_lifeShield->setOutlineColor(sf::Color::Black);
    m_magic->setOutlineColor(sf::Color::Black);

    //Place transformation origin at center of texts
    m_life->setOrigin(m_life->getGlobalBounds().width / 2, m_life->getGlobalBounds().height / 2);
    m_lifeShield->setOrigin(m_lifeShield->getGlobalBounds().width / 2, m_lifeShield->getGlobalBounds().height / 2);
    m_magic->setOrigin(m_magic->getGlobalBounds().width / 2, m_magic->getGlobalBounds().height / 2);

    //Place texts in their positions (relative to magic circular bar)
    m_life->setPosition(m_magicBarBackground->getPosition().x, m_magicBarBackground->getPosition().y);
    m_lifeShield->setPosition(m_life->getPosition().x, m_life->getPosition().y + 15);
    m_magic->setPosition(m_life->getPosition().x, m_life->getPosition().y + 45);
}

//Updates the UI
void UIManager::update(){
    
}

//Displays the UI
void UIManager::render(){
    m_window->clear(sf::Color(79,195,247));
    
    m_window->draw(*m_magicBarBackground);

    //Magic bar
    for (int i = 0; i < m_magicBarFragments; i++){
        m_window->draw(*m_magicBarForeground);
        m_magicBarForeground->rotate(270.0 / 579.0);
    
        if (i == m_magicBarFragments - 1){
            m_magicBarForeground->setRotation(-135);
        }
    }

    m_window->draw(*m_player);

    m_window->draw(*m_life);

    //Hide life shield at 0%
    if (m_lifeShield->getString() != "0%"){
        m_window->draw(*m_lifeShield);
    }

    m_window->draw(*m_magic);

    m_window->display();
}

//Changes the HP of a player in the screen
void UIManager::setLife(int p_life){
    m_life->setString(std::to_string(p_life) + "%");
    m_life->setOrigin(m_life->getGlobalBounds().width / 2, m_life->getGlobalBounds().height / 2);
    m_life->setPosition(m_magicBarBackground->getPosition().x, m_magicBarBackground->getPosition().y);

    //Change face
    if (p_life >= 30){
        m_player->setTextureRect(sf::IntRect(0, 256, 256, 256));
    }

    else{
        m_player->setTextureRect(sf::IntRect(256, 256, 256, 256));
    }
}

//Changes the life shield of a player in the screen
void UIManager::setLifeShield(int p_lifeShield){
    m_lifeShield->setString(std::to_string(p_lifeShield) + "%");
    m_lifeShield->setOrigin(m_lifeShield->getGlobalBounds().width / 2, m_lifeShield->getGlobalBounds().height / 2);
    m_lifeShield->setPosition(m_life->getPosition().x, m_life->getPosition().y + 15);
}

//Changes the MP of a player in the screen
void UIManager::setMagic(int p_magic){
    //Magic counter
    m_magic->setString(std::to_string(p_magic) + "%");
    m_magic->setOrigin(m_magic->getGlobalBounds().width / 2, m_magic->getGlobalBounds().height / 2);
    m_magic->setPosition(m_life->getPosition().x, m_life->getPosition().y + 45);

    //Magic bar
    m_magicBarFragments = (int) (p_magic * 579) / 100;
}


//Returns a pointer to game window
sf::RenderWindow* UIManager::getWindow(){
    return m_window;
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