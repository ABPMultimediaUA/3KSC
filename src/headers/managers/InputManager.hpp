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

#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <irrlicht.h>

#include "../entities/Character.hpp"

class InputManager : public irr::IEventReceiver{
    private:
    static InputManager* m_instance;
    int** m_bindings;
    bool m_keyIsDown[irr::KEY_KEY_CODES_COUNT];

    //Movement
    irr::u32        m_prevTime;
    irr::u32        m_nowTime;
    irr::f32        m_frameDeltaTime;
    irr::f32        m_moveSpeed;
    int             m_runningFactor;
    int             m_jumpMaxTime;          // Control the time in which the character is in the air (in frames)
    int             m_jumpCurrentTime;      // Control variable. Checks in which frame of the jump the character is in
    bool            m_jumping;              // Controls if the jump is still going
    float           m_jumpTable[10];        // Determines how high the player goes each frame while jumping
    

    public:
    static InputManager* instance();
    InputManager();
    ~InputManager();
    virtual bool OnEvent(const irr::SEvent& p_event);
    virtual bool IsKeyDown(irr::EKEY_CODE p_keyCode) const;
    void onKeyPressed(int p_key);

    void timeStamp();
    void updateFrameDeltaTime();
    void playerInput(Character* p_player);
    void jump(Character* p_player);
};

#endif