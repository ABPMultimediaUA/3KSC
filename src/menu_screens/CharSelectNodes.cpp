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

#include "../include/menu_screens/CharSelectNodes.hpp"
#include "../include/managers/InputManager.hpp"
#include "../include/extra/Inputs.hpp"

//Global variables
int g_cursorCount   = 0;
int g_tokenCount    = 0;
int g_charCount     = 0;

/* ****************************** CURSORS ****************************** */
CursorNode::CursorNode(sf::Sprite* p_sprite){
    m_id            = g_cursorCount++;
    m_inputManager  = &InputManager::instance();
    m_sprite        = p_sprite;
    m_dragging      = nullptr;
    m_searching     = false;
    m_mouse         = (m_id == m_inputManager->getDeviceCount() - 1);
}

//Moves the cursor. Returns true when looking for tokens.
bool CursorNode::input(){
    //Mouse input
    if (m_mouse){
        m_sprite->setPosition(m_inputManager->getMouseX(), m_inputManager->getMouseY());
        m_searching = m_inputManager->isMousePressed();
    }

    //Joystick input
    else{
        float   t_offsetX = m_inputManager->getAxisPosition(m_id, Axis::X) * 0.125,
                t_offsetY = m_inputManager->getAxisPosition(m_id, Axis::Y) * 0.125;

        m_sprite->move(t_offsetX, t_offsetY);
        m_searching = m_inputManager->isButtonPressed(m_id, Button::X);
    }

    return m_searching;
}










/* ****************************** TOKENS ****************************** */
TokenNode::TokenNode(sf::Sprite* p_sprite, int p_player){
    m_id            = g_tokenCount++;
    m_sprite        = p_sprite;
    m_player        = p_player;
    m_dragger       = nullptr;
}

//If cursor collides with token, sets its as dragger and returns true. Returns false otherwise.
bool TokenNode::beginDrag(CursorNode* p_cursor){
    if (!p_cursor->m_dragging){
        if (m_sprite->getGlobalBounds().contains(p_cursor->m_sprite->getPosition())){
            m_dragger               = p_cursor;
            m_dragger->m_dragging   = this;
            return true;
        }
    }

    return false;
}

//If token has a dragger, it moves with it and returns true. Returns false otherwise.
bool TokenNode::drag(){
    if (m_dragger){
        m_sprite->setPosition(m_dragger->m_sprite->getPosition());
        return true;
    }

    return false;
}

//Sets the cursor and token pointers to null
void TokenNode::endDrag(){
    m_dragger->m_dragging   = nullptr;
    m_dragger               = nullptr;
}










/* ****************************** CHARACTERS BAR ****************************** */
CharBarNode::CharBarNode(sf::Sprite* p_sprite){
    m_id            = g_charCount++;
    m_sprite        = p_sprite;

    switch (m_id){
        case 0:     { m_name = "Kira";      break; }
        case 1:     { m_name = "Luka";      break; }
        case 2:     { m_name = "Miyagi";    break; }
        case 3:     { m_name = "Plup";      break; }
        case 4:     { m_name = "Rawr";      break; }
        case 5:     { m_name = "Sparky";    break; }
        case 6:     { m_name = "???";       break; }
    }
}

bool CharBarNode::isTokenHere(TokenNode* p_token){
    return m_sprite->getGlobalBounds().contains(p_token->m_sprite->getPosition());
}