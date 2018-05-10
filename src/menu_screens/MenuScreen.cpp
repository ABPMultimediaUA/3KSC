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

#include "../include/menu_screens/MenuScreen.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/managers/InputManager.hpp"
#include "../include/extra/MenuActions.hpp"
#include <iostream>

//Struct containing menu actions and its properties
struct MenuActionMapping{
    MenuAction  action;                     //Action to map
    bool        (MenuScreen::*function)();  //Function for the action
    bool        onlyOnce;                   //Wait for input release?
    bool        enabled;                    //Enabled or not
};

//Constructor
MenuScreen::MenuScreen(MenuState* p_menu){
    m_menu              = p_menu;
    m_engineManager     = &EngineManager::instance();
    m_inputManager      = &InputManager::instance();

    m_prev              = Screen::Undefined;
    m_next              = Screen::Undefined;
    m_settingsScreen    = Screen::Undefined;

    m_selectedRect      = new sf::RectangleShape();
}

MenuScreen::~MenuScreen(){
    std::cout << "~MenuScreen\n" << std::endl;

    m_selectedNode = nullptr;
    if (m_selectedRect) { delete m_selectedRect;    m_selectedRect = nullptr;   }
    if(m_controlsBG)    { delete m_controlsBG;      m_controlsBG = nullptr;     }
    if(m_controls)      { delete m_controls;        m_controls = nullptr;       }
}

float MenuScreen::getViewportWidth(float p_factor){
    return m_engineManager->getWindowSize().width * p_factor;
}

float MenuScreen::getViewportHeight(float p_factor){
    return m_engineManager->getWindowSize().height * p_factor;
}

void MenuScreen::stylizeText(sf::Text* p_text, const sf::Color& p_color){
    p_text->setFillColor(p_color);
    p_text->setOutlineThickness(2);
    p_text->setOutlineColor(sf::Color::White);
}

void MenuScreen::createControlsBar(int p_variant){
    //Create background for controls
    m_controlsBG = new sf::RectangleShape(sf::Vector2f(getViewportWidth(), 70));
    m_controlsBG->setPosition(0, getViewportHeight() - 70);
    m_controlsBG->setFillColor(sf::Color::Black);

    m_controls = new sf::Sprite(*(m_menu->m_spritesheet));

    //Create base texture rectangle and then modify it
    sf::IntRect t_textureRect(0, 1260, 1024, 50);

    //If there's no controller, move rectangle down (keyboard section)
    if (!m_inputManager->isConnected(0)){
        t_textureRect.top += 250;
    }

    //Pick the right variant
    t_textureRect.top += p_variant * 50;

    //Apply texture rectangle and place sprite
    m_controls->setTextureRect(t_textureRect);
    setOriginIndex(m_controls, 6);
    m_controls->setPosition(10, getViewportHeight() - 10);
}

//Calls action functions when they are active
void MenuScreen::doActions(){
    MenuActionMapping* t_iterator = m_menu->m_actions;

    while(t_iterator->function){
        //We call the function, it'll return false when action finishes
        if(t_iterator->enabled){
            (this->*(t_iterator->function))();
            t_iterator->enabled = false;
        }
        
        ++t_iterator;
    }
}

void MenuScreen::input(){
    m_inputManager->updateMenuActions();

    MenuActionMapping* t_iterator   = m_menu->m_actions;

    //Loop through actions to enable them
    while(t_iterator->function){    
        if (t_iterator->onlyOnce){
            if (m_inputManager->checkMenuAction(t_iterator->action)){
                m_menu->m_keepWaiting = true;

                if (!m_menu->m_waitRelease){
                    t_iterator->enabled = true;
                    m_menu->m_waitRelease = true;
                }
            }
        }

        else{
            t_iterator->enabled = m_inputManager->checkMenuAction(t_iterator->action);
        }

        ++t_iterator;
    }

    m_menu->m_waitRelease = m_menu->m_keepWaiting;
    m_menu->m_keepWaiting = false;
}

void MenuScreen::update(){
    doActions();

    if (m_selectedRect && m_selectedNode){
        m_selectedRect->setPosition(m_selectedNode->element->getPosition());
    }
}

void MenuScreen::render(){

}










/* ****************************** ACTIONS ****************************** */
void MenuScreen::up(){
    if (m_selectedNode && m_selectedNode->up){
        m_selectedNode = m_selectedNode->up;
    }
}

void MenuScreen::down(){    
    if (m_selectedNode && m_selectedNode->down){
        m_selectedNode = m_selectedNode->down;
    }
}

void MenuScreen::left(){    
    if (m_selectedNode && m_selectedNode->left){
        m_selectedNode = m_selectedNode->left;
    }
}

void MenuScreen::right(){    
    if (m_selectedNode && m_selectedNode->right){
        m_selectedNode = m_selectedNode->right;
    }
}

void MenuScreen::select(){    
    if (m_selectedNode && m_selectedNode->target != Screen::Undefined){
        m_menu->setScreen(m_selectedNode->target);
    }
}

void MenuScreen::back(){
    m_menu->setScreen(m_prev);
}

void MenuScreen::save(){
    m_menu->setScreen(m_next);
}

void MenuScreen::settings(){
    m_menu->setScreen(m_settingsScreen);
}
