#include "StaticInclude\Gift.h"


//--------------------------------------------------
//start took gift sound

void Gift::startSound()
{
    static sf::Sound effect;
    effect.setBuffer(*FileManager::p2FileManager().getSound(S_GIFT));
    effect.play();
    effect.setVolume(VOLUME_COLLISION+2);
}