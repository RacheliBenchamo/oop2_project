//--------------------------- Include section  ---------------------------
#include "CollisionDetection.h"
// Moveable Objects
#include "MovingInclude/Player.h"
#include "MovingInclude/Monster.h"
// Static Objects.
#include "StaticInclude/Floor.h"
#include "StaticInclude/Teleport.h"
#include "StaticInclude/Diamond.h"

namespace // anonymous namespace � the standard way to make function "static"
{
    using HitFunctionPtr = void (*)(GameObjBase&, GameObjBase&);
    using MapKey = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<MapKey, HitFunctionPtr>;


void startSound(sf::SoundBuffer* sound, const int volum)
{
    static sf::Sound effect;
    if (FileManager::instance().getToPlayAudio())
    {
        effect.setBuffer(*sound);
        effect.setVolume(volum);
        effect.play();
    }
}
//------------------------------------------
void playerSound(sf::SoundBuffer* sound, const int volum)
{
    static sf::Sound effect;
    if (FileManager::instance().getToPlayAudio())
    {
        effect.setBuffer(*sound);
        effect.setVolume(volum);
        effect.play();
    }
}
//------------------------------------------
// Handle the event that the player collides with the floor.
// Push the player back to his previous position before the collision.

void PlayerFloor(GameObjBase& p, GameObjBase& f)
{
    if (!static_cast<Player&>(p).getClimbing())
    {
        if (typeid(f) == typeid(RightFloor))
            static_cast<Player&>(p).handleCollisionRightFloor(f);
        else if (typeid(f) == typeid(LeftFloor))
            static_cast<Player&>(p).handleCollisionLeftFloor(f);
        else
            static_cast<Player&>(p).handleCollisionFloor(f);
    }
}
//------------------------------------------
// Handle the event that the player collides with the gate.

void playerGate(GameObjBase& p, GameObjBase& f)
{
    //so we can see the player enter the gate
    static int gateCounter = 0;

    if (static_cast<Gate&>(f).getIsOpen())
    {
        if (gateCounter == 0)
        {
            gateCounter = 20;
        }
        else if (gateCounter > 1)
        {
            --gateCounter;
        }
        else
        {
            gateCounter = 0;
            static_cast<Player&>(p).setGotToNextLev();
        }
    }
}
//------------------------------------------
// Handle the event that the player collides with the teleport.

void PlayerTeleport(GameObjBase& p, GameObjBase& f)
{
    static_cast<Player&>(p).setPos(static_cast<Teleport&>(f).getPertnetPos());
    playerSound(FileManager::instance().getShareSaund(S_IN_TELEPORT),
        VOLUME_COLLISION);
}
//------------------------------------------
// Handle the event that the player collides with monster.

void playerMonster(GameObjBase& p, GameObjBase& f)
{
    if (static_cast<Player&>(p).getHitingStatus())
    {
        playerSound(FileManager::instance().getShareSaund(S_FIGHT),VOLUME_COLLISION);
        FileManager::instance().startSound(FileManager::instance().getMonsterSound(HURT,
            static_cast<Monster&>(f).getCurrLevel(), 
            static_cast<Monster&>(f).getMonNumber()),
            VOLUME_COLLISION);
        static_cast<Monster&>(f).handleHit
        (static_cast<Player&>(p).getDamage());
    } 
    else
    {
        startSound(FileManager::instance().getMonsterSound(HIT,
            static_cast<Monster&>(f).getCurrLevel(),
            static_cast<Monster&>(f).getMonNumber()),
            VOLUME_COLLISION);
        static_cast<Player&>(p).handleHit
        (static_cast<Monster&>(f).getDamage());
    }
}
//------------------------------------------
//Handle the event that the player collides with diamond.
// 1. Update the amount of diamond the player has accumulated so far.
// 2. Update that the object of diamond no longer exists.

void playerDiamond(GameObjBase& p, GameObjBase& g)
{
    playerSound(FileManager::instance().getShareSaund
    (S_TAKE_DIAMOND), VOLUME_COLLISION);
    static_cast<Player&>(p).addDiamond();
    static_cast<Diamond&>(g).setToDelete();
}
//------------------------------------------
//Handle the event that the player collides with rope.

void playerRope(GameObjBase& p, GameObjBase& g)
{
        static_cast<Player&>(p).setClimbing(true);
        static_cast<Player&>(p).setPos({ static_cast<Rope&>(g).getPos().x+
            (9* static_cast<Player&>(p).getScale().x)
           ,static_cast<Player&>(p).getPos().y });
}
//------------------------------------------
//Handle the event that the player collides with life potion.

void playerLifePotion(GameObjBase& p, GameObjBase& g)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        playerSound(FileManager::instance().getShareSaund
        (S_TAKE_POSION), VOLUME_COLLISION);
        static_cast<Player&>(p).addLife();
        static_cast<LifePotion&>(g).setToDelete(); 
    }
}
//------------------------------------------
//Handle the event that the player collides with power potion.

void playerPowerPotion(GameObjBase& p, GameObjBase& g)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        playerSound(FileManager::instance().getShareSaund
        (S_TAKE_POSION), VOLUME_COLLISION);
        static_cast<Player&>(p).addPower();
        static_cast<PowerPotion&>(g).setToDelete();
    }
}
//------------------------------------------
// Handle the event that the monster collides with the floor.

void monsterFloor(GameObjBase& e, GameObjBase& f)
{
   static_cast<Monster&>(e).handleCollisionFloor(f);
}
//------------------------------------------
// Insert all the player's collision functions into the map Data Structure.

void setPlayerCollisionHandling(HitMap& phm)
{
    //// Player & floor.
    phm[MapKey(typeid(Player), typeid(Floor))] = &PlayerFloor;
    phm[MapKey(typeid(Player), typeid(RightFloor))] = &PlayerFloor;
    phm[MapKey(typeid(Player), typeid(LeftFloor))] = &PlayerFloor;
    // Player & Diamond.
    phm[MapKey(typeid(Player), typeid(Diamond))] = &playerDiamond;
    // Player & Rope.
    phm[MapKey(typeid(Player), typeid(Rope))] = &playerRope;
    // Player & Gate.
    phm[MapKey(typeid(Player), typeid(Gate))] = &playerGate;
    //Player & Teleport
    phm[MapKey(typeid(Player), typeid(Teleport))] = &PlayerTeleport;
    // Player & Monster
    phm[MapKey(typeid(Player), typeid(Monster))] = &playerMonster;
    //// Player & ExtraLife
    phm[MapKey(typeid(Player), typeid(LifePotion))] = &playerLifePotion;
    //// Player & ExtraPower
    phm[MapKey(typeid(Player), typeid(PowerPotion))] = &playerPowerPotion;
}

//------------------------------------------
// Insert all the monster's collision functions into the map Data Structure.

void setMonsterCollisionHandling(HitMap& phm)
{
    phm[MapKey(typeid(Monster), typeid(Floor))] = &monsterFloor;
}
//------------------------------------------
// Intialize the collision handling map.
// Calls to auxiliary functions that insert the keys of the objects that
// collide and the corresponding function for that collision.

HitMap initializeCollisionMap()
{
    HitMap phm;

    setPlayerCollisionHandling(phm);
    setMonsterCollisionHandling(phm);

    return phm;
}
//------------------------------------------
// Look up and find out if there is a suitable collision between the
// 2 objects that committed a collision.

HitFunctionPtr lookup(const std::type_index& class1,
    const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();

    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}
} // end namespace
//------------------------------------------
/// Process the collision.
// Calls the function lookup that searches if there is a suitable function
// for the current collision. If a suitable function is found, it 
// activates it.

void processCollision(GameObjBase& object1, GameObjBase& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (phf)
    {
        phf(object1, object2);
    }
}
