## Game Description

The game consists in a 1 vs 1 duel between two characters, each with the same moveset and playstyle. The first player that knocks out the other by reducing their opponent's health bar to zero wins.



## Team Members:

- Adrian Mirabel (GitHub Link: [M1R4B3L](https://github.com/M1R4B3L))
- Marc Ariza (GitHub Link: [MarcArizaAlborni](https://github.com/MarcArizaAlborni))
- Pau Pedra (GitHub Link: [OuEsquerra](https://github.com/OuEsquerra))
- Angel Gonzalez (GitHub Link: [BarcinoLechiguino](https://github.com/BarcinoLechiguino))



## Game Control Keys

### Player One (left):

**Movement input Keys:** D Key (Go Right), A Key (Go Left), W Key (Jump), S Key (Crouch).

**Punch Input Button:** Q Key

**Kick Input Button:** E Key

**Special Attack Input Button:** F Key 



### Player Two (Right):

**Movement input Keys:** K Key (Go Left), Ñ key (Go Right), O key (Jump), L key (Crouch).

**Punch Input Button:** P Key

**Kick Input Button:** I Key

**Special Attack Input Button:**  J Key



## Game Debug Keys:

**God Mode(player becomes invincible):** G Key

**Show Collider Boxes Mode:** C Key

**Insta-Win Input Button:** V Key

**Insta-Lose Input Button:** X Key



## Changelist:

**v0.1:** 

- Implemented the possibility of scrolling an empty background. (Not Done: Module Audio Creation)

**v0.2:** 

* Added a Welcome Screen, the First and Second level scenes and a Congratulation Screen. 
* Added a scene cycle functionality so the congratulation screen transitions into the welcome screen. (Not Done: Module Audio with the correct music for each scene.) 

**v0.3:** 

- Added Player Movement (without collisions). 
- Added movement animations while the player is moving (Ryu) 
- Added the Hadouken as a particle that can be shot by the player.

**v0.4:** 

- Added colliders to the player(Ryu) and its particles(Hadouken) 
- Players can now collide with something in the environment. (Not done: Camera limits and God mode when pressing F5)

**v.0.5(current version):**  

- Added the win/lose condition (Empty health bar).

- Added 5 Scene transitions: Welcome Screen, Game Screen, Win/Lose Screen, Back to Welcome Screen.  

- Added Camera Limits so the Player cannot move out of the camera.

- Implemented the pertaining music for each screen along with the pertaining sound effects for each movement and interaction.

- Added minimum debug functionalities such as God Mode (grants invincibility to the player), Collision Boxes Mode (shows the collision boxes on screen), and both direct win and lose inputs.

- Implemented fully functional Health bars.

- Implemented Jump, one Kick and one Punch and one Special Attack.  (as state machine driven mechanics)

- Added the Ryu stage art (Different backgrounds + Parallax)  with Ryu vs Ryu.

    



## Project's GitHub Page:

Click [this link](<https://github.com/OuEsquerra/Beat-The-Meat-Studio>) to access the GitHub page.