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

#ifndef MENU_SCREEN
#define MENU_SCREEN

#include "../states/MenuState.hpp"
#include <CESceneSprite.hpp>
#include <vector>

class EngineManager;
class InputManager;

struct MenuNode{
    //Attributes
    MenuNode*           up;
    MenuNode*           down;
    MenuNode*           left;
    MenuNode*           right;
    Screen              target;
    CESceneSprite*      element;

    //Methods
    MenuNode(CESceneSprite* p_element){
        up = down = left = right = nullptr;
        target      = Screen::Undefined;
        element     = p_element;
    }
    ~MenuNode(){}

    void    setUp(MenuNode* p_node)     { this->up      = p_node;    p_node->down   = this; }
    void    setDown(MenuNode* p_node)   { this->down    = p_node;    p_node->up     = this; }
    void    setLeft(MenuNode* p_node)   { this->left    = p_node;    p_node->right  = this; }
    void    setRight(MenuNode* p_node)  { this->right   = p_node;    p_node->left   = this; }
    void    setTarget(Screen p_screen)  { this->target  = p_screen;                         }
};

class MenuScreen{
    protected:
        MenuScreen(MenuState* p_menu);
        
        void createFromFile(const char* p_url);

        MenuState*          m_menu;
        EngineManager*      m_engineManager;
        InputManager*       m_inputManager;
        
        std::vector<MenuNode*>  m_nodes;  
        MenuNode*               m_selectedNode;

        std::vector<CESceneSprite*> m_sprites;

        // sf::Transformable*  m_selected;
        sf::RectangleShape* m_selectedRect;

        sf::RectangleShape* m_controlsBG;
        sf::Sprite*         m_controls;

        Screen              m_prev;             //Previous screen
        Screen              m_next;             //Next screen (save)
        Screen              m_settingsScreen;   //Settings screen for that menu

        //Receives a pointer to element and an index in range [0-8].
        // Sets the transform origin to one of the common 9 points.
        template <class T>
        void setOriginIndex(T* p_element, int p_index){
            float t_x = 0, t_y = 0;
        
            t_x = p_element->getGlobalBounds().width    * (0.5 * (p_index % 3));
            t_y = p_element->getGlobalBounds().height   * (0.5 * (p_index / 3));

            p_element->setOrigin(t_x, t_y);
        }

        //Return the width/height of the viewport. Optionally, they can return part of it.
        float getViewportWidth(float p_factor = 1);
        float getViewportHeight(float p_factor = 1);

        virtual void clipElements()         {}
        virtual void setElementsOrigins()   {}
        virtual void placeElements()        {}
        virtual void initializeNodes()      {}
        
        virtual void createSelectionRect(){
            sf::FloatRect t_bbox = m_selectedNode->element->getGlobalBounds();            

            m_selectedRect->setSize(sf::Vector2f(t_bbox.width, t_bbox.height));
            setOriginIndex(m_selectedRect, 4);
            m_selectedRect->setPosition(m_selectedNode->element->getPosition());
            m_selectedRect->setFillColor(sf::Color::Transparent);
            m_selectedRect->setOutlineThickness(6);
            m_selectedRect->setOutlineColor(sf::Color(209, 45, 58));
        }

        void stylizeText(sf::Text* p_text, const sf::Color& p_color = sf::Color(255, 128, 0));
        void createControlsBar(int p_variant);

        virtual void doActions();

    public:
        virtual ~MenuScreen();

        void setPrev(Screen p_prev)                 { m_prev = p_prev; }

        virtual void input();
        virtual void update();
        virtual void render();
        
        virtual void up();
        virtual void down();
        virtual void left();
        virtual void right();
        virtual void select();
        virtual void back();
        virtual void save();
        virtual void settings();
};

#endif