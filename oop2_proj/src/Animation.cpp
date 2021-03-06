#include "Animation.h"

Animation::Animation(const AnimationData& data, Operation dir,
    sf::RectangleShape& sprite, sf::Texture* texture)
    : m_gameData(data), m_operation(dir), m_shape(sprite)
{
    m_shape.setTexture(texture);
    update();
}
//------------------------------------------
// Set the current operation of the animation played.

void Animation::operation(Operation op)
{
    if (m_operation == op)
    {
        return;
    }
    else
        m_operation = op;

    if (!m_gameData.m_playOnce.find(m_operation)->second)
        m_index %= m_gameData.m_data.find(m_operation)->second.size();
    else
        m_index = 0;

    update();
}
//------------------------------------------
// Update the next frame index by the delta time.

void Animation::update(sf::Time delta)
{
    auto temp = m_gameData.m_data;
    m_elapsed += delta;

    if (m_elapsed >= sf::seconds(m_gameData.m_time.find(m_operation)->second))
    {
        m_elapsed -= sf::seconds(m_gameData.m_time.find(m_operation)->second);
        ++m_index;

        if (!m_gameData.m_playOnce.find(m_operation)->second)
        {
            // Set animation from the start if last frame played
            m_index %= m_gameData.m_data.find(m_operation)->second.size();   
        }

        else
            updateOnLastFrame();
        
        update();
    }
}
//------------------------------------------
// Returns the current animation operation

const Operation Animation::getOperation()
{
    return m_operation;
}
//------------------------------------------
// Returns the current index of the animation frame.

const int Animation::getCurrentIndex() const
{
    return m_index;
}
//------------------------------------------
// Set each frame in rect. 

void Animation::update()
{
    auto inRect = m_gameData.m_data.find(m_operation)->second[m_index];
    m_shape.setTextureRect(inRect);
}
//------------------------------------------
// On last frame update accordingly if the 
// animation suppose to play only once.

void Animation::updateOnLastFrame()
{
    if (m_index >= m_gameData.m_data.find(m_operation)->second.size())
    {
        m_index = m_gameData.m_data.find(m_operation)->second.size() - 1;

        if (m_operation != Dead &&
            m_operation != Fall)
        {
            m_index = 0;
            m_operation = Stay;
        }
    }
}
