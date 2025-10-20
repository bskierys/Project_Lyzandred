# Project Lyzandred

The goal of this project is to learn Unreal Engine 5 basics during the course
`Unreal Engine Developer`. This project will be used to submit tasks and general
practice of development. The end goal is to publish it as addition to my
portfolio.

## Game Overview

Below you can find the basic game concept. Be aware that it may change based on
the timeline, user feedback and what will be needed to practice during the
course.

* **Genre**: 3D platformer with puzzle and combat elements
* **Core Concept**: The player controls three heroes — *Knight*, *Rogue*, and
*Mage* — who are magically bound together and must escape a mad wizard’s
dungeon. Success relies on fluid character switching to combine their unique
abilities across three gameplay pillars:
	* Platforming
	* Simple Combat
	* Environmental puzzles
* **Tone & Style**: Cartoon-like visuals with slightly muted colors,
dark-fantasy dungeon environments occasionally blending into themed biomes 
(forest, tundra, corrupted lands).

## Project Documentation

* Requirements, game concept, phases and their scope can be read [here]
(https://docs.google.com/document/d/1DrvJXb6CEkmLhxYdb8WuErr3_Md8C4HMcQFWw5wo65E/edit?tab=t.q6uybdcipmha).
* Project [Trello Board](https://trello.com/b/fafrFQdF/project-lyzandred).
* See the [`CHANGELOG.md`](CHANGELOG.md) for full history of the project.
* For Each of the tasks from the class, separate Readme file will be created for
clarity. Naming example: `README_TASK_3.md`.

## Character Controlls

The game will have a tutorial or in game page about Character Controlls, but
until then here is the list of user input. The below mapping is listed for Xbox
Controller (Dual Sense) / Mouse with Keyboard.

** Note: ** The game is being designed primarily for Game Controller.

* Left Thumbstick / WSAD – Move
* Right Thumbstick / Mouse – Look around
* A (Cross) / Spacebar – Jump, Double Jump
* X (Square) / Left Mouse Button – Primary Ability
* RT (R2) / Shift Key – Secondary Ability while holding
* RB (R1) / E Key - Next Character Form
* LB (L1) / Q Key - Previous Character Form
* Y (Triangle) / F Key – Interact (contextual)
* Right Thumbstick (R3) / G Key – Attention Whistle
* Menu (Start) / P Key – Game Pause
* Left Thumbstick (L3) / Backspace – Character Showcase

Rogue
* Primary Ability: Dash (Slide if sprinting on the ground)
* Secondary Ability: Sprint
* Other: Double Jump

Mage
* Primary Ability: Magic Pulse
* Secondary Ability: Light
* Other: Can use portals

Knight
* Primary Ability: Sword Attack
* Secondary Ability: Raise Shield
* Other: Wall Jump

## Used Assets

For the purpose of publishing the project, here is the list of resources used to
give credit.

* [Devvy Platformer Assets](https://devenabled.itch.io/devvy-channel-mascot-project)
* [Stylized Fire Assets](https://www.unrealengine.com/marketplace/en-US/product/stylized-fire-effects?sessionInvalidated=true)
* [KayKit - Dungeon Remastered Pack](https://kaylousberg.itch.io/kaykit-dungeon-remastered)
* [KayKit - Character Pack : Adventurers](https://kaylousberg.itch.io/kaykit-adventurers)
* [KayKit - Character Pack : Skeletons](https://kaylousberg.itch.io/kaykit-adventurers)

## Troubleshooting

Useful links for working with the project.

* P4 Helix server may not start by default. Use [this guide]
(https://portal.perforce.com/s/article/2463).
* If Unreal don't compile with code 6, be sure to disable Live Coding and choose
Rider Configuration : `DebugGame -> Editor`.
* Here is the link to [basic markdown sytax]
(https://www.markdownguide.org/basic-syntax/) for formatting this document.