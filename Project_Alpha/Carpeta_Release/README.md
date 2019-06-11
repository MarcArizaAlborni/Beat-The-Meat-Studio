## Game Description

The game consists in a 1 vs 1 duel between two characters, each with the same moveset and playstyle. There are two win conditions: The player who knocks out the other by reducing their opponent's health bar to zero wins or the player that has the most health out of the two when the time runs out (99 seconds) wins the round. The first to win 2 rounds wins the duel.



## Team Members:

- Adrian Mirabel (GitHub Link: [M1R4B3L](https://github.com/M1R4B3L))
- Marc Ariza (GitHub Link: [MarcArizaAlborni](https://github.com/MarcArizaAlborni))
- Pau Pedra (GitHub Link: [OuEsquerra](https://github.com/OuEsquerra))
- Angel Gonzalez (GitHub Link: [BarcinoLechiguino](https://github.com/BarcinoLechiguino))



## Game Control Keys

### Player One (left):

#### Keyboard Control Keys:

**Movement input Keys:** 

- Go Left: A Key
- Go Right: D Key
- Jump: W Key
- Crouch: S Key

**Punch Input Keys:** U Key (LP), I Key (MP), O Key (HP)

**Kick Input Keys:** J Key (LK), K Key (MK), L Key (HK)

**Grab Input:**  "_Wild Fang_": A or D + HP

**Special Attack Inputs:**  

- "_Electric Thunder_": Repeatedly press in a short time span any punch input key.  

- "_Rolling Attack_":  (Left side) Holding A + D + Any Punch Input (D and punch input need to be simultaneous). (Right side is the same but with LEFT and RIGHT switched)

  

#### Gamepad Control Scheme (XBOX controller):

**Movement inputs:**

- Go Left: D-pad LEFT Button or Joystick to the LEFT
- Go Right: D-pad RIGHT Button or Joystick to the RIGHT
- Jump: D-pad UP Button or Joystick UP
- Crouch: D-pad DOWN Button or Joystick DOWN

**Punch Input Button:** X Button (LP), Y Button (MP), LB Button (HP)

**Kick Input Button:** A Button (LP), B Button (MK), RB Button (HK)

**Grab Input:**  "_Wild Fang_": D-pad LEFT / Joystick LEFT or  D-pad RIGHT / Joystick RIGHT + HP

**Special Attack Inputs:** 

- "_Electric Thunder_": Repeatedly press in a short time span any punch input button.  

- "_Rolling Attack_":  (Left side) Holding D-pad LEFT or Joystick LEFT + D-pad RIGHT or Joystick RIGHT + Any Punch Input (D-pad RIGHT / Joystick RIGHT and punch input need to be simultaneous). (Right side is the same but with LEFT and RIGHT switched)

  

#### Character Select Screen:

**Pointer Movement inputs:** 

- Left: A Key or D-pad LEFT / Joystick LEFT
- Right: D Key or D-pad RIGHT / Joystick RIGHT
- Up: W Key or D-pad UP / Joystick UP
- Down: S Key or  D-pad DOWN / Joystick DOWN

**Character Select Input:** U Key or X Button



### Player Two (Right):

#### Keyboard Control Keys:

**Movement input Keys:** 

- Go Left: LEFT Key
- Go Right: RIGHT Key
- Jump: UP key
- Crouch: DOWN Key

**Punch Input Keys:** (Numeric Keyboard) Num_7 Key (LP), Num_8 Key (MP), Num_9 (HP)

**Kick Input Keys:** (Numeric Keyboard) Num_4 Key (LK), Num_5 Key (MK), Num_6 (HK)

**Special Attack Inputs:** 

- "_Electric Thunder_": Repeatedly press in a short time span any punch input key.  

- "_Rolling Attack_":  (Right side) Holding RIGHT + LEFT + Any Punch Input (LEFT and punch input need to be simultaneous). (Left side is the same but with LEFT and RIGHT switched)

  

#### Gamepad Control Scheme (XBOX controller):

**Movement inputs:** 

- Go Left: D-pad LEFT Button or Joystick to the LEFT (Go Left) 
- Go Right: D-pad RIGHT Button or Joystick to the RIGHT () 
- Jump: D-pad UP Button or Joystick UP (Jump) 
- Crouch: D-pad DOWN Button or Joystick DOWN Key (Crouch).

**Punch Input Keys:** (Numeric Keyboard) Num_7 Key (LP), Num_8 Key (MP), Num_9 (HP)

**Kick Input Keys:** (Numeric Keyboard) Num_4 Key (LK), Num_5 Key (MK), Num_6 (HK)

**Grab Input:**  "_Wild Fang_": D-pad LEFT / Joystick LEFT or  D-pad RIGHT / Joystick RIGHT + HP

**Special Attack Inputs:** 

- "_Electric Thunder_": Repeatedly press in a short time span any punch input key.  
- "_Rolling Attack_":  (Right side) Holding D-pad RIGHT or Joystick RIGHT + D-pad LEFT or Joystick LEFT  + Any Punch Input (D-pad LEFT / Joystick LEFT and punch input need to be simultaneous). (Right side is the same but with LEFT and RIGHT switched)



#### Character Select Screen:

**Pointer Movement inputs:** 

- Left: LEFT Key or D-pad LEFT / Joystick LEFT
- Right: RIGHT Key or D-pad RIGHT / Joystick RIGHT
- Up: UP Key or D-pad UP / Joystick UP
- Down: DOWN Key or  D-pad DOWN / Joystick DOWN

**Character Select Input:** (Numeric Keyboard) Num_7 Key or X Button



## Game Debug Keys and Other Relevant Inputs:

**God Mode(player becomes invincible):** F1 Key

**Debug mode:** F2 Key

**Insta-Win Input Button:** F3 Key

**Insta-Lose Input Button:** F4 Key

**Input to reduce reduce Player 1's health:** F5 Key

**Input to reduce Player 2's health:** F6 Key

**Introduce Coin Input:** SPACE Key or BACK Button (Select)



## Changelist:

**v0.1:** 

- Implemented the possibility of scrolling an empty background.



**v0.2:** 

* Added a Welcome Screen, the First and Second level scenes and a Congratulation Screen. 
* Added a scene cycle functionality so the congratulation screen transitions into the welcome screen.



**v0.3:** 

- Added Player Movement (without collisions). 
- Added movement animations while the player is moving (Ryu) 
- Added the Hadouken as a particle that can be shot by the player.



**v0.4:** 

- Added colliders to the player(Ryu) and its particles(Hadouken) 
- Players can now collide with something in the environment. (Not done: Camera limits and God mode when pressing F5)
- Solved all current Memory Leaks.



**v0.5** 

- Added the win/lose conditions: Empty health bar or time runs out (99 seconds).

- Added 5 Scene transitions: Welcome Screen, Game Screen, Win/Lose Screen, Back to Welcome Screen.  

- Added Camera Limits so the Player cannot move out of the camera.

- Implemented the Audio Module.

- Implemented the pertaining music for each screen along with the pertaining sound effects for each movement and interaction.

- Added minimum debug functionalities such as God Mode (grants invincibility to the player), Collision Boxes Mode (shows the collision boxes on screen), both direct win and lose inputs as well as reducing both player's health.

- Implemented fully functional Health bars.

- Implemented Jump, one Kick and one Punch and one Special Attack.  (as state machine driven mechanics)

- Added the Ryu stage art with Ryu vs Ryu.

  

**v1.0**

- Blanka has been implemented as a new playable character and the sprites and icons for player 2's Blanka have been colour altered. Ryu has been disabled as a playable character.

- All scenes implemented in v0.5 have been actualized to match the new playable character and now also transition according to the timer.

- Added 3 new Scenes with their own properly timed transitions: Skyscraper Intro Screen (With the game logo animation at the end), Character Select Screen, Vs Screen.

- Added the Guile Stage art with Blanka vs Blanka and disabled the v0.5 Ryu Stage.

- Fully functional Camera that follows the players through the stage. <-- 

- Fully implemented all 3 punch buttons (LP, MP, HP), all kick buttons (LK, MK, HK) and a primitive combo system has been implemented in substitution of the Special Attack Button from v0.5.

- The Fighting Stage UI has been tweaked. The things that have changed: Characters names have both changed to "Blanka". Timer now works as a font and the time limit for the rounds shows remaining time in game. 

- Now the Duel works at the best of 3 rounds. Also added pre-battle and post-battle animations.  --<

- All pertaining audio fxs and musics have been implemented as in the original arcade game. --<

- Gamepads have been implemented. Now up to two controllers can be used to play the game.

- The game now plays in full screen.

    

## Project's GitHub Page:

Click [this link](<https://github.com/OuEsquerra/Beat-The-Meat-Studio>) to access our GitHub Repository.

Click [this other link](<https://marcarizaalborni.github.io/Hit-The-Meat-Studio/>) to access our GitHub Web.