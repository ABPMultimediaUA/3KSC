#include "../include/states/State.hpp"
#include <iostream>

void State::setDeltaTime(long long p_delta){
    m_deltaTime = p_delta / 1000000000.0;
    //std::cout << "DELTA: " << m_deltaTime << std::endl;
}