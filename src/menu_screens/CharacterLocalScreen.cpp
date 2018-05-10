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

#include "../include/menu_screens/CharacterLocalScreen.hpp"

#include "../include/managers/InputManager.hpp"
#include "../include/Game.hpp"
#include "../include/menu_screens/CharSelectNodes.hpp"
#include <iostream>

#define k_characters    7
#define k_players       4

//Returns the only instance of this class
CharacterLocalScreen& CharacterLocalScreen::instance(){
    static CharacterLocalScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
CharacterLocalScreen::CharacterLocalScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    
    m_game              = Game::getInstance();

    loadCharSpritesheet();

    m_localPlayers = m_inputManager->getDeviceCount();

    m_backgrounds       = new sf::Sprite*[k_players];
    m_faces             = new sf::Sprite*[k_players];
    m_checkboxes        = new sf::Sprite*[k_players];
    m_names             = new sf::Text*[k_players];
    m_tokens            = new sf::Sprite*[k_players];

    for (int i = 0; i < k_players; i++){
        m_backgrounds[i]    = new sf::Sprite(*m_charSpritesheet);
        m_faces[i]          = new sf::Sprite(*m_charSpritesheet);
        m_checkboxes[i]     = new sf::Sprite(*m_charSpritesheet);

        m_names[i] = new sf::Text("???", *(m_menu->m_font), 40);
        stylizeText(m_names[i], sf::Color(98, 105, 112));
        // m_names[i]->setOutlineThickness(2);
        // m_names[i]->setOutlineColor(sf::Color::White);
        // m_names[i]->setFillColor(sf::Color(98, 105, 112));

        m_tokens[i]         = new sf::Sprite(*m_charSpritesheet);
    }

    //Characters bar
    m_charactersBar = new sf::Sprite*[k_characters];

    for (int i = 0; i < k_characters; i++){
        m_charactersBar[i] = new sf::Sprite(*m_charSpritesheet);
    }

    //Cursors
    m_cursors = new sf::Sprite*[m_localPlayers];

    for (int i = 0; i < m_localPlayers; i++){
        m_cursors[i]    = new sf::Sprite(*m_charSpritesheet);
    }
    

    clipElements();
    setElementsOrigins();
    placeElements();
    initializeNodes();

    m_prev              = Screen::Main;
    m_next              = Screen::Map;
    m_settingsScreen    = Screen::BattleSettings;

    createControlsBar(3);

    //Enable characters
    for (int i = 0; i < k_players; i++){
        chooseCharacter(i, 6);
    }
}

//Destructor
CharacterLocalScreen::~CharacterLocalScreen(){
    std::cout << "~CharacterLocalScreen" << std::endl;

    for (int i = 0; i < k_players; i++){
        if (m_names[i])         { delete m_names[i];        m_names[i] = nullptr;       }
        if (m_backgrounds[i])   { delete m_backgrounds[i];  m_backgrounds[i] = nullptr; }
        if (m_faces[i])         { delete m_faces[i];        m_faces[i] = nullptr;       }
        if (m_checkboxes[i])    { delete m_checkboxes[i];   m_checkboxes[i] = nullptr;  }
        if (m_tokens[i])        { delete m_tokens[i];       m_tokens[i] = nullptr;      }
    }

    if (m_names)        { delete[] m_names;         m_names = nullptr;          }
    if (m_backgrounds)  { delete[] m_backgrounds;   m_backgrounds = nullptr;    }
    if (m_faces)        { delete[] m_faces;         m_faces = nullptr;          }
    if (m_checkboxes)   { delete[] m_checkboxes;    m_checkboxes = nullptr;     }
    if (m_tokens)       { delete[] m_tokens;        m_tokens = nullptr;     }

    for (int i = 0; i < 7; i++){
        if (m_charactersBar[i]) { delete m_charactersBar[i];    m_charactersBar[i] = nullptr;   }
    }

    if (m_charactersBar)    { delete[] m_charactersBar; m_charactersBar = nullptr;  }

    for (int i = 0; i < m_localPlayers; i++){
        if (m_cursors[i])   { delete m_cursors[i];  m_cursors[i] = nullptr; }
    }

    if (m_cursors)          { delete[] m_cursors;       m_cursors = nullptr;            }
    if (m_charSpritesheet)  { delete m_charSpritesheet; m_charSpritesheet = nullptr;    }
}

//Loads the common spritesheet for all menu screens
void CharacterLocalScreen::loadCharSpritesheet(){
    m_charSpritesheet = new sf::Texture();

    if (!m_charSpritesheet->loadFromFile("assets/UI/Spritesheet_characterMenu.png")){
        std::cerr << "Error loading characters spritesheet!" << std::endl;
    }
}

//Chooses a character for a player
void CharacterLocalScreen::chooseCharacter(int p_player, int p_character){
    if (p_character != -1){
        enablePlayer(p_player, (m_tokenNodes[p_player].m_player != 4));
        clipFace(p_player, p_character);
        m_names[p_player]->setString(m_charNodes[p_character].m_name);
        
        //Re-center text
        setOriginIndex(m_names[p_player], 1);
        sf::Vector2f t_pos = m_backgrounds[p_player]->getPosition();
        m_names[p_player]->setPosition(t_pos.x, t_pos.y + 120);
    }

    else{
        disablePlayer(p_player);
    }
}

//Enables a player
void CharacterLocalScreen::enablePlayer(int p_player, bool p_playable){
    m_checkboxes[p_player]->setTextureRect(sf::IntRect(1800, 0, 200, 200));

    if (p_playable){
        clipBackground(p_player, p_player);

        switch (p_player){
            case 0: { m_names[p_player]->setFillColor(sf::Color(209, 45, 58));      break; }
            case 1: { m_names[p_player]->setFillColor(sf::Color(64, 172, 215));     break; }
            case 2: { m_names[p_player]->setFillColor(sf::Color(255, 231, 61));     break; }
            case 3: { m_names[p_player]->setFillColor(sf::Color(138, 217, 79));     break; } 
        }
    }

    else{
        clipBackground(p_player, 4);
        m_names[p_player]->setFillColor(sf::Color(98, 105, 112));
    }

    m_enabledPlayers[p_player] = true;
    m_game->setPlayerEnabled(p_player);
}

//Disables a player
void CharacterLocalScreen::disablePlayer(int p_player){
    m_checkboxes[p_player]->setTextureRect(sf::IntRect(1600, 0, 200, 200));
    clipBackground(p_player, 4);
    m_faces[p_player]->setTextureRect(sf::IntRect(1000, 328, 200, 200));
    m_names[p_player]->setString("");

    m_enabledPlayers[p_player] = false;
    m_game->setPlayerEnabled(p_player, false);
}

//Clips the texture for each element
void CharacterLocalScreen::clipElements(){
    for (int i = 0; i < k_players; i++){
        clipBackground(i, 4);
        i < m_localPlayers ? clipToken(i, i) : clipToken(i, 4);
        m_faces[i]->setTextureRect(sf::IntRect(1000, 328, 200, 200));
        m_checkboxes[i]->setTextureRect(sf::IntRect(1600, 0, 200, 200));
    }

    for (int i = 0; i < k_characters; i++){
        m_charactersBar[i]->setTextureRect(sf::IntRect(1000 + (128 * i), 200, 128, 128));
    }

    //Cursors
    for (int i = 0; i < m_localPlayers; i++){
        m_cursors[i]->setTextureRect(sf::IntRect(64 * (i + 5), 400, 64, 64));
    }
}

//Sets the origin of transformation for each element
void CharacterLocalScreen::setElementsOrigins(){
    for (int i = 0; i < k_players; i++){
        setOriginIndex(m_backgrounds[i], 4);
        setOriginIndex(m_faces[i], 4);
        setOriginIndex(m_checkboxes[i], 8);
        setOriginIndex(m_names[i], 1);
        setOriginIndex(m_tokens[i], 4);
    }

    for (int i = 0; i < k_characters; i++){
        setOriginIndex(m_charactersBar[i], 4);
    }
}

//Places each element
void CharacterLocalScreen::placeElements(){
    for (int i = 0; i < k_characters; i++){
        m_charactersBar[i]->setPosition(getViewportWidth(0.5), getViewportHeight(0.75));
        m_charactersBar[i]->move(128 * (i - 3) , 0);
    }

    for (int i = 0; i < k_players; i++){
        m_backgrounds[i]->setPosition(getViewportWidth(1.0/8.0) * (2 * i + 1), getViewportHeight(3.0/8.0));
        m_checkboxes[i]->setPosition(m_backgrounds[i]->getPosition());
        m_faces[i]->setPosition(m_backgrounds[i]->getPosition());
        m_names[i]->setPosition(m_backgrounds[i]->getPosition());
        m_tokens[i]->setPosition(m_charactersBar[6]->getPosition());

        m_checkboxes[i]->move(112, -35);
        m_names[i]->move(0, 120);
        m_tokens[i]->move((i % 2 == 0 ? -32 : 32), (i / 2 == 0 ? -32 : 32));
    }

    for (int i = 0; i < m_localPlayers; i++){
        m_cursors[i]->setPosition(getViewportWidth(0.25 * i + 0.125), getViewportHeight(0.5));
    }
}

//Initializes the menu nodes
void CharacterLocalScreen::initializeNodes(){
    //CharBarNodes
    for (int i = 0; i < k_characters; i++){
        m_charNodes.push_back(CharBarNode(m_charactersBar[i]));

        //Use loop for TokenNodes and CursorNodes, too
        if (i < k_players){
            m_tokenNodes.push_back(TokenNode(m_tokens[i], (i < m_localPlayers ? i : 4)));

            if (i < m_localPlayers){
                m_cursorNodes.push_back(CursorNode(m_cursors[i]));
            }
        }
    }
}

//Handles the user inputs for the screen
void CharacterLocalScreen::input(){
    //Call to default input for navigation purposes
    MenuScreen::input();

    for (CursorNode& t_cursor : m_cursorNodes){
        if (t_cursor.input()){
            for (TokenNode& t_token : m_tokenNodes){
                if (t_token.m_player == t_cursor.m_id || t_token.m_player == 4){                    
                    t_token.beginDrag(&t_cursor);
                }
            }
        }

        else{
            if (t_cursor.m_dragging){
                t_cursor.m_dragging->endDrag();
            }
        }
    }
}

//Updates the state of the screen
void CharacterLocalScreen::update(){
    //Call to default update for navigation purposes
    MenuScreen::update();

    bool t_found = false;

    for(TokenNode& t_token : m_tokenNodes){
        if (t_token.drag()){
            t_found = false;

            for (CharBarNode& t_character : m_charNodes){
                if (t_character.isTokenHere(&t_token)){
                    chooseCharacter(t_token.m_id, t_character.m_id);
                    t_found = true;
                    break;
                }
            }

            if (!t_found){
                chooseCharacter(t_token.m_id, -1);
            }
        }
    }
}

//Draws to the screen
void CharacterLocalScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));

    for (int i = 0; i < k_characters; i++){
        m_menu->m_texture->draw(*m_charactersBar[i]);
    }

    for (int i = 0; i < k_players; i++){
        m_menu->m_texture->draw(*m_names[i]);
        m_menu->m_texture->draw(*m_backgrounds[i]);
        m_menu->m_texture->draw(*m_faces[i]);
        m_menu->m_texture->draw(*m_checkboxes[i]);
    }

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    for (int i = 0; i < k_players; i++){
        m_menu->m_texture->draw(*m_tokens[i]);
    }

    for (int i = 0; i < m_localPlayers; i++){
        m_menu->m_texture->draw(*m_cursors[i]);
    }

    m_menu->m_texture->display();
}










/* ****************************** ACTIONS ****************************** */
void CharacterLocalScreen::select(){
    save();
}

//Create override save method (don't save until everyone chooses)