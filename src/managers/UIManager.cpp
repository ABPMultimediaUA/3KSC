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

#include "../include/managers/UIManager.hpp"
#include "../include/managers/EngineManager.hpp"
#include <string> //For std::to_string()
#include <iostream>

//Returns the only instance of this class
UIManager& UIManager::instance(){
    static UIManager instance;
    return instance;
}

//Constructor
UIManager::UIManager(){
    m_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "3KSC");
    m_players = 4;
    m_playersLives = new int[m_players];
    
    for (int i = 0; i < m_players; i++){
        m_playersLives[i] = 3;
    }
    
    initializeHUD();
}

//Destructor
UIManager::~UIManager(){}

void UIManager::initializeHUD(){
    sf::Texture* t_texture = new sf::Texture();
    sf::Font* t_font = new sf::Font;

    //Load texture
    if (!t_texture->loadFromFile("assets/UI/HUD/Spritesheet.png")){
        std::cerr << "Error loading HUD sprites" << std::endl;
    }

    //Load font
    if (!t_font->loadFromFile("assets/fonts/Ubuntu-R.ttf")){
        std::cerr << "Error loading HUD font" << std::endl;
    }


    //Initialize arrays
    m_faces             = new sf::Sprite*[m_players];
    m_names             = new sf::Sprite*[m_players];
    m_lives             = new sf::CircleShape**[m_players];
    m_barsBG            = new sf::RectangleShape*[m_players*2];
    m_HPBarsFG          = new sf::RectangleShape*[m_players];
    m_HPShieldBarsFG    = new sf::RectangleShape*[m_players];
    m_MPBarsFG          = new sf::RectangleShape*[m_players];
    m_barTexts          = new sf::Text*[m_players*2];

    int t_character;
    
    for (int i = 0; i < m_players; i++){
        //Initialize sprites, shapes and texts
        m_faces[i]              = new sf::Sprite(*t_texture);
        m_names[i]              = new sf::Sprite(*t_texture); 
        m_lives[i]              = new sf::CircleShape*[m_playersLives[i]];
        m_barsBG[i]             = new sf::RectangleShape(sf::Vector2f(150, 16));
        m_barsBG[i+m_players]   = new sf::RectangleShape(sf::Vector2f(150, 16));
        m_HPBarsFG[i]           = new sf::RectangleShape(sf::Vector2f(150, 16));
        m_HPShieldBarsFG[i]     = new sf::RectangleShape(sf::Vector2f(0, 16));
        m_MPBarsFG[i]           = new sf::RectangleShape(sf::Vector2f(150, 16));
        m_barTexts[i]           = new sf::Text("100/100", *t_font, 12);
        m_barTexts[i+m_players] = new sf::Text("100/100", *t_font, 12);

        //Clip sprites
        if      (i == 0)    t_character = 0;
        else if (i == 1)    t_character = 4;
        else if (i == 2)    t_character = 3;
        else if (i == 3)    t_character = 1;

        clipFace(i, t_character, 0);
        clipName(i, t_character, 0);

        //Color shapes and texts
        m_barsBG[i]->setFillColor(sf::Color(98, 105, 112));
        m_barsBG[i+m_players]->setFillColor(sf::Color(98, 105, 112));
        m_HPBarsFG[i]->setFillColor(sf::Color(138, 217, 79));
        m_HPShieldBarsFG[i]->setFillColor(sf::Color(108, 177, 169));
        m_MPBarsFG[i]->setFillColor(sf::Color(64, 172, 215));
        m_barTexts[i]->setFillColor(sf::Color::Black);
        m_barTexts[i+m_players]->setFillColor(sf::Color::Black);

        //Place transformation origins
        //Center
        m_faces[i]->setOrigin(m_faces[i]->getGlobalBounds().width / 2, m_faces[i]->getGlobalBounds().height / 2);
        m_names[i]->setOrigin(m_names[i]->getGlobalBounds().width / 2, m_names[i]->getGlobalBounds().height / 2);
        m_barTexts[i]->setOrigin(m_barTexts[i]->getGlobalBounds().width / 2, m_barTexts[i]->getGlobalBounds().height / 2);
        m_barTexts[i+m_players]->setOrigin(m_barTexts[i+m_players]->getGlobalBounds().width / 2, m_barTexts[i+m_players]->getGlobalBounds().height / 2);

        //Left-center
        m_barsBG[i]->setOrigin(0, m_barsBG[i]->getGlobalBounds().height / 2);
        m_barsBG[i+m_players]->setOrigin(0, m_barsBG[i+m_players]->getGlobalBounds().height / 2);
        m_HPBarsFG[i]->setOrigin(0, m_HPBarsFG[i]->getGlobalBounds().height / 2);
        m_HPShieldBarsFG[i]->setOrigin(0, m_HPShieldBarsFG[i]->getGlobalBounds().height / 2);
        m_MPBarsFG[i]->setOrigin(0, m_MPBarsFG[i]->getGlobalBounds().height / 2);

        //Place elements (relative to faces)
        m_faces[i]->setPosition(14 + 64 + (320 * i), m_window->getSize().y - 128);
        m_names[i]->setPosition(m_faces[i]->getPosition().x, m_faces[i]->getPosition().y + 64 + 16);
        m_barsBG[i]->setPosition(m_faces[i]->getPosition().x + 64, m_faces[i]->getPosition().y);
        m_barsBG[i+m_players]->setPosition(m_faces[i]->getPosition().x + 64, m_faces[i]->getPosition().y + 32);
        m_HPBarsFG[i]->setPosition(m_barsBG[i]->getPosition());
        m_HPShieldBarsFG[i]->setPosition(m_barsBG[i]->getPosition());
        m_MPBarsFG[i]->setPosition(m_barsBG[i+m_players]->getPosition());
        m_barTexts[i]->setPosition(m_HPBarsFG[i]->getPosition().x + 75, m_HPBarsFG[i]->getPosition().y);
        m_barTexts[i+m_players]->setPosition(m_MPBarsFG[i]->getPosition().x + 75, m_MPBarsFG[i]->getPosition().y);

        //Lives
        for (int j = 0; j < m_playersLives[i]; j++){
            m_lives[i][j] = new sf::CircleShape(8);
            m_lives[i][j]->setFillColor(sf::Color(108, 177, 169));
            m_lives[i][j]->setOrigin(0, m_lives[i][j]->getGlobalBounds().height / 2);
            m_lives[i][j]->setPosition(m_faces[i]->getPosition().x + 64, m_faces[i]->getPosition().y - 32);
            m_lives[i][j]->move(20 * j, 0);
        }
    }

    //Selected player rectangle
    m_selected = new sf::RectangleShape(sf::Vector2f(128+150+6, 128+32));
    m_selected->setFillColor(sf::Color::Transparent);
    m_selected->setOutlineThickness(3);
    m_selected->setOutlineColor(sf::Color(209, 45, 58));
    m_selected->setPosition(m_faces[0]->getPosition());
    m_selected->move(-64, -64);
}


//Clips the specified variant of a character's face
void UIManager::clipFace(int p_player, int p_face, int p_variant){
    m_faces[p_player]->setTextureRect(sf::IntRect(128 * p_face, 128 * p_variant, 128, 128));
}

//Clips the specified variant of a character's face (no face change)
void UIManager::clipFace(int p_player, int p_variant){
    m_faces[p_player]->setTextureRect(sf::IntRect(m_faces[p_player]->getTextureRect().left, 128 * p_variant, 128, 128));
}

//Clips the specified variant of a character's name
void UIManager::clipName(int p_player, int p_name, int p_variant){
    m_names[p_player]->setTextureRect(sf::IntRect(128 * p_name, 64 * (p_variant + 4), 128, 64));
}

//Clips the specified variant of a character's face (no face change)
void UIManager::clipName(int p_player, int p_variant){
    m_faces[p_player]->setTextureRect(sf::IntRect(m_names[p_player]->getTextureRect().left, 128 * p_variant, 128, 128));
}

//Sets the number of lives the specified player has left
void UIManager::setLives(int p_player, int p_lives){
    m_playersLives[p_player] = p_lives;
}

//Changes the HP of a player in the screen
void UIManager::setHP(int p_player, int p_HP){
    m_HPBarsFG[p_player]->setSize(sf::Vector2f((p_HP * 150) / 100, 16));

    //Red HP bar and hurt face
    if (p_HP <= 30){
        m_HPBarsFG[p_player]->setFillColor(sf::Color(209, 45, 58));
        clipFace(p_player, 1);
    }

    //Green HP bar and normal face
    else{
        m_HPBarsFG[p_player]->setFillColor(sf::Color(138, 217, 79));
        clipFace(p_player, 0);
    }

    m_barTexts[p_player]->setString(std::to_string(p_HP) + "/100");
}

//Changes the HP shield of a player in the screen
void UIManager::setHPShield(int p_player, int p_HPShield){

}

//Changes the MP of a player in the screen
void UIManager::setMP(int p_player, int p_MP){
    m_MPBarsFG[p_player]->setSize(sf::Vector2f((p_MP * 150) / 100, 16));
    m_barTexts[p_player+m_players]->setString(std::to_string(p_MP) + "/100");
}

//Puts a rectangle arround selected player
void UIManager::selectPlayer(int p_player){
    m_selected->setPosition(14 + (320 * p_player), m_selected->getPosition().y);
}

//Updates the UI
void UIManager::update(){
    
}

//Displays the UI
void UIManager::render(){
    m_window->clear(sf::Color(79,195,247));

    for (int i = 0; i < m_players; i++){
        m_window->draw(*m_faces[i]);
        m_window->draw(*m_names[i]);

        //Draw multiple lives
        for (int j = 0; j < m_playersLives[i]; j++){
            m_window->draw(*m_lives[i][j]);
        }
        
        m_window->draw(*m_barsBG[i]);
        m_window->draw(*m_barsBG[i+m_players]);
        m_window->draw(*m_HPBarsFG[i]);
        m_window->draw(*m_HPShieldBarsFG[i]);
        m_window->draw(*m_MPBarsFG[i]);
        m_window->draw(*m_barTexts[i]);
        m_window->draw(*m_barTexts[i+m_players]);
    }

    m_window->draw(*m_selected);

    m_window->display();
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