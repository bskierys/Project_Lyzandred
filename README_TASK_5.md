# README for Task 5: Main Level

## Character Controlls

The game will have a tutorial or in game page about Character Controlls but
until then here is the list of user input.

Below mapping is listed in format "Xbox Controller (Dual Sense) / Mause with
Keyboard".

** Note: ** The game is being designed primarly for Game Controller.

* Left Thumbstick / WSAD – Move
* Right Thumbstick / Mouse – Look around
* A (Cross) / Spacebar – Jump, Double Jump
* RT (R2) / Shift – Sprint while holding
* X (Square) / Left Mouse Button – Dash (Slide if sprinting on the ground)
* Y (Triangle) / F – Interact (contextual)
* LT (L2) / Q – Magical Light while holding
* Menu (Start) / P – Game Pause

## Level introduction

* The game opens at the `L_Landscape` map. I included some gameplay there.
* It is said there is a treasure at the center of the Dungeon on top of the
mysterious hill. Can you reach it?

*Level Tip*: Sprint allows longer jump. Sliding before jump even further. For
super long jump: Sprint -> Slide -> Double Jump (before end of slide) -> Dash.

## Task 5

### Level flow

* The game should start with `L_MainMenu` where you will be redirected to `L_MainLevel` after 5 seconds.
* The "NPC" will tell you to go to the ACT1 and find an evil book. It is hidden in the center of the Labirynth.
* Then you have to go back, and travel to ACT2. When you reach the exit, the game quits (after you go through the door).

Know issues:
* I forgot to change the starting level in the Project Settings. Sorry for that.
* There is annoying backtracking with bringing the book back. I implemented a teleport (solution is in TestChamber), but I had a bug and did not have time to fix it so I removed them. But If you die, you still have the book collected (another known issue).
* There are some very temporary solutions in the code.

### Sublevels

* I've added two solutions here:
	* LevelLoader is reponsible for loading a sublevel. The aim is to load level when character goes through tunnel.
	* LevelLoadingManager gets all the loaders from level. When one loads, manager asks other loaders to unload their level
	* There is also an Actor component attached to some actors that is responsible for reaction on level loaded: torches light up, doors open.

### Keys

* I've added a system of keys that is stored in `GameState`. You can create and choose an aset with `DataAssets`.

### Event Dispatchers

* After Loading/Unloading a Level
* When the Key is collected, GameState notifies the listeners.

## Task 4

### Inheritance

I wanted to understand inheritance and connection between BP and Cpp in Unreal
better so I spent significant amount of time on that area. I know this will be
partially discussed later, but I learn more when I experiment before someone
tell me how to do it, so I can clearly see my mistakes.

* Coins:
	* `ALyz_CoinPicup`, `ULyz_CoinType`, `BP_CoinBase`, `BP_CoinCopper`,
	`BP_CoinSilver`, `BP_CoinGold`
	* Done in similar manner as in Sifuri. Each coin has different value that is
	added to the widget visible on the screen.
* Traps:
	* `ALyz_Trap`, `BP_SpikeTrap`, `BP_KillingPlane`, `BP_Flamethrower`,
	`BP_SpikedPillarTrap`
	* All inherit from a class `Lyz_Trap` in C++. They have implemented a single
	common method to kill a character
* Dungeon Tunnels:
	* `BP_DungeonTunnel`, `BP_DungeonCorner`, and `BP_DungeonTunnelWall` have
	all the construction script done in Cpp. They are using ISM to optimise draw
	calls.
	* Tunnel and Corner have common base class. 

**Note:** Later on I discovered that everything can be build witch just tunnels
and walls so it would be better for them to have single parrent or use each
other, but I wanted to avoid another refactor so I left it there. It caused me
enough crashes of the Editor.

* Spawners:
	* `BP_CircleCoinSpawner`, `BP_RectangleCoinSpawner`, `BP_LineCoinSpawner`
	inhertits from `ALyz_CircleCoinSpawner`, `ALyz_RectangleCoinSpawner`,
	`ALyz_LineCoinSpawner`. They have a common base of `ALyz_CoinSpawner`

**Note**. I had a couple of iterations here.
* Each of these spawners had quite complex spawning grapf in BP, and I wanted to
move this part to Cpp. But coin actors to spawn were defined in BP only.
* I started with mapping done in BP and duplicated in every spawner. 
* In next iteration I tried to implement a strategy design pattern using
Instanced `UObject`. You can see the result in `SpawnStrategy` directory in Cpp
and in `BP_RectangleCoinSpawnerWithStrategy`. Unfortunately, with the params in
generic SpawnStrategy I was not able to use the 3d widget in editor which made
the solution less designer-firendly. I resigned from this solution, but the code
for now (to reference when writing more later).
* In the last iteration, I used the pattern from previous iteration to create
`ULyz_CoinMapper` and use it to use BP code (`BP_CoinMapper`) in Cpp.

### Input and Sprint

I copied sprint from another sample project, so not the best example. But I
implemented other movement options myself.

* RT (R2) / Shift – Sprint while holding (copied).
* X (Square) / Left Mouse Button – Dash (Slide if sprinting on the ground).
* Left Thumbstick / WSAD – Move. I did not like how the character is turning
slowly. I wanted more "snappy" turning so I implemented character turning around
in Blueprint.
* LT (L2) / Q – Magical Light while holding. It also has flickering nice
material.

### Game Pause

* Menu (Start) / P – Game Pause. 
* Added through new IMC.
* I've added simple pause widget so it's clear how to unpause (static text for
now).

## Task 3

### Resources picked on collision

* Rotating coins in the game world. When character picks it up, sound cue is
played and value in Game State is updated.
* Simple Widget with animation when coin is picked up.
* 3 types of coins: Copper (worth 1), Silver (worth 5), Gold (worth 10).
Different shape, material instance. Inheritance based on UObject.
* I also implemented spawners to easier place coins on the level editor:
	* Circle spawner (radius param, you can specify coins)
	* Line spawner (line vector param, you can specify coins)
	* Chest (uses circle spawner), that opens on interaction. I forgot that I
	can add child actor, so the code there is a little messy.
	* More on inheritance here in Task 4.

### Static Meshes 

* From Geometry
	* Coin static meshes
	* Traps static meshes: rotating pillar and spikes on the ground
	* Stairs leading to tunnel

* Imported
	* Chest asset
	* Torch asset
	* Fire niagara effect for torches and flamethrower
	* Tunnel assets: walls, floor, ceiling, column

* Instanciated Static Meshes
	* Tunnel is build using Bluprint that adds ISM to its scene root
	dynamically. But the code in Construction Script is awful. I yet have to
	refactor it. I also added BP struct to handle parameters. I'm also not proud
	of this part.
	* Spike Trap Blueprint also uses ISM for spikes.

### Lightning

* Torches on the wall are emmiting static point light
* I made it flicker a little bit using material, if "Flicker Light" is checked
in BP instance on the map.

### Landscape

* For Landscape go to map `L_LandscapeTest`. There is a placeholder for the
Labirynth, but I only finished one tunnel with traps. There is a reward at the
end of it.
* There is also `L_TestChamber`, where I tested mechanics in isolation.

### Enemies (Traps)

Intead of enemies, I implemented traps. The idea is similar for now – on
collision kill the character (I don't plan any health for the character).

* Spike trap – Rows, Cols, Gap controlled from editor
* Spiked Pillar – Movement Vector and movement duration can be specified.
* Flamethrower
* Killing plane – for faling off the map (KillZ caused me some problems), and
dangerous surfaces (e.g. lava)
