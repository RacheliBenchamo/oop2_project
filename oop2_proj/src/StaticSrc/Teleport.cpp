#include "StaticInclude\Teleport.h"


//--------------------------------------------------

void Teleport::startSound()
{
    static sf::Sound effect;
    effect.setBuffer(*FileManager::p2FileManager().getSound(S_IN_TELEPORT));
    effect.play();
    effect.setVolume(VOLUME_COLLISION);
}
//--------------------------------------------------

void Teleport::setPartnerPos(sf::Vector2f pos)
{
    m_Partner = pos;
}
//--------------------------------------------------

bool Teleport::isOpen()
{
    return m_isOpen;
}
//--------------------------------------------------

void Teleport::handleCollision(GameObjBase& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
