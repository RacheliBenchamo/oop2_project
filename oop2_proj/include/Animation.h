#pragma once
#include "AnimationData.h"

class Animation
{
public:
    Animation(const AnimationData&, Operation,
        sf::RectangleShape&, sf::Texture*);
    ~Animation() = default;

    void operation(Operation);
    void update(sf::Time);
    const Operation getOperation();
    const int getCurrentIndex() const;

private:
    void update();
    void updateOnLastFrame();

    const AnimationData& m_gameData;
    sf::Time m_elapsed = {};
    Operation m_operation = Operation::Stay;
    int m_index = 0;
    sf::RectangleShape& m_shape;
};
