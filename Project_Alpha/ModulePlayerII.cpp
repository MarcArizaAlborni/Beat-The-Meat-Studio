#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayerII.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer.h"
#include <stdio.h>
#include "ModuleUI.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
void deleteCollider2(Collider* coll) {
	if (coll != nullptr) { coll->to_delete = true; };
}


ModulePlayer2::ModulePlayer2()
{
	graphicsP2 = NULL;
	currentP2_animation = NULL;

	scoreP2 = 0;

	healthP2.x = 100;
	healthP2.y = 400;
	healthP2.w = 200;
	healthP2.h = 20;


	{ //BASIC MOVEMENTS ANIMATIONS

		//Idle animation (arcade sprite sheet)
		idleP2.PushBack({ 233, 27, 100, 100 });
		idleP2.PushBack({ 32, 27, 100, 100 });
		idleP2.PushBack({ 135, 27, 100, 100 });
		idleP2.PushBack({ 32, 27, 100, 100 });
		idleP2.speed = 0.08f;

		//Walk FORWARD Animation
		forwardP2.PushBack({ 699, 127, 97, 84 });
		forwardP2.PushBack({ 232, 127, 90, 84 });
		forwardP2.PushBack({ 322, 127, 100, 84 });
		forwardP2.PushBack({ 422, 127, 100, 84 });
		forwardP2.PushBack({ 522, 127, 88, 84 });
		forwardP2.PushBack({ 609, 127, 90, 84 });
		forwardP2.PushBack({ 132, 127, 100, 84 });
		forwardP2.PushBack({ 29, 127, 105, 84 });
		forwardP2.loop = true;
		forwardP2.speed = 0.14f;

		//Walk backwards animation

		backwardP2.PushBack({ 29, 211, 104, 101 }); //1
		backwardP2.PushBack({ 132, 211, 100, 101 }); //2
		backwardP2.PushBack({ 427, 211, 95, 101 }); //3
		backwardP2.PushBack({ 322, 211, 105, 101 }); //4
		backwardP2.PushBack({ 232, 211, 91, 101 }); //5
		backwardP2.PushBack({ 522, 211, 87, 101 }); //6
		backwardP2.PushBack({ 609, 211, 85, 101 }); //7
		backwardP2.PushBack({ 694, 211, 101, 101 }); //8
		backwardP2.loop = true;
		backwardP2.speed = 0.14f;

		//Crouch Animation
		crouchP2.PushBack({ 427, 323, 99, 94 });
		crouchP2.PushBack({ 526, 323, 89, 94 });
		crouchP2.PushBack({ 615, 323, 93, 94 });
		crouchP2.speed = 0.5f;
		crouchP2.loop = false;

		//Neutral Jump Animation
		NjumpP2.PushBack({ 28, 525, 97, 128 });
		NjumpP2.PushBack({ 125, 525, 85, 128 });
		NjumpP2.PushBack({ 210, 525, 83, 128 });
		NjumpP2.PushBack({ 293, 525, 86, 128 });
		NjumpP2.PushBack({ 210, 525, 83, 128 });
		NjumpP2.PushBack({ 125, 525, 85, 128 });
		NjumpP2.PushBack({ 28, 525, 97, 128 });
		NjumpP2.speed = 0.1f;
		NjumpP2.loop = false;

		//Forward Jump Animation
		FjumpP2.PushBack({ 28, 525, 97, 128 });
		FjumpP2.PushBack({ 125, 525, 85, 128 });
		FjumpP2.PushBack({ 210, 525, 83, 128 });
		FjumpP2.PushBack({ 293, 525, 86, 128 });
		FjumpP2.PushBack({ 379, 525, 90, 128 });
		FjumpP2.PushBack({ 469, 525, 98, 128 });
		FjumpP2.PushBack({ 567, 525, 119, 128 });
		FjumpP2.PushBack({ 686, 525, 96, 128 });
		FjumpP2.PushBack({ 379, 525, 90, 128 });
		FjumpP2.PushBack({ 293, 525, 86, 128 });
		FjumpP2.speed = 0.17f;
		FjumpP2.loop = false;

		//Backward Jump Animation
		BjumpP2.PushBack({ 28, 525, 97, 128 });
		BjumpP2.PushBack({ 125, 525, 85, 128 });
		BjumpP2.PushBack({ 210, 525, 83, 128 });
		BjumpP2.PushBack({ 293, 525, 86, 128 });
		BjumpP2.PushBack({ 210, 525, 83, 128 });
		BjumpP2.PushBack({ 125, 525, 85, 128 });
		BjumpP2.PushBack({ 28, 525, 97, 128 });
		BjumpP2.speed = 0.17f;
		BjumpP2.loop = false;

		//Standing Turn Animation
		SturnP2.PushBack({ 36, 418, 89, 105 });
		SturnP2.PushBack({ 125, 418, 103, 105 });
		SturnP2.PushBack({ 228, 418, 97, 105 });

		//Crouch Turn Animation
		CturnP2.PushBack({ 622, 451, 82, 71 });
		CturnP2.PushBack({ 516, 451, 106, 71 });
		CturnP2.PushBack({ 428, 451, 88, 71 });

		//Standing Block Animation
		SblockP2.PushBack({ 730, 2169, 100, 96 });
		SblockP2.PushBack({ 730, 2169, 100, 96 });
		SblockP2.PushBack({ 730, 2169, 100, 96 });
		SblockP2.PushBack({ 630, 2169, 100, 96 });
		SblockP2.PushBack({ 630, 2169, 100, 96 });
		SblockP2.PushBack({ 630, 2169, 100, 96 });
		SblockP2.PushBack({ 630, 2169, 100, 96 });
		SblockP2.PushBack({ 630, 2169, 100, 96 });

		//Crouch Block Animation
		CblockP2.PushBack({ 730, 2100, 100, 63 });
		CblockP2.PushBack({ 730, 2100, 100, 63 });
		CblockP2.PushBack({ 730, 2100, 100, 63 });
		CblockP2.PushBack({ 630, 2100, 100, 63 });
		CblockP2.PushBack({ 630, 2100, 100, 63 });
		CblockP2.PushBack({ 630, 2100, 100, 63 });
		CblockP2.PushBack({ 630, 2100, 100, 63 });

		//Standing Damage Light
		SdamageLP2.PushBack({ 170, 2451, 88, 101 });
		SdamageLP2.PushBack({ 170, 2451, 88, 101 });
		SdamageLP2.PushBack({ 170, 2451, 88, 101 });
		SdamageLP2.PushBack({ 170, 2451, 88, 101 });
		SdamageLP2.PushBack({ 265, 2450, 101, 98 });
		SdamageLP2.PushBack({ 265, 2450, 101, 98 });
		SdamageLP2.loop = false;
		SdamageLP2.speed = 0.5;

		//Standing Damage Medium
		SdamageMP2.PushBack({ 170, 2451, 88, 101 });
		SdamageMP2.PushBack({ 170, 2451, 88, 101 });
		SdamageMP2.PushBack({ 170, 2451, 88, 101 });
		SdamageMP2.PushBack({ 170, 2451, 88, 101 });
		SdamageMP2.PushBack({ 265, 2450, 101, 98 });
		SdamageMP2.PushBack({ 265, 2450, 101, 98 });
		SdamageMP2.PushBack({ 32, 2459, 120, 86 });
		SdamageMP2.PushBack({ 32, 2459, 120, 86 });
		SdamageMP2.speed = 0.35f;

		//Standing Damage Hard
		SdamageHP2.PushBack({ 170, 2451, 88, 101 });
		SdamageHP2.PushBack({ 170, 2451, 88, 101 });
		SdamageHP2.PushBack({ 170, 2451, 88, 101 });
		SdamageHP2.PushBack({ 170, 2451, 88, 101 });
		SdamageHP2.PushBack({ 265, 2450, 101, 98 });
		SdamageHP2.PushBack({ 265, 2450, 101, 98 });
		SdamageHP2.PushBack({ 32, 2459, 120, 86 });
		SdamageHP2.PushBack({ 32, 2459, 120, 86 });
		SdamageHP2.PushBack({ 377, 2458, 86, 86 });
		SdamageHP2.PushBack({ 377, 2458, 86, 86 });
		SdamageHP2.speed = 0.3f;


		//Standing Damage Low Attack Light
		SdamagelowLP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowLP2.PushBack({ 30, 2363, 100, 79 });
		SdamagelowLP2.PushBack({ 30, 2363, 100, 79 });
		SdamagelowLP2.speed = 0.05f;

		//Standing Damage Low Attack Medium
		SdamagelowMP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowMP2.PushBack({ 30, 2363, 100, 79 });
		SdamagelowMP2.PushBack({ 30, 2363, 100, 79 });
		SdamagelowMP2.PushBack({ 133, 2363, 106, 72 });
		SdamagelowMP2.PushBack({ 133, 2363, 106, 72 });
		SdamagelowMP2.speed = 0.05f;


		//Standing Damage Low Attack Hard
		SdamagelowHP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP2.PushBack({ 30, 2278, 96, 85 });
		SdamagelowHP2.PushBack({ 30, 2363, 100, 79 });
		SdamagelowHP2.PushBack({ 30, 2363, 100, 79 });
		SdamagelowHP2.PushBack({ 133, 2363, 106, 72 });
		SdamagelowHP2.PushBack({ 133, 2363, 106, 72 });
		SdamagelowHP2.PushBack({ 377, 2458, 86, 86 });
		SdamagelowHP2.PushBack({ 377, 2458, 86, 86 });
		SdamagelowHP2.speed = 0.05f;

		//Crouch Damage
		CdamageP2.PushBack({});

		//Electric Thunder Damage
		ETdamgeP2.PushBack({});

		//Recovery
		RecoveryP2.PushBack({});

	}

	{ //ATTACKS ANIMATIONS

	  //Standing FAR LP
		SFLP_P2.PushBack({ 28, 658, 104, 105 });
		SFLP_P2.PushBack({ 132, 658, 143, 105 });
		SFLP_P2.PushBack({ 275, 658, 123, 105 });
		SFLP_P2.speed = 0.2f;
		SFLP_P2.loop = false;

		//Standing CLOSE LP
		SCLP_P2.PushBack({ 30, 1365, 110, 93 });
		SCLP_P2.PushBack({ 149, 1360, 149, 98 });
		SCLP_P2.PushBack({ 149, 1360, 149, 98 });
		SCLP_P2.PushBack({ 149, 1360, 149, 98 });
		SCLP_P2.PushBack({ 149, 1360, 149, 98 });
		SCLP_P2.PushBack({ 149, 1360, 149, 98 });
		SCLP_P2.PushBack({ 149, 1360, 149, 98 });
		SCLP_P2.PushBack({ 306, 1359, 135, 99 });
		SCLP_P2.PushBack({ 306, 1359, 135, 99 });
		SCLP_P2.PushBack({ 149, 1360, 149, 98 });
		SCLP_P2.PushBack({ 30, 1365, 110, 93 });
		SCLP_P2.speed = 0.5f;

		//Crouch LP
		CLP_P2.PushBack({ 610, 709, 109, 56 });
		CLP_P2.PushBack({ 727, 715, 154, 50 });
		CLP_P2.PushBack({ 890, 713, 142, 52 });
		CLP_P2.speed = 0.2f;
		CLP_P2.loop = false;

		//Jumping LP
		JLP_P2.PushBack({ 610, 1369, 94, 83 });
		JLP_P2.PushBack({ 840, 1371, 84, 81 });
		JLP_P2.PushBack({ 840, 1371, 84, 81 });
		JLP_P2.PushBack({ 712, 1372, 119, 80 });
		JLP_P2.PushBack({ 712, 1372, 119, 80 });
		JLP_P2.PushBack({ 712, 1372, 119, 80 });
		JLP_P2.PushBack({ 712, 1372, 119, 80 });
		JLP_P2.PushBack({ 712, 1372, 119, 80 });
		JLP_P2.PushBack({ 840, 1371, 84, 81 });
		JLP_P2.PushBack({ 610, 1369, 94, 83 });
		JLP_P2.speed = 0.5f;

		//Standing FAR MP 
		SFMP_P2.PushBack({ 32, 766, 88, 130});
		SFMP_P2.PushBack({ 134, 788, 120, 108 });
		SFMP_P2.PushBack({ 264, 799, 130, 97 });
		SFMP_P2.PushBack({ 403, 803, 103, 93 }); 
		SFMP_P2.PushBack({ 264, 799, 130, 97 });
		SFMP_P2.PushBack({ 134, 788, 120, 108 });
		SFMP_P2.PushBack({ 32, 766, 88, 130 });
		SFMP_P2.speed = 0.25f;

		//Standing CLOSE MP
		SCMP_P2.PushBack({ 30, 1365, 110, 93 });
		SCMP_P2.PushBack({ 149, 1360, 149, 98 });
		SCMP_P2.PushBack({ 149, 1360, 149, 98 });
		SCMP_P2.PushBack({ 149, 1360, 149, 98 });
		SCMP_P2.PushBack({ 149, 1360, 149, 98 });
		SCMP_P2.PushBack({ 149, 1360, 149, 98 });
		SCMP_P2.PushBack({ 149, 1360, 149, 98 });
		SCMP_P2.PushBack({ 306, 1359, 135, 99 });
		SCMP_P2.PushBack({ 306, 1359, 135, 99 });
		SCMP_P2.PushBack({ 149, 1360, 149, 98 });
		SCMP_P2.PushBack({ 30, 1365, 110, 93 });
		SCMP_P2.speed = 0.4f;

		//Crouch MP
		CMP_P2.PushBack({ 610, 792, 82, 64 });
		CMP_P2.PushBack({ 703, 794, 140, 62 });
		CMP_P2.PushBack({ 851, 790, 147, 66 });
		CMP_P2.PushBack({ 1005, 786, 140, 70 });
		CMP_P2.PushBack({ 851, 790, 147, 66 });
		CMP_P2.PushBack({ 703, 794, 140, 62 });
		CMP_P2.PushBack({ 610, 792, 82, 64 });
		CMP_P2.speed = 0.2f;

		//Jump MP
		JMP_P2.PushBack({ 610, 1369, 94, 83 });
		JMP_P2.PushBack({ 840, 1371, 84, 81 });
		JMP_P2.PushBack({ 840, 1371, 84, 81 });
		JMP_P2.PushBack({ 712, 1372, 119, 80 });
		JMP_P2.PushBack({ 712, 1372, 119, 80 });
		JMP_P2.PushBack({ 712, 1372, 119, 80 });
		JMP_P2.PushBack({ 712, 1372, 119, 80 });
		JMP_P2.PushBack({ 712, 1372, 119, 80 });
		JMP_P2.PushBack({ 840, 1371, 84, 81 });
		JMP_P2.PushBack({ 610, 1369, 94, 83 });
		JMP_P2.speed = 0.4f;

		//Standing FAR HP
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.speed = 0.5f;
		SFHP_P2.loop = false;

		//Standing CLOSE HP
		SCHP_P2.PushBack({ 30, 1471, 104, 70 });
		SCHP_P2.PushBack({ 30, 1471, 104, 70 });
		SCHP_P2.PushBack({ 141, 1473, 67, 68 });
		SCHP_P2.PushBack({ 141, 1473, 67, 68 });
		SCHP_P2.PushBack({ 218, 1482, 76, 59 });
		SCHP_P2.PushBack({ 218, 1482, 76, 59 });
		SCHP_P2.PushBack({ 308, 1471, 88, 70 });
		SCHP_P2.PushBack({ 308, 1471, 88, 70 });
		SCHP_P2.PushBack({ 407, 1463, 88, 86 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 155, 1553, 75, 74 });
		SCHP_P2.PushBack({ 155, 1553, 75, 74 });
		SCHP_P2.PushBack({ 141, 1473, 67, 68 });
		SCHP_P2.PushBack({ 141, 1473, 67, 68 });
		SCHP_P2.PushBack({ 141, 1473, 67, 68 });
		SCHP_P2.PushBack({ 218, 1482, 76, 59 });
		SCHP_P2.PushBack({ 218, 1482, 76, 59 });
		SCHP_P2.PushBack({ 308, 1471, 88, 70 });
		SCHP_P2.PushBack({ 308, 1471, 88, 70 });
		SCHP_P2.PushBack({ 407, 1463, 88, 86 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 30, 1560, 118, 68 });
		SCHP_P2.PushBack({ 155, 1553, 75, 74 });
		SCHP_P2.PushBack({ 155, 1553, 75, 74 });
		SCHP_P2.speed = 0.7f;

		//Crouch HP
		CHP_P2.PushBack({ 612, 895, 84, 58 });
		CHP_P2.PushBack({ 710, 898, 96, 55 });
		CHP_P2.PushBack({ 710, 898, 96, 55 });
		CHP_P2.PushBack({ 815, 869, 166, 84 });
		CHP_P2.PushBack({ 815, 869, 166, 84 });
		CHP_P2.PushBack({ 710, 898, 96, 55 });
		CHP_P2.PushBack({ 710, 898, 96, 55 });
		CHP_P2.PushBack({ 710, 898, 96, 55 });
		CHP_P2.PushBack({ 710, 898, 96, 55 });
		CHP_P2.PushBack({ 710, 898, 96, 55 });
		CHP_P2.PushBack({ 612, 895, 84, 58 });
		CHP_P2.PushBack({ 612, 895, 84, 58 });
		CHP_P2.PushBack({ 612, 895, 84, 58 });
		CHP_P2.speed = 0.3f;

		//Jump HP F and B
		JHPFB_P2.PushBack({ 610, 1462, 85, 117 });
		JHPFB_P2.PushBack({ 610, 1462, 85, 117 });
		JHPFB_P2.PushBack({ 610, 1462, 85, 117 });
		JHPFB_P2.PushBack({ 699, 1490, 126, 80 });
		JHPFB_P2.PushBack({ 699, 1490, 126, 80 });
		JHPFB_P2.PushBack({ 826, 1495, 98, 85 });
		JHPFB_P2.PushBack({ 826, 1495, 98, 85 });
		JHPFB_P2.PushBack({ 826, 1495, 98, 85 });
		JHPFB_P2.PushBack({ 925, 1491, 72, 89 });
		JHPFB_P2.PushBack({ 925, 1491, 72, 89 });
		JHPFB_P2.PushBack({ 925, 1491, 72, 89 });
		JHPFB_P2.speed = 0.5f;

		//Jump Hp N
		JHPN_P2.PushBack({ 610, 1587, 136, 84 });
		JHPN_P2.PushBack({ 753, 1591, 78, 80 });
		JHPN_P2.PushBack({ 857, 1589, 65, 82 });
		JHPN_P2.PushBack({ 753, 1591, 78, 80 });
		JHPN_P2.PushBack({ 610, 1587, 136, 84 });
		JHPN_P2.speed = 0.25f;


		//Standing FAR LK
		SFLK_P2.PushBack({ 33, 1028, 81, 96 });
		SFLK_P2.PushBack({ 124, 1031, 97, 94 });
		SFLK_P2.PushBack({ 230, 1032, 137, 93 });
		SFLK_P2.PushBack({ 230, 1032, 137, 93 });
		SFLK_P2.PushBack({ 124, 1031, 97, 94 });
		SFLK_P2.PushBack({ 33, 1028, 81, 96 });
		SFLK_P2.speed = 0.3f;
		SFLK_P2.loop = false;

		//Standing CLOSE LK
		SCLK_P2.PushBack({ 30, 1637, 79, 111 });
		SCLK_P2.PushBack({ 30, 1637, 79, 111 });
		SCLK_P2.PushBack({ 122, 1644, 66, 104 });
		SCLK_P2.PushBack({ 122, 1644, 66, 104 });
		SCLK_P2.PushBack({ 196, 1648, 60, 99 });
		SCLK_P2.PushBack({ 196, 1648, 60, 99 });
		SCLK_P2.PushBack({ 264, 1648, 75, 94 });
		SCLK_P2.PushBack({ 264, 1648, 75, 94 });
		SCLK_P2.PushBack({ 264, 1648, 75, 94 });
		SCLK_P2.PushBack({ 264, 1648, 75, 94 });
		SCLK_P2.PushBack({ 264, 1648, 75, 94 });
		SCLK_P2.PushBack({ 264, 1648, 75, 94 });
		SCLK_P2.PushBack({ 196, 1648, 60, 99 });
		SCLK_P2.PushBack({ 196, 1648, 60, 99 });
		SCLK_P2.PushBack({ 122, 1644, 66, 104 });
		SCLK_P2.PushBack({ 122, 1644, 66, 104 });
		SCLK_P2.PushBack({ 30, 1637, 79, 111 });
		SCLK_P2.PushBack({ 30, 1637, 79, 111 });

		SCLK_P2.speed = 0.7f;

		//Crouch LK
		CLK_P2.PushBack({ 610, 980, 74, 78 });
		CLK_P2.PushBack({ 702, 978, 74, 78 });
		CLK_P2.PushBack({ 790, 972, 139, 68 });
		CLK_P2.PushBack({ 702, 978, 74, 78 });
		CLK_P2.PushBack({ 610, 980, 74, 78 });
		CLK_P2.speed = 0.3f;

		//Jump LK
		JLK_P2.PushBack({ 610, 1690, 80, 79 });
		JLK_P2.PushBack({ 702, 1679, 102, 86 });
		JLK_P2.PushBack({ 816, 1680, 127, 85 });
		JLK_P2.PushBack({ 816, 1680, 127, 85 });
		JLK_P2.PushBack({ 816, 1680, 127, 85 });
		JLK_P2.speed = 0.27f;

		//Standing FAR MK
		SFMK_P2.PushBack({ 28, 1135, 92, 85 });
		SFMK_P2.PushBack({ 129, 1135, 101, 85 });
		SFMK_P2.PushBack({ 236, 1135, 124, 85 });
		SFMK_P2.PushBack({ 236, 1135, 124, 85 });
		SFMK_P2.PushBack({ 129, 1135, 101, 85 });
		SFMK_P2.PushBack({ 28, 1135, 92, 85 });
		SFMK_P2.speed = 0.23f;
		SFMK_P2.loop = false;

		//Standing CLOSE MK
		SCMK_P2.PushBack({ 30, 1637, 79, 111 });
		SCMK_P2.PushBack({ 30, 1637, 79, 111 });
		SCMK_P2.PushBack({ 122, 1644, 66, 104 });
		SCMK_P2.PushBack({ 122, 1644, 66, 104 });
		SCMK_P2.PushBack({ 196, 1648, 60, 99 });
		SCMK_P2.PushBack({ 196, 1648, 60, 99 });
		SCMK_P2.PushBack({ 196, 1648, 60, 99 });
		SCMK_P2.PushBack({ 196, 1648, 60, 99 });
		SCMK_P2.PushBack({ 196, 1648, 60, 99 });
		SCMK_P2.PushBack({ 196, 1648, 60, 99 });
		SCMK_P2.PushBack({ 264, 1648, 75, 94 });
		SCMK_P2.PushBack({ 264, 1648, 75, 94 });
		SCMK_P2.PushBack({ 264, 1648, 75, 94 });
		SCMK_P2.PushBack({ 264, 1648, 75, 94 });
		SCMK_P2.PushBack({ 264, 1648, 75, 94 });
		SCMK_P2.PushBack({ 264, 1648, 75, 94 });
		SCMK_P2.PushBack({ 196, 1648, 60, 99 });
		SCMK_P2.PushBack({ 196, 1648, 60, 99 });
		SCMK_P2.PushBack({ 122, 1644, 66, 104 });
		SCMK_P2.PushBack({ 122, 1644, 66, 104 });
		SCMK_P2.PushBack({ 30, 1637, 79, 111 });
		SCMK_P2.PushBack({ 30, 1637, 79, 111 });
		SCMK_P2.speed = 0.7f;

		//Crouch MK
		CMK_P2.PushBack({ 610, 980, 74, 78 });
		CMK_P2.PushBack({ 702, 978, 74, 78 });
		CMK_P2.PushBack({ 790, 972, 139, 68 });
		CMK_P2.PushBack({ 790, 972, 139, 68 });
		CMK_P2.PushBack({ 702, 978, 74, 78 });
		CMK_P2.PushBack({ 610, 980, 74, 78 });
		CMK_P2.speed = 0.22f;

		//Jump MK
		JMK_P2.PushBack({ 610, 1690, 80, 79 });
		JMK_P2.PushBack({ 702, 1679, 102, 86 });
		JMK_P2.PushBack({ 816, 1680, 127, 85 });
		JMK_P2.PushBack({ 816, 1680, 127, 85 });
		JMK_P2.PushBack({ 816, 1680, 127, 85 });
		JMK_P2.PushBack({ 702, 1679, 102, 86 });
		JMK_P2.PushBack({ 610, 1690, 80, 79 });
		JMK_P2.speed = 0.3f;


		//Standing FAR HK
		SFHK_P2.PushBack({ 34, 1263, 90, 85 });
		SFHK_P2.PushBack({ 143, 1263, 163, 85 });
		SFHK_P2.PushBack({ 316, 1249, 122, 99 });
		SFHK_P2.PushBack({ 445, 1221, 88, 127 });
		SFHK_P2.PushBack({ 536, 1250, 138, 98 });
		SFHK_P2.PushBack({ 686, 1279, 103, 69 });
		SFHK_P2.speed = 0.2f;
		SFHK_P2.loop = false;

		//Standing CLOSE HK
		SCHK_P2.PushBack({ 30, 1752, 72, 81 });
		SCHK_P2.PushBack({ 30, 1752, 72, 81 });
		SCHK_P2.PushBack({ 117, 1757, 91, 76 });
		SCHK_P2.PushBack({ 117, 1757, 91, 76 });
		SCHK_P2.PushBack({ 214, 1764, 161, 69 });
		SCHK_P2.PushBack({ 214, 1764, 161, 69 });
		SCHK_P2.PushBack({ 214, 1764, 161, 69 });
		SCHK_P2.PushBack({ 214, 1764, 161, 69 });
		SCHK_P2.PushBack({ 214, 1764, 161, 69 });
		SCHK_P2.PushBack({ 117, 1757, 91, 76 });
		SCHK_P2.PushBack({ 117, 1757, 91, 76 });
		SCHK_P2.PushBack({ 117, 1757, 91, 76 });
		SCHK_P2.PushBack({ 30, 1752, 72, 81 });
		SCHK_P2.PushBack({ 30, 1752, 72, 81 });
		SCHK_P2.PushBack({ 30, 1752, 72, 81 });
		SCHK_P2.speed = 0.4f;

		//Crouch HK
		CHK_P2.PushBack({ 30, 1752, 72, 81 });
		CHK_P2.PushBack({ 30, 1752, 72, 81 });
		CHK_P2.PushBack({ 117, 1757, 91, 76 });
		CHK_P2.PushBack({ 117, 1757, 91, 76 });
		CHK_P2.PushBack({ 214, 1764, 161, 69 });
		CHK_P2.PushBack({ 214, 1764, 161, 69 });
		CHK_P2.PushBack({ 214, 1764, 161, 69 });
		CHK_P2.PushBack({ 214, 1764, 161, 69 });
		CHK_P2.PushBack({ 214, 1764, 161, 69 });
		CHK_P2.PushBack({ 117, 1757, 91, 76 });
		CHK_P2.PushBack({ 117, 1757, 91, 76 });
		CHK_P2.PushBack({ 117, 1757, 91, 76 });
		CHK_P2.PushBack({ 30, 1752, 72, 81 });
		CHK_P2.PushBack({ 30, 1752, 72, 81 });
		CHK_P2.PushBack({ 30, 1752, 72, 81 });
		CHK_P2.speed = 0.4f;

		//Jump HK
		JHK_P2.PushBack({ 610, 1787, 96, 79 });
		JHK_P2.PushBack({ 706, 1779, 136, 87 });
		JHK_P2.PushBack({ 849, 1780, 170, 88 });
		JHK_P2.PushBack({ 849, 1780, 170, 88 });
		JHK_P2.PushBack({ 849, 1780, 170, 88 });
		JHK_P2.PushBack({ 706, 1779, 136, 87 });
		JHK_P2.PushBack({ 610, 1787, 96, 79 });
		JHK_P2.PushBack({ 610, 1787, 96, 79 });
		JHK_P2.PushBack({ 610, 1787, 96, 79 });
		JHK_P2.speed = 0.2f;

		//Headbut
		Headbut_P2.PushBack({ 616, 1954, 90, 100 });
		Headbut_P2.PushBack({ 616, 1954, 90, 100 });
		Headbut_P2.PushBack({ 717, 1959, 90, 95 });
		Headbut_P2.PushBack({ 717, 1959, 90, 95 });
		Headbut_P2.PushBack({ 717, 1959, 90, 95 });
		Headbut_P2.PushBack({ 717, 1959, 90, 95 });
		Headbut_P2.PushBack({ 717, 1959, 90, 95 });
		Headbut_P2.PushBack({ 820, 1978, 106, 76 });
		Headbut_P2.PushBack({ 820, 1978, 106, 76 });
		Headbut_P2.PushBack({ 937, 1999, 102, 56 });
		Headbut_P2.PushBack({ 820, 1978, 106, 76 });
		Headbut_P2.PushBack({ 820, 1978, 106, 76 });
		Headbut_P2.PushBack({ 717, 1959, 90, 95 });
		Headbut_P2.PushBack({ 717, 1959, 90, 95 });
		Headbut_P2.PushBack({ 616, 1954, 90, 100 });
		Headbut_P2.PushBack({ 616, 1954, 90, 100 });
		Headbut_P2.speed = 0.4f;

		//Throw
		Throw_P2.PushBack({ 27, 2141, 89, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 214, 2141, 76, 104 });
		Throw_P2.PushBack({ 214, 2141, 76, 104 });
		Throw_P2.PushBack({ 301, 2141, 93, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 301, 2141, 93, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 301, 2141, 93, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 301, 2141, 93, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 301, 2141, 93, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 301, 2141, 93, 104 });
		Throw_P2.PushBack({ 123, 2141, 82, 104 });
		Throw_P2.PushBack({ 27, 2141, 89, 104 });
		Throw_P2.speed = 0.1f;

		//Electric Thunder 
		Ethunder_P2.PushBack({ 27, 1871, 93, 75 });
		Ethunder_P2.PushBack({ 130, 1874, 86, 72 });
		Ethunder_P2.PushBack({ 27, 1871, 93, 75 });
		Ethunder_P2.PushBack({ 130, 1874, 86, 72 });
		Ethunder_P2.PushBack({ 27, 1871, 93, 75 });
		Ethunder_P2.PushBack({ 130, 1874, 86, 72 });
		Ethunder_P2.PushBack({ 228, 1866, 136, 79 });
		Ethunder_P2.PushBack({ 375, 1883, 85, 63 });
		Ethunder_P2.PushBack({ 228, 1866, 136, 79 });
		Ethunder_P2.PushBack({ 228, 1866, 136, 79 });
		Ethunder_P2.PushBack({ 228, 1866, 136, 79 });
		Ethunder_P2.PushBack({ 228, 1866, 136, 79 });
		Ethunder_P2.PushBack({ 375, 1883, 85, 63 });
		Ethunder_P2.PushBack({ 375, 1883, 85, 63 });
		Ethunder_P2.PushBack({ 228, 1866, 136, 79 });
		Ethunder_P2.PushBack({ 228, 1866, 136, 79 });
		Ethunder_P2.PushBack({ 228, 1866, 136, 79 });
		Ethunder_P2.PushBack({ 375, 1883, 85, 63 });
		Ethunder_P2.PushBack({ 375, 1883, 85, 63 });
		Ethunder_P2.PushBack({ 27, 1871, 93, 75 });
		Ethunder_P2.PushBack({ 130, 1874, 86, 72 });
		Ethunder_P2.PushBack({ 27, 1871, 93, 75 });
		Ethunder_P2.speed = 0.3f;

		//Rolling Attack
		RollingP2.PushBack({ 27, 1965, 67, 68 });
		RollingP2.PushBack({ 107, 1974, 76, 59 });
		RollingP2.PushBack({ 191, 1978, 88, 55 });
		RollingP2.PushBack({ 288, 1977, 82, 56 });
		RollingP2.PushBack({ 383, 1965, 67, 68 });
		RollingP2.PushBack({ 458, 1974, 76, 59 });
		RollingP2.PushBack({ 27, 2053, 88, 55 });
		RollingP2.PushBack({ 120, 2052, 82, 55 });
		RollingP2.PushBack({ 212, 2040, 67, 68 });
		RollingP2.PushBack({ 107, 1974, 76, 59 });
		RollingP2.PushBack({ 191, 1978, 88, 55 });
		RollingP2.PushBack({ 288, 1977, 82, 56 });
		RollingP2.PushBack({ 383, 1965, 67, 68 });
		RollingP2.PushBack({ 458, 1974, 76, 59 });
		RollingP2.PushBack({ 27, 2053, 88, 55 });
		RollingP2.PushBack({ 120, 2052, 82, 55 });
		RollingP2.PushBack({ 107, 1974, 76, 59 });
		RollingP2.speed = 0.5f;
		RollingP2.loop = true;


		//Rolling Rebound 

		RollingRebP2.PushBack({ 27, 1965, 67, 68 });
		RollingRebP2.PushBack({ 107, 1974, 76, 59 });
		RollingRebP2.PushBack({ 191, 1978, 88, 55 });
		RollingRebP2.PushBack({ 288, 1977, 82, 56 });
		RollingRebP2.PushBack({ 383, 1965, 67, 68 });
		RollingRebP2.speed = 0.5f;
		RollingRebP2.loop = true;

	}
}
	


ModulePlayer2::~ModulePlayer2()
{

}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");

	graphicsP2 = App->textures->Load("Sprites/BlankaP2.png"); // JA TE LA FOTO BONA
	
	currentstateP2 = idlestateP2;
	comboP2[0] = ' ';
	*startCP2 = comboP2[0];
	*finishCP2 = comboP2[0];

	//Player 2 stest collider
	playerP2_collider = App->collision->AddCollider({ positionP2.x , positionP2.y,47,200 }, COLLIDER_PLAYER2, NOATTACK, App->player2);
	attackP2_collider = nullptr;
	return true;
}


bool ModulePlayer2::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphicsP2);

	return true;
}


update_status ModulePlayer2::PreUpdate() {
	
	

	//MOVE BACKWARD
	//inputplayerP2.Right_active = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT;
	////MOVE FORWARD
	//inputplayerP2.Left_active = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT;
	////JUMP
	//inputplayerP2.Up_active = App->input->keyboard[SDL_SCANCODE_UP] == KEY_REPEAT;  
	////CROUCH
	//inputplayerP2.Down_active = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT;

	
	
	timeP2 = SDL_GetTicks() / 20;
	camxP2 = App->render->camera.x / SCREEN_ADD;
	camyP2 = App->render->camera.y / SCREEN_ADD;
	

	 inputplayerP2.Right_active = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)|| SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP2.Left_active = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_LEFT)|| SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	 inputplayerP2.Down_active = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP2.Up_active = App->input->keyboard[SDL_SCANCODE_UP] == KEY_REPEAT  || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;

	 inputplayerP2.Num7_active = App->input->keyboard[SDL_SCANCODE_KP_7] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_2] == KEY_DOWN;
	 inputplayerP2.Num8_active = App->input->keyboard[SDL_SCANCODE_KP_8] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_Y][GAME_PAD_2] == KEY_DOWN;
	 inputplayerP2.Num9_active = App->input->keyboard[SDL_SCANCODE_KP_9] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_LEFTSHOULDER][GAME_PAD_2] == KEY_DOWN;
	 inputplayerP2.Num4_active = App->input->keyboard[SDL_SCANCODE_KP_4] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] == KEY_DOWN;
	 inputplayerP2.Num5_active = App->input->keyboard[SDL_SCANCODE_KP_5] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_B][GAME_PAD_2] == KEY_DOWN;
	 inputplayerP2.Num6_active = App->input->keyboard[SDL_SCANCODE_KP_6] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER][GAME_PAD_2] == KEY_DOWN;

	 if (inputplayerP2.Left_active && inputplayerP2.Right_active) {
		 inputplayerP2.Left_active = false;
		 inputplayerP2.Right_active = false;
	 }

	
	 {
		 //STUNBLOCK CHECK
		 if (currentstateP2 == SblockstunP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SblockP2.Reset();
			 }

		 }
		 if (currentstateP2 == CblockstunP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = crouchstateP2;
				 CblockP2.Reset();
			 }

		 }

		 //Standing Far Attacks Animation check
		 /*if (currentstateP1 == standingfarLPP1) {
			 if (currentP1_animation->Finished()) {
				 deleteCollider(attackP1_collider);
				 currentstateP1 = idlestateP1;
				 SFLP_P1.Reset();
			 }
		 }*/

		 if (currentstateP2 == standingfarMPP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 App->player->alreadyHitP1 = false;
				 SFMP_P2.Reset();
			 }

			 if (currentP2_animation->Finished() && !inputplayerP2.Num8_active) {
				 currentstateP2 = idlestateP2;
				 deleteCollider2(attackP2_collider);
				 SFMP_P2.Reset();
				 LOG("LP to IDLE");
				 ++thundertickP2;
			 }

			 if (!currentP2_animation->Finished() && inputplayerP2.Num8_active && !inputplayerP2.Right_active && !inputplayerP2.Left_active) {
				 if (thundertickP2 > 3) {
					 currentstateP2 = thunder1P2;
					 deleteCollider2(attackP2_collider);

					 SFMP_P2.Reset();

					 LOG("LP to Thunder1");
				 }
			 }
		 }
		 if (currentstateP2 == standingfarHPP2) {
			 /* if (currentP1_animation->Finished()) {
				  deleteCollider(attackP1_collider);
				  currentstateP1 = idlestateP1;
				  SFHP_P1.Reset();
			  }*/

			 if (currentP2_animation->Finished() && !inputplayerP2.Num9_active) {
				 currentstateP2 = idlestateP2;
				 deleteCollider2(attackP2_collider);
				 App->player->alreadyHitP1 = false;
				 SFHP_P2.Reset();
				 LOG("LP to IDLE");
				 ++thundertickP2;
			 }

			 if (!currentP2_animation->Finished() && inputplayerP2.Num9_active && !inputplayerP2.Right_active && !inputplayerP2.Left_active) {
				 if (thundertickP2 > 3) {
					 currentstateP2 = thunder1P2;
					 deleteCollider2(attackP2_collider);

					 SFHP_P2.Reset();

					 LOG("LP to Thunder1");
				 }
			 }

		 }
		 if (currentstateP2 == standingfarLKP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 App->player->alreadyHitP1 = false;
				 SFLK_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingfarMKP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 App->player->alreadyHitP1 = false;
				 SFMK_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingfarHKP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 App->player->alreadyHitP1 = false;
				 SFHK_P2.Reset();
			 }
		 }
		 //Close Attacks Check
		 if (currentstateP2 == standingcloseMPP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 App->player->alreadyHitP1 = false;
				 SCMP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingcloseLPP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SCLP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingcloseHPP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SCHP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingcloseLKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SCLK_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingcloseMKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SCMK_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingcloseHKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SCHK_P2.Reset();
			 }
		 }
		 //Crouch attack checks
		 if (currentstateP2 == crouchLPP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = crouchstateP2;
				 CLP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == crouchMPP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = crouchstateP2;
				 CMP_P2.Reset();
			 }
		 }
		 if (currentstateP2== crouchHPP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = crouchstateP2;
				 CHP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == crouchLKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = crouchstateP2;
				 CLK_P2.Reset();
			 }
		 }
		 if (currentstateP2 == crouchMKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = crouchstateP2;
				 CMK_P2.Reset();
			 }
		 }
		 if (currentstateP2 == crouchHKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = crouchstateP2;
				 CHK_P2.Reset();
			 }
		 }
		 //Jumping attack check
		 if (currentstateP2 == jumpLPP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 App->player->alreadyHitP1 = false;
				 if (neutralJumpP2 == true) { currentstateP2 = NjumpstateP2; }
				 if (forwardJumpP2 == true) { currentstateP2 = FjumpstateP2; }
				 if (backwardJumpP2 == true) { currentstateP2 = BjumpstateP2; }
				 JLP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == jumpMPP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 App->player->alreadyHitP1 = false;
				 if (neutralJumpP2 == true) { currentstateP2 = NjumpstateP2; }
				 if (forwardJumpP2 == true) { currentstateP2 = FjumpstateP2; }
				 if (backwardJumpP2 == true) { currentstateP2 = BjumpstateP2; }
				 JMP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == NjumpHPP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 if (neutralJumpP2 == true) { currentstateP2 = NjumpstateP2; }
				 if (forwardJumpP2 == true) { currentstateP2 = FjumpstateP2; }
				 if (backwardJumpP2 == true) { currentstateP2 = BjumpstateP2; }
				 JHPN_P2.Reset();
			 }
		 }
		 if (currentstateP2 == DjumpHPP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 if (neutralJumpP2 == true) { currentstateP2 = NjumpstateP2; }
				 if (forwardJumpP2 == true) { currentstateP2 = FjumpstateP2; }
				 if (backwardJumpP2 == true) { currentstateP2 = BjumpstateP2; }
				 JHPFB_P2.Reset();
			 }
		 }
		 if (currentstateP2 == jumpLKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 if (neutralJumpP2 == true) { currentstateP2 = NjumpstateP2; }
				 if (forwardJumpP2 == true) { currentstateP2 = FjumpstateP2; }
				 if (backwardJumpP2 == true) { currentstateP2 = BjumpstateP2; }
				 JLK_P2.Reset();
			 }
		 }
		 if (currentstateP2 == jumpMKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 if (neutralJumpP2 == true) { currentstateP2 = NjumpstateP2; }
				 if (forwardJumpP2 == true) { currentstateP2 = FjumpstateP2; }
				 if (backwardJumpP2 == true) { currentstateP2 = BjumpstateP2; }
				 JMK_P2.Reset();
			 }
		 }
		 if (currentstateP2 == jumpHKP2) {
			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 deleteCollider2(attackP2_collider);
				 if (neutralJumpP2 == true) { currentstateP2 = NjumpstateP2; }
				 if (forwardJumpP2 == true) { currentstateP2 = FjumpstateP2; }
				 if (backwardJumpP2 == true) { currentstateP2 = BjumpstateP2; }
				 JHK_P2.Reset();
			 }
		 }
		 //Damaged chack
		 if (currentstateP2 == SdamagedLP2) {
			 if (currentP2_animation->Finished()) {
				 currentstateP2 = idlestateP2;
				 SdamageLP2.Reset();
			 }
		 }
		 if (currentstateP2 == SdamagedMP2) {
			 if (currentP2_animation->Finished()) {
				 currentstateP2 = idlestateP2;
				 SdamageMP2.Reset();
			 }
		 }
		 if (currentstateP2 == SdamagedHP2) {
			 if (currentP2_animation->Finished()) {
				 currentstateP2 = idlestateP2;
				 SdamageHP2.Reset();
			 }
		 }

		 //IDLE STATE
		 if (currentstateP2 == idlestateP2) {
			 comboInputP2(' ');

			 if (inputplayerP2.Left_active) {
				 currentstateP2 = backwardstateP2;

				 LOG("IDLE TO BACK");
			 }
			 if (inputplayerP2.Right_active) {
				 currentstateP2 = forwardstateP2;
				 LOG("IDLE TO forward");
			 }
			 if (inputplayerP2.Down_active) {
				 currentstateP2 = crouchstateP2;
				 LOG("IDLE to CROUCH");
			 }

			 if (inputplayerP2.Up_active) {
				 jumpingP2 = true;
				 neutralJumpP2 = true;

				 currentstateP2 = NjumpstateP2;
				 jumpstartP2 = timeP2;
				 jumpTimerP2 = 0;
				 LOG("IDLE to JUMP");
			 }
			 if (!App->player->closeP1) {
				 if (inputplayerP2.Num7_active) {
					 currentstateP2 = standingfarLPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 70, 20 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
					 LOG("IDLE to LP");

				 }
				 if (inputplayerP2.Num8_active) {
					 currentstateP2 = standingfarMPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 35 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP2.Num9_active) {
					 currentstateP2 = standingfarHPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 80, 18 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP2.Num4_active) {
					 currentstateP2 = standingfarLKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 57, 25 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP2.Num5_active) {
					 currentstateP2 = standingfarMKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 75, 15 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP2.Num6_active) {
					 currentstateP2 = standingfarHKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 75, 15 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
					 LOG("IDLE to HEAVY KICK");
				 }
			 }

			 //close attacks
			 if (App->player->closeP1) {
				 if (inputplayerP2.Num7_active) {
					 currentstateP2 = standingcloseLPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 50 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
					 LOG("IDLE to LP");
				 }
				 if (inputplayerP2.Num8_active) {
					 currentstateP2 = standingcloseMPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 30 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
				 if (inputplayerP2.Num9_active) {
					 currentstateP2 = standingcloseHPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 60, 25 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }

				 if (inputplayerP2.Num4_active) {
					 currentstateP2 = standingcloseLKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 57, 25 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }

				 if (inputplayerP2.Num5_active) {
					 currentstateP2 = standingcloseMKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 57, 25 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }

				 if (inputplayerP2.Num6_active) {
					 currentstateP2 = standingcloseHKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 22 }, COLLIDER_PLAYER2_ATTACK, CH, App->player);
					 LOG("IDLE to HEAVY KICK");
				 }



			 }
		 }
		 //BACKWARDS STATE
		 if (currentstateP2 == backwardstateP2) {
			 comboInputP2('n');
			 comboInputP2('m');
			 if (!inputplayerP2.Left_active) {
				 currentstateP2 = idlestateP2;

				 LOG("BACK to IDLE");
			 }
			 if (inputplayerP2.Down_active) {
				 currentstateP2 = crouchstateP2;
				 LOG("BACK to CROUCH");
			 }
			 if (inputplayerP2.Up_active) {

				 jumpingP2 = true;
				 backwardJumpP2 = true;
				 currentstateP2 = BjumpstateP2;
				 jumpstartP2 = timeP2;
				 jumpTimerP2 = 0;
				 LOG("IDLE to CROUCH");
			 }
			 if (inputplayerP2.Num7_active) {
				 currentstateP2 = standingfarLPP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 70, 20 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
				 LOG("BACK to LP");
			 }
			 if (inputplayerP2.Num8_active) {
				 if (!App->player->closeP1) {
					 currentstateP2 = standingfarMPP2;
					 attackP2_collider = App->collision->AddCollider({0, -100, 100, 35 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
					 LOG("IDLE to HEAVY PUNCH");
				 }
			 }
			 if (inputplayerP2.Num9_active) {
				 currentstateP2 = standingfarHPP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 80, 18 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num4_active) {
				 currentstateP2 = standingfarLKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 57, 25 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num5_active) {
				 currentstateP2 = standingfarMKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 75, 15 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num6_active) {
				 currentstateP2 = standingfarHKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 75, 15 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
				 LOG("IDLE to HEAVY KICK");
			 }

			 if (inputplayerP2.Right_active && inputplayerP2.Num7_active) {

				 currentstateP2 = rollingattackP2LIGHT;


			 }
			 if (inputplayerP2.Right_active && inputplayerP2.Num8_active) {

				 currentstateP2 = rollingattackP2MEDIUM;

			 }

			 if (inputplayerP2.Right_active && inputplayerP2.Num9_active) {

				 currentstateP2 = rollingattackP2HEAVY;

			 }

			 if (inputplayerP2.Num8_active && !inputplayerP2.Right_active && App->player->closeP1) { //falta CONDICIO COLIDER APROP

				 currentstateP2 = HeadbuttP2;
				 LOG("BACKWARD TO HEADBUT");
			 }

			 if (inputplayerP2.Num9_active && App->player->closeP1) {

				 currentstateP2 = throwP2;

			 }

			 if (inputplayerP2.Num6_active && App->player->closeP1) {

				 currentstateP2 = throwP2;
			 }

		 }
		 //FORWARD STATE
		 if (currentstateP2 == forwardstateP2) {

			 if (!inputplayerP2.Right_active) {
				 //blockP1_collider->to_delete = true;
				 currentstateP2 = idlestateP2;

				 LOG("FOR to IDLE");
			 }
			 if (inputplayerP2.Left_active) {
				 currentstateP2 = backwardstateP2;

				 LOG("FOR to BACK");
			 }
			 if (inputplayerP2.Down_active) {

				 currentstateP2 = crouchstateP2;
				 LOG("FOR to CROUCH");
			 }
			 if (inputplayerP2.Up_active) {

				 jumpingP2 = true;
				 forwardJumpP2 = true;
				 currentstateP2 = FjumpstateP2;
				 jumpstartP2 = timeP2;
				 jumpTimerP2 = 0;
				 LOG("FOR to CROUCH");
			 }
			 if (inputplayerP2.Num7_active) {

				 currentstateP2 = standingfarLPP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 70, 20 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
				 LOG("FOR to LP");
			 }
			 if (inputplayerP2.Num8_active) { //aqui falta condicio de no s'estan tocant els coliders
				 if (!App->player->closeP1) {
					 currentstateP2 = standingfarMPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 35 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
					 LOG("idle to heavy punch");
				 }
			 }
			 if (inputplayerP2.Num9_active && !App->player->closeP1) {

				 currentstateP2 = standingfarHPP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 80, 18 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
				 LOG("IDLE to HEAVY PUNCH");

			 }
			 if (inputplayerP2.Num4_active) {
				 currentstateP2 = standingfarLKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 57, 25 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num5_active) {
				 currentstateP2 = standingfarMKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 75, 15 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num6_active) {
				 currentstateP2 = standingfarHKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 75, 15 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
				 LOG("IDLE to HEAVY KICK");
			 }

			 if (inputplayerP2.Num8_active && App->player->closeP1) { //falta CONDICIO COLIDER APROP
				 currentstateP2 = HeadbuttP2;
				 LOG("FORWARD TO HEADBUT");

			 }
			 if (inputplayerP2.Num9_active && App->player->closeP1) {
				 currentstateP2 = throwP2;
			 }

		 }
		 //CROUCH STATE
		 if (currentstateP2 == crouchstateP2) {
			 comboInputP2('s');
			 if (!inputplayerP2.Down_active) {
				 crouchP2.Reset();
				 currentstateP2 = idlestateP2;

				 LOG("CROUCH to IDLE");
			 }
			 if (inputplayerP2.Num7_active) {
				 currentstateP2 = crouchLPP2;
				 LOG("CROUCH to LP");

			 }
			/* if (inputplayerP2.Left_active) {
				 crouchBlockingP2 = true;
			 }
			 if (!inputplayerP2.Left_active) {
				 crouchBlockingP2 = false;
			 }*/
			 if (inputplayerP2.Num7_active) {
				 currentstateP2 = crouchLPP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 93, 20 }, COLLIDER_PLAYER2_ATTACK, CL, App->player);
				 LOG("IDLE to LP");
			 }
			 if (inputplayerP2.Num8_active) {
				 currentstateP2 = crouchMPP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 93, 20 }, COLLIDER_PLAYER2_ATTACK, CM, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num9_active) {
				 currentstateP2 = crouchHPP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 20 }, COLLIDER_PLAYER2_ATTACK, CH, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num4_active) {
				 currentstateP2 = crouchLKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 79, 22 }, COLLIDER_PLAYER2_ATTACK, CL, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num5_active) {
				 currentstateP2 = crouchMKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 22 }, COLLIDER_PLAYER2_ATTACK, CM, App->player);
				 LOG("IDLE to HEAVY PUNCH");
			 }
			 if (inputplayerP2.Num6_active) {
				 currentstateP2 = crouchHKP2;
				 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 22 }, COLLIDER_PLAYER2_ATTACK, CH, App->player);
				 LOG("IDLE to HEAVY KICK");
			 }
		 }
		 //JUMP STATE
		 if (jumpingP2 == true) {
			 comboInputP2('w');
			 if (positionP2.y >= groundLevelP2 + 1) {
				 deleteCollider2(attackP2_collider);
				 positionP2.y = groundLevelP2;
				 currentstateP2 = idlestateP2;
				 NjumpP2.Reset();
				 FjumpP2.Reset();
				 BjumpP2.Reset();
				 JLP_P2.Reset();
				 JMP_P2.Reset();
				 JHPN_P2.Reset();
				 JHPFB_P2.Reset();
				 JLK_P2.Reset();
				 JMK_P2.Reset();
				 JHK_P2.Reset();
				 jumpingP2 = false;
				 airkickP2 = true;
				 neutralJumpP2 = false;
				 forwardJumpP2 = false;
				 backwardJumpP2 = false;
				 App->player->alreadyHitP1 = false;
				 jumpTimerP2 = 0;

			 }
		 }
		 if (jumpingP2 == true) {
			 if (airkickP2 == true) {

				 if (inputplayerP2.Num7_active) {
					 currentstateP2 = jumpLPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 55, 23 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
					 airkickP2 = false;
				 }
				 if (inputplayerP2.Num8_active) {
					 currentstateP2 = jumpMPP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 65, 33 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
					 airkickP2 = false;
				 }
				 if (inputplayerP2.Num4_active) {
					 currentstateP2 = jumpLKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 70, 23 }, COLLIDER_PLAYER2_ATTACK, SL, App->player);
					 airkickP2 = false;
				 }
				 if (inputplayerP2.Num5_active) {
					 currentstateP2 = jumpMKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 57, 25 }, COLLIDER_PLAYER2_ATTACK, SM, App->player);
					 airkickP2 = false;
				 }
				 if (inputplayerP2.Num6_active) {
					 currentstateP2 = jumpHKP2;
					 attackP2_collider = App->collision->AddCollider({ 0,-100, 70, 33 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
					 airkickP2 = false;
				 }
				 if (currentstateP2 == FjumpstateP2 || currentstateP2 == BjumpstateP2) {
					 if (inputplayerP2.Num9_active) {
						 currentstateP2 = DjumpHPP2;
						 attackP2_collider = App->collision->AddCollider({ 0,-100, 70, 50 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
						 airkickP2 = false;
					 }
				 }
				 else {
					 if (inputplayerP2.Num9_active) {
						 currentstateP2 = NjumpHPP2;
						 attackP2_collider = App->collision->AddCollider({ 0,-100, 100, 25 }, COLLIDER_PLAYER2_ATTACK, SH, App->player);
						 airkickP2 = false;
					 }
				 }

			 }

		 }

		 //ATTACKS
		 //STANDING FAR LP
		 if (currentstateP2 == standingfarLPP2) {
			 if (currentP2_animation->Finished() && !inputplayerP2.Num7_active) {
				 currentstateP2 = idlestateP2;
				 deleteCollider2(attackP2_collider);
				 alreadyHitP2 = false;
				 App->player->alreadyHitP1 = false;
				 SFLP_P2.Reset();
				 LOG("LP to IDLE");
				 ++thundertickP2;
			 }

			 if (!currentP2_animation->Finished() && inputplayerP2.Num7_active && !inputplayerP2.Right_active && !inputplayerP2.Left_active) {
				 if (thundertickP2 > 3) {
					 deleteCollider2(attackP2_collider);
					 SFLP_P2.Reset();
					 App->player->alreadyHitP1 = false;

					 currentstateP2 = thunder1P2;
					 alreadyHitP2 = false;


					 LOG("LP to Thunder1");
				 }
			 }

		 }
		 //THUNDER
		 if (currentstateP2 == thunder1P2) {

			 if (currentP2_animation->Finished() && !inputplayerP2.Num7_active && !inputplayerP2.Num8_active && !inputplayerP2.Num9_active) {  ////////////////// AQUI ESTA EL PROBLEMA
				 alreadyHitP2 = false;
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 
				 SFLP_P2.Reset();
				 Ethunder_P2.Reset();
				 LOG("Thunder 1 to IDLE");
			 }

			 if (!currentP2_animation->Finished() && inputplayerP2.Num7_active && !inputplayerP2.Right_active && !inputplayerP2.Left_active) {
				
				 currentstateP2 = thunder2P2;
				 alreadyHitP2 = false;
				 SFLP_P2.Reset();

				 LOG("LP to Thunder1");

			 }

			 if (!currentP2_animation->Finished() && inputplayerP2.Num8_active && !inputplayerP2.Right_active && !inputplayerP2.Left_active) {
				 
				 currentstateP2 = thunder2P2;
				 alreadyHitP2 = false;
				 SFMP_P2.Reset();
				 SFLP_P2.Reset();
				 SFHP_P2.Reset();
				 LOG("LP to Thunder1");

			 }

			 if (!currentP2_animation->Finished() && inputplayerP2.Num9_active && !inputplayerP2.Right_active && !inputplayerP2.Left_active) {
				 
				 currentstateP2 = thunder2P2;
				 alreadyHitP2 = false;
				 SFHP_P2.Reset();
				 SFLP_P2.Reset();
				 SFMP_P2.Reset();
				 LOG("LP to Thunder1");
			 }
		 }

		 if (currentstateP2 == thunder2P2) {


			 if (currentP2_animation->Finished()) {
				 App->player->alreadyHitP1 = false;
				 currentstateP2 = idlestateP2;
				 deleteCollider2(attackP2_collider);
				 Ethunder_P2.Reset();
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
		 if (currentstateP2 == throwP2) {

			 if (currentP2_animation->Finished())
			 {
				 Throw_P2.Reset();

				 currentstateP2 = idlestateP2;

			 }

		 }

		 //CROUCH LP
		 if (currentstateP2 == crouchLPP2) {
			 if (currentP2_animation->Finished() && !inputplayerP2.Num7_active && inputplayerP2.Down_active) {
				 currentstateP2 = crouchstateP2;

				 alreadyHitP2 = false;
				 CLP_P2.Reset();
				 LOG("LP to CROUCH");
			 }
			 if (currentP2_animation->Finished() && !inputplayerP2.Num7_active && !inputplayerP2.Down_active) {
				 currentstateP2 = idlestateP2;
				 alreadyHitP2 = false;
				 CLP_P2.Reset();
				 LOG("LP CROUCHED to IDLE");
			 }
		 }
		 if (currentstateP2 == SdamagedP2) {
			 if (currentP2_animation->Finished()) {
				 currentstateP2 = idlestateP2;
				 SdamageLP2.Reset();
			 }
		 }

		 //HEADBUTT
		 if (currentstateP2 == HeadbuttP2) {


			 if (currentP2_animation->Finished() && inputplayerP2.Num8_active && !inputplayerP2.Left_active && !inputplayerP2.Right_active) {

				 Headbut_P2.Reset();

				 currentstateP2 = standingfarMPP2;

			 }

			 if (currentP2_animation->Finished() && !inputplayerP2.Num8_active && !inputplayerP2.Left_active && !inputplayerP2.Right_active) {

				 Headbut_P2.Reset();

				 currentstateP2 = idlestateP2;

			 }

			 if (currentP2_animation->Finished() && !inputplayerP2.Num8_active && !inputplayerP2.Left_active && inputplayerP2.Right_active) {

				 Headbut_P2.Reset();

				 currentstateP2 = forwardstateP2;

			 }
			 if (currentP2_animation->Finished() && !inputplayerP2.Num8_active && inputplayerP2.Left_active && !inputplayerP2.Right_active) {

				 Headbut_P2.Reset();

				 currentstateP2 = backwardstateP2;

			 }
		 }

		 if (currentstateP2 == rollingattackP2LIGHT) {



			 if (positionP2.x + 40 == App->player2->positionP2.x) {

				 currentstateP2 = rollingreboundP2;
				 RollingP2.Reset();

			 }
		 }

		 if (currentstateP2 == rollingattackP2MEDIUM) {

			 if (positionP2.x + 40 >= App->player2->positionP2.x) {

				 currentstateP2 = rollingreboundP2;
				 RollingP2.Reset();

			 }
		 }

		 if (currentstateP2 == rollingattackP2HEAVY) {


			 if (positionP2.x + 40 == App->player2->positionP2.x) {

				 currentstateP2 = rollingreboundP2;
				 RollingP2.Reset();
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

		 if (currentstateP2 == rollingreboundP2) {

			 if (currentP2_animation->Finished() && !inputplayerP2.Right_active && inputplayerP2.Num8_active && !inputplayerP2.Num9_active) {

				 // RollingP1.Reset();
				 deleteCollider2(attackP2_collider);
				 RollingRebP2.Reset();
				 currentstateP2 = standingfarMPP2;
			 }
		 }

		 if (currentstateP2 == rollingreboundP2) {

			 if (currentP2_animation->Finished() && !inputplayerP2.Right_active && !inputplayerP2.Num8_active && inputplayerP2.Num9_active) {

				 // RollingP1.Reset();
				 deleteCollider2(attackP2_collider);
				 RollingRebP2.Reset();
				 currentstateP2 = standingfarHPP2;
			 }
		 }

		 if (currentstateP2 == rollingreboundP2) {

			 if (currentP2_animation->Finished() && inputplayerP2.Right_active && !inputplayerP2.Num8_active && !inputplayerP2.Num9_active) {
				 deleteCollider2(attackP2_collider);
				 RollingRebP2.Reset();
				 currentstateP2 = forwardstateP2;
			 }
		 }

		 if (currentstateP2 == rollingreboundP1) {

			 if (currentP2_animation->Finished() && !inputplayerP2.Right_active && !inputplayerP2.Num8_active && !inputplayerP2.Num9_active) {
				 deleteCollider2(attackP2_collider);
				 // RollingP1.Reset();
				 RollingRebP2.Reset();
				 currentstateP2 = idlestateP2;
			 }
		 }

		 return UPDATE_CONTINUE;
	 }
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	SblockingP2 = false;
	CblockingP2 = false;
	switch (currentstateP2)
	{

	case idlestateP2:
		playerP2_collider->rect.h = 93;
		positionP2.y = groundLevelP2;
		currentP2_animation = &idleP2;
		App->player->alreadyHitP1 = false;
		//LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstateP2:
		playerP2_collider->rect.h = 93;
		if (!App->player->flipP1) {
			currentP2_animation = &forwardP2;
		}
		else {
			currentP2_animation = &backwardP2;
		}
		positionP2.x -= speedP2;
		if (!App->player->flipP1) { SblockingP2 = false; }
		else { SblockingP2 = true; }
		LOG("BACK ANIMATION ACTIVE");
		break;

	case forwardstateP2:

		if (!App->player->flipP1) {
			currentP2_animation = &backwardP2;
		}
		else {
			currentP2_animation = &forwardP2;
		}
		positionP2.x += speedP2;
		if (!App->player->flipP1) { SblockingP2 = true; }
		else { SblockingP2 = false; }
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case crouchstateP2:
		currentP2_animation = &crouchP2;
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x + 15 - camxP2, positionP2.y - 65 - camyP2);

		if (!App->player->flipP1) {
			if (inputplayerP2.Left_active) { CblockingP2 = false; }
			else { CblockingP2 = true; }
		}
		else {
			if (inputplayerP2.Right_active) { CblockingP2 = true; }
			else { CblockingP2 = false; }
		}
		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case NjumpstateP2:
		currentP2_animation = &NjumpP2;
		//MRUA
		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;

	case FjumpstateP2:
		if (App->player->flipP1) { currentP2_animation = &FjumpP2; }
		else { currentP2_animation = &BjumpP2; }
		LOG(" FORWARD JUMP ANIMATION ACTIVE");
		break;

	case BjumpstateP2:
		if (App->player->flipP1) { currentP2_animation = &BjumpP2; }
		else { currentP2_animation = &FjumpP2; }
		LOG(" BACKWARD JUMP ANIMATION ACTIVE");
		break;

	case standingfarLPP2:
		currentP2_animation = &SFLP_P2;         //&SFLP_P1
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 90 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 90 - camyP2);
		}
		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarMPP2:
		currentP2_animation = &SFMP_P2;         //&SFMP_P1
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 40 - camxP2, positionP2.y - 107 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 107 - camyP2);
		}

		LOG("LP ANIMATION ACTIVE");
		break;
	case standingfarHPP2:
		currentP2_animation = &SFHP_P2;         //&SFHP_P1
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 55 - camxP2, positionP2.y - 90 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 90 - camyP2);
		}

		LOG("LP ANIMATION ACTIVE");
		break;
	case standingfarLKP2:
		currentP2_animation = &SFLK_P2;         //&SFLK_P1
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 80 - camxP2, positionP2.y - 75 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 75 - camyP2);
		}

		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarMKP2:
		currentP2_animation = &SFMK_P2;         //&SFMK_P1

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 85 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 85 - camyP2);
		}
		LOG("LP ANIMATION ACTIVE");
		break;

	case standingfarHKP2:
		currentP2_animation = &SFHK_P2;         //&SFHK_P1
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 85 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 85 - camyP2);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseLPP2:
		currentP2_animation = &SCLP_P2;
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 85 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 85 - camyP2);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseMPP2:
		currentP2_animation = &SCMP_P2;

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 50 - camxP2, positionP2.y - 85 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 85 - camyP2);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseHPP2:
		positionP2.y = groundLevelP2-25;
		currentP2_animation = &SCHP_P2;
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 85 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 85 - camyP2);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseLKP2:
		currentP2_animation = &SCLK_P2;

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 85 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 85 - camyP2);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseMKP1:
		currentP2_animation = &SCMK_P2;

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 85 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 85 - camyP2);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case standingcloseHKP2:
		currentP2_animation = &SCHK_P2;
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 25 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 25 - camyP2);
		}
		LOG("HK ANIMATION ACTIVE");
		break;

	case thunder1P2:
		currentP2_animation = &SFLP_P2;
		LOG("THUNDER 1 ANIMATION ACTIVE");
		break;

	case thunder2P2:
		currentP2_animation = &Ethunder_P2;
		LOG("THUNDER 2 ANIMATION ACTIVE");
		break;

	case throwP2:
		currentP2_animation = &Throw_P2;

		LOG("THROW ANIMATION ACTIVE");
		break;

		//crouch attacks
	case crouchLPP2:
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x + 15 - camxP2, positionP2.y - 65 - camyP2);

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 55 - camxP2, positionP2.y - 55 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 55 - camyP2);
		}
		currentP2_animation = &CLP_P2;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchMPP2:
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x + 15 - camxP2, positionP2.y - 65 - camyP2);

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 55 - camxP2, positionP2.y - 55 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 55 - camyP2);
		}
		currentP2_animation = &CMP_P2;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchHPP2:
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x + 15 - camxP2, positionP2.y - 65 - camyP2);

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 65 - camxP2, positionP2.y - 65 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 65 - camyP2);
		}
		currentP2_animation = &CHP_P2;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchLKP2:
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x + 15 - camxP2, positionP2.y - 65 - camyP2);

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 48 - camxP2, positionP2.y - 25);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 25);
		}
		currentP2_animation = &CLK_P2;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchMKP2:
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x + 15 - camxP2, positionP2.y - 65 - camyP2);

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 48 - camxP2, positionP2.y - 25 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 25 - camyP2);
		}
		currentP2_animation = &CMK_P2;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	case crouchHKP2:
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x + 15 - camxP2, positionP2.y - 65 - camyP2);

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 25 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 25 - camyP2);
		}
		currentP2_animation = &CHK_P2;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;

		//Jumping attacks
	case jumpLPP2:
		currentP2_animation = &JLP_P2;

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 45 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 45 - camyP2);
		}
		break;
	case jumpMPP2:
		currentP2_animation = &JMP_P2;

		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 50 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 50 - camyP2);
		}
		break;
	case NjumpHPP2:
		currentP2_animation = &JHPN_P2;
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 45 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 45 - camyP2);
		}
		break;
	case DjumpHPP2:
		currentP2_animation = &JHPFB_P2;
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 45 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 45 - camyP2);
		}
		break;
	case jumpLKP2:
		currentP2_animation = &JLK_P2;
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 25 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 25 - camyP2);
		}
		break;
	case jumpMKP1:
		currentP2_animation = &JMK_P2;
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 25 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 25 - camyP2);
		}
		break;
	case jumpHKP2:
		currentP2_animation = &JHK_P2;
		if (App->player->flipP1) {
			attackP2_collider->SetPos(positionP2.x + 60 - camxP2, positionP2.y - 25 - camyP2);
		}
		else {
			attackP2_collider->SetPos(positionP2.x - extradisP2 - camxP2, positionP2.y - 25 - camyP2);
		}
		break;

		//damaged
	case SdamagedLP2:
		currentP2_animation = &SdamageLP2;
		if (App->player->flipP1){
			positionP2.x -= 1;
		}
		else {
			positionP2.x += 1;
		}
		break;
	case SdamagedMP2:
		currentP2_animation = &SdamageMP2;
		if (App->player->flipP1) {positionP2.x -= 1;}
		else {positionP2.x += 1;}
		break;
	case SdamagedHP2:
		currentP2_animation = &SdamageHP2;
		if (App->player->flipP1) {	positionP2.x -= 1;}
		else {positionP2.x += 1;}
		break;
	case SblockstunP2:
		currentP2_animation = &SblockP2;
		if (App->player->flipP1) { positionP2.x -= 1; }
		else { positionP2.x += 1; }
		
		break;
	case CblockstunP2:
		currentP2_animation = &CblockP2;
		if (App->player->flipP1) { positionP2.x -= 1; }
		else { positionP2.x += 1; }
		break;
		
	
	case HeadbuttP2:
		currentP2_animation = &Headbut_P2; // falta ANIMACIO HEADBUTT
		LOG("HEADBUTT ANIMATION ACTIVE");
		break;


	case rollingattackP2LIGHT:

		positionP2.y = 180;
		positionP2.x += 7;
		attackP2_collider->SetPos(positionP2.x - camxP2, positionP2.y - 60 - camyP2);
		currentP2_animation = &RollingP2;

		LOG("ROLLING ANIMATION ACTIVE");
		break;


	case rollingattackP2MEDIUM:
		attackP2_collider->SetPos(positionP2.x - camxP2, positionP2.y - 60 - camyP2);
		positionP2.y = 180;
		positionP2.x += 7;
		currentP2_animation = &RollingP2;
		LOG("ROLLING ANIMATION ACTIVE");
		break;

	case rollingattackP2HEAVY:
		attackP2_collider->SetPos(positionP2.x - camxP2, positionP2.y - 60 - camyP2);
		positionP2.y = 180;
		positionP2.x += 7;
		currentP2_animation = &RollingP2;
		LOG("ROLLING ANIMATION ACTIVE");
		break;

	case rollingreboundP2:

		int positionstart = positionP2.x;
		currentP2_animation = &RollingRebP2;

		//positionP1.x -= speed;
		//positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA

		positionP2.x -= speedP2 * 4;
		//positionP1.y = groundLevel + (yvel*jumpTimer*3) + (-9*(gravity) * (9*jumpTimer*jumpTimer)); //MRUA

		positionP2.y -= 7;

		/*positionP1.y  -= 5;
		positionP1.x -= 12;*/

		LOG("ROLLING REBOUND ANIMATION ACTIVE");
		break;
	}

	if (currentstateP2 != crouchstateP2 && currentstateP2 != crouchLPP2 && currentstateP2 != crouchMPP1 && currentstateP2 != crouchHPP2 && currentstateP2 != crouchLKP2 && currentstateP2 != crouchMKP2 && currentstateP2 != crouchHKP2) {
		if (!App->player->flipP1) {
			playerP2_collider->SetPos(positionP2.x +30 - App->render->camera.x / SCREEN_ADD, positionP2.y - 93 - App->render->camera.y / SCREEN_ADD);
		}
		else {
			playerP2_collider->SetPos(positionP2.x + 15 - App->render->camera.x / SCREEN_ADD, positionP2.y - 93 - App->render->camera.y / SCREEN_ADD);
		}
	}
	SDL_Rect r = currentP2_animation->GetCurrentFrame();
	//SHADOW
	shadowP2 = { 796,27,100,20 };

	
	if (jumpingP2) {
		jumpTimerP2 = timeP2 - jumpstartP2;
		playerP2_collider->SetPos(positionP2.x + 15 - App->render->camera.x / SCREEN_ADD, positionP2.y - 93 - App->render->camera.y / SCREEN_ADD);
		positionP2.y = groundLevelP2- (yvelP2*jumpTimerP2) + (0.5*(gravityP2) * (jumpTimerP2*jumpTimerP2));
		App->render->camera.y -= (0.2 * jumpTimerP2) + (0.5*(-0.9) * (jumpTimerP2*jumpTimerP2)) / 60;
		if (forwardJumpP2 == true) {
			positionP2.x += speedP2;
		}
		if (backwardJumpP2 == true) {
			positionP2.x -= speedP2;
		}
	}

	
		if (positionP2.x <= (App->render->camera.x / 5 - 10))
		{
			positionP2.x = (App->render->camera.x / 5 - 10);
		}
		if (positionP2.x >= (180 + App->render->camera.x / 5) + 115)
		{
			positionP2.x = (180 + App->render->camera.x / 5) + 115;
		}
	


	if (!App->player->flipP1) {
		App->render->Blit(graphicsP2, positionP2.x + 10, App->player->groundLevelP1 - 15, &shadowP2, 1.0f, true,SDL_FLIP_NONE, 0.0, INT_MAX, INT_MAX, true);
		App->render->Blit(graphicsP2, positionP2.x, positionP2.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE, 0.0, INT_MAX, INT_MAX, true);
	}
	else
	{
		App->render->Blit(graphicsP2, positionP2.x + 10, App->player->groundLevelP1 - 15, &shadowP2, 1.0f, true, SDL_FLIP_NONE);
		App->render->Blit(graphicsP2, positionP2.x, positionP2.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE);
	}


	return UPDATE_CONTINUE;
}


void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER2 && c2->type == COLLIDER_PLAYER_ATTACK) {
		
		
			if (!alreadyHitP2) {
				if (currentstateP2 != crouchstateP2 && currentstateP2 != crouchLPP2 && currentstateP2 != crouchMPP2 && currentstateP2 != crouchHPP2 && currentstateP2 != crouchLKP2 && currentstateP2 != crouchMKP2 && currentstateP2 != crouchHKP2) {
					//standing if not crouching
					if (c2->attack == SL) { //L
						if (!SblockingP2) {
							currentstateP2 = SdamagedLP2;
							alreadyHitP2 = true;
							deleteCollider2(attackP2_collider);
							App->ui->health.x -= 5;
						}
						else {
							SblockP2.speed = 0.45f;
							currentstateP2 = SblockstunP2;
							alreadyHitP2 = true;
							deleteCollider2(attackP2_collider);
						}
					}
					else if (c2->attack == SM) {//M
						if (!SblockingP2) {
							currentstateP2 = SdamagedMP2;
							alreadyHitP2 = true;
							deleteCollider2(attackP2_collider);
							App->ui->health.x -= 10;
						}
						else {
							SblockP2.speed = 0.35f;
							currentstateP2 = SblockstunP2;
							alreadyHitP2 = true;
							deleteCollider2(attackP2_collider);
						}
					}
					else if (c2->attack == SH) {//H
						if (!SblockingP2) {
							/*if (currentstateP1 = SdamagedHP1) {
								SblockP1.Reset();
							}*/
							currentstateP2 = SdamagedHP2;
							alreadyHitP2 = true;
							deleteCollider2(attackP2_collider);
							App->ui->health.x -= 15;
						}
						else {
							SblockP2.speed = 0.25f;
							currentstateP2 = SblockstunP2;
							alreadyHitP2 = true;
							deleteCollider2(attackP2_collider);
						}
					}
				}
				//Crouching
				if (c2->attack == CL) {//L
					if (!CblockingP2) {
						currentstateP2 = SdamagedLP2;
						alreadyHitP2 = true;
						deleteCollider2(attackP2_collider);
						App->ui->health.x -= 5;
					}
					else {
						CblockP2.speed = 0.45f;
						currentstateP2 = CblockstunP2;
						alreadyHitP2 = true;
						deleteCollider2(attackP2_collider);
					}
				}
				else if (c2->attack == CM) {//M
					if (!CblockingP2) {
						currentstateP2 = SdamagedMP2;
						alreadyHitP2 = true;
						App->ui->health.x -= 10;
						deleteCollider2(attackP2_collider);
					}
					else {
						CblockP2.speed = 0.35f;
						currentstateP2 = CblockstunP2;
						alreadyHitP2 = true;
						deleteCollider2(attackP2_collider);
					}
				}
				else if (c2->attack == CH) {//H
					if (!CblockingP2) {
						currentstateP2 = SdamagedHP2;
						alreadyHitP2 = true;
						deleteCollider2(attackP2_collider);
						App->ui->health.x -= 15;
					}
					else {
						CblockP2.speed = 0.25f;
						currentstateP2 = CblockstunP2;
						alreadyHitP2 = true;
						deleteCollider2(attackP2_collider);
					}
				}
			}
		
		
	}

}

bool ModulePlayer2::comboActiveP2() {

	//Input button combination for special attack	
	int i = 0;
	int j = startcomboP2;
	int done = 0; //If done = 3. Special attack = true 

	while (i < 100) {
		switch (done) {
		case 0:
			if (comboP2[j] == 'c')//punch
				done++;
			break;
		case 1:
			if (comboP2[j] == 'd')//forward
				done++;
			break;
		case 2:
			if (comboP2[j] == 'n' && 'm') // enredere
				done++;
			break;
		case 3:
			if (comboP2[j] == 's') //down
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


void ModulePlayer2::comboInputP2(char comboInput) {
	comboP2[*finishCP2] = comboInput; //We add the newInput to the last inputs array

	if (*finishCP2 < 99) //We change last pointer's position 
		(*finishCP2)++;
	else
		*finishCP2 = 0;

	//We change first pointer's position 
	if (*startCP2 == *startCP2 && *startCP2 < 99)
		(*startCP2)++;
	else if (*startCP2 == *finishCP2 && *startCP2 >= 99)
		* startCP2 = 0;
}
