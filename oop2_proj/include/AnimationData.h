#pragma once

//-------------------------- Include section  ----------------------------
#include "Macros.h"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>


using ListType = std::vector<sf::IntRect>;

// Data of the IntRect of the animation.
using DataType = std::unordered_map<Operation, ListType>;

// Time play of each frame in the animation.
using TimeData = std::unordered_map<Operation, float>;

// The frequancy the animation supposed to be played(Once or more).
using PlayOnceData = std::unordered_map<Operation, bool>;


// Data structure of the animations.
struct AnimationData
{
    DataType m_data;
    TimeData m_time;
    PlayOnceData playOnce;
};
