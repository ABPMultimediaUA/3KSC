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

#ifndef CHARACTER_ONLINE_SCREEN
#define CHARACTER_ONLINE_SCREEN

class Game;

#include "MenuScreen.hpp"

class CharacterOnlineScreen : public MenuScreen{
    private:
        CharacterOnlineScreen(MenuState* p_menu);
        
        Game*           m_game;
        
        sf::Text**      m_names;
        sf::Sprite**    m_characters;
        sf::Sprite**    m_faces;
        sf::Sprite*     m_charactersBar;
        sf::Sprite**    m_tokens;

        sf::Texture*    m_charSpritesheet;

        //They clip the background/name/face of the specified character for a certain player
        void clipBackground(int p_player, int p_character)  { m_characters[p_player]->setTextureRect(sf::IntRect(200 * (p_character), 200, 200, 200)); }
        void clipToken(int p_player, int p_character)       { m_tokens[p_player]->setTextureRect(sf::IntRect(200 * p_character, 400, 128,  128)); }
        void clipFace(int p_player, int p_character)        { m_faces[p_player]->setTextureRect(sf::IntRect(200 * p_character,   0, 200, 200)); }
        
        void loadCharSpritesheet();

        void clipElements()         override;
        void setElementsOrigins()   override;
        void placeElements()        override;
        void initializeNodes()      override;

    public:
        static CharacterOnlineScreen& instance();
        ~CharacterOnlineScreen();

        void input();
        void update();
        void render();

        void select()               override;
};

#endif