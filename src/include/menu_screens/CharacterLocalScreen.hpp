/*
    3KSC: A fighting game
    Copyright (C);

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

#ifndef CHARACTER_LOCAL_SCREEN
#define CHARACTER_LOCAL_SCREEN

class Game;
class CursorNode;
class TokenNode;
class CharBarNode;

#include "MenuScreen.hpp"
#include <vector>

class CharacterLocalScreen : public MenuScreen{
    private:
        CharacterLocalScreen(MenuState* p_menu);
        
        Game*           m_game;

        // CharBarNode**   m_charNodes;
        // TokenNode**     m_tokenNodes;
        // bool            m_dragging[4];

        std::vector<CursorNode>      m_cursorNodes;
        std::vector<TokenNode>       m_tokenNodes;
        std::vector<CharBarNode>     m_charNodes;
        
        sf::Sprite**    m_backgrounds;
        sf::Sprite**    m_faces;
        sf::Sprite**    m_checkboxes;
        sf::Text**      m_names;
        
        sf::Sprite**    m_charactersBar;
        sf::Sprite**    m_tokens;
        sf::Sprite**    m_cursors;

        sf::Texture*    m_charSpritesheet;

        int             m_localPlayers;
        bool            m_enabledPlayers[4];

        //They clip the background/name/face of the specified character for a certain player
        void clipBackground(int p_player, int p_character)  { m_backgrounds[p_player]->setTextureRect(sf::IntRect(200 * (p_character), 200, 200, 200)); }
        void clipToken(int p_player, int p_character)       { m_tokens[p_player]->setTextureRect(sf::IntRect(64 * p_character, 400, 64,  64)); }
        void clipFace(int p_player, int p_character)        { m_faces[p_player]->setTextureRect(sf::IntRect(200 * p_character,   0, 200, 200)); }
        
        void loadCharSpritesheet();
        void chooseCharacter(int p_player, int p_character);
        void enablePlayer(int p_player, bool p_playable = true);
        void disablePlayer(int p_player);

        void clipElements()         override;
        void setElementsOrigins()   override;
        void placeElements()        override;
        void initializeNodes()      override;

    public:
        static CharacterLocalScreen& instance();
        ~CharacterLocalScreen();

        void input();
        void update();
        void render();

        void select()               override;
};

#endif