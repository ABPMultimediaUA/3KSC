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
#include <fstream>
#include <sstream>
#include <string>

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

    for (MenuNode* t_node : m_nodes)            { delete t_node;    }   m_nodes.clear();
    for (CESceneSprite* t_sprite : m_sprites)   { delete t_sprite;  }   m_sprites.clear();
}

//Reads a CGS file and creates the screen from it
void MenuScreen::createFromFile(const char* p_url){
    std::ifstream   t_file(p_url);
    std::string     t_line;
    std::string     t_tag;

    //Loop through file
    while(std::getLine(t_file, t_line)){
        //Ignore empty lines and comments
        if (t_line == "" || t_line == "#") continue;

        //Separate string by spaces
        std::istringstream          t_tokens(t_line);
        std::vector<std::string>    t_elements(std::istream_iterator<std::string>{t_tokens}, std::istream_iterator<std::string>());

        t_tag = t_elements[0].c_str();

        //Menu nodes
        if (t_tag == "n"){
            const char* t_url   = t_elements[2].c_str();
            float t_width       = strtof(t_elements[3].c_str(), nullptr);
            float t_height      = strtof(t_elements[4].c_str(), nullptr);

            CESceneSprite* t_sprite = m_engineManager->createSprite(t_url, t_width, t_height);
            MenuNode* t_node        = new MenuNode(t_sprite);      
            m_nodes.push_back(t_node);
        }

        //Menu nodes horizontal links
        else if (t_tag == "nhl"){
            int t_nodeA = (int) strtof(t_elements[1].c_str(), nullptr);
            int t_nodeB = (int) strtof(t_elements[2].c_str(), nullptr);

            m_nodes[t_nodeA]->setRight(m_nodes[t_nodeB]);
        }

        //Menu nodes vertical links
        else if (t_tag == "nvl"){
            int t_nodeA = (int) strtof(t_elements[1].c_str(), nullptr);
            int t_nodeB = (int) strtof(t_elements[2].c_str(), nullptr);

            m_nodes[t_nodeA]->setDown(m_nodes[t_nodeB]);            
        }

        //Menu nodes target links
        else if (t_tag == "ntl"){
            int t_index = (int) strtof(t_elements[1].c_str(), nullptr);

            if      (t_elements[2] == "Title"           )   { m_nodes[t_index]->target = Screen::Title;             }
            else if (t_elements[2] == "Main"            )   { m_nodes[t_index]->target = Screen::Main;              }
            else if (t_elements[2] == "CharacterLocal"  )   { m_nodes[t_index]->target = Screen::CharacterLocal;    }
            else if (t_elements[2] == "CharacterOnline" )   { m_nodes[t_index]->target = Screen::CharacterOnline;   }
            else if (t_elements[2] == "BattleSettings"  )   { m_nodes[t_index]->target = Screen::BattleSettings;    }
            else if (t_elements[2] == "Map"             )   { m_nodes[t_index]->target = Screen::Map;               }
            else if (t_elements[2] == "OnlineMode"      )   { m_nodes[t_index]->target = Screen::OnlineMode;        }
            else if (t_elements[2] == "OnlineCreate"    )   { m_nodes[t_index]->target = Screen::OnlineCreate;      }
            else if (t_elements[2] == "OnlineJoin"      )   { m_nodes[t_index]->target = Screen::OnlineJoin;        }
            else if (t_elements[2] == "GameSettings"    )   { m_nodes[t_index]->target = Screen::GameSettings;      }
        }
    }     
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
