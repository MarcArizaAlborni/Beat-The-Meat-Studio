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

	scoreP1 = 0;

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
		forwardP1.speed = 0.14f;

		//Walk backwards animation

		backwardP1.PushBack({ 29, 211, 104, 101 }); //1
		backwardP1.PushBack({ 132, 211, 100, 101 }); //2
		backwardP1.PushBack({ 427, 211, 95, 101 }); //3
		backwardP1.PushBack({ 322, 211, 105, 101 }); //4
		backwardP1.PushBack({ 232, 211, 91, 101 }); //5
		backwardP1.PushBack({ 522, 211, 87, 101 }); //6
		backwardP1.PushBack({ 609, 211, 85, 101 }); //7
		backwardP1.PushBack({ 694, 211, 101, 101 }); //8
		backwardP1.loop = true;
		backwardP1.speed = 0.14f;

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

		//Crouch Damage L
		CdamageLP1.PushBack({ 30, 2573, 84, 93 });
		CdamageLP1.PushBack({ 30, 2573, 84, 93 });
		CdamageLP1.speed = 0.05f;

		//Crouch Damage M
		CdamageMP1.PushBack({ 30, 2573, 84, 93 });
		CdamageMP1.PushBack({ 30, 2573, 84, 93 });
		CdamageMP1.PushBack({ 128, 2573,101, 90 });
		CdamageMP1.PushBack({ 128, 2573,101, 90 });
		CdamageMP1.speed = 0.05f;

		//Crouch Damage H
		CdamageHP1.PushBack({ 30, 2573, 84, 93 });
		CdamageHP1.PushBack({ 30, 2573, 84, 93 });
		CdamageHP1.PushBack({ 128, 2573,101, 90 });
		CdamageHP1.PushBack({ 128, 2573,101, 90 });
		CdamageHP1.PushBack({ 248, 2585,109, 78 });
		CdamageHP1.PushBack({ 248, 2585,109, 78 });
		CdamageHP1.speed = 0.05f;

		//Electric Thunder Damage
		ETdamgeP1.PushBack({});

		//Jump Damage
		JdamageP1.PushBack({ 30, 2278, 96, 85 });
		JdamageP1.PushBack({ 258, 2282,114, 62 });
		JdamageP1.PushBack({ 275, 2348, 76, 59 });
		JdamageP1.PushBack({ 212, 2040, 67, 68 });
		JdamageP1.PushBack({ 120, 2052, 82, 55 });
		JdamageP1.PushBack({ 27, 2053, 88, 55 });
		JdamageP1.PushBack({ 458, 1974, 76, 59 });
		JdamageP1.PushBack({ 383, 1965, 67, 68 });
		JdamageP1.PushBack({ 288, 1977, 82, 56 });
		JdamageP1.PushBack({ 191, 1978, 88, 55 });
		JdamageP1.PushBack({ 384, 2573,127, 68 });
		JdamageP1.PushBack({ 316, 1250, 122, 99 });
		JdamageP1.PushBack({ 445, 1221, 88, 127 });
		JdamageP1.PushBack({ 536, 1250, 138, 98 });
		JdamageP1.PushBack({ 258, 2282,114, 62 });
		
		//Death 
		DeathP1.PushBack({ 30, 2278, 96, 85 });
		DeathP1.PushBack({ 134, 2283, 118, 66 });
		DeathP1.PushBack({ 384, 2573, 127, 68 });
		DeathP1.PushBack({ 182, 2824, 163, 52 });
		DeathP1.PushBack({ 384, 2573, 127, 68 });
		DeathP1.PushBack({ 357, 2837, 177, 39 });
		DeathP1.speed = 0.04f;

		//Victory 1
		Victory1P1.PushBack({ 639, 2542, 80,113 });
		Victory1P1.PushBack({ 725, 2525, 94,130 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 725, 2525, 94,130 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 725, 2525, 94,130 });
		Victory1P1.PushBack({ 639, 2542, 80,113 });
		Victory1P1.PushBack({ 725, 2525, 94,130 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 725, 2525, 94,130 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 725, 2525, 94,130 });
		Victory1P1.PushBack({ 639, 2542, 80,113 });
		Victory1P1.PushBack({ 725, 2525, 94,130 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 725, 2525, 94,130 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.PushBack({ 819, 2504, 87,151 });
		Victory1P1.speed = 0.09f;

		//Victory 2
		Victory2P1.PushBack({ 622, 351, 85, 63 });
		Victory2P1.PushBack({ 528, 343, 86, 64 });
		Victory2P1.PushBack({ 432, 328, 93, 87 });
		Victory2P1.PushBack({ 47, 530, 121, 72 });
		Victory2P1.PushBack({ 725, 2706, 91, 86 });
		Victory2P1.PushBack({ 191, 1978, 88, 55 });
		Victory2P1.PushBack({ 107, 1974, 76, 59 });
		Victory2P1.PushBack({ 27, 1965, 67, 68 });
		Victory2P1.PushBack({ 1053,2700, 91, 86 });
		Victory2P1.PushBack({ 634, 2830, 104, 70 });
		Victory2P1.PushBack({ 432, 328, 93, 87 });
		Victory2P1.speed = 0.4f;
		Victory2P1.loop = true;
		
		

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
	  JLP_P1.speed = 0.5f;
	   
	  //Standing FAR MP 
	  SFMP_P1.PushBack({31, 765, 88, 104 }); 
	  SFMP_P1.PushBack({134, 788, 120, 108 });
	  SFMP_P1.PushBack({264, 799, 130, 97 });
	  SFMP_P1.PushBack({403, 803, 103, 93}); //This is not correct I think
	  SFMP_P1.speed = 0.17f;
		
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
	  JMP_P1.speed = 0.3f;

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
	  CHP_P1.speed = 0.3f;

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
	  JHPFB_P1.speed = 0.2f;

	  //Jump Hp N
	  JHPN_P1.PushBack({ 610, 1587, 136, 84 });
	  JHPN_P1.PushBack({ 753, 1591, 78, 80 });
	  JHPN_P1.PushBack({ 857, 1589, 65, 82 });
	  JHPN_P1.PushBack({ 753, 1591, 78, 80 });
	  JHPN_P1.PushBack({ 610, 1587, 136, 84 });
	  JHPN_P1.speed = 0.1f;


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
	  JLK_P1.speed = 0.2f;

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
	  JMK_P1.speed = 0.2f;


	  //Standing FAR HK
	  SFHK_P1.PushBack({ 34, 1263, 90, 85 });
	  SFHK_P1.PushBack({ 143, 1263, 163, 85 });
	  SFHK_P1.PushBack({ 316, 1250, 122, 99 });
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
	  JHK_P1.speed = 0.2f;

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
{
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	graphicsP1 = App->textures->Load("Sprites/BlankaP1.png"); // JA TE LA FOTO BONA
	currentstateP1 = idlestateP1;
	comboP1[0] = ' ';
	*startCP1 = comboP1[0];
	*finishCP1 = comboP1[0];

	//Player 2 stest collider
	playerP1_collider = App->collision->AddCollider({ positionP1.x , positionP1.y,47,200 }, COLLIDER_PLAYER,NOATTACK, App->player);
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
	timeP1 = SDL_GetTicks() / 20;
	camxP1 = App->render->camera.x / SCREEN_ADD;
	camyP1 = App->render->camera.y / SCREEN_ADD;
	
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
		 /*if (currentstateP1 == standingfarLPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFLP_P1.Reset();
			 }
		 }*/

		 if (currentstateP1 == standingfarMPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFMP_P1.Reset();
			 }

			 if (currentP1_animation->Finished() && !inputplayerP1.I_active) {
				 currentstateP1 = idlestateP1;
				 deleteCollider(attackP1_collider);
				 SFMP_P1.Reset();
				 LOG("LP to IDLE");
				 ++thundertickP1;
			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.I_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {
				 if (thundertickP1 > 3) {
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
				 ++thundertickP1;
			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.O_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {
				 if (thundertickP1 > 3) {
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
		 if (currentstateP1 == crouchLPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = crouchstateP1;
				 CLP_P1.Reset();
			 }
		 }
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
				 if (neutralJumpP1 == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJumpP1 == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJumpP1 == true) { currentstateP1 = BjumpstateP1; }
				 JLP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == jumpMPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJumpP1 == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJumpP1 == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJumpP1 == true) { currentstateP1 = BjumpstateP1; }
				 JMP_P1.Reset();
			 }
		 }
		 if (currentstateP1 == NjumpHPP1) {
			 if (currentP1_animation->Finished()) {
				 
				 deleteCollider(attackP1_collider);
				 if (neutralJumpP1 == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJumpP1 == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJumpP1 == true) { currentstateP1 = BjumpstateP1; }
				 JHPN_P1.Reset();
			 }
		 }
		 if (currentstateP1 == DjumpHPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJumpP1 == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJumpP1 == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJumpP1 == true) { currentstateP1 = BjumpstateP1; }
				 JHPFB_P1.Reset();
			 }
		 }
		 if (currentstateP1 == jumpLKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJumpP1 == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJumpP1 == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJumpP1 == true) { currentstateP1 = BjumpstateP1; }
				 JLK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == jumpMKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJumpP1 == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJumpP1 == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJumpP1 == true) { currentstateP1 = BjumpstateP1; }
				 JMK_P1.Reset();
			 }
		 }
		 if (currentstateP1 == jumpHKP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 if (neutralJumpP1 == true) { currentstateP1 = NjumpstateP1; }
				 if (forwardJumpP1 == true) { currentstateP1 = FjumpstateP1; }
				 if (backwardJumpP1 == true) { currentstateP1 = BjumpstateP1; }
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
			 comboInputP1(' ');

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
				 jumpingP1 = true;
				 neutralJumpP1 = true;
				 
				 currentstateP1 = NjumpstateP1;
				 jumpstartP1 = timeP1;
				 jumpTimerP1 = 0;
				 LOG("IDLE to JUMP");
			 }
			 if (!closeP1) {
				 if (inputplayerP1.U_active) {
					 currentstateP1 = standingfarLPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 70, 20 }, COLLIDER_PLAYER_ATTACK,SFLP, App->player);
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
			 if (closeP1) {
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
			 comboInputP1('n');
			 comboInputP1('m');
			 if (!inputplayerP1.A_active) {
				 currentstateP1 = idlestateP1;
				
				 LOG("BACK to IDLE");
			 }
			 if (inputplayerP1.S_active) {
				 currentstateP1 = crouchstateP1;
				 LOG("BACK to CROUCH");
			 }
			 if (inputplayerP1.W_active) {
				 
				 jumpingP1 = true;
				 backwardJumpP1 = true;
				 currentstateP1 = BjumpstateP1;
				 jumpstartP1 = timeP1;
				 jumpTimerP1 = 0;
				 LOG("IDLE to CROUCH");
			 }
			 if (inputplayerP1.U_active) {
				 currentstateP1 = standingfarLPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 70, 20 }, COLLIDER_PLAYER_ATTACK, SFLP, App->player);
				 LOG("BACK to LP");
			 }
			 if (inputplayerP1.I_active) {
				 if (!closeP1) {
					 currentstateP1 = standingfarMPP1;
					 attackP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x + 55, positionP1.y - 80 - App->render->camera.y * 2, 100, 35 }, COLLIDER_PLAYER_ATTACK, SFMP, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
			 }
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

			
			

			 if (inputplayerP1.I_active && !inputplayerP1.D_active && closeP1) { //falta CONDICIO COLIDER APROP


				 currentstateP1 = HeadbuttP1;
				 LOG("BACKWARD TO HEADBUT");

			 }

			 if (inputplayerP1.O_active && closeP1) {


				 currentstateP1 = throwP1;

			 }

			 if (inputplayerP1.L_active && closeP1) {

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
				
				 jumpingP1 = true;
				 forwardJumpP1 = true;
				 currentstateP1 = FjumpstateP1;
				 jumpstartP1 = timeP1;
				 jumpTimerP1 = 0;
				 LOG("FOR to CROUCH");
			 }
			 if (inputplayerP1.U_active) {
				
				 currentstateP1 = standingfarLPP1;
				 attackP1_collider = App->collision->AddCollider({ 0,0, 70, 20 }, COLLIDER_PLAYER_ATTACK, SFLP, App->player);
				 LOG("FOR to LP");
			 }
			 if (inputplayerP1.I_active) { //aqui falta condicio de no s'estan tocant els coliders
				 if (!closeP1) {
					 currentstateP1 = standingfarMPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 35 }, COLLIDER_PLAYER_ATTACK, SFMP, App->player);
					 LOG("idle to heavy punch");
				 }
			 }
			 if (inputplayerP1.O_active && !closeP1) {
				 
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
	
			 if (inputplayerP1.I_active && closeP1) { //falta CONDICIO COLIDER APROP
				 currentstateP1 = HeadbuttP1;
				 LOG("FORWARD TO HEADBUT");

			 }
			 if (inputplayerP1.O_active && closeP1) {
				 currentstateP1 = throwP1;
			 }

		 }
		 //CROUCH STATE
		 if (currentstateP1 == crouchstateP1) {
			 comboInputP1('s');
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
				 attackP1_collider = App->collision->AddCollider({ 0,0, 93, 20 }, COLLIDER_PLAYER_ATTACK,CLP, App->player);
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
		 if (jumpingP1 == true) {
			 comboInputP1('w');
			 if (positionP1.y >= groundLevelP1 + 1) {
				 deleteCollider(attackP1_collider);
				 positionP1.y = groundLevelP1;
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
				 jumpingP1 = false;
				 airkickP1 = true;
				 neutralJumpP1 = false;
				 forwardJumpP1 = false;
				 backwardJumpP1 = false;
				 jumpTimerP1 = 0;

			 }
		 }
		 if (jumpingP1 == true) {
			 if (airkickP1 == true) {
				 
				 if (inputplayerP1.U_active) {
					 currentstateP1 = jumpLPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 55, 23 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
					 airkickP1 = false;
				 }
				 if (inputplayerP1.I_active) {
					 currentstateP1 = jumpMPP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 65, 33 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
					 airkickP1 = false;
				 }
				 if (inputplayerP1.J_active) {
					 currentstateP1 = jumpLKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 70, 23 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
					 airkickP1 = false;
				 }
				 if (inputplayerP1.K_active) {
					 currentstateP1 = jumpMKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 57, 25 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
					 airkickP1 = false;
				 }
				 if (inputplayerP1.L_active) {
					 currentstateP1 = jumpHKP1;
					 attackP1_collider = App->collision->AddCollider({ 0,0, 70, 33 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
					 airkickP1 = false;
				 }
				 if (currentstateP1 == FjumpstateP1 || currentstateP1 == BjumpstateP1) {
					 if (inputplayerP1.O_active) {
						 currentstateP1 = DjumpHPP1;
						 attackP1_collider = App->collision->AddCollider({ 0,0, 70, 50 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
						 airkickP1 = false;
					 }
				 }
				 else {
					 if (inputplayerP1.O_active) {
						 currentstateP1 = NjumpHPP1;
						 attackP1_collider = App->collision->AddCollider({ 0,0, 100, 25 }, COLLIDER_PLAYER_ATTACK, SFLK, App->player);
						 airkickP1 = false;
					 }
				 }
				
			 }

		 }

		 //ATTACKS
		 //STANDING FAR LP
		 if (currentstateP1 == standingfarLPP1) {
			 if (currentP1_animation->Finished() && !inputplayerP1.U_active) {
				 currentstateP1 = idlestateP1;
				 deleteCollider(attackP1_collider);
				 alreadyHitP1 = false;
				 SFLP_P1.Reset();
				 LOG("LP to IDLE");
				 ++thundertickP1;
			 }

			  if ( !currentP1_animation->Finished() && inputplayerP1.U_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {
				  if (thundertickP1 > 3) {
					  deleteCollider(attackP1_collider);
					  SFLP_P1.Reset();

					   
					  currentstateP1 = thunder1P1;
					  alreadyHitP1 = false;
					 
					  
					  LOG("LP to Thunder1");
				  }
			  }
			
		 }
		 //THUNDER
		 if (currentstateP1 == thunder1P1) {

			 if (currentP1_animation->Finished()&&!inputplayerP1.U_active && !inputplayerP1.I_active && !inputplayerP1.O_active) {  ////////////////// AQUI ESTA EL PROBLEMA
				 alreadyHitP1 = false;
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFLP_P1.Reset();
				 Ethunder_P1.Reset();
				 LOG("Thunder 1 to IDLE");
			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.U_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {

				 currentstateP1 = thunder2P1;
				 alreadyHitP1 = false;
				 SFLP_P1.Reset();
				
				 LOG("LP to Thunder1");

			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.I_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {

				 currentstateP1 = thunder2P1;
				 alreadyHitP1 = false;
				 SFMP_P1.Reset();
				 SFLP_P1.Reset();
				 SFHP_P1.Reset();
				 LOG("LP to Thunder1");

			 }

			 if (!currentP1_animation->Finished() && inputplayerP1.O_active && !inputplayerP1.D_active && !inputplayerP1.A_active) {

				 currentstateP1 = thunder2P1;
				 alreadyHitP1 = false;
				 SFHP_P1.Reset();
				 SFLP_P1.Reset();
				 SFMP_P1.Reset();
				 LOG("LP to Thunder1");
			 }
		 }

		 if (currentstateP1 == thunder2P1) {
		 

			 if (currentP1_animation->Finished()) {
				 currentstateP1 = idlestateP1;
				 deleteCollider(attackP1_collider);
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
				 alreadyHitP1 = false;
				 CLP_P1.Reset();
				 LOG("LP to CROUCH");
			 }
			 if (currentP1_animation->Finished() && !inputplayerP1.U_active && !inputplayerP1.S_active) {
				 currentstateP1 =idlestateP1;
				 alreadyHitP1 = false;
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

			

			 if (positionP1.x + 40 == App->player2->positionP2.x) {

				 currentstateP1 = rollingreboundP1;
				 RollingP1.Reset();

			 }
		 }

		 if (currentstateP1 == rollingattackP1MEDIUM) {

			 if (positionP1.x + 40 >= App->player2->positionP2.x) {

				 currentstateP1 = rollingreboundP1;
				 RollingP1.Reset();

			 }
		 }

		 if (currentstateP1 == rollingattackP1HEAVY) {


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
				 deleteCollider(attackP1_collider);
				 RollingRebP1.Reset();
			    currentstateP1 = standingfarMPP1;
			 }
		 }

		 if (currentstateP1 == rollingreboundP1) {

			 if (currentP1_animation->Finished() && !inputplayerP1.D_active && !inputplayerP1.I_active && inputplayerP1.O_active) {

			    // RollingP1.Reset();
				 deleteCollider(attackP1_collider);
				 RollingRebP1.Reset();
				 currentstateP1 = standingfarHPP1;
			 }
		 }

		 if (currentstateP1 == rollingreboundP1) {

			 if (currentP1_animation->Finished()&& inputplayerP1.D_active && !inputplayerP1.I_active && !inputplayerP1.O_active ) {
				 deleteCollider(attackP1_collider);
				 RollingRebP1.Reset();
			    currentstateP1 = forwardstateP1;
			 }
		 }

		 if (currentstateP1 == rollingreboundP1) {

			 if (currentP1_animation->Finished() && !inputplayerP1.D_active && !inputplayerP1.I_active && !inputplayerP1.O_active) {
				 deleteCollider(attackP1_collider);
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
		positionP1.y = groundLevelP1;
		currentP1_animation = &idleP1;
		//LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstateP1:
		playerP1_collider->rect.h = 93;
		currentP1_animation = &backwardP1;
		positionP1.x -= speedP1;
		LOG("BACK ANIMATION ACTIVE");
		break;

	case forwardstateP1:

		currentP1_animation = &forwardP1;

		positionP1.x += speedP1;
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case crouchstateP1:
		currentP1_animation = &crouchP1;
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x + 15 - camxP1, positionP1.y - 65 - camyP1);

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
		LOG(" FORWARD JUMP ANIMATION ACTIVE");
		break;

	case BjumpstateP1:
		if (!flipP1) { currentP1_animation = &BjumpP1; }
		else { currentP1_animation = &FjumpP1; }
		LOG(" BACKWARD JUMP ANIMATION ACTIVE");
		break;

	case standingfarLPP1:
		currentP1_animation = &SFLP_P1;         //&SFLP_P1
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 40 - camxP1, positionP1.y - 90 - camyP1);
		}
		else{
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 90 - camyP1);
		}
		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarMPP1:
		currentP1_animation = &SFMP_P1;         //&SFMP_P1
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 40 - camxP1, positionP1.y - 107 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 107 - camyP1);
		}
		
		LOG("LP ANIMATION ACTIVE");
		break;
	case standingfarHPP1:
		currentP1_animation = &SFHP_P1;         //&SFHP_P1
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 55 - camxP1, positionP1.y - 90 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 90 - camyP1);
		}
		
		LOG("LP ANIMATION ACTIVE");
		break;
	case standingfarLKP1:
		currentP1_animation = &SFLK_P1;         //&SFLK_P1
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 80 - camxP1, positionP1.y - 75 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 75 - camyP1);
		}
		
		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarMKP1:
		currentP1_animation = &SFMK_P1;         //&SFMK_P1
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 85 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 85 - camyP1);
		}
		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarHKP1:
		currentP1_animation = &SFHK_P1;         //&SFHK_P1
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 85 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 85 - camyP1);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseLPP1:
		currentP1_animation = &SCLP_P1;  
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 85 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 85 - camyP1);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseMPP1:
		currentP1_animation = &SCMP_P1;
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 50 - camxP1, positionP1.y - 85 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 85 - camyP1);
		}
		LOG("HK ANIMATION ACTIVE");
		break; 

	case standingcloseHPP1:
		currentP1_animation = &SCHP_P1;
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 85 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 85 - camyP1);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseLKP1:
		currentP1_animation = &SCLK_P1;
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 85 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 85 - camyP1);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseMKP1:
		currentP1_animation = &SCMK_P1;
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 85 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x- extradisP1 - camxP1, positionP1.y - 85 - camyP1);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseHKP1:
		currentP1_animation = &SCHK_P1;
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 25 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 25 - camyP1);
		}
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
		
		LOG("THROW ANIMATION ACTIVE");
		break;

		//crouch attacks
	case crouchLPP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x + 15 - camxP1, positionP1.y - 65 - camyP1);
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 55 - camxP1, positionP1.y - 55 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 55 - camyP1);
		}
		currentP1_animation = &CLP_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchMPP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x + 15 - camxP1, positionP1.y - 65 - camyP1);
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 55 - camxP1, positionP1.y - 55 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x- extradisP1 - camxP1, positionP1.y - 55 - camyP1);
		}
		currentP1_animation = &CMP_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchHPP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x + 15 - camxP1, positionP1.y - 65 - camyP1);
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 65 - camxP1, positionP1.y - 65 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 65 - camyP1);
		}
		currentP1_animation = &CHP_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchLKP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x + 15 - camxP1, positionP1.y - 65 - camyP1);
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 48 - camxP1, positionP1.y - 25);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 25);
		}
		currentP1_animation = &CLK_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchMKP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x + 15 - camxP1, positionP1.y - 65 - camyP1);
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 48 - camxP1, positionP1.y - 25 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 25 - camyP1);
		}
		currentP1_animation = &CMK_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchHKP1:
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x + 15 - camxP1, positionP1.y - 65 - camyP1);
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 25 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 25 - camyP1);
		}
		currentP1_animation = &CHK_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;

	//Jumping attacks
	case jumpLPP1:
		currentP1_animation = &JLP_P1;
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 45 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x- extradisP1 - camxP1, positionP1.y - 45 - camyP1);
		}
		break;
	case jumpMPP1:
		currentP1_animation = &JMP_P1;
		
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 50 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x- extradisP1 - camxP1, positionP1.y - 50 - camyP1);
		}
		break;
	case NjumpHPP1:
		currentP1_animation = &JHPN_P1;
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 45 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x- extradisP1 - camxP1, positionP1.y - 45 - camyP1);
		}
		break;
	case DjumpHPP1:
		currentP1_animation = &JHPFB_P1;
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 45 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 45 - camyP1);
		}
		break;
	case jumpLKP1:
		currentP1_animation = &JLK_P1;
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 25 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x- extradisP1 - camxP1, positionP1.y - 25 - camyP1);
		}
		break;
	case jumpMKP1:
		currentP1_animation = &JMK_P1;
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 25 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x- extradisP1 - camxP1, positionP1.y - 25 - camyP1);
		}
		break;
	case jumpHKP1:
		currentP1_animation = &JHK_P1;
		if (!flipP1) {
			attackP1_collider->SetPos(positionP1.x + 60 - camxP1, positionP1.y - 25 - camyP1);
		}
		else {
			attackP1_collider->SetPos(positionP1.x - extradisP1 - camxP1, positionP1.y - 25 - camyP1);
		}
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
		attackP1_collider->SetPos(positionP1.x  - camxP1, positionP1.y - 60 - camyP1);
		currentP1_animation = &RollingP1;
		
		LOG("ROLLING ANIMATION ACTIVE");
		break;


	case rollingattackP1MEDIUM:
		attackP1_collider->SetPos(positionP1.x  - camxP1, positionP1.y - 60 - camyP1);
		positionP1.y = 180;
		positionP1.x += 7;

		currentP1_animation = &RollingP1;

		LOG("ROLLING ANIMATION ACTIVE");
		break;
	

	case rollingattackP1HEAVY:
		attackP1_collider->SetPos(positionP1.x - camxP1, positionP1.y - 60 - camyP1);
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
		
		positionP1.x -= speedP1 *4;
		//positionP1.y = groundLevel + (yvel*jumpTimer*3) + (-9*(gravity) * (9*jumpTimer*jumpTimer)); //MRUA
		
		positionP1.y -= 7;
		
		/*positionP1.y  -= 5;
		positionP1.x -= 12;*/
		
		LOG("ROLLING REBOUND ANIMATION ACTIVE");
		break;
    }

	if ( currentstateP1 != crouchstateP1 && currentstateP1 != crouchLPP1 && currentstateP1 != crouchMPP1 && currentstateP1 != crouchHPP1 && currentstateP1 != crouchLKP1 && currentstateP1 != crouchMKP1 && currentstateP1 != crouchHKP1 ) {
		if (!flipP1) {
			playerP1_collider->SetPos(positionP1.x + 15 - App->render->camera.x / SCREEN_ADD, positionP1.y - 93 - App->render->camera.y / SCREEN_ADD);
		}
		else {
			playerP1_collider->SetPos(positionP1.x + 30 - App->render->camera.x / SCREEN_ADD, positionP1.y - 93 - App->render->camera.y / SCREEN_ADD);
		}
	}

	SDL_Rect r = currentP1_animation->GetCurrentFrame();
	//SHADOW
	shadowP1 = {796,27,100,20};
	
	//close check
	if (!flipP1) {
		if (positionP1.x + 50 > App->player2->positionP2.x) {
			closeP1 = true;
		}
		else {
			closeP1 = false;
		}
	}
	else {
		if (positionP1.x - App->player2->positionP2.x - 50 < 10) {
			closeP1 = true;
		}
		else {
			closeP1 = false;
		}
	}
	
	//Jumping boolean
	if (jumpingP1) {
		jumpTimerP1 = timeP1 - jumpstartP1;
		playerP1_collider->SetPos(positionP1.x + 15 - App->render->camera.x / SCREEN_ADD, positionP1.y - 93 - App->render->camera.y / SCREEN_ADD);
		positionP1.y = groundLevelP1 - (yvelP1*jumpTimerP1) + (0.5*(gravityP1) * (jumpTimerP1*jumpTimerP1));
		if (forwardJumpP1 == true) {
			positionP1.x += speedP1;
		}
		if (backwardJumpP1 == true) {
			positionP1.x -= speedP1;
		}
	}

	//Flip of the players when they change sides
	if (positionP1.x +35 < App->player2->positionP2.x + 35 ) {
		flipP1 = false;
		App->render->Blit(graphicsP1, positionP1.x - 5, groundLevelP1 -15, &shadowP1, 1.0f, true,SDL_FLIP_NONE);
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE,0.0f);
	}
	else {
		flipP1 = true;
		App->render->Blit(graphicsP1, positionP1.x +7, groundLevelP1 -15, &shadowP1, 1.0f, true, SDL_FLIP_HORIZONTAL);
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_HORIZONTAL);
	}
	if (!jumpingP1) {
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

	//camera Dynamic
	if (positionP1.x - 30 <= App->render->camera.x / 5 ) { // player1 is left screen 

		if(App->player2->positionP2.x <= (180 + App->render->camera.x / 5) + 120){ // player2 is close right camera

			App->render->camera.x -= speedP1 *2.5; //Move screen left
		}
	}

	if (positionP1.x >= ((App->render->camera.x / 5) + SCREEN_WIDTH - 130)){ // player1 is right screen

		if (App->player2->positionP2.x >= (App->render->camera.x / 5 )) { //player2 is close to left camera

			App->render->camera.x += speedP1 * 2.5; // Move camera right
		}
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

bool ModulePlayer::comboActiveP1() {

	//Input button combination for special attack	
	int i = 0;
	int j = startcomboP1;
	int done = 0; //If done = 3. Special attack = true 

	while (i < 100) {
		switch (done) {
		case 0:
			if (comboP1[j] == 'c')//punch
				done++;
			break;
		case 1:
			if (comboP1[j] == 'd')//forward
				done++;
			break;
		case 2:
			if (comboP1[j] == 'n' && 'm') // enredere
				done++;
			break;
		case 3:
			if (comboP1[j] == 's') //down
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


void ModulePlayer::comboInputP1(char comboInput) {
	comboP1[*finishCP1] = comboInput; //We add the newInput to the last inputs array

	if (*finishCP1 < 99) //We change last pointer's position 
		(*finishCP1)++;
	else
		*finishCP1 = 0;

	//We change first pointer's position 
	if (*startCP1 == *startCP1 && *startCP1 < 99)
		(*startCP1)++;
	else if (*startCP1 == *finishCP1 && *startCP1 >= 99)
		* startCP1 = 0;
}
