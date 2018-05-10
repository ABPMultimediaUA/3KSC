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

#include "../include/menu_screens/GameSettingsScreen.hpp"
#include "../include/Game.hpp"
#include "../include/extra/ResolutionPresets.hpp"

//Returns the only instance of this class
GameSettingsScreen& GameSettingsScreen::instance(){
    static GameSettingsScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
GameSettingsScreen::GameSettingsScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    
    m_game              = Game::getInstance();

    m_resolution        = new sf::Sprite(*(m_menu->m_spritesheet));
    m_videoMode         = new sf::Sprite(*(m_menu->m_spritesheet));
    m_BGM               = new sf::Sprite(*(m_menu->m_spritesheet));
    m_FX                = new sf::Sprite(*(m_menu->m_spritesheet));
    m_voices            = new sf::Sprite(*(m_menu->m_spritesheet));

    m_resolutionText    = new sf::Text(g_resolutionPresets[m_game->getResolutionPreset()].resolutionString, *(m_menu->m_font), 40);
    m_videoModeText     = new sf::Text((m_game->isFullscreen() ? "Pantalla Completa" : "Ventana"), *(m_menu->m_font), 40);

    stylizeText(m_resolutionText);
    stylizeText(m_videoModeText);

    m_barsBGM           = new sf::RectangleShape*[20];
    m_barsFX            = new sf::RectangleShape*[20];
    m_barsVoices        = new sf::RectangleShape*[20];

    for (int i = 0; i < 20; i++){
        m_barsBGM[i]    = new sf::RectangleShape(sf::Vector2f(10, 50));
        m_barsFX[i]     = new sf::RectangleShape(sf::Vector2f(10, 50));
        m_barsVoices[i] = new sf::RectangleShape(sf::Vector2f(10, 50));

        m_barsBGM[i]->setFillColor(sf::Color(255, 128, 0));
        m_barsFX[i]->setFillColor(sf::Color(255, 128, 0));
        m_barsVoices[i]->setFillColor(sf::Color(255, 128, 0));
    }

    m_volBGM            = m_game->getVolBGM();
    m_volFX             = m_game->getVolFX();
    m_volVoices         = m_game->getVolVoices();

    clipElements();
    setElementsOrigins();
    placeElements();
    initializeNodes();

    m_prev              = Screen::Main;
    m_next              = Screen::Main;

    createControlsBar(2);
}

//Destructor
GameSettingsScreen::~GameSettingsScreen(){
    std::cout << "~GameSettingsScreen" << std::endl;
    if(m_resolutionNode){
        delete m_resolutionNode;
        m_resolutionNode = nullptr;
    }

    if(m_videoModeNode){
        delete m_videoModeNode;
        m_videoModeNode = nullptr;
    }

    if(m_BGMNode){
        delete m_BGMNode;
        m_BGMNode = nullptr;
    }

    if(m_FXNode){
        delete m_FXNode;
        m_FXNode = nullptr;
    }

    if(m_voicesNode){
        delete m_voicesNode;
        m_voicesNode = nullptr;
    }

    if(m_resolution){
        delete m_resolution;
        m_resolution = nullptr;
    }

    if(m_videoMode){
        delete m_videoMode;
        m_videoMode = nullptr;
    }

    if(m_BGM){
        delete m_BGM;
        m_BGM = nullptr;
    }

    if(m_FX){
        delete m_FX;
        m_FX = nullptr;
    }

    if(m_voices){
        delete m_voices;
        m_voices = nullptr;
    }

    if(m_resolutionText){
        delete m_resolutionText;
        m_resolutionText = nullptr;
    }

    if(m_videoModeText){
        delete m_videoModeText;
        m_videoModeText = nullptr;
    }

    for (int i = 0; i < 20; i++){
        if(m_barsBGM[i]){
            delete m_barsBGM[i];
            m_barsBGM[i] = nullptr;
        }

        if(m_barsFX[i]){
            delete m_barsFX[i];
            m_barsFX[i] = nullptr;
        }

        if(m_barsVoices[i]){
            delete m_barsVoices[i];
            m_barsVoices[i] = nullptr;
        }
    }

    if (m_barsBGM){
        delete[] m_barsBGM;
        m_barsBGM = nullptr;
    }

    if (m_barsFX){
        delete[] m_barsFX;
        m_barsFX = nullptr;
    }

    if (m_barsVoices){
        delete[] m_barsVoices;
        m_barsVoices = nullptr;
    }
}

//Clips the texture for each element
void GameSettingsScreen::clipElements(){
    m_resolution->setTextureRect(sf::IntRect(0, 560, 1120, 80));
    m_videoMode->setTextureRect(sf::IntRect(0, 640, 1120, 80));
    m_BGM->setTextureRect(sf::IntRect(0, 720, 1120, 80));
    m_FX->setTextureRect(sf::IntRect(0, 800, 1120, 80));
    m_voices->setTextureRect(sf::IntRect(0, 880, 1120, 80));
}

//Sets the origin of transformation for each element
void GameSettingsScreen::setElementsOrigins(){
    setOriginIndex(m_videoMode, 4);
    setOriginIndex(m_BGM, 4);
    setOriginIndex(m_FX, 4);
    setOriginIndex(m_voices, 4);
    setOriginIndex(m_resolutionText, 4);
    setOriginIndex(m_videoModeText, 4);

    for (int i = 0; i < 20; i++){
        setOriginIndex(m_barsBGM[i], 3);
        setOriginIndex(m_barsFX[i], 3);
        setOriginIndex(m_barsVoices[i], 3);
    }
}

//Places each element
void GameSettingsScreen::placeElements(){
    m_resolution->setPosition(getViewportWidth(0.5), getViewportHeight(0.5) + 70);
    m_videoMode->setPosition(m_resolution->getPosition());
    m_BGM->setPosition(m_resolution->getPosition());
    m_FX->setPosition(m_resolution->getPosition());
    m_voices->setPosition(m_resolution->getPosition());
    
    m_resolution->move(0, -200);
    m_videoMode->move(0, -100);
    m_FX->move(0, 100);
    m_voices->move(0, 200);

    m_resolutionText->setPosition(m_resolution->getPosition().x + 280, m_resolution->getPosition().y);
    m_videoModeText->setPosition(m_videoMode->getPosition().x + 280, m_videoMode->getPosition().y);

    for (int i = 0; i < 20; i++){
        m_barsBGM[i]->setPosition(m_BGM->getPosition().x + 140 + (i * (10 + 4)), m_BGM->getPosition().y);
        m_barsFX[i]->setPosition(m_FX->getPosition().x + 140 + (i * (10 + 4)), m_FX->getPosition().y);
        m_barsVoices[i]->setPosition(m_voices->getPosition().x + 140 + (i * (10 + 4)), m_voices->getPosition().y);
    }
}

//Initializes the menu nodes
void GameSettingsScreen::initializeNodes(){
    m_resolutionNode    = new MenuNode(Screen::Undefined, m_resolution); 
    m_videoModeNode     = new MenuNode(Screen::Undefined, m_videoMode); 
    m_BGMNode           = new MenuNode(Screen::Undefined, m_BGM); 
    m_FXNode            = new MenuNode(Screen::Undefined, m_FX); 
    m_voicesNode        = new MenuNode(Screen::Undefined, m_voices); 
    
    m_resolutionNode->setDown(m_videoModeNode);
    m_videoModeNode->setDown(m_BGMNode);
    m_BGMNode->setDown(m_FXNode);
    m_FXNode->setDown(m_voicesNode);
    m_voicesNode->setDown(m_resolutionNode);

    m_selectedNode = m_resolutionNode;
    createSelectionRect();
}

//Draws to the screen
void GameSettingsScreen::render(){
    m_menu->m_texture->clear(sf::Color(79,195,247));

    m_menu->m_texture->draw(*m_resolution);
    m_menu->m_texture->draw(*m_resolutionText);
    m_menu->m_texture->draw(*m_videoMode);
    m_menu->m_texture->draw(*m_videoModeText);

    m_menu->m_texture->draw(*m_BGM);
    m_menu->m_texture->draw(*m_FX);
    m_menu->m_texture->draw(*m_voices);
    
    for (int i = 0; i < 20; i++){
        if (m_volBGM > i)       { m_menu->m_texture->draw(*m_barsBGM[i]); }
        if (m_volFX > i)        { m_menu->m_texture->draw(*m_barsFX[i]); }
        if (m_volVoices > i)    { m_menu->m_texture->draw(*m_barsVoices[i]); }
    }

    m_menu->m_texture->draw(*m_selectedRect);

    m_menu->m_texture->draw(*m_controlsBG);
    m_menu->m_texture->draw(*m_controls);

    m_menu->m_texture->display();
}










/* ****************************** ACTIONS ****************************** */
void GameSettingsScreen::select(){
    save();
}