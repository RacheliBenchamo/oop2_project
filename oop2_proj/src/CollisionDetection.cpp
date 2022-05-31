//--------------------------- Include section  ---------------------------
#include "CollisionDetection.h"

// Moveable Objects
#include "MovingInclude/Player.h"
#include "MovingInclude/Monster.h"


//#include "MovingInclude/Box.h"

// Static Objects.
//#include "StaticInclude/Block.h"
#include "StaticInclude/Floor.h"
//#include "StaticInclude/Rope.h"
#include "StaticInclude/Teleport.h"
#include "StaticInclude/Diamond.h"
#include "StaticInclude/ExtraLife.h"


namespace // anonymous namespace � the standard way to make function "static"
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
    static_cast<Player&>(p).handleCollision(static_cast<Floor&>(f));

}

void playerMonster(GameObjBase& p, GameObjBase& f)
{
    if (static_cast<Player&>(p).getHitingStatus())
        static_cast<Monster&>(f).handleHit();
    else
        static_cast<Player&>(p).handelHit(static_cast<Monster&>(f).getForce());

    //static_cast<Player&>(p).handleCollision(static_cast<Floor&>(f));

}

//---------------------------- playerGold --------------------------------
// Handle the event that the player collides with gold.
// 1. Update the amount of gold the player has accumulated so far.
// 2. Update that the object of gold no longer exists.
//------------------------------------------------------------------------
void playerDiamond(GameObjBase& p, GameObjBase& g)
{
    //auto d = static_cast<Diamond&>(g);
    static_cast<Player&>(p).addDiamond();
    //voice of takinf diamonds
    static_cast<Diamond&>(g).setToDelete();
    FileManager::instance().playSound(S_TAKE_DIAMOND);
}

//------------------------------------------------

void playerLifePotion(GameObjBase& p, GameObjBase& g)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        //auto d = static_cast<Diamond&>(g);
        static_cast<Player&>(p).addLife();
        //voice of takinf diamonds
        static_cast<LifePosion&>(g).setToDelete();
        // FileManager::instance().playSound(COLLECT_DIAMOND_SOUND);
    }
}
//------------------------------------------------

void playerPowerPotion(GameObjBase& p, GameObjBase& g)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        //auto d = static_cast<Diamond&>(g);
        static_cast<Player&>(p).addPower();
        //voice of takinf diamonds
        static_cast<PowerPosion&>(g).setToDelete();
        // Resources::instance().playSound(COLLECT_DIAMOND_SOUND);
    }
}

////--------------------------- enemyFloor ---------------------------------
//// Handle the event that the enemy collides with the floor.
//// Push the enemy back to his previous position before the collision.
////------------------------------------------------------------------------
void monsterFloor(GameObjBase& e, GameObjBase& f)
{
    static_cast<Monster&>(e).handleCollision(static_cast<Floor&>(f));
}


    //---------------------- setPlayerCollisionHandling ----------------------
    // Insert all the players collision functions into the map Data Structure.
    //------------------------------------------------------------------------
    void setPlayerCollisionHandling(HitMap& phm)
    {
        //// Player & floor.
        phm[MapKey(typeid(Player), typeid(Floor))] = &PlayerFloor;
        // Player & Diamond.
        phm[MapKey(typeid(Player), typeid(Diamond))] = &playerDiamond;
        // Player & Monster.
        phm[MapKey(typeid(Player), typeid(Monster))] = &playerMonster;
        //// Player & ExtraLife
        phm[MapKey(typeid(Player), typeid(LifePosion))] = &playerLifePotion;
         //// Player & ExtraPower
        phm[MapKey(typeid(Player), typeid(PowerPosion))] = &playerPowerPotion;
    }


    //---------------------- setEnemyCollisionHandling -----------------------
    // Insert all the enemy's collision functions into the map Data Structure.
    //------------------------------------------------------------------------
    void setMonsterCollisionHandling(HitMap& phm)
    {
        //// Bear & Floor.
        phm[MapKey(typeid(Monster), typeid(Floor))] = &monsterFloor;

    }


    //---------------------- setStaticCollisionHandling ----------------------
    // Insert all the static collision functions into the map Data Structure.
    //------------------------------------------------------------------------
    void setStaticCollisionHandling(HitMap& phm)
    {
    //    // Box & floor
    //    phm[MapKey(typeid(Box), typeid(Block))] = &boxFloor;


    //    // StoneArrow & Block
    //    phm[MapKey(typeid(StoneArrow), typeid(Block))] = &arrowStaticObject;

    //    // StoneArrow & Box
    //    phm[MapKey(typeid(StoneArrow), typeid(Box))] = &arrowStaticObject;


    //    // FireArrow & Block
    //    phm[MapKey(typeid(FireArrow), typeid(Block))] = &arrowStaticObject;

    //    // FireArrow & Box
    //    phm[MapKey(typeid(FireArrow), typeid(Box))] = &arrowStaticObject;
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
