## Game Description

The game consists in a 1 vs 1 duel between two characters, each with the same moveset and playstyle. There are two win conditions: The player who knocks out the other by reducing their opponent's health bar to zero wins or the player that has the most health out of the two when the time runs out (99 seconds) wins.



## Team Members:

- Adrian Mirabel (GitHub Link: [M1R4B3L](https://github.com/M1R4B3L))
- Marc Ariza (GitHub Link: [MarcArizaAlborni](https://github.com/MarcArizaAlborni))
- Pau Pedra (GitHub Link: [OuEsquerra](https://github.com/OuEsquerra))
- Angel Gonzalez (GitHub Link: [BarcinoLechiguino](https://github.com/BarcinoLechiguino))



## Game Control Keys

### Player One (left):

**Movement input Keys:** D Key (Go Right), A Key (Go Left), W Key (Jump), S Key (Crouch).

**Punch Input Button:** C Key

**Kick Input Button:** V Key

**Special Attack Input Button:** B Key 



### Player Two (Right):

**Movement input Keys:** LEFT Key (Go Left), RIGHT Key (Go Right), UP key (Jump), DOWN Key (Crouch).

**Punch Input Button:** P Key

**Kick Input Button:** O Key

**Special Attack Input Button:**  I Key



## Game Debug Keys:

**God Mode(player becomes invincible):** F1 Key

**Debug mode:** F2 Key

**Insta-Win Input Button:** F3 Key

**Insta-Lose Input Button:** F4 Key

**Input to reduce reduce Player 1's health:** F5 Key

**Input to reduce Player 2's health:** F6 Key



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

**v.0.5(current version):**  

- Added the win/lose conditions: Empty health bar or time runs out (99 seconds).

- Added 5 Scene transitions: Welcome Screen, Game Screen, Win/Lose Screen, Back to Welcome Screen.  

- Added Camera Limits so the Player cannot move out of the camera.

- Implemented the Audio Module.

- Implemented the pertaining music for each screen along with the pertaining sound effects for each movement and interaction.

- Added minimum debug functionalities such as God Mode (grants invincibility to the player), Collision Boxes Mode (shows the collision boxes on screen), both direct win and lose inputs as well as reducing both player's health.

- Implemented fully functional Health bars.

- Implemented Jump, one Kick and one Punch and one Special Attack.  (as state machine driven mechanics)

- Added the Ryu stage art with Ryu vs Ryu.

    



## Project's GitHub Page:

Click [this link](<https://github.com/OuEsquerra/Beat-The-Meat-Studio>) to access the GitHub page.