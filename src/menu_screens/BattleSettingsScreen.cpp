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

#include "../include/menu_screens/BattleSettingsScreen.hpp"
#include "../include/Game.hpp"
#include <string> //For std::to_string()

//Returns the only instance of this class
BattleSettingsScreen& BattleSettingsScreen::instance(){
    static BattleSettingsScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
BattleSettingsScreen::BattleSettingsScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
        
    m_game              = Game::getInstance();

    m_rounds            = new sf::Sprite(*(m_menu->m_spritesheet));
    m_lives             = new sf::Sprite(*(m_menu->m_spritesheet));
    m_timeLimit         = new sf::Sprite(*(m_menu->m_spritesheet));

    m_roundsText        = new sf::Text(std::to_string(m_game->getRounds()), *(m_menu->m_font), 40);
    m_livesText         = new sf::Text(std::to_string(m_game->getLives()), *(m_menu->m_font), 40);
    m_timeLimitText     = new sf::Text((m_game->getTimeLimit() == -1 ? "Ilimitado" : std::to_string(m_game->getTimeLimit())), *(m_menu->m_font), 40);

    clipElements();
    setElementsOrigins();
    placeElements();
    initializeNodes();

    m_prev              = Screen::CharacterLocal;
    m_next              = Screen::CharacterLocal;

    createControlsBar(2);
}

//Destructor
BattleSettingsScreen::~BattleSettingsScreen(){
    std::cout << "~BattleSettingsScreen" << std::endl;
    
    if (m_rounds){
        delete m_rounds;
        m_rounds = nullptr;
    }

    if (m_lives){
        delete m_lives;
        m_lives = nullptr;
    }

    if (m_timeLimit){
        delete m_timeLimit;
        m_timeLimit = nullptr;
    }

    if (m_roundsText){
        delete m_roundsText;
        m_roundsText = nullptr;
    }

    if (m_livesText){
        delete m_livesText;
        m_livesText = nullptr;
    }

    if (m_timeLimitText){
        delete m_timeLimitText;
        m_timeLimitText = nullptr;
    }
}

//Clips the texture for each element
void BattleSettingsScreen::clipElements(){
    m_rounds->setTextureRect(sf::IntRect(0, 960, 1120, 80));
    m_lives->setTextureRect(sf::IntRect(0, 1040, 1120, 80));
    m_timeLimit->setTextureRect(sf::IntRect(0, 1120, 1120, 80));
}

//Sets the origin of transformation for each element
void BattleSettingsScreen::setElementsOrigins(){
    setOriginIndex(m_rounds, 4);
    setOriginIndex(m_lives, 4);
    setOriginIndex(m_timeLimit, 4);
    setOriginIndex(m_roundsText, 4);
    setOriginIndex(m_livesText, 4);
    setOriginIndex(m_timeLimitText, 4);
}

//Places each element
void BattleSettingsScreen::placeElements(){
    m_rounds->setPosition(getViewportWidth(0.5), getViewportHeight(0.5) + 70);
    m_lives->setPosition(m_rounds->getPosition());
    m_timeLimit->setPosition(m_rounds->getPosition());
    
    m_rounds->move(0, -100);
    m_timeLimit->move(0, 100);

    m_roundsText->setPosition(m_rounds->getPosition().x + 280, m_rounds->getPosition().y);
    m_livesText->setPosition(m_lives->getPosition().x + 280, m_lives->getPosition().y);
    m_timeLimitText->setPosition(m_timeLimit->getPosition().x + 280, m_timeLimit->getPosition().y);

    stylizeText(m_roundsText);
    stylizeText(m_livesText);
    stylizeText(m_timeLimitText);
}

//Initializes the menu nodes
void BattleSettingsScreen::initializeNodes(){
    m_roundsNode    = new MenuNode(Screen::Undefined, m_rounds);
    m_livesNode     = new MenuNode(Screen::Undefined, m_lives);
    m_timeLimitNode = new MenuNode(Screen::Undefined, m_timeLimit);

    m_roundsNode->setDown(m_livesNode);
    m_livesNode->setDown(m_timeLimitNode);
    m_timeLimitNode->setDown(m_roundsNode);

    m_selectedNode = m_roundsNode;
    createSelectionRect();
}

//Draws to the screen
void BattleSettingsScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));

    m_menu->m_texture->draw(*m_rounds);
    m_menu->m_texture->draw(*m_roundsText);
    m_menu->m_texture->draw(*m_lives);
    m_menu->m_texture->draw(*m_livesText);
    m_menu->m_texture->draw(*m_timeLimit);
    m_menu->m_texture->draw(*m_timeLimitText);

    m_menu->m_texture->draw(*m_selectedRect);

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    m_menu->m_texture->display();
}










/* ****************************** ACTIONS ****************************** */
void BattleSettingsScreen::select(){
    save();
}