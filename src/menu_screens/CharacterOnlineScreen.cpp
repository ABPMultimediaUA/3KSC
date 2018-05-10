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

#include "../include/menu_screens/CharacterOnlineScreen.hpp"
#include "../include/Game.hpp"
#include <iostream>

#define k_playerNumber  4
// #define k_localPlayers  1

//Returns the only instance of this class
CharacterOnlineScreen& CharacterOnlineScreen::instance(){
    static CharacterOnlineScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
CharacterOnlineScreen::CharacterOnlineScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    
    m_game              = Game::getInstance();

    loadCharSpritesheet();

    m_names             = new sf::Text*[k_playerNumber];
    m_characters        = new sf::Sprite*[k_playerNumber];
    m_faces             = new sf::Sprite*[k_playerNumber];
    m_charactersBar     = new sf::Sprite(*m_charSpritesheet);
    m_tokens            = new sf::Sprite*[k_playerNumber];

    for (int i = 0; i < k_playerNumber; i++){
        m_names[i]       = new sf::Text("???", *(m_menu->m_font), 40);
        m_names[i]->setOutlineThickness(2);
        m_names[i]->setOutlineColor(sf::Color::White);

        if (i == 0){
            m_names[i]->setFillColor(sf::Color(209, 45, 58));
        }

        else{
            m_names[i]->setFillColor(sf::Color(98, 105, 112));
        }

        m_characters[i]  = new sf::Sprite(*m_charSpritesheet);
        m_faces[i]       = new sf::Sprite(*m_charSpritesheet);
        m_tokens[i]      = new sf::Sprite(*m_charSpritesheet);
    }

    clipElements();
    setElementsOrigins();
    placeElements();
    initializeNodes();

    m_prev              = Screen::Main;
    m_next              = Screen::Map;
    m_settingsScreen    = Screen::BattleSettings;

    createControlsBar(4);
}

//Destructor
CharacterOnlineScreen::~CharacterOnlineScreen(){
    std::cout << "~CharacterOnlineScreen" << std::endl;

    for (int i = 0; i < k_playerNumber; i++){
        if (m_names[i]){
            delete m_names[i];
            m_names[i] = nullptr;
        }

        if (m_characters[i]){
            delete m_characters[i];
            m_characters[i] = nullptr;
        }

        if (m_faces[i]){
            delete m_faces[i];
            m_faces[i] = nullptr;
        }

        if (m_tokens[i]){
            delete m_tokens[i];
            m_tokens[i] = nullptr;
        }
    }

    if(m_names){
        delete[] m_names;
        m_names = nullptr;
    }

    if(m_characters){
        delete[] m_characters;
        m_characters = nullptr;
    }

    if(m_faces){
        delete[] m_faces;
        m_faces = nullptr;
    }

    if(m_tokens){
        delete[] m_tokens;
        m_tokens = nullptr;
    }

    if (m_charactersBar){
        delete m_charactersBar;
        m_charactersBar = nullptr;
    }
}

//Loads the common spritesheet for all menu screens
void CharacterOnlineScreen::loadCharSpritesheet(){
    m_charSpritesheet = new sf::Texture();

    if (!m_charSpritesheet->loadFromFile("assets/UI/Spritesheet_characterMenu.png")){
        std::cerr << "Error loading characters spritesheet!" << std::endl;
    }
}

//Clips the texture for each element
void CharacterOnlineScreen::clipElements(){
    for (int i = 0; i < k_playerNumber; i++){
        if (i == 0){
            clipBackground(i, i);
            clipToken(i, i);
            clipFace(i, 6);
        }

        else{
            clipBackground(i, 4);
            clipFace(i, 7);
        }
    }

    m_charactersBar->setTextureRect(sf::IntRect(1000, 200, 896, 128));
}

//Sets the origin of transformation for each element
void CharacterOnlineScreen::setElementsOrigins(){
    for (int i = 0; i < k_playerNumber; i++){
        setOriginIndex(m_characters[i], 4);
        setOriginIndex(m_faces[i], 4);
        setOriginIndex(m_names[i], 1);
        setOriginIndex(m_tokens[i], 4);
    }

    setOriginIndex(m_charactersBar, 4);
}

//Places each element
void CharacterOnlineScreen::placeElements(){
    m_charactersBar->setPosition(getViewportWidth(0.5), getViewportHeight(0.75));

    for (int i = 0; i < k_playerNumber; i++){
        m_characters[i]->setPosition(getViewportWidth(1.0/8.0) * (2 * i + 1), getViewportHeight(3.0/8.0));
        m_names[i]->setPosition(m_characters[i]->getPosition());
        m_faces[i]->setPosition(m_characters[i]->getPosition());
        m_tokens[i]->setPosition(m_charactersBar->getPosition());

        m_tokens[i]->move(384, 0);
        m_names[i]->move(0, 120);
    }
}

//Initializes the menu nodes
void CharacterOnlineScreen::initializeNodes(){
    
}

//Handles the user inputs for the screen
void CharacterOnlineScreen::input(){
    MenuScreen::input();
}

//Updates the state of the screen
void CharacterOnlineScreen::update(){
    MenuScreen::update();
}

//Draws to the screen
void CharacterOnlineScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));

    m_menu->m_texture->draw(*m_charactersBar);

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    for (int i = 0; i < k_playerNumber; i++){
        m_menu->m_texture->draw(*m_names[i]);
        m_menu->m_texture->draw(*m_characters[i]);
        m_menu->m_texture->draw(*m_faces[i]);

        if (i == 0){
            m_menu->m_texture->draw(*m_tokens[i]);        
        }
    }

    m_menu->m_texture->display();
}









/* ****************************** ACTIONS ****************************** */
void CharacterOnlineScreen::select(){
    save();
}