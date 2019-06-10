#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayerII.h"
#include <stdio.h>
#include <iostream>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA




using namespace std;
void deleteCollider(Collider* coll) {
	if (coll != nullptr) { coll->to_delete = true; };
};


ModulePlayer::ModulePlayer()
{
	graphicsP1 = NULL;
	currentP1_animation = NULL;

	score = 0;

	healthP1.x = 100;
	healthP1.y = 400;
	healthP1.w = 200;
	healthP1.h = 20;

	{ //BASIC MOVEMENTS ANIMATIONS

		//Idle animation (arcade sprite sheet)
		idleP1.PushBack({ 233, 27, 100, 100 }); 
		idleP1.PushBack({ 32, 27, 100, 100 }); 
		idleP1.PushBack({ 135, 27, 100, 100 }); 
		idleP1.PushBack({ 32, 27, 100, 100 });
		idleP1.speed = 0.08f;

		//Walk FORWARD Animation
		forwardP1.PushBack({ 699, 127, 97, 84 });
		forwardP1.PushBack({ 232, 127, 90, 84 });
		forwardP1.PushBack({ 322, 127, 100, 84 });
		forwardP1.PushBack({ 422, 127, 100, 84 });
		forwardP1.PushBack({ 522, 127, 88, 84 });
		forwardP1.PushBack({ 609, 127, 90, 84 });
		forwardP1.PushBack({ 132, 127, 100, 84 });
		forwardP1.PushBack({ 29, 127, 105, 84 });
		forwardP1.loop = true;
		forwardP1.speed = 0.1f;

		//Walk backwards animation
		backwardP1.PushBack({ 694, 211, 101, 101 });
		backwardP1.PushBack({ 609, 211, 85, 101 });
		backwardP1.PushBack({ 522, 211, 87, 101 });
		backwardP1.PushBack({ 232, 211, 91, 101 });
		backwardP1.PushBack({ 322, 211, 105, 101 });
		backwardP1.PushBack({ 427, 211, 95, 101 });
		backwardP1.PushBack({ 132, 211, 100, 101 });
		backwardP1.PushBack({ 29, 211, 104, 101 });
		backwardP1.loop = true;
		backwardP1.speed = 0.1f;

		//Crouch Animation
		crouchP1.PushBack({ 427, 323, 99, 94 });
		crouchP1.PushBack({ 526, 323, 89, 94 });
		crouchP1.PushBack({ 615, 323, 93, 94 });
		crouchP1.speed = 0.5f;
		crouchP1.loop = false;

		//Neutral Jump Animation
		NjumpP1.PushBack({ 28, 525, 97, 128 });
		NjumpP1.PushBack({ 125, 525, 85, 128 });
		NjumpP1.PushBack({ 210, 525, 83, 128 });
		NjumpP1.PushBack({ 293, 525, 86, 128 });
		NjumpP1.PushBack({ 210, 525, 83, 128 });
		NjumpP1.PushBack({ 125, 525, 85, 128 });
		NjumpP1.PushBack({ 28, 525, 97, 128 });
		NjumpP1.speed = 0.1f;
		NjumpP1.loop = false;

		//Forward Jump Animation
		FjumpP1.PushBack({ 28, 525, 97, 128 });
		FjumpP1.PushBack({ 125, 525, 85, 128 });
		FjumpP1.PushBack({ 210, 525, 83, 128 });
		FjumpP1.PushBack({ 293, 525, 86, 128 });
		FjumpP1.PushBack({ 379, 525, 90, 128 });
		FjumpP1.PushBack({ 469, 525, 98, 128 });
		FjumpP1.PushBack({ 567, 525, 119, 128 });
		FjumpP1.PushBack({ 686, 525, 96, 128 });
		FjumpP1.PushBack({ 379, 525, 90, 128 });
		FjumpP1.PushBack({ 293, 525, 86, 128 });
		FjumpP1.speed = 0.17f;
		FjumpP1.loop = false;

		//Backward Jump Animation
		BjumpP1.PushBack({ 28, 525, 97, 128 });
		BjumpP1.PushBack({ 125, 525, 85, 128 });
		BjumpP1.PushBack({ 210, 525, 83, 128 });
		BjumpP1.PushBack({ 293, 525, 86, 128 });
		BjumpP1.PushBack({ 210, 525, 83, 128 });
		BjumpP1.PushBack({ 125, 525, 85, 128 });
		BjumpP1.PushBack({ 28, 525, 97, 128 });
		BjumpP1.speed = 0.17f;
		BjumpP1.loop = false;

		//Standing Turn Animation
		SturnP1.PushBack({ 36, 418, 89, 105 });
		SturnP1.PushBack({ 125, 418, 103, 105 });
		SturnP1.PushBack({ 228, 418, 97, 105 });

		//Crouch Turn Animation
		CturnP1.PushBack({ 622, 451, 82, 71 });
		CturnP1.PushBack({ 516, 451, 106, 71 });
		CturnP1.PushBack({ 428, 451, 88, 71 });

		//Standing Block Animation
		SblockP1.PushBack({ 730, 2169, 100, 96 });
		SblockP1.PushBack({ 630, 2169, 100, 96 });
		
		//Crouch Block Animation
		CblockP1.PushBack({ 730, 2100, 100, 63 });
		CblockP1.PushBack({ 630, 2100, 100, 63 });

	    //Standing Damage Light
		SdamageLP1.PushBack({ 170, 2451, 88, 101 });
		SdamageLP1.PushBack({ 170, 2451, 88, 101 });
		SdamageLP1.PushBack({ 170, 2451, 88, 101 });
		SdamageLP1.PushBack({ 170, 2451, 88, 101 });
		SdamageLP1.PushBack({ 265, 2450, 101, 98 });
		SdamageLP1.PushBack({ 265, 2450, 101, 98 });
		SdamageLP1.loop = false;
		SdamageLP1.speed = 0.5;

		//Standing Damage Medium
		SdamageMP1.PushBack({ 170, 2451, 88, 101 });
		SdamageMP1.PushBack({ 170, 2451, 88, 101 });
		SdamageMP1.PushBack({ 170, 2451, 88, 101 });
		SdamageMP1.PushBack({ 170, 2451, 88, 101 });
		SdamageMP1.PushBack({ 265, 2450, 101, 98 });
		SdamageMP1.PushBack({ 265, 2450, 101, 98 });
		SdamageMP1.PushBack({ 32, 2459, 120, 86 });
		SdamageMP1.PushBack({ 32, 2459, 120, 86 });
		SdamageMP1.speed = 0.35f;

		//Standing Damage Hard
		SdamageHP1.PushBack({ 170, 2451, 88, 101 });
		SdamageHP1.PushBack({ 170, 2451, 88, 101 });
		SdamageHP1.PushBack({ 170, 2451, 88, 101 });
		SdamageHP1.PushBack({ 170, 2451, 88, 101 });
		SdamageHP1.PushBack({ 265, 2450, 101, 98 });
		SdamageHP1.PushBack({ 265, 2450, 101, 98 });
		SdamageHP1.PushBack({ 32, 2459, 120, 86 });
		SdamageHP1.PushBack({ 32, 2459, 120, 86 });
		SdamageHP1.PushBack({ 377, 2458, 86, 86 });
		SdamageHP1.PushBack({ 377, 2458, 86, 86 });
		SdamageHP1.speed = 0.3f;


		//Standing Damage Low Attack Light
		SdamagelowLP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP1.PushBack({ 30, 2363, 100, 79 });
		SdamagelowLP1.PushBack({ 30, 2363, 100, 79 });
		SdamagelowLP1.speed = 0.05f;

		//Standing Damage Low Attack Medium
		SdamagelowMP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP1.PushBack({ 30, 2363, 100, 79 });
		SdamagelowMP1.PushBack({ 30, 2363, 100, 79 });
		SdamagelowMP1.PushBack({ 133, 2363, 106, 72 });
		SdamagelowMP1.PushBack({ 133, 2363, 106, 72 });
		SdamagelowMP1.speed = 0.05f;


		//Standing Damage Low Attack Hard
		SdamagelowHP1.PushBack({ 30, 2278, 96, 85 }); 
		SdamagelowHP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP1.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP1.PushBack({ 30, 2363, 100, 79 });
		SdamagelowHP1.PushBack({ 30, 2363, 100, 79 });
		SdamagelowHP1.PushBack({ 133, 2363, 106, 72 });
		SdamagelowHP1.PushBack({ 133, 2363, 106, 72 });
		SdamagelowHP1.PushBack({ 377, 2458, 86, 86 });
		SdamagelowHP1.PushBack({ 377, 2458, 86, 86 });
		SdamagelowHP1.speed = 0.05f;

		//Crouch Damage
		CdamageP1.PushBack({});

		//Electric Thunder Damage
		ETdamgeP1.PushBack({});

		//Recovery
		RecoveryP1.PushBack({});

	}

	{ //ATTACKS ANIMATIONS
		
	  //Standing FAR LP
	  SFLP_P1.PushBack({28, 658, 104, 105});
	  SFLP_P1.PushBack({132, 658, 143, 105});
	  SFLP_P1.PushBack({275, 658, 123, 105});
	  SFLP_P1.speed = 0.2f;	
	  SFLP_P1.loop = false;

	  //Standing CLOSE LP
	  SCLP_P1.PushBack({ 30, 1365, 110, 93 });
	  SCLP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCLP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCLP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCLP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCLP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCLP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCLP_P1.PushBack({ 306, 1359, 135, 99 });
	  SCLP_P1.PushBack({ 306, 1359, 135, 99 });
	  SCLP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCLP_P1.PushBack({ 30, 1365, 110, 93 });
	  SCLP_P1.speed = 0.2f;

	  //Crouch LP
	  CLP_P1.PushBack({610, 709, 109, 56 });
	  CLP_P1.PushBack({727, 715, 154, 50 });
	  CLP_P1.PushBack({890, 713, 142, 52 });
	  CLP_P1.speed = 0.2f;
	  CLP_P1.loop = false;

	  //Jumping LP
	  JLP_P1.PushBack({ 610, 1369, 94, 83 });
	  JLP_P1.PushBack({ 840, 1371, 84, 81 });
	  JLP_P1.PushBack({ 840, 1371, 84, 81 });
	  JLP_P1.PushBack({ 712, 1372, 119, 80 });
	  JLP_P1.PushBack({ 712, 1372, 119, 80 });
	  JLP_P1.PushBack({ 712, 1372, 119, 80 });
	  JLP_P1.PushBack({ 712, 1372, 119, 80 });
	  JLP_P1.PushBack({ 712, 1372, 119, 80 });
	  JLP_P1.PushBack({ 840, 1371, 84, 81 });
	  JLP_P1.PushBack({ 610, 1369, 94, 83 });
	  JLP_P1.speed = 0.09f;
	   
	  //Standing FAR MP 
	  SFMP_P1.PushBack({31, 765, 88, 104 }); 
	  SFMP_P1.PushBack({134, 788, 120, 108 });
	  SFMP_P1.PushBack({264, 799, 130, 97 });
	  SFMP_P1.PushBack({403, 803, 103, 93}); //This is not correct I think
	  SFMP_P1.speed = 0.2f;
		
	  //Standing CLOSE MP
	  SCMP_P1.PushBack({ 30, 1365, 110, 93 });
	  SCMP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCMP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCMP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCMP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCMP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCMP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCMP_P1.PushBack({ 306, 1359, 135, 99 });
	  SCMP_P1.PushBack({ 306, 1359, 135, 99 });
	  SCMP_P1.PushBack({ 149, 1360, 149, 98 });
	  SCMP_P1.PushBack({ 30, 1365, 110, 93 });
	  SCMP_P1.speed = 0.2f;

	  //Crouch MP
	  CMP_P1.PushBack({ 610, 792, 82, 64 });
	  CMP_P1.PushBack({ 703, 794, 140, 62 });
	  CMP_P1.PushBack({ 851, 790, 147, 66 });
	  CMP_P1.PushBack({ 1005, 786, 140, 70 });
	  CMP_P1.PushBack({ 851, 790, 147, 66 });
	  CMP_P1.PushBack({ 703, 794, 140, 62 });
	  CMP_P1.PushBack({ 610, 792, 82, 64 });
	  CMP_P1.speed = 0.2f;

	  //Jump MP
	  JMP_P1.PushBack({ 610, 1369, 94, 83 });
	  JMP_P1.PushBack({ 840, 1371, 84, 81 });
	  JMP_P1.PushBack({ 840, 1371, 84, 81 });
	  JMP_P1.PushBack({ 712, 1372, 119, 80 });
	  JMP_P1.PushBack({ 712, 1372, 119, 80 });
	  JMP_P1.PushBack({ 712, 1372, 119, 80 });
	  JMP_P1.PushBack({ 712, 1372, 119, 80 });
	  JMP_P1.PushBack({ 712, 1372, 119, 80 });
	  JMP_P1.PushBack({ 840, 1371, 84, 81 });
	  JMP_P1.PushBack({ 610, 1369, 94, 83 });
	  JMP_P1.speed = 0.09f;

	  //Standing FAR HP
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.speed = 0.5f;
	  SFHP_P1.loop = false;

	  //Standing CLOSE HP
	  SCHP_P1.PushBack({ 30, 1471, 104, 70 });
	  SCHP_P1.PushBack({ 30, 1471, 104, 70 });
	  SCHP_P1.PushBack({ 141, 1473, 67, 68 });
	  SCHP_P1.PushBack({ 141, 1473, 67, 68 });
	  SCHP_P1.PushBack({ 218, 1482, 76, 59 });
	  SCHP_P1.PushBack({ 218, 1482, 76, 59 });
	  SCHP_P1.PushBack({ 308, 1471, 88, 70 });
	  SCHP_P1.PushBack({ 308, 1471, 88, 70 });
	  SCHP_P1.PushBack({ 407, 1463, 88, 86 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 155, 1553, 75, 74 });
	  SCHP_P1.PushBack({ 155, 1553, 75, 74 });
	  SCHP_P1.PushBack({ 141, 1473, 67, 68 });
	  SCHP_P1.PushBack({ 141, 1473, 67, 68 });
	  SCHP_P1.PushBack({ 141, 1473, 67, 68 });
	  SCHP_P1.PushBack({ 218, 1482, 76, 59 });
	  SCHP_P1.PushBack({ 218, 1482, 76, 59 });
	  SCHP_P1.PushBack({ 308, 1471, 88, 70 });
	  SCHP_P1.PushBack({ 308, 1471, 88, 70 });
	  SCHP_P1.PushBack({ 407, 1463, 88, 86 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 30, 1560, 118, 68 });
	  SCHP_P1.PushBack({ 155, 1553, 75, 74 });
	  SCHP_P1.PushBack({ 155, 1553, 75, 74 });
	  SCHP_P1.speed = 0.3f;   

	  //Crouch HP
	  CHP_P1.PushBack({ 612, 895, 84, 58 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 815, 869, 166, 84 });
	  CHP_P1.PushBack({ 815, 869, 166, 84 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 612, 895, 84, 58 });
	  CHP_P1.PushBack({ 612, 895, 84, 58 });
	  CHP_P1.PushBack({ 612, 895, 84, 58 });
	  CHP_P1.speed = 0.2f;

	  //Jump HP F and B
	  JHPFB_P1.PushBack({ 610, 1462, 85, 117 });
	  JHPFB_P1.PushBack({ 610, 1462, 85, 117 });
	  JHPFB_P1.PushBack({ 610, 1462, 85, 117 });
	  JHPFB_P1.PushBack({ 699, 1490, 126, 80 });
	  JHPFB_P1.PushBack({ 699, 1490, 126, 80 });
	  JHPFB_P1.PushBack({ 826, 1495, 98, 85 });
	  JHPFB_P1.PushBack({ 826, 1495, 98, 85 });
	  JHPFB_P1.PushBack({ 826, 1495, 98, 85 });
	  JHPFB_P1.PushBack({ 925, 1491, 72, 89 });
	  JHPFB_P1.PushBack({ 925, 1491, 72, 89 });
	  JHPFB_P1.PushBack({ 925, 1491, 72, 89 });
	  JHPFB_P1.speed = 0.09f;

	  //Jump Hp N
	  JHPN_P1.PushBack({ 610, 1587, 136, 84 });
	  JHPN_P1.PushBack({ 753, 1591, 78, 80 });
	  JHPN_P1.PushBack({ 857, 1589, 65, 82 });
	  JHPN_P1.PushBack({ 753, 1591, 78, 80 });
	  JHPN_P1.PushBack({ 610, 1587, 136, 84 });
	  JHPN_P1.speed = 0.3f;


	  //Standing FAR LK
	  SFLK_P1.PushBack({ 33, 1028, 81, 96 });
	  SFLK_P1.PushBack({ 124, 1031, 97, 94 });
	  SFLK_P1.PushBack({ 230, 1032, 137, 93 });
	  SFLK_P1.PushBack({ 230, 1032, 137, 93 });
	  SFLK_P1.PushBack({ 124, 1031, 97, 94 });
	  SFLK_P1.PushBack({ 33, 1028, 81, 96 });
	  SFLK_P1.speed = 0.2f;
	  SFLK_P1.loop = false;

	  //Standing CLOSE LK
	  SCLK_P1.PushBack({ 30, 1637, 79, 111 });
	  SCLK_P1.PushBack({ 30, 1637, 79, 111 });
	  SCLK_P1.PushBack({ 122, 1644, 66, 104 });
	  SCLK_P1.PushBack({ 122, 1644, 66, 104 });
	  SCLK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCLK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCLK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCLK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCLK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCLK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCLK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCLK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCLK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCLK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCLK_P1.PushBack({ 122, 1644, 66, 104 });
	  SCLK_P1.PushBack({ 122, 1644, 66, 104 });
	  SCLK_P1.PushBack({ 30, 1637, 79, 111 });
	  SCLK_P1.PushBack({ 30, 1637, 79, 111 });

	  SCLK_P1.speed = 0.7f;

	  //Crouch LK
	  CLK_P1.PushBack({ 610, 980, 74, 78 }); 
	  CLK_P1.PushBack({ 702, 978, 74, 78 });
	  CLK_P1.PushBack({ 790, 972, 139, 68 });
	  CLK_P1.PushBack({ 702, 978, 74, 78 });
	  CLK_P1.PushBack({ 610, 980, 74, 78 });
	  CLK_P1.speed = 0.2f;

	  //Jump LK
	  JLK_P1.PushBack({ 610, 1690, 80, 79 });
	  JLK_P1.PushBack({ 702, 1679, 102, 86 });
	  JLK_P1.PushBack({ 816, 1680, 127, 85 });
	  JLK_P1.PushBack({ 816, 1680, 127, 85 });
	  JLK_P1.PushBack({ 816, 1680, 127, 85 });
	  JLK_P1.speed = 0.3f;

	  //Standing FAR MK
	  SFMK_P1.PushBack({28, 1135, 92, 85 });
	  SFMK_P1.PushBack({ 129, 1135, 101, 85 });
	  SFMK_P1.PushBack({ 236, 1135, 124, 85 });  
	  SFMK_P1.PushBack({ 236, 1135, 124, 85 });
	  SFMK_P1.PushBack({ 129, 1135, 101, 85 });
	  SFMK_P1.PushBack({ 28, 1135, 92, 85 });
	  SFMK_P1.speed = 0.2f;
	  SFMK_P1.loop = false;

	  //Standing CLOSE MK
	  SCMK_P1.PushBack({ 30, 1637, 79, 111 });
	  SCMK_P1.PushBack({ 30, 1637, 79, 111 });
	  SCMK_P1.PushBack({ 122, 1644, 66, 104 });
	  SCMK_P1.PushBack({ 122, 1644, 66, 104 });
	  SCMK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCMK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCMK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCMK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCMK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCMK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCMK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCMK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCMK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCMK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCMK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCMK_P1.PushBack({ 264, 1648, 75, 94 });
	  SCMK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCMK_P1.PushBack({ 196, 1648, 60, 99 });
	  SCMK_P1.PushBack({ 122, 1644, 66, 104 });
	  SCMK_P1.PushBack({ 122, 1644, 66, 104 });
	  SCMK_P1.PushBack({ 30, 1637, 79, 111 });
	  SCMK_P1.PushBack({ 30, 1637, 79, 111 });
	  SCMK_P1.speed = 0.5f;
	
	  //Crouch MK
	  CMK_P1.PushBack({ 610, 980, 74, 78 });
	  CMK_P1.PushBack({ 702, 978, 74, 78 });
	  CMK_P1.PushBack({ 790, 972, 139, 68 });
	  CMK_P1.PushBack({ 790, 972, 139, 68 });
	  CMK_P1.PushBack({ 702, 978, 74, 78 });
	  CMK_P1.PushBack({ 610, 980, 74, 78 });

	  //Jump MK
	  JMK_P1.PushBack({ 610, 1690, 80, 79 });
	  JMK_P1.PushBack({ 702, 1679, 102, 86 });
	  JMK_P1.PushBack({ 816, 1680, 127, 85 });
	  JMK_P1.PushBack({ 816, 1680, 127, 85 });
	  JMK_P1.PushBack({ 816, 1680, 127, 85 });
	  JMK_P1.PushBack({ 702, 1679, 102, 86 });
	  JMK_P1.PushBack({ 610, 1690, 80, 79 });
	  JMK_P1.speed = 0.06f;


	  //Standing FAR HK
	  SFHK_P1.PushBack({ 34, 1263, 90, 85 });
	  SFHK_P1.PushBack({ 143, 1263, 163, 85 });
	  SFHK_P1.PushBack({ 316, 1249, 122, 99 });
	  SFHK_P1.PushBack({ 445, 1221, 88, 127 });
	  SFHK_P1.PushBack({ 536, 1250, 138, 98 });
	  SFHK_P1.PushBack({ 686, 1279, 103, 69 });
	  SFHK_P1.speed = 0.2f;
	  SFHK_P1.loop = false;

	  //Standing CLOSE HK
	  SCHK_P1.PushBack({ 30, 1752, 72, 81 });
	  SCHK_P1.PushBack({ 30, 1752, 72, 81 });
	  SCHK_P1.PushBack({ 117, 1757, 91, 76 });
	  SCHK_P1.PushBack({ 117, 1757, 91, 76 });
	  SCHK_P1.PushBack({ 214, 1764, 161, 69 });
	  SCHK_P1.PushBack({ 214, 1764, 161, 69 });
	  SCHK_P1.PushBack({ 214, 1764, 161, 69 });
	  SCHK_P1.PushBack({ 214, 1764, 161, 69 });
	  SCHK_P1.PushBack({ 214, 1764, 161, 69 });
	  SCHK_P1.PushBack({ 117, 1757, 91, 76 });
	  SCHK_P1.PushBack({ 117, 1757, 91, 76 });
	  SCHK_P1.PushBack({ 117, 1757, 91, 76 });
	  SCHK_P1.PushBack({ 30, 1752, 72, 81 });
	  SCHK_P1.PushBack({ 30, 1752, 72, 81 });
	  SCHK_P1.PushBack({ 30, 1752, 72, 81 });
	  SCHK_P1.speed = 0.4f;

	  //Crouch HK
	  CHK_P1.PushBack({610, 1078, 72, 80 });
	  CHK_P1.PushBack({698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 799, 1090, 161, 69 });
	  CHK_P1.PushBack({ 799, 1090, 161, 69 });
	  CHK_P1.PushBack({ 698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 610, 1078, 72, 80 });
	  CHK_P1.PushBack({ 610, 1078, 72, 80 });
	  CHK_P1.PushBack({ 610, 1078, 72, 80 });
	  CHK_P1.PushBack({ 610, 1078, 72, 80 });
	  CHK_P1.speed = 0.2f;

	  //Jump HK
	  JHK_P1.PushBack({ 610, 1787, 96, 79 });
	  JHK_P1.PushBack({ 706, 1779, 136, 87 });
	  JHK_P1.PushBack({ 849, 1780, 170, 88 });
	  JHK_P1.PushBack({ 849, 1780, 170, 88 });
	  JHK_P1.PushBack({ 849, 1780, 170, 88 });
	  JHK_P1.PushBack({ 706, 1779, 136, 87 });
	  JHK_P1.PushBack({ 610, 1787, 96, 79 });
	  JHK_P1.PushBack({ 610, 1787, 96, 79 });
	  JHK_P1.PushBack({ 610, 1787, 96, 79 });
	  JHK_P1.speed = 0.07f;

	  //Headbut
	  Headbut_P1.PushBack({ 616, 1954, 90, 100 });
	  Headbut_P1.PushBack({ 616, 1954, 90, 100 });
	  Headbut_P1.PushBack({ 717, 1959, 90, 95 });
	  Headbut_P1.PushBack({ 717, 1959, 90, 95 });
	  Headbut_P1.PushBack({ 717, 1959, 90, 95 });
	  Headbut_P1.PushBack({ 717, 1959, 90, 95 });
	  Headbut_P1.PushBack({ 717, 1959, 90, 95 });
	  Headbut_P1.PushBack({ 820, 1978, 106, 76 });
	  Headbut_P1.PushBack({ 820, 1978, 106, 76 });
	  Headbut_P1.PushBack({ 913, 1999, 126, 55 });
	  Headbut_P1.PushBack({ 820, 1978, 106, 76 });
	  Headbut_P1.PushBack({ 820, 1978, 106, 76 });
	  Headbut_P1.PushBack({ 717, 1959, 90, 95 });
	  Headbut_P1.PushBack({ 717, 1959, 90, 95 });
	  Headbut_P1.PushBack({ 616, 1954, 90, 100 });
	  Headbut_P1.PushBack({ 616, 1954, 90, 100 });
	  Headbut_P1.speed = 0.2f;

	  //Throw
	  Throw_P1.PushBack({ 27, 2141, 89, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 214, 2141, 76, 104 });
	  Throw_P1.PushBack({ 214, 2141, 76, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 27, 2141, 89, 104 });
	  Throw_P1.speed = 0.1f;
	
	  //Electric Thunder 
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.PushBack({ 130, 1874, 86, 72 });
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.PushBack({ 130, 1874, 86, 72 });
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.PushBack({ 130, 1874, 86, 72 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.PushBack({ 130, 1874, 86, 72 });
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.speed = 0.3f;

	  //Rolling Attack
	  RollingP1.PushBack({ 27, 1965, 67, 68 });
	  RollingP1.PushBack({ 107, 1974, 76, 59 });
	  RollingP1.PushBack({ 191, 1978, 88, 55 });
	  RollingP1.PushBack({ 288, 1977, 82, 56 });
	  RollingP1.PushBack({ 383, 1965, 67, 68 });
	  RollingP1.PushBack({ 458, 1974, 76, 59 });
	  RollingP1.PushBack({ 27, 2053, 88, 55 });
	  RollingP1.PushBack({ 120, 2052, 82, 55 });
	  RollingP1.PushBack({ 212, 2040, 67, 68 });
	  RollingP1.PushBack({ 107, 1974, 76, 59 });
	  RollingP1.PushBack({ 191, 1978, 88, 55 });
	  RollingP1.PushBack({ 288, 1977, 82, 56 });
	  RollingP1.PushBack({ 383, 1965, 67, 68 });
	  RollingP1.PushBack({ 458, 1974, 76, 59 });
	  RollingP1.PushBack({ 27, 2053, 88, 55 });
	  RollingP1.PushBack({ 120, 2052, 82, 55 });
	  RollingP1.PushBack({ 107, 1974, 76, 59 });
	  RollingP1.speed = 0.5f;
	  RollingP1.loop = true;


	  //Rolling Rebound 

	  RollingRebP1.PushBack({ 27, 1965, 67, 68 });
	  RollingRebP1.PushBack({ 107, 1974, 76, 59 });
	  RollingRebP1.PushBack({ 191, 1978, 88, 55 });
	  RollingRebP1.PushBack({ 288, 1977, 82, 56 });
	  RollingRebP1.PushBack({ 383, 1965, 67, 68 });
	  RollingRebP1.speed = 0.5f;
	  RollingRebP1.loop = true;

	}
}



ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	graphicsP1 = App->textures->Load("Sprites/BlankaP1.png"); // JA TE LA FOTO BONA
	currentstateP1 = idlestateP1;
	combo[0] = ' ';
	*startC = combo[0];
	*finishC = combo[0];

	//Player 2 stest collider
	playerP1_collider = App->collision->AddCollider({ positionP1.x , positionP1.y - 100, 60, 93 }, COLLIDER_PLAYER,NOATTACK, App->player);
	attackP1_collider = nullptr;
	return true;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphicsP1);
	return true;
}

update_status ModulePlayer::PreUpdate() {
	time = SDL_GetTicks() / 20;
	camx = App->render->camera.x / SCREEN_ADD;
	camy = App->render->camera.y / SCREEN_ADD;

	//MOVE BACKWARD
	//inputplayerP1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
	//MOVE FORWARD
	//inputplayerP1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	//CROUCH
	//inputplayerP1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
	//JUMP
//	inputplayerP1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	/* inputplayerP1.right_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP1.down_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP1.up_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;
	 inputplayerP1.down_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;*/
	 App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN;
	 App->input->game_pad[SDL_CONTROLLER_BUTTON_B][GAME_PAD_1] == KEY_DOWN;
     App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_1] == KEY_DOWN;
	 inputplayerP1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)|| SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_LEFT)|| SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	 inputplayerP1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;
	 
	 inputplayerP1.U_active = App->input->keyboard[SDL_SCANCODE_U] == KEY_DOWN || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_X);
	 inputplayerP1.I_active = App->input->keyboard[SDL_SCANCODE_I] == KEY_DOWN;
	 inputplayerP1.O_active = App->input->keyboard[SDL_SCANCODE_O] == KEY_DOWN;
	 inputplayerP1.J_active = App->input->keyboard[SDL_SCANCODE_J] == KEY_DOWN;
	 inputplayerP1.K_active = App->input->keyboard[SDL_SCANCODE_K] == KEY_DOWN;
	 inputplayerP1.L_active = App->input->keyboard[SDL_SCANCODE_L] == KEY_DOWN;
	 {
		
		 
		 //Standing Far Attacks Animation check
		 if (currentstateP1 == standingfarMPP1) {
			/* if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFMP_P1.Reset();
			 }*/

			 if (currentP1_animation->Finished() && !inputplayerP1.I_active) {
				 currentstateP1 = idlestateP1;
				 deleteCollider(attackP1_collider);
				 SFMP_P1.Reset();
				 LOG("LP to IDLE");
				 ++thundertick;
			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.I_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {
				 if (thundertick > 3) {
					 currentstateP1 = thunder1P1;
					 deleteCollider(attackP1_collider);
					
					 SFMP_P1.Reset();

					 LOG("LP to Thunder1");
				 }
			 }
		 }
		 if (currentstateP1 == standingfarHPP1) {
			/* if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFHP_P1.Reset();
			 }*/

			 if (currentP1_animation->Finished() && !inputplayerP1.O_active) {
				 currentstateP1 = idlestateP1;
				 deleteCollider(attackP1_collider);
				 SFHP_P1.Reset();
				 LOG("LP to IDLE");
				 ++thundertick;
			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.O_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {
				 if (thundertick > 3) {
					 currentstateP1 = thunder1P1;
					 deleteCollider(attackP1_collider);

					 SFHP_P1.Reset();

					 LOG("LP to Thunder1");
				 }
			 }

		 }
		 if (currentstateP1 == standingfarLKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFLK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == standingfarMKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFMK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == standingfarHKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFHK_P1.Reset();
			 }
		 }
		 //Close Attacks Check
		 if (currentstateP1 == standingcloseMPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SCMP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == standingcloseLPP1) {
			 if (currentP1_animation->Finished()) {

				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SCLP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == standingcloseHPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SCHP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == standingcloseLKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SCLK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == standingcloseMKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SCMK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == standingcloseHKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SCHK_P1.Reset();
			 }
		 }
		 //Crouch attack checks
		 if (currentstateP1 == crouchMPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = crouchstateP1;
				 CMP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == crouchHPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = crouchstateP1;
				 CHP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == crouchLKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = crouchstateP1;
				 CLK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == crouchMKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = crouchstateP1;
				 CMK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == crouchHKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = crouchstateP1;
				 CHK_P1.Reset();
			 }
		 }
		 //Jumping attack check
		 if (currentstateP1 == jumpLPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJump == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJump == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJump == true) { currentstateP1 = BjumpstateP1; }
				 JLP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == jumpMPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJump == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJump == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJump == true) { currentstateP1 = BjumpstateP1; }
				 JMP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == NjumpHPP1) {
			 if (currentP1_animation->Finished()) {
				 
				 deleteCollider(attackP1_collider);
				 if (neutralJump == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJump == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJump == true) { currentstateP1 = BjumpstateP1; }
				 JHPN_P1.Reset();
			 }
		 }
		 if (currentstateP1 == DjumpHPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJump == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJump == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJump == true) { currentstateP1 = BjumpstateP1; }
				 JHPFB_P1.Reset();
			 }
		 }
		 if (currentstateP1 == jumpLKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJump == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJump == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJump == true) { currentstateP1 = BjumpstateP1; }
				 JLK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == jumpMKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJump == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJump == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJump == true) { currentstateP1 = BjumpstateP1; }
				 JMK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == jumpHKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJump == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJump == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJump == true) { currentstateP1 = BjumpstateP1; }
				 JHK_P1.Reset();
			 }
		 }
		 //Damaged chack
		 if (currentstateP1 == SdamagedLP1) {
			 if (currentP1_animation->Finished()) {
				 currentstateP1 = idlestateP1;
				 SdamageLP1.Reset();
			 }
		 }
		 if (currentstateP1 == SdamagedMP1) {
			 if (currentP1_animation->Finished()) {
				 currentstateP1 = idlestateP1;
				 SdamageMP1.Reset();
			 }
		 }
		 if (currentstateP1 == SdamagedHP1) {
			 if (currentP1_animation->Finished()) {
				 currentstateP1 = idlestateP1;
				 SdamageHP1.Reset();
			 }
		 }
		 
		 //IDLE STATE
		 if (currentstateP1 == idlestateP1) {
			 comboInput(' ');

			 if (inputplayerP1.A_active) {
				 currentstateP1 = backwardstateP1;

				 LOG("IDLE TO BACK");
			 }
			 if (inputplayerP1.D_active) {
				 currentstateP1 = forwardstateP1;
				 LOG("IDLE TO forward");
			 }
			 if (inputplayerP1.S_active) {
				 currentstateP1 = crouchstateP1;
				 LOG("IDLE to CROUCH");
			 }
			 
			 if (inputplayerP1.W_active) {
				 jumping = true;
				 neutralJump = true;
				 
				 currentstateP1 = NjumpstateP1;
				 jumpstart = time;
				 jumpTimer = 0;
				 LOG("IDLE to JUMP");
			 }
			 if (!close) {
				 if (inputplayerP1.U_active) {
					 currentstateP1 = standingfarLPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 50 }, COLLIDER_PLAYER_ATTACK,SFLP, App->player);
					 LOG("IDLE to LP");
					
				 }
				 if (inputplayerP1.I_active) {
					 currentstateP1 = standingfarMPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 35 }, COLLIDER_PLAYER_ATTACK,SFMP, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP1.O_active) {
					 currentstateP1 = standingfarHPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 80, 18 }, COLLIDER_PLAYER_ATTACK,SFHP, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP1.J_active) {
					 currentstateP1 = standingfarLKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 57, 25 }, COLLIDER_PLAYER_ATTACK,SFLK, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP1.K_active) {
					 currentstateP1 = standingfarMKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 75, 15 }, COLLIDER_PLAYER_ATTACK,SFMK, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP1.L_active) {
					 currentstateP1 = standingfarHKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 75, 15 }, COLLIDER_PLAYER_ATTACK,SFHK, App->player);
					 LOG("IDLE to HEAVY KICK");
				 }
			 }

			 //close attacks
			 if (close) {
				 if (inputplayerP1.U_active) {
					 currentstateP1 = standingcloseLPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 50 }, COLLIDER_PLAYER_ATTACK,SCLP, App->player);
					 LOG("IDLE to LP");
				 }
				 if (inputplayerP1.I_active) {
					 currentstateP1 = standingcloseMPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 30 }, COLLIDER_PLAYER_ATTACK,SCMP, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP1.O_active) {
					 currentstateP1 = standingcloseHPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 60, 25 }, COLLIDER_PLAYER_ATTACK,SCHP, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }

				 if (inputplayerP1.J_active) {
					 currentstateP1 = standingcloseLKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 57, 25 }, COLLIDER_PLAYER_ATTACK,SCLK, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }

				 if (inputplayerP1.K_active) {
					 currentstateP1 = standingcloseMKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 57, 25 }, COLLIDER_PLAYER_ATTACK, SCMK, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }

				 if (inputplayerP1.L_active) {
					 currentstateP1 = standingcloseHKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 22 }, COLLIDER_PLAYER_ATTACK,SCHK, App->player);
					 LOG("IDLE to HEAVY KICK");
				 }


				
			 }
		 }
		 //BACKWARDS STATE
		 if (currentstateP1 == backwardstateP1) {
			 comboInput('n');
			 comboInput('m');
			 if (!inputplayerP1.A_active) {
				 currentstateP1 = idlestateP1;
				
				 LOG("BACK to IDLE");
			 }
			 if (inputplayerP1.S_active) {
				 currentstateP1 = crouchstateP1;
				 LOG("BACK to CROUCH");
			 }
			 if (inputplayerP1.W_active) {
				 
				 jumping = true;
				 backwardJump = true;
				 currentstateP1 = BjumpstateP1;
				 jumpstart = time;
				 jumpTimer = 0;
				 LOG("IDLE to CROUCH");
			 }
			 if (inputplayerP1.U_active) {
				 currentstateP1 = standingfarLPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 50 }, COLLIDER_PLAYER_ATTACK, SFLP, App->player);
				 LOG("BACK to LP");
			 }
			/* if (inputplayerP1.I_active) {
				 currentstateP1 = standingfarMPP1;
				attackP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x + 55, positionP1.y - 80 - App->render->camera.y * 2, 100, 35 }, COLLIDER_PLAYER_ATTACK,SFMP, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }*/
			 if (inputplayerP1.O_active) {
				 currentstateP1 = standingfarHPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 80, 18 }, COLLIDER_PLAYER_ATTACK, SFHP, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.J_active) {
				 currentstateP1 = standingfarLKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 57, 25 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.K_active) {
				 currentstateP1 = standingfarMKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 75, 15 }, COLLIDER_PLAYER_ATTACK, SFMK, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.L_active) {
				 currentstateP1 = standingfarHKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 75, 15 }, COLLIDER_PLAYER_ATTACK, SFHK, App->player);
				 LOG("IDLE to HEAVY KICK");
			 }
			 
			 if (inputplayerP1.D_active && inputplayerP1.U_active) {

				 currentstateP1 = rollingattackP1LIGHT;


			 }
			 if (inputplayerP1.D_active && inputplayerP1.I_active) {

				 currentstateP1 = rollingattackP1MEDIUM;

			 }
			 
			 if (inputplayerP1.D_active && inputplayerP1.O_active) {

				 currentstateP1 = rollingattackP1HEAVY;

			 }

			
			

			 if (inputplayerP1.I_active && !inputplayerP1.D_active && close) { //falta CONDICIO COLIDER APROP


				 currentstateP1 = HeadbuttP1;
				 LOG("BACKWARD TO HEADBUT");

			 }

			 if (inputplayerP1.O_active && close) {


				 currentstateP1 = throwP1;

			 }

			 if (inputplayerP1.L_active && close) {

				 currentstateP1 = throwP1;
			 }

		 }
		 //FORWARD STATE
		 if (currentstateP1 == forwardstateP1) {
			 
			 if (!inputplayerP1.D_active) {
				 //blockP1_collider->to_delete = true;
				 currentstateP1 = idlestateP1;
				
				 LOG("FOR to IDLE");
			 }
			 if (inputplayerP1.A_active) {
				 currentstateP1 = backwardstateP1;

				 LOG("FOR to BACK");
			 }
			 if (inputplayerP1.S_active) {
				
				 currentstateP1 = crouchstateP1;
				 LOG("FOR to CROUCH");
			 }
			 if (inputplayerP1.W_active){
				
				 jumping = true;
				 forwardJump = true;
				 currentstateP1 = FjumpstateP1;
				 jumpstart = time;
				 jumpTimer = 0;
				 LOG("FOR to CROUCH");
			 }
			 if (inputplayerP1.U_active) {
				
				 currentstateP1 = standingfarLPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 50 }, COLLIDER_PLAYER_ATTACK, SFLP, App->player);
				 LOG("FOR to LP");
			 }
			 //if (inputplayerp1.i_active) { //aqui falta condicio de no s'estan tocant els coliders
				// currentstatep1 = standingfarmpp1;
				// attackP1_collider = App->collision->AddCollider({ 0,0, 100, 35 }, COLLIDER_PLAYER_ATTACK,SFMP, App->player);
				// log("idle to heavy punch");
			 //}
			 if (inputplayerP1.O_active && !inputplayerP1.D_active) {
				 currentstateP1 = standingfarHPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 80, 18 }, COLLIDER_PLAYER_ATTACK, SFHP, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.J_active) {
				 currentstateP1 = standingfarLKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 57, 25 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.K_active) {
				 currentstateP1 = standingfarMKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 75, 15 }, COLLIDER_PLAYER_ATTACK, SFMK, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.L_active) {
				 currentstateP1 = standingfarHKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 75, 15 }, COLLIDER_PLAYER_ATTACK, SFHK, App->player);
				 LOG("IDLE to HEAVY KICK");
			 }
	
			 if (inputplayerP1.I_active && close ) { //falta CONDICIO COLIDER APROP
				 currentstateP1 = HeadbuttP1;
				 LOG("FORWARD TO HEADBUT");

			 }
			 if (inputplayerP1.O_active && close) {
				 currentstateP1 = throwP1;
			 }

		 }
		 //CROUCH STATE
		 if (currentstateP1 == crouchstateP1) {
			 comboInput('s');
			 if (!inputplayerP1.S_active) {
				 crouchP1.Reset();
				 currentstateP1 = idlestateP1;
				 
				 LOG("CROUCH to IDLE");
			 }
			 if (inputplayerP1.U_active) {
				 currentstateP1 = crouchLPP1;
				 LOG("CROUCH to LP");
				 
			 }
			 if (inputplayerP1.A_active) {
				 crouchBlockingP1 = true;
			 }
			 if (!inputplayerP1.A_active ) {
				 crouchBlockingP1 = false;
			 }
			 if (inputplayerP1.U_active) {
				 currentstateP1 = crouchLPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 50, 15 }, COLLIDER_PLAYER_ATTACK,CLP, App->player);
				 LOG("IDLE to LP");
			 }
			 if (inputplayerP1.I_active) {
				 currentstateP1 = crouchMPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 93, 20 }, COLLIDER_PLAYER_ATTACK,CMP, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.O_active) {
				 currentstateP1 = crouchHPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 20 }, COLLIDER_PLAYER_ATTACK,CHP, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.J_active) {
				 currentstateP1 = crouchLKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 79, 22 }, COLLIDER_PLAYER_ATTACK,CLK, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.K_active) {
				 currentstateP1 = crouchMKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 22 }, COLLIDER_PLAYER_ATTACK,CMK, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP1.L_active) {
				 currentstateP1 = crouchHKP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 22 }, COLLIDER_PLAYER_ATTACK,CHK, App->player);
				 LOG("IDLE to HEAVY KICK");
			 }
		 }
		 //JUMP STATE
		 if (jumping == true) {
			 comboInput('w');
			 if (positionP1.y >= groundLevel + 1) {
				 positionP1.y = groundLevel;
				 currentstateP1 = idlestateP1;
				 NjumpP1.Reset();
				 FjumpP1.Reset();
				 BjumpP1.Reset();
				 JLP_P1.Reset();
				 JMP_P1.Reset();
				 JHPN_P1.Reset();
				 JHPFB_P1.Reset();
				 JLK_P1.Reset();
				 JMK_P1.Reset();
				 JHK_P1.Reset();
				 jumping = false;
				 airkick = true;
				 neutralJump = false;
				 forwardJump = false;
				 backwardJump = false;
				 jumpTimer = 0;

			 }
		 }
		 if (jumping == true) {
			 if (airkick == true) {
				 
				 if (inputplayerP1.U_active) {
					 currentstateP1 = jumpLPP1;
					 airkick = false;
				 }
				 if (inputplayerP1.I_active) {
					 currentstateP1 = jumpMPP1;
					 airkick = false;
				 }
				 if (inputplayerP1.J_active) {
					 currentstateP1 = jumpLKP1;
					 airkick = false;
				 }
				 if (inputplayerP1.K_active) {
					 currentstateP1 = jumpMKP1;
					 airkick = false;
				 }
				 if (inputplayerP1.L_active) {
					 currentstateP1 = jumpHKP1;
					 airkick = false;
				 }
				 if (currentstateP1 == FjumpstateP1 || currentstateP1 == BjumpstateP1) {
					 if (inputplayerP1.O_active) {
						 currentstateP1 = DjumpHPP1;
						 airkick = false;
					 }
				 }
				 else {
					 if (inputplayerP1.O_active) {
						 currentstateP1 = NjumpHPP1;
						 airkick = false;
					 }
				 }
				
			 }

		 }



		 //ATTACKS
		 //STANDING FAR LP
		 if (currentstateP1 == standingfarLPP1) {
			 if (currentP1_animation->Finished() && !inputplayerP1.U_active) {
				 currentstateP1 = idlestateP1;
				 alreadyHit = false;
				 SFLP_P1.Reset();
				 LOG("LP to IDLE");
				 ++thundertick;
			 }

			  if ( !currentP1_animation->Finished() && inputplayerP1.U_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {
				  if (thundertick > 3) {
					  currentstateP1 = thunder1P1;
					  alreadyHit = false;
					  SFLP_P1.Reset();
					  
					  LOG("LP to Thunder1");
				  }
			  }
			
		 }
		 //THUNDER
		 if (currentstateP1 == thunder1P1) {

			 if (currentP1_animation->Finished()&&!inputplayerP1.U_active && !inputplayerP1.I_active && !inputplayerP1.O_active) {  ////////////////// AQUI ESTA EL PROBLEMA
				 alreadyHit = false;

				 currentstateP1 = idlestateP1;
				 SFLP_P1.Reset();
				 Ethunder_P1.Reset();
				 LOG("Thunder 1 to IDLE");
			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.U_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {

				 currentstateP1 = thunder2P1;
				 alreadyHit = false;
				 SFLP_P1.Reset();
				
				 LOG("LP to Thunder1");

			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.I_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {

				 currentstateP1 = thunder2P1;
				 alreadyHit = false;
				 SFMP_P1.Reset();
				 SFLP_P1.Reset();
				 SFHP_P1.Reset();
				 LOG("LP to Thunder1");

			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.O_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {

				 currentstateP1 = thunder2P1;
				 alreadyHit = false;
				 SFHP_P1.Reset();
				 SFLP_P1.Reset();
				 SFMP_P1.Reset();
				 LOG("LP to Thunder1");

			 }

		 }


		 if (currentstateP1 == thunder2P1) {
		 

			 if (currentP1_animation->Finished()) {
				 currentstateP1 = idlestateP1;
				 Ethunder_P1.Reset();
				 LOG("GOING BACK TO IDLE ");
			 }
		 }

		 /*if (currentstateP1 == standingfarHPP1) {

			 if (currentP1_animation->Finished() && !inputplayerP1.J_active){
				 currentstateP1 = idlestateP1;
			 }
		 }
*/
		 //THROW
		 if (currentstateP1 == throwP1) {

			 if (currentP1_animation->Finished())
			 {
				 Throw_P1.Reset();
				 
				 currentstateP1 = idlestateP1;

			 }

		 }

		 //CROUCH LP
		 if (currentstateP1 == crouchLPP1) {
			 if (currentP1_animation->Finished() && !inputplayerP1.U_active && inputplayerP1.S_active) {
				 currentstateP1 = crouchstateP1;
				 alreadyHit = false;
				 CLP_P1.Reset();
				 LOG("LP to CROUCH");
			 }
			 if (currentP1_animation->Finished() && !inputplayerP1.U_active && !inputplayerP1.S_active) {
				 currentstateP1 =idlestateP1;
				 alreadyHit = false;
				 CLP_P1.Reset();
				 LOG("LP CROUCHED to IDLE");
			 }
		 }
		 if (currentstateP1 == SdamagedP1) {
			 if (currentP1_animation->Finished()) {
				 currentstateP1 = idlestateP1;
				 SdamageLP1.Reset();
			 }
		 }

		 //HEADBUTT
		 if (currentstateP1 == HeadbuttP1) {

			
			 if (currentP1_animation->Finished() && inputplayerP1.I_active && !inputplayerP1.A_active && !inputplayerP1.D_active) {

				 Headbut_P1.Reset();

				 currentstateP1 = standingfarMPP1;

			 }

			 if (currentP1_animation->Finished() && !inputplayerP1.I_active && !inputplayerP1.A_active && !inputplayerP1.D_active) {

				 Headbut_P1.Reset();

				 currentstateP1 = idlestateP1;

			 }
			  
			 if (currentP1_animation->Finished() && !inputplayerP1.I_active && !inputplayerP1.A_active && inputplayerP1.D_active) {

				 Headbut_P1.Reset();

				 currentstateP1 = forwardstateP1;

			 }
			 if (currentP1_animation->Finished() && !inputplayerP1.I_active && inputplayerP1.A_active && !inputplayerP1.D_active) {

				 Headbut_P1.Reset();

				 currentstateP1 = backwardstateP1;

			 }

			
		 }

		 if (currentstateP1 == rollingattackP1LIGHT) {

			 //if (currentP1_animation->Finished()&& inputplayerP1.D_active && !inputplayerP1.I_active && !inputplayerP1.O_active ) {

				
				//RollingP1.Reset();
				// currentstateP1 = forwardstateP1;
			 //}

			 if (positionP1.x + 40 == App->player2->positionP2.x) {

				 currentstateP1 = rollingreboundP1;
				 RollingP1.Reset();

			 }

		 }

		 if (currentstateP1 == rollingattackP1MEDIUM) {

			 //if (currentP1_animation->Finished() && !inputplayerP1.D_active && !inputplayerP1.I_active && !inputplayerP1.O_active) {

				// // RollingP1.Reset();
				//RollingP1.Reset();
				// currentstateP1 =  idlestateP1;
			 //}

			 if (positionP1.x + 40 >= App->player2->positionP2.x) {

				 currentstateP1 = rollingreboundP1;
				 RollingP1.Reset();

			 }
		 }

		 if (currentstateP1 == rollingattackP1HEAVY) {

			 //if (currentP1_animation->Finished() && !inputplayerP1.D_active && !inputplayerP1.I_active && inputplayerP1.O_active) {

				// // RollingP1.Reset();
				// RollingP1.Reset();
				// currentstateP1 = standingfarHPP1;
			 //}

			 if (positionP1.x + 40 == App->player2->positionP2.x) {

				 currentstateP1 = rollingreboundP1;
				 RollingP1.Reset();

			 }
		 }

		 //if (currentstateP1 == rollingattackP1) {

			// //if (currentP1_animation->Finished() && !inputplayerP1.D_active && inputplayerP1.I_active && !inputplayerP1.O_active) {

			//	// // RollingP1.Reset();
			//	// RollingP1.Reset();
			//	// currentstateP1 = standingfarMPP1;
			// //}

			// if (positionP1.x+ 40 == App->player2->positionP2.x) {

			//	 currentstateP1 = rollingreboundP1;
			//	 RollingP1.Reset();

			// }
		 //}

		 if (currentstateP1  == rollingreboundP1) {

			 if (currentP1_animation->Finished() && !inputplayerP1.D_active && inputplayerP1.I_active && !inputplayerP1.O_active) {

			    // RollingP1.Reset();
				 RollingRebP1.Reset();
			    currentstateP1 = standingfarMPP1;
			}


		 }

		 if (currentstateP1 == rollingreboundP1) {


			 if (currentP1_animation->Finished() && !inputplayerP1.D_active && !inputplayerP1.I_active && inputplayerP1.O_active) {

			    // RollingP1.Reset();
				 RollingRebP1.Reset();
			    currentstateP1 = standingfarHPP1;
			}



		 }

		 if (currentstateP1 == rollingreboundP1) {


			 if (currentP1_animation->Finished()&& inputplayerP1.D_active && !inputplayerP1.I_active && !inputplayerP1.O_active ) {


				 RollingRebP1.Reset();
			    currentstateP1 = forwardstateP1;
			}


		 }
		 
		 if (currentstateP1 == rollingreboundP1) {



			 if (currentP1_animation->Finished() && !inputplayerP1.D_active && !inputplayerP1.I_active && !inputplayerP1.O_active) {

			    // RollingP1.Reset();
				 RollingRebP1.Reset();
			    currentstateP1 =  idlestateP1;
			}


		 }
		return UPDATE_CONTINUE;
	}
}

update_status ModulePlayer::Update() {

	switch (currentstateP1)
	{

	case idlestateP1:
		playerP1_collider->rect.h = 93;
		positionP1.y = groundLevel;
		currentP1_animation = &idleP1;
		//LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstateP1:
		playerP1_collider->rect.h = 93;

		currentP1_animation = &backwardP1;
		positionP1.x -= speed;
		LOG("BACK ANIMATION ACTIVE");
		break;

	case forwardstateP1:

		currentP1_animation = &forwardP1;

		positionP1.x += speed;
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case crouchstateP1:
		currentP1_animation = &crouchP1;
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - camx, positionP1.y - 68 - camy);

		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case NjumpstateP1:
		currentP1_animation = &NjumpP1;
		 //MRUA
		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;

	case FjumpstateP1:
		if (!flipP1) { currentP1_animation = &FjumpP1; }
		else { currentP1_animation = &BjumpP1; }
		//positionP1.x += speed;
		//positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		LOG(" FORWARD JUMP ANIMATION ACTIVE");
		break;

	case BjumpstateP1:
		if (!flipP1) { currentP1_animation = &BjumpP1; }
		else { currentP1_animation = &FjumpP1; }
		//positionP1.x -= speed;
		//positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		LOG(" BACKWARD JUMP ANIMATION ACTIVE");
		break;

	case standingfarLPP1:
		currentP1_animation = &SFLP_P1;         //&SFLP_P1
		attackP1_collider->SetPos(positionP1.x - camx,positionP1.y - camy);
		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarMPP1:
		currentP1_animation = &SFMP_P1;         //&SFMP_P1
		attackP1_collider->SetPos(positionP1.x +40 - camx, positionP1.y -107 - camy);
		LOG("LP ANIMATION ACTIVE");
		break;
	case standingfarHPP1:
		currentP1_animation = &SFHP_P1;         //&SFHP_P1
		attackP1_collider->SetPos(positionP1.x + 55 - camx, positionP1.y - 90 - camy);
		LOG("LP ANIMATION ACTIVE");
		break;
	case standingfarLKP1:
		currentP1_animation = &SFLK_P1;         //&SFLK_P1
		attackP1_collider->SetPos(positionP1.x + 80 - camx, positionP1.y - 75 - camy);
		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarMKP1:
		currentP1_animation = &SFMK_P1;         //&SFMK_P1
		attackP1_collider->SetPos(positionP1.x + 60 - camx, positionP1.y - 85 - camy);
		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarHKP1:
		currentP1_animation = &SFHK_P1;         //&SFHK_P1
		attackP1_collider->SetPos(positionP1.x + 60 - camx, positionP1.y - 85 - camy);
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseLPP1:
		currentP1_animation = &SCLP_P1;  
		attackP1_collider->SetPos(positionP1.x + 60 - camx, positionP1.y - 85 - camy);
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseMPP1:
		currentP1_animation = &SCMP_P1;
		attackP1_collider->SetPos(positionP1.x + 50 - camx, positionP1.y - 85 - camy);
		LOG("HK ANIMATION ACTIVE");
		break; 

	case standingcloseHPP1:
		currentP1_animation = &SCHP_P1;
		attackP1_collider->SetPos(positionP1.x + 60 - camx, positionP1.y - 85 - camy);
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseLKP1:
		currentP1_animation = &SCLK_P1;
		attackP1_collider->SetPos(positionP1.x + 60 - camx, positionP1.y - 85 - camy);
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseMKP1:
		currentP1_animation = &SCMK_P1;
		attackP1_collider->SetPos(positionP1.x + 60 - camx, positionP1.y - 85 - camy);
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseHKP1:
		currentP1_animation = &SCHK_P1;
		attackP1_collider->SetPos(positionP1.x + 60 - camx, positionP1.y - 25 - camy);
		LOG("HK ANIMATION ACTIVE");
		break;

	case thunder1P1:
		currentP1_animation = &SFLP_P1;
		LOG("THUNDER 1 ANIMATION ACTIVE");
		break;

	case thunder2P1:
		currentP1_animation = &Ethunder_P1;
		LOG("THUNDER 2 ANIMATION ACTIVE");
		break;

	case throwP1:
		currentP1_animation = &Throw_P1;
		/*App->player2->currentstateP2 = SdamagedHP2;
		App->player2->currentP2_animation = SdamageHP1;*/
		LOG("THROW ANIMATION ACTIVE");
		break;
		//crouch attacks
	case crouchLPP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - camx, positionP1.y - 68 - camy);
		
		currentP1_animation = &CLP_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchMPP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - camx, positionP1.y - 68 - camy);
		attackP1_collider->SetPos(positionP1.x + 55 -camx, positionP1.y - 55 - camy);
		currentP1_animation = &CMP_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchHPP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - camx, positionP1.y - 68 - camy);
		attackP1_collider->SetPos(positionP1.x + 65 - camx, positionP1.y - 65 - camy);
		currentP1_animation = &CHP_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchLKP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - camx, positionP1.y - 68 - camy);
		attackP1_collider->SetPos(positionP1.x + 48 -camx, positionP1.y - 25);
		currentP1_animation = &CLK_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchMKP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - camx, positionP1.y - 68 - camy);
		attackP1_collider->SetPos(positionP1.x + 48 -camx, positionP1.y - 25 -camy);
		currentP1_animation = &CMK_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchHKP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - camx, positionP1.y - 68 - camy);
		attackP1_collider->SetPos(positionP1.x + 60 -camx, positionP1.y - 25 -camy);
		currentP1_animation = &CHK_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	//Jumping attacks
	case jumpLPP1:
		currentP1_animation = &JLP_P1;
		break;
	case jumpMPP1:
		currentP1_animation = &JMP_P1;
		break;
	case NjumpHPP1:
		currentP1_animation = &JHPN_P1;
		break;
	case DjumpHPP1:
		currentP1_animation = &JHPFB_P1;
		break;
	case jumpLKP1:
		currentP1_animation = &JLK_P1;
		break;
	case jumpMKP1:
		currentP1_animation = &JMK_P1;
		break;
	case jumpHKP1:
		currentP1_animation = &JHK_P1;
		break;
	//damaged
	case SdamagedLP1:
		currentP1_animation = &SdamageLP1;
		positionP1.x -= 1;
		break;
	case SdamagedMP1:
		currentP1_animation = &SdamageMP1;
		positionP1.x -= 1;
		break;
	case SdamagedHP1:
		currentP1_animation = &SdamageHP1;
		positionP1.x -= 1;
		break;
	case SblockstunP1:
		currentP1_animation = &SblockP1;
		break;
	case HeadbuttP1:
		currentP1_animation = &Headbut_P1; // falta ANIMACIO HEADBUTT
		LOG("HEADBUTT ANIMATION ACTIVE");
		break;


	case rollingattackP1LIGHT:
		
		positionP1.y = 180;
		positionP1.x += 7;
		
		currentP1_animation = &RollingP1;
		
		LOG("ROLLING ANIMATION ACTIVE");
		break;


	case rollingattackP1MEDIUM:

		positionP1.y = 180;
		positionP1.x += 7;

		currentP1_animation = &RollingP1;

		LOG("ROLLING ANIMATION ACTIVE");
		break;
	

	case rollingattackP1HEAVY:

		positionP1.y = 180;
		positionP1.x += 7;

		currentP1_animation = &RollingP1;

		LOG("ROLLING ANIMATION ACTIVE");
		break;


	case rollingreboundP1:
	
		int positionstart = positionP1.x;
		currentP1_animation = &RollingRebP1;
		
		
		//positionP1.x -= speed;
		//positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		
		positionP1.x -= speed*4;
		//positionP1.y = groundLevel + (yvel*jumpTimer*3) + (-9*(gravity) * (9*jumpTimer*jumpTimer)); //MRUA
		
		
		
			positionP1.y -= 7;
		
		

		

			
		
		/*positionP1.y  -= 5;
		positionP1.x -= 12;*/
		
		LOG("ROLLING REBOUND ANIMATION ACTIVE");
		break;



    }

	

	if ( currentstateP1 != crouchstateP1 && currentstateP1 != crouchLPP1 && currentstateP1 != crouchMPP1 && currentstateP1 != crouchHPP1 && currentstateP1 != crouchLKP1 && currentstateP1 != crouchMKP1 && currentstateP1 != crouchHKP1 ) {
		playerP1_collider->SetPos(positionP1.x  - App->render->camera.x / SCREEN_ADD, positionP1.y - 93 - App->render->camera.y / SCREEN_ADD);
	}

	SDL_Rect r = currentP1_animation->GetCurrentFrame();
	//SHADOW
	shadowP1 = {796,27,100,20};
	
	//close check
	if (!flipP1) {
		if (positionP1.x + 50 > App->player2->positionP2.x) {
			close = true;
		}
		else {
			close = false;
		}
	}
	else {
		if (positionP1.x - App->player2->positionP2.x - 50 < 10) {
			close = true;
		}
		else {
			close = false;
		}
	}
	
	

	//Jumping boolean

	if (jumping) {
		jumpTimer = time - jumpstart;
		playerP1_collider->SetPos(positionP1.x - App->render->camera.x / SCREEN_ADD, positionP1.y - 80 - App->render->camera.y / SCREEN_ADD);
		positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer));
		if (forwardJump == true) {
			positionP1.x += speed;
		}
		if (backwardJump == true) {
			positionP1.x -= speed;
		}
	}
	//Flip of the players when they change sides
	if (positionP1.x +35 < App->player2->positionP2.x + 35 ) {
		flipP1 = false;
		App->render->Blit(graphicsP1, positionP1.x - 5, groundLevel-15, &shadowP1, 1.0f, true,SDL_FLIP_NONE);
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE,0.0f);
	}
	else {
		flipP1 = true;
		App->render->Blit(graphicsP1, positionP1.x +7, groundLevel -15, &shadowP1, 1.0f, true, SDL_FLIP_HORIZONTAL);
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_HORIZONTAL);
	}
	if (!jumping) {
		if (!flipP1) {
			if (positionP1.x + 35 > App->player2->positionP2.x) {
				positionP1.x = App->player2->positionP2.x - 35;
			}
		}
		else {
			if (App->player2->positionP2.x > positionP1.x - 35) {
				App->player2->positionP2.x = positionP1.x - 35;
			}
		}
	}

	if (positionP1.x <= App->render->camera.x /5)
	{
		positionP1.x = App->render->camera.x /5;
	}
	if (positionP1.x >= ((App->render->camera.x / 5) + SCREEN_WIDTH -100) )
	{
		positionP1.x = ((App->render->camera.x / 5) + SCREEN_WIDTH - 100) ;
	}

	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_PLAYER2_ATTACK) {
		
		if (c2->attack == SFLP || c2->attack == SFLK || c2->attack == SCLP || c2->attack == SCLK) {
			currentstateP1 = SdamagedLP1;
			deleteCollider(App->player2->attackP2_collider);

		}
		else if (c2->attack == SFMP || c2->attack == SFMK || c2->attack == SCMP || c2->attack == SCMK) {
			currentstateP1 = SdamagedMP1;
			deleteCollider(App->player2->attackP2_collider);
		}
		else if (c2->attack == SFHP || c2->attack == SFHK || c2->attack == SCHP || c2->attack == SCHK){
			currentstateP1 = SdamagedHP1;
			deleteCollider(App->player2->attackP2_collider);
		}
	}

}

bool ModulePlayer::comboActive() {

	//Input button combination for special attack	
	int i = 0;
	int j = startcombo;
	int done = 0; //If done = 3. Special attack = true 

	while (i < 100) {
		switch (done) {
		case 0:
			if (combo[j] == 'c')//punch
				done++;
			break;
		case 1:
			if (combo[j] == 'd')//forward
				done++;
			break;
		case 2:
			if (combo[j] == 'n' && 'm') // enredere
				done++;
			break;
		case 3:
			if (combo[j] == 's') //down
				return true;
		default:
			//Special attack is false
			return false;
		}

		if (j > 0)
			j--;
		else
			j = 99;
		i++;
	}

	return false;
}


void ModulePlayer::comboInput(char comboInput) {
	combo[*finishC] = comboInput; //We add the newInput to the last inputs array

	if (*finishC < 99) //We change last pointer's position 
		(*finishC)++;
	else
		*finishC = 0;

	//We change first pointer's position 
	if (*startC == *startC && *startC < 99)
		(*startC)++;
	else if (*startC == *finishC && *startC >= 99)
		* startC = 0;
}
