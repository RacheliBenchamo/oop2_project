//--------------------------- Include section  ---------------------------
#include "CollisionDetection.h"

// Moveable Objects
#include "MovingInclude/Player.h"
#include "MovingInclude/Monster.h"

// Static Objects.
#include "StaticInclude/Floor.h"
#include "StaticInclude/Teleport.h"
#include "StaticInclude/Diamond.h"


namespace // anonymous namespace — the standard way to make function "static"
{
    using HitFunctionPtr = void (*)(GameObjBase&, GameObjBase&);
    using MapKey = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<MapKey, HitFunctionPtr>;



////----------------------------- PlayerFloor ------------------------------
//// Handle the event that the player collides with the floor.
//// Push the player back to his previous position before the collision.
////------------------------------------------------------------------------
void PlayerFloor(GameObjBase& p, GameObjBase& f)
{
    if (!static_cast<Player&>(p).getClimbing())
    {

        if (typeid(f) == typeid(RightFloor))
        {
            static_cast<Player&>(p).handleCollisionRightFloor(f);

        }
        else if (typeid(f) == typeid(LeftFloor))
        {
            static_cast<Player&>(p).handleCollisionLeftFloor(f);
        }

        else
            static_cast<Player&>(p).handleCollisionFloor(f);

    }

}
//------------------------------------------------------------------
void playerGate(GameObjBase& p, GameObjBase& f)
{
    if (static_cast<Gate&>(f).getIsOpen())
    {
        FileManager::instance().startSound(FileManager::instance().getShareSaund(S_WIN_LEVEL));
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        static_cast<Player&>(p).setGotToNextLev();
    }
       
}
//------------------------------------------------------------------
void PlayerTeleport(GameObjBase& p, GameObjBase& f)
{
    static_cast<Player&>(p).setPos(static_cast<Teleport&>(f).getPertnetPos());
    FileManager::instance().startSound(FileManager::instance().getShareSaund(S_IN_TELEPORT));
}
//------------------------------------------------------------------

void playerMonster(GameObjBase& p, GameObjBase& f)
{
    if (static_cast<Player&>(p).getHitingStatus())
    {
        FileManager::instance().startSound(FileManager::instance().getMonsterSound(HURT,
            static_cast<Monster&>(f).getCurrLevel(), static_cast<Monster&>(f).getMonNumber()));
        static_cast<Monster&>(f).handleHit(static_cast<Player&>(p).getDamage());
    }
        
    else
    {
        FileManager::instance().startSound(FileManager::instance().getMonsterSound(HIT,
            static_cast<Monster&>(f).getCurrLevel(), static_cast<Monster&>(f).getMonNumber()));
        static_cast<Player&>(p).handleHit(static_cast<Monster&>(f).getDamage());
    }

}
//---------------------------- playerGold --------------------------------
// Handle the event that the player collides with gold.
// 1. Update the amount of gold the player has accumulated so far.
// 2. Update that the object of gold no longer exists.
//------------------------------------------------------------------------
void playerDiamond(GameObjBase& p, GameObjBase& g)
{
    FileManager::instance().startSound(FileManager::instance().getShareSaund(S_TAKE_DIAMOND));
   
    static_cast<Player&>(p).addDiamond();
    static_cast<Diamond&>(g).setToDelete();
}
//------------------------------------------------

void playerRope(GameObjBase& p, GameObjBase& g)
{
       //Resources::instance().playSound(COLLECT_DIAMOND_SOUND);
        static_cast<Player&>(p).setClimbing(true);

        static_cast<Player&>(p).setPos({ static_cast<Rope&>(g).getPos().x+
            (9* static_cast<Player&>(p).getScale().x)
           ,static_cast<Player&>(p).getPos().y });
}
//------------------------------------------------

void playerLifePotion(GameObjBase& p, GameObjBase& g)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        static_cast<Player&>(p).addLife();
        static_cast<LifePotion&>(g).setToDelete();
    }
}
//------------------------------------------------

void playerPowerPotion(GameObjBase& p, GameObjBase& g)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        static_cast<Player&>(p).addPower();
        static_cast<PowerPotion&>(g).setToDelete();
    }
}

////--------------------------- enemyFloor ---------------------------------
//// Handle the event that the enemy collides with the floor.
//// Push the enemy back to his previous position before the collision.
////------------------------------------------------------------------------
void monsterFloor(GameObjBase& e, GameObjBase& f)
{
   static_cast<Monster&>(e).handleCollisionFloor(f);
}

//---------------------- setPlayerCollisionHandling ----------------------
// Insert all the players collision functions into the map Data Structure.
//------------------------------------------------------------------------
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

//---------------------- setEnemyCollisionHandling -----------------------
// Insert all the enemy's collision functions into the map Data Structure.
//------------------------------------------------------------------------
void setMonsterCollisionHandling(HitMap& phm)
{
    //// monster & Floor.
    phm[MapKey(typeid(Monster), typeid(Floor))] = &monsterFloor;
}

//------------------------ initializeCollisionMap ------------------------
// Intialize the collision handling map.
// Calls to auxiliary functions that insert the keys of the objects that
// collide and the corresponding function for that collision.
//------------------------------------------------------------------------
HitMap initializeCollisionMap()
{
    HitMap phm;

    setPlayerCollisionHandling(phm);

    setMonsterCollisionHandling(phm);

    return phm;
}


//------------------------------ lookup ----------------------------------
// Look up and find out if there is a suitable collision between the
// 2 objects that committed a collision.
//------------------------------------------------------------------------
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

//------------------------- processCollision -----------------------------
// Process the collision.
// Calls the function lookup that searches if there is a suitable function
// for the current collision. If a suitable function is found, it 
// activates it.
//------------------------------------------------------------------------
void processCollision(GameObjBase& object1, GameObjBase& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (phf)
    {
        phf(object1, object2);
    }
}
