//--------------------------- Include section  ---------------------------
#include "CollisionDetection.h"

// Moveable Objects
#include "MovingInclude/Player.h"
#include "MovingInclude/DesertMonster.h"
#include "MovingInclude/ForestMonster.h"
#include "MovingInclude/SnowMonster.h"

//#include "MovingInclude/Box.h"

// Static Objects.
//#include "StaticInclude/Block.h"
//#include "StaticInclude/Floor.h"
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
    //std::cout << "2\n";
    static_cast<Player&>(p).handleCollision(static_cast<Floor&>(f));

}


//--------------------------- playerHurricane ----------------------------
// Handle the event that the player collides with a hurricane.
// The hurricane lifts the player upwards.
//------------------------------------------------------------------------
//void playerTeleport(GameObjBase& p, GameObjBase& h)
//{
//    static_cast<Player&>(p).handleCollision(static_cast<Teleport&>(h));
//}


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
   // Resources::instance().playSound(COLLECT_DIAMOND_SOUND);
}

////----------------------------- playerKey --------------------------------
//// Handle the event that the player collides with a key.
//// Let the player to pick up the key and update the key status of the
//// player.
////------------------------------------------------------------------------
//void playerKey(GameObject& player, GameObject& key)
//{
//    //static_cast<Player&>(player).setKeyStatus(true);
//    if (!key.getDisapperStatus()) {
//        static_cast<Player&>(player).addKey();
//        key.setDisappear(true);
//        Resources::instance().playSound(COLLECT_KEY_SOUND);
//    }
//}
//

////---------------------------- playerSpike -------------------------------
//// Handle the event that the player collides with a key.
//// Let the player to pick up the key and update the key status of the
//// player.
////------------------------------------------------------------------------
//void playerSpike(GameObject& p, GameObject& s)
//{
//    static_cast<Player&>(p).handleCollision(static_cast<Spike&>(s));
//}

//
////-------------------------- playerFastMoving ----------------------------
//// Handle the event that the player collides with a fast moving ability 
//// gem. Update the player's special ability and also update that the gem
//// object does not exist anymore.
////------------------------------------------------------------------------
//void playerFastMoving(GameObject& player, GameObject& fastMoving)
//{
//    static_cast<Player&>(player).setSpecialAbility(EXTRA_SPEED_ABILITY);
//    fastMoving.setDisappear(true);
//}
//
////-------------------------- playerJumpBoost -----------------------------
//// Handle the event that the player collides with a jump boot ability gem.
//// Update the player's special ability and also update that the gem object
//// does not exist anymore.
////------------------------------------------------------------------------
//void playerJumpBoost(GameObject& player, GameObject& jumpBoost)
//{
//    static_cast<Player&>(player).setSpecialAbility(EXTRA_JUMP_ABILITY);
//    jumpBoost.setDisappear(true);
//}
//

////------------------------- playerExtraLife ------------------------------
//// Handle the event that the player collides with a heart that adds life 
//// to the player current health. Also, update that the heart object does
//// not exist anymore.
////------------------------------------------------------------------------
//void playerExtraLife(GameObjBase& player, GameObjBase& extraLife)
//{
//    static_cast<Player&>(player).incLife();
//    Resources::instance().playSound(LIFE_BOOST_SOUND);
//    extraLife.setDisappear(true);
//}

////----------------------------- playerDoor -------------------------------
//// Handle the event that the player collides with the door.
//// If the player has already collected the key, update that the level is
//// over.
////------------------------------------------------------------------------
//void playerDoor(GameObject& p, GameObject& d)
//{
//    static_cast<Player&>(p).handleCollision(static_cast<Door&>(d));
//}


////---------------------------- playerEnemy -------------------------------
//// Handle the event that the enemy collides with a player.
//// If the player attacks absorb the blow.
////------------------------------------------------------------------------
//void playerMonster(GameObjBase& p, GameObjBase& e)
//{
//    auto& enemy = static_cast<Enemy&>(e);
//
//    if (static_cast<Player&>(p).isHiting())
//    {
//        enemy.handleHit(enemy, 50);//damage
//    }
//}


////--------------------------- enemyFloor ---------------------------------
//// Handle the event that the enemy collides with the floor.
//// Push the enemy back to his previous position before the collision.
////------------------------------------------------------------------------
//void enemyFloor(GameObject& e, GameObject& f)
//{
//    static_cast<Enemy&>(e).handleCollision(static_cast<Block&>(f));
//}


////----------------------------- enemyBox ---------------------------------
//// Handle the event that the enemy collides with a box.
//// Push the enemy back to his previous position before the collision.
////------------------------------------------------------------------------
//void enemyBox(GameObject& e, GameObject& b)
//{
//    static_cast<Enemy&>(e).handleCollision(static_cast<Box&>(b));
//}


////----------------------------- bearPlayer -------------------------------
//// Handle the event that the enemy collides with a bear.
//// 1. Attack the player - Displays the necessary animations.
//// 2. Lower the player's amount of life.
////------------------------------------------------------------------------
//void bearPlayer(GameObject& b, GameObject& p)
//{
//    auto& bear = static_cast<Bear&>(b);
//    bear.hit(bear);
//    static_cast<Player&>(p).handleCollision(bear);
//}


////----------------------------- crowPlayer -------------------------------
//// Handle the event that the enemy collides with a bear.
//// 1. Attack the player - Displays the necessary animations.
//// 2. Lower the player's amount of life.
////------------------------------------------------------------------------
//void crowPlayer(GameObjBase& c, GameObjBase& p)
//{
//    auto& crow = static_cast<Crow&>(c);
//    crow.hit(crow);
//    static_cast<Player&>(p).handleCollision(crow);
//}

////----------------------------- crowPlayer -------------------------------
//// Handle the event that the enemy collides with a bear.
//// 1. Attack the player - Displays the necessary animations.
//// 2. Lower the player's amount of life.
////------------------------------------------------------------------------
//void wolfPlayer(GameObjBase& w, GameObjBase& p)
//{
//    auto& wolf = static_cast<Wolf&>(w);
//    wolf.hit(wolf);
//    static_cast<Player&>(p).handleCollision(wolf);
//}

////---------------------------- enemyPlayer -------------------------------
//// Handle the event that the enemy collides with an Arrow.
//// 1. Absorb the damage from the arrow.
//// 2. Update that the arrow no longer exists.
////------------------------------------------------------------------------
//void enemyArrow(GameObjBase& enemy, GameObjBase& arrow)
//{
//    auto& e = static_cast<Enemy&>(enemy);
//    auto& a = static_cast<StoneArrow&>(arrow);
//
//    e.handleHit(e, a.getDamage());
//    a.setDisappear(true);
//}


////----------------------------- boxFloor ---------------------------------
//// Handle the event that the box collides with the floor.
//// Push back the box from the floor.
////------------------------------------------------------------------------
//void boxFloor(GameObjBase& b, GameObjBase& f)
//{
//    static_cast<Box&>(b).handleCollision(static_cast<Block&>(f));
//}


////------------------------- arrowStaticObject ----------------------------
//// Handle the event that the arrow collides with the a block.
//// Disappear the arrow.
////------------------------------------------------------------------------
//void arrowStaticObject(GameObjBase& arrow, GameObjBase& floor)
//{
//    arrow.setDisappear(true);
//}


    //---------------------- setPlayerCollisionHandling ----------------------
    // Insert all the players collision functions into the map Data Structure.
    //------------------------------------------------------------------------
    void setPlayerCollisionHandling(HitMap& phm)
    {
        //// Player & floor.
        phm[MapKey(typeid(Player), typeid(Floor))] = &PlayerFloor;

        // Player & Diamond.
        phm[MapKey(typeid(Player), typeid(Diamond))] = &playerDiamond;

        //// Player & ExtraLife
        //phm[MapKey(typeid(Player), typeid(ExtraLife))] = &playerExtraLife;

         //// Player & ExtraPower
        //phm[MapKey(typeid(Player), typeid(ExtraPower))] = &playerExtraLife;

        //// Player & Monster
        //phm[MapKey(typeid(Player), typeid(Bear))] = &playerEnemy;

        //// Player & Door
        //phm[MapKey(typeid(Player), typeid(Door))] = &playerDoor;
    }


    //---------------------- setEnemyCollisionHandling -----------------------
    // Insert all the enemy's collision functions into the map Data Structure.
    //------------------------------------------------------------------------
    void setEnemyCollisionHandling(HitMap& phm)
    {
        //// Bear & Block.
        //phm[MapKey(typeid(Bear), typeid(Block))] = &enemyFloor;

        //// Bear & player.
        //phm[MapKey(typeid(Bear), typeid(Player))] = &bearPlayer;

        //// Bear & Box.
        //phm[MapKey(typeid(Bear), typeid(Box))] = &enemyBox;

        //// Bear & Arrow.
        //phm[MapKey(typeid(Bear), typeid(StoneArrow))] = &enemyArrow;

        //// Bear & FireArrow.
        //phm[MapKey(typeid(Bear), typeid(FireArrow))] = &enemyArrow;


        //// Wolf & Block.
        //phm[MapKey(typeid(Wolf), typeid(Block))] = &enemyFloor;

        //// Wolf & Player.
        //phm[MapKey(typeid(Wolf), typeid(Player))] = &wolfPlayer;

        //// Wolf & Box.
        //phm[MapKey(typeid(Wolf), typeid(Box))] = &enemyBox;

        //// Wolf & Arrow.
        //phm[MapKey(typeid(Wolf), typeid(StoneArrow))] = &enemyArrow;

        //// Wolf & FireArrow.
        //phm[MapKey(typeid(Wolf), typeid(FireArrow))] = &enemyArrow;


        //// Crow & block.
        //phm[MapKey(typeid(Crow), typeid(Block))] = &enemyFloor;

        //// Crow & Player.
        //phm[MapKey(typeid(Crow), typeid(Player))] = &crowPlayer;

        //// Crow & Box.
        //phm[MapKey(typeid(Crow), typeid(Box))] = &enemyBox;

        //// Crow & Arrow.
        //phm[MapKey(typeid(Crow), typeid(StoneArrow))] = &enemyArrow;

        //// Crow & FireArrow.
        //phm[MapKey(typeid(Crow), typeid(FireArrow))] = &enemyArrow;
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

        //setEnemyCollisionHandling(phm);

        //setStaticCollisionHandling(phm);

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
