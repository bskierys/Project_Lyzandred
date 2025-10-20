# Changelog - Project Lyzandred

Delow is the list of changes made to the project with dates and connection to
Trello task. Ideally this should be mirrorred in P4 changelist.

As for the `Unreal Engine Developer` project, we don't submit the project
through P4 server, but rather through the Google Drive, I created this file for
the tutors to have glimps into my workflow.

* Requirements, game concept, phases and their scope can be read [here]
  (https://docs.google.com/document/d/1DrvJXb6CEkmLhxYdb8WuErr3_Md8C4HMcQFWw5wo65E/edit?tab=t.q6uybdcipmha).
* Project [Trello Board](https://trello.com/b/fafrFQdF/project-lyzandred).

## Phase 1: Prototype 1

The phase scope can be summarised as follows:

* A single vertical slice level that showcases platforming, combat, and puzzle
  switching.
* Prove fun in character swapping and responsive controls before expanding
  content.

### 2025-08-31

* LYZ-8: Initial Project Lyzandred setup in P4.
    * Empty Unreal Engine 5.5.4 Project created with base file structure.
    * Changelog, Readme, links to documents.
    * Submitted to P4 server.

* LYZ-9: Simple Character Model and Movement.
    * Add Sample Character Model.
    * Basic movement including jump, double jump, wall slide, sprint.

### 2025-09-01

* LYZ-10 [Coins] Create Simple coins of different types (1/5/10) that character
  can pick up.
    * Create pickable coins that inherit from the same class.
    * Different coin value: Copper - 1, Siler - 5, Gold - 10.
    * Add rotating animation and pickup sound.
    * Add simple widget tracking current value of picked coins.

* LYZ-23 [Coins] Create a widget pop animation when coin collected.

* LYZ-14 [Coins] Chest with parameters that spawns coins.
    * Possibility to spawn coins of different values.
    * Widget hinting possible interaction.

* LYZ-13 [Coins] Horizontal and Vertical line of Coins with parameters in
  Editor.
    * Coins spawned on the editable vector. Editable quantity.
    * Circle coins spawner with editable radius and quantity.
    * All spawners can be attached to moving platforms.

### 2025-09-02

* LYZ-20 [Prop] Create a torch that emits light.
    * Torch with stylized effect.
    * Flickering Light Material. Torch attaches created Dynamic Instance of it.

* LYZ-32 [Coins] Add Pause with menu.
    * Chore: Optimise Torch performance by turning the flickering off.

### 2025-09-03

* LYZ-12 [Character] Character Kill and Destroy handling.
    * Added widget with sound and animation to present character death.
    * Respawn Character at the Player Start.

* LYZ-18 [Traps] Add new types of traps with inheritance.
    * Spikes on the floor,
    * Rotating column with spikes,
    * Rotating flamethrower,
    * Kill Flat Surface.
    * Intersecting with collision kills the character.

### 2025-09-04

* LYZ-26 [Level] Build simple level with landscape.
    * Showcase all currently available mechanics.

* LYZ-26 [Level] Adjustements to demo level.
    * Change Poison to Lava (colors)
    * Change steps to ramp for smoother approach to wall jump.

### 2025-09-06

* LYZ-47 [Traps] Fix C++ inheritance in Traps

* LYZ-38 [Props] Dungeon Tunnel Corner BP implementation.
    * Implemented Actors for tunnel, corner and wall.
    * Actors written in C++ with inheritance.

* LYZ-29 [Level] Build a Labirynth with torches to practice lightning and ISM.

### 2025-09-07

* LYZ-30 [Coins] Simplify the chest coin spawning through the usage of
  ChildActor.

* LYZ-22 [Coins] Introduce Inheritance in Coin Spawners.
    * Rewrite Spawners to C++.
    * Add Rectangle Spawner that is a child of the same parent as Line Spawner.

* LYZ-39 [Character] Summon magical light by pressing Q.
    * Summon light with VFX frost flame effect.
    * Flickering light effect.
    * Camera close-up over character arm.

### 2025-09-08

* LYZ-22 [Coins] Introduce Inheritance in Coin Spawners.
    * Add mapping UObject to reduce copied code
    * Try UObject strategy pattern for spawners (rejected for lack of visual
      widget for rectangle spawner, but left in code for future reference)

* CHORE: Refactor of C++ code and tidying up the assets a little. Add missing
  files to Perforce.

* LYZ-28 [Coins] Add param for fixed distance between coins in the coin line
  coin spawner.

### 2025-09-09

* LYZ-31 [Props] New "Interact" props. Extract the "Interact" logic as Blueprint
  Component.
    * Add the door actor that swings open away from the character and can be
      closed 

* LYZ-32 [UI] Move Pause Button to a separate Input Mapping Context.

* Fix LYZ-47 [Level] Bug: Camera is "Jumping" during wall jump on the Landscape Level.

### 2025-09-10

* LYZ-31 [Props] New "Interact" props: Lever.
    * Simple Lever that changes position. No customization options.
    * Update the Mesh for doors.

* LYZ-61 [Level] Add meshes for more pickups for complex level in Task 5.

### 2025-09-12

* LYZ-54 [Save] Base for checkpoint.
    * Create an actor for checkpoint.
    * Stone Arc that has a pulsing glow when active.
    * No logic for now.

* LYZ-65 [Traps] Make a Lava Glow
    * `BP_Lava` Trap Actor with glow effect (material and rect light).
    * Possibility to turn off light per instance for optimization.

* LYZ-61 [Level] Build a more complex level with sublevels for task 5.
    * Create A loaders that load/unload level. They also load level on
    collision.
    * Added LevelLoaderManager where you can add reactions to the event of a
    level being loaded.
    * Loading Manager also unloads all the other levels when one is loaded.

* LYZ-55 [Level] Create another level with the goal reaching the end of it.
    * As simple as possible using the existing components.
    * Improving the level in the separate task.

* LYZ-46 [Coins] Make coin texture a little emissive to glow in the dark.

### 2025-09-13

* LYZ-61 [Level] Build a more complex level with sublevels for task 5.
    * Load / Unload Act 1 with the whole landscape.
    * Make a hole in landscape for the tunnel.

### 2025-09-14

* LYZ-54 [Save] Checkpoints.
    * Simplified checkpoint system.
    * In Player Controller, Position is saved from latest checkpoint
    * Checkpoint that is active is glowing
    * Only one active checkpoint at a time
    * When Character dies it is respawned at last checkpoint

* CHORE: Small fixes after review
    * Remove additional semicolon in Lyz_Coin.
    * Add check if `GetWorld` is valid.

* LYZ-63 [Props] "Key" actor whose collection is saved so that we can change the
logic based on it.
    * Created a generic system of flags / keys that are set on the level and
    that actors can react to.
    * Added a simple actor that is a key and marks a flag when collected.
    * Added an Actor component that alters the door to be unlocked based on the
    collection of required keys.

* LYZ-61 [Level] Build a more complex level with sub-levels for task 5.
    * Create an empty Main Menu level, which will take you to the MainLevel
    level after 5 seconds.
    * Added Evil Book - Key that is required to open door to Act2.
    * Added Game Exit when reached end of Act2.

* LYZ-67 [Props] Only "Open" interaction with door. They should close
automatically some time after character end overlap.

### 2025-09-15

* LYZ-79 [UI] Change the interaction icon from traingle to keyboard "F".

* Fix LYZ-65 [Bug] Loading level multiple times, spawns multiplied coins.

### 2025-09-16

* LYZ-77 [Level] Improve the lightning in the loading tunnels.

* LYZ-70 [Loading] Change loading reaction from centralised model to actor components.

* CHORE: Group level objects in Main Level into folders.

* LYZ-78 [Props] Add portal to beginning of the level.
    * Interactable portal that can be linked with the other. When Interacted, it
    will teleport the player to the other portal.
    * When made Interactable, it will appear with simple animation.

### 2025-09-18

* Fix LYZ-82 [Bug] Killing character without checkpoint moves it to PlayerStart
without unloading a level.
    * Fixed by setting actor on the scene in a different way. It's impossible to
    leave the tunnel without passing the gate.
    * Added option to turn off the auto-closing of the door to prevent camera
    clipping with closed doors.

* LYZ-83 [Level] Improve the lightning in the dungeon tunnel.
    * Added option for torches to have more intensity and radious to have more
    control over lightning.

* Fix LYZ-89 [Bug] Camera collides with the spiked pillar.

* LYZ-80 [Code] Add BFL to automatically cast to my pawn.
    * Both cpp and BP level.
    * Replaced the code in the project.

* LYZ-71 [Level] Sublevel should load when the loader is crossed in one direction and
unload on the other.
    * Added an Arrow component to ease placing in the world. 

* LYZ-90 [Props] Improve portal material.
    * Add purple, swirling, glowing material for the portal.

### 2025-09-19

* LYZ-84 [Loading] Change the filling of the list in loading manager from "find
all actors on scene" to dependency inversion.

* Fix LYZ-88 [Bug] Unbind dispatchers.
    * Unbound both in actor and owner of dispatcher:
    * Key changed events.
    * Respawn position changed events.
    * Level Loaded events.

* LYZ-69 [Chore] Tidy-up the project.
    * Group Content into folders.
    * Move them from imported to the `Lyzandred` directory.
    * Rename the files to match convention.

### 2025-09-20

* LYZ-86 [Cutscene] When the character enters the Act1, cutscene to show the
level.
    * Triggered on level entrance.
    * Extracted Glowing Static Mesh Component to use on Keys and Checkpoint.
    * Added outline to the coins.

* LYZ-87 [Cutscene] Cutscene on button.
    * Press L3 or Backspace to change the camera and play one of three random
    Anim Montages.
    * To be replaced later on with better montages when I work on animations.

* LYZ-85 [UI] Revamp the look and feel of UI widgets.
    * Changed: Pause menu, HUD, Dialogues, Interaction Prompt.
    * Added Hud Actor.
    * Modified sequencer to show/hide hud during the cutscene.

* LYZ-94 [Cutscene] Prompt during the cutscene.

* LYZ-90 [UI] Animating coin in the HUD.

### 2025-09-22

* LYZ-16 [Character] Change types of character – simple color change and
ability base.
    * RB/LB to switch between forms. Indicated by a simple material color
    change.
    * When form switched, Key is added to the game state that can be checked by
    any object in the world. Any object can also subscribe to change.
    * Dash and Sprint Available only to Rogue. A light available only to Mage.

* LYZ-105 [Props] Slower rotation of coins.

### 2025-09-23

* LYZ-108 [Character] Blinking animation for character switching.
    * Created as `ActorComponent` in Cpp
    * Parameters to set time and blink intervals.

### 2025-09-24

* LYZ-97 [Character] Jumping: Different Heights of Jump. Only Rogue can double
jump.

* LYZ-100 [Character] Only Knight should Wall Jump, Rogue fast wall slide, Mage
no wall interaction.
    * All the character attributes are done on DataAsset to allow for easy
    tweaking by the designer.

### 2025-09-26

* LYZ-103 [Character] Allow Double Jump after Wall Jump.

* LYZ-96 [Bug] Sliding off the wall makes the character float or even fly.

* LYZ-17 [Character] Allow only Rogue to double jump, sprint and dash.

* LYZ-117 [Character] Restore Change of Dash speed based on the Character
Velocity.

* LYZ-99 [Character] Restore Slide ability to Rogue.
    * Character speeds up when sliding and plays animation montage.
    * Properly handle jumping and sprint interaction with sliding.
    * Interaction between various jumps and sliding.

* LYZ-118 [Character] Fully Replace old Character with Triform.
    * Replace all the instances without renaming the asset.

* CHORE: Remove unnecessary spawner classes.

### 2025-09-27

* LYZ-115 [Character] Change KillCharacter to interface or component to avoid
direct reference to pawn.
    * Added Killable Interface. This will allow traps to kill enemies.

* LYZ-114 [UI] Change coin value to subscribe to changes instead of setter.

* LYZ-116 [Character] Ability Components improvements.
    * Ability Components are now not blueprint spawnable.
    * Throw error when not attaching to `Lyz_TriformCharacter`.

### 2025-09-28

* LYZ-58 [UI] Main Menu.
    * Main Menu with a button to start the game. 
    * Possible to control with the mouse or controller.

* LYZ-58 [UI] Main Menu.
    * Add a scene as a background of the menu.
    * Start Game and Quit buttons are working.

* LYZ-81 [Props] Make Interactable Props an Actor reusable.
    * Moved some logic to Interactable Component.
    * Rewritten Interactable Interface to Cpp.
    * Move the property of being interactable to the component.

* Fix LYZ-98 [Bug] Key change not affecting interaction prompt when character
already is overlapping.
    * Interactable Component is a single place of truth for property of
    being interactable and reacts on dynamic changes of the key.

* LYZ-111 [CPP] Move Interactable Interface to Cpp.

### 2025-09-29

* LYZ-125 [Magic] Highlight objects that can be affected by magic when in mage
form.
    * Created `ActorComponent` that can be attached to any actor with mesh.
    * Actor gets glowing overlay when PlayerCharacter is in Mage form.

* LYZ-123 [Refactor] Remove BP BFL from project.

* LYZ-124 [Props] Portal appears when the key is collected, but only Mage Form
can enter it.
    * `BP_UnlockableComponent` not takes an object with function that determines
    what should happen when required keys are collected.

* LYZ-73 [UI] Create a "toast" — a simple UI that can display a short text for a
few seconds and then disappear.

* LYZ-130 [Props] When an object requires key and player character approaches,
display short toast why an object not interactable.

### 2025-09-30

* LYZ-51 [Magic] Platform becomes solid when a button pressed in close distance.
    * When Primary Ability activated as Mage, toggle all “magical” objects in
    the area.
    * Switch between a solid and invisible object with no collision.
    * Works only in close distance, but more than just object box overlap from 
    the character
    * Currently works only on simple meshes.

* LYZ-135 [Level] Add Magic platforms to the main level.

* LYZ-136 [Level] Add simple tutorial prompts to Main Level.

### 2025-10-01

* LYZ-51 [Magic] Platform becomes solid when button pressed in close distance.
    * Changed the reveal logic to appear only when we are in mage form and
    disappear when the player switches form to something else.

### 2025-10-02

* Fix LYZ-144 [Bug] Magic Sphere triggers Collecting Key.

* LYZ-145 [Magic] Try: Magic objects are never solid to other forms. Only mage
can jump on them.

* Lesson 20: Add a simple enemy that goes towards an actor.

### 2025-10-03

* LYZ-133 [Magic] Magic reaction that enables/disables gravity of an object.

### 2025-10-04

* LYZ-148 [Magic] Magic reaction that controls moving platforms.
    * Magic to pause or reverse the movement of the infinite falling platform.
    * Rotating platforms with movement possible to reverse or pause.

* LYZ-149 [Enemy] Separate Test Chamber for Enemies and Combat

### 2025-10-05

* LYZ-140 [Character] ABP for Mage.
    * Base ABP animation.
    * Light casting animation.
    * Magic Casting animation.
    * Adjust Light to match Staff animation.

* LYZ-131 [Character] ABP for Knight.
    * Base ABP animation.
    * Shield block animation.
    * Simple attack animation.

* LYZ-152 [Character] ABP for Rogue.
    * Base ABP animation.
    * Sprint animation.

* LYZ-156 [Character] Simple Showcase Animation for new models.
    * Simple Cheer animation for each of models.

* LYZ-160 [Character] Add Force Feedback to Mage Spellcast.

* LYZ-139 [Character] Cast animation for light spell.

* LYZ-154 [Character] Dash animation for new models.

* LYZ-155 [Character] Ground Slide animation for new models.

* LYZ-153 [Character] Wall Slide animations for new models.
    * Wall Slide Knight Animation.
    * Wall Slide Rogue Animation.

### 2025-10-06

* LYZ-159 [Enemy] ABP for basic enemy (skeleton).

* LYZ-171 [Props] Add dice as infinite falling objects
    * Imported Dice Static Mesh and Textures.
    * They can be attached to an Infinite falling platform actor.

### 2025-10-08

* LYZ-181 [Enemy] Basic enemy AI: Patrol + chasing player when seen.

* LYZ-143 [Bug] When chest/box/die is marked as magical, it does not glow in
Mage Form.
    * Removed Nanite from some objects. Nanite prevents Overlays from working.
    * Removed HeightMap from Dice as it was making a texture higher than 
    overlay.

* LYZ-179 Create a custom default collision channel "BlockAllButCamera".

### 2025-10-09

* LYZ-92 [Platforming] Mushrooms that character can bounce off.

* Fix LYZ-186 [Bug] Magically Hidden objects still generate overlap Events.

* LYZ-184 [Character] Knight air attack does ground pound that allows you to
jump higher on the bouncy mushrooms.
    * Ground pound based on Anim Montage.
    * Additional effect of screen shake and force feedback.

### 2025-10-11

* LYZ-164 [Combat] Skeleton attacks kills character.
    * Skeletor Minion performs basic attack that can kill a character.

* LYZ-187 [Enemy] Patrolling Enemy that reacts to whistle.
    * Basic patrolling enemy that starts chasing character if they whistle.
    * Enemy plays animation when noticing character and when going back to
    patrol. Also, their speed is changing depending on a state. 
    * Multiple Enemies that can patrol and chase the player character together.
    * Investigation mode after hearing a sound

* LYZ-191 [Combat] Enemy can be killed

### 2025-10-12

* LYZ-190 [Enemy] Enemies don't forget about the player immediately after they
stop seeing them.
    * Enemies will start investigating and looking for player. If they find
    them, they will resume chasing them.
    * Switching between states using the Behavior Tree.

* LYZ-163 [Combat] Knights attack kills skeletons.

* LYZ-192 [Combat] Improve the feeling and range of Knight's Attacks.
    * Improve the range and effects for both Knight's attacks and Skeleton
    attacks.

* Fix LYZ-194 [Bug] Enemies have their box collision blocking the path after
they die.

### 2025-10-16

* LYZ-196 [Character] Make Knight much slower and heavier to move around and
enemies faster. Knight should be slow but strong.
    * Different Movement Speed for characters. Knight moves slowest.
    * Slowed down the attack speed of a knight but adjusted the effects to make 
    it look more powerful.

* LYZ-197 [Combat] Throttle attacks to apply damage only once per attack.

* LYZ-198 [Combat] Common attack component to remove code duplication

* LYZ-188 [Enemy] An enemy behavior that is wandering in some radius from the
area.
    * Moved Movement Mode from enum to data assets.
    * Moved Passive state to behavior `UObject`.

### 2025-10-17

* LYZ-189 [Enemy] Enemies that Spawn When The player character moves to a
certain area (not based on senses).
    * Fixed a bug with sword attack clashing with non-killable actors.
    * Enemies will spawn and chase the player if a player enters the area.
    * If Player Character leaves the area they lose the sight of them in some
    time.

### 2025-10-20

* Fix LYZ-200 [Bug] Enemies will not forget Actor that they have never seen.
    * Separate forgetting and losing actor for all senses.
    * Turning off perception for unspawned enemies.

* LYZ-205 [Enemy] Enemies should return to patrol area running.

* LYZ-209 [Level] Level Loading Subsystem.
    * Deleted `LevelLoadingManager`.
    * Removed all level loading logic from `LevelLoader`.
    * Moved all the logic to a new World Subsystem `LevelLoaderSubsystem`.
    * Updated `BP_SwitchOnOnLoadComponent` to use Subsystem.
    * Added Data Asset representing levels.