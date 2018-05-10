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

#ifndef CHAR_SELECT_NODES
#define CHAR_SELECT_NODES

class InputManager;
class TokenNode;

#include <SFML/Graphics/Sprite.hpp>
#include <vector>

/* ****************************** CURSORS ****************************** */
class CursorNode{
    private:
        InputManager*           m_inputManager;
        bool                    m_mouse;
        bool                    m_searching;

    public:
        int         m_id;
        sf::Sprite* m_sprite;
        TokenNode*  m_dragging;     //Pointer to the Token this cursor is dragging

        CursorNode(sf::Sprite* p_sprite);
        ~CursorNode() = default;

        bool input();
};

/* ****************************** TOKENS ****************************** */
class TokenNode{
    public:
        int         m_id;       
        int         m_player;       // [0 - 3]: Playable (index of player), 4: IA
        sf::Sprite* m_sprite;
        CursorNode* m_dragger;      // Pointer to dragger CursorNode

        TokenNode(sf::Sprite* p_sprite, int p_player);
        ~TokenNode() = default;

        bool beginDrag(CursorNode* p_cursor);
        bool drag();
        void endDrag();

};

/* ****************************** CHARACTERS BAR ****************************** */
class CharBarNode{
    public:
        int         m_id;
        sf::Sprite* m_sprite;
        const char* m_name;

        CharBarNode(sf::Sprite* p_sprite);        
        ~CharBarNode() = default;

        bool isTokenHere(TokenNode* p_token);
};

#endif