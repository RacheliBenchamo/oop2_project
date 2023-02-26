Ahutors : Racheli Benchamo & Yarden Cohen

The Diamonds Fighter is a 2D platform game with an emphasis on exploration and collecting
diamonds to open the gate to the next stage. The player controls male or female character,
and must jump, climb, fight the monsters, and use various other abilities to navigate the
game's world and finish the different stages.

The program accepts as input in the Resources folder a file containing all the stages, and
where in the first row of each stage appears the size of the board and the type of that stage
(forest, desert, or snow). Each level has to contain one gate and an even number of teleports.

Collect all the diamonds and enter the gate to the next stage while fighting the monsters.
Each collision with a monster reduces the amount of life of the player depending on the type.
Every fight against a monster reduces the amount of power a player has. If the player runs out
of life, he dies and must repeat the stage anew. The player can replenish the stock of life
and power by pressing the Z button when standing next to a potion that fell from a monster he/she killed.

There are various classes that manage different aspects of the game, such as the Controller,
FileManager, Screen, GameScreen, MenuScreen, HelpScreen, WinLevelScreen, WinGameScreen,
LoseLevelScreen, Board, StatusBar, DataBase, GameObjBase, MovingObj, StaticObj, Player,
Monster, Gate, Diamond, Rope, Teleport, Potion, and StageDec.

There is a more detailed README within the project itself.
Enjoy!
