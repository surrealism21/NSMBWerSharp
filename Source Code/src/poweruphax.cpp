#include <common.hpp>
#include <game.hpp>
#include <g3dhax.hpp>
#include <profileid.hpp>
#include <poweruphax.hpp>
#include <kamek.hpp>

// FixVanillaMap

kmWrite32(0x80926D58,0x281F0007);
kmWrite32(0x80927A88,0x28170007);
kmWrite32(0x80926C4C,0x281c0008);
kmWrite32(0x809272CC,0x907a08e0);
kmWrite32(0x800bb3a8,0x88a50969);
kmWrite32(0x800bb358,0x88a50969);
kmWrite32(0x800ce434,0x98a30969);
kmWrite32(0x800bb3f8,0x88030969);

// expand acpy?
kmWrite32(0x801443C8,0x38602D0C);

// hammer, don't touch mario or yoshi!!!
kmWriteNop(0x8001DFDC);
kmWriteNop(0x8001E02C);

// extend hammer struct
kmWrite32(0x807FCBA8,0x3860045C);

// various other garbage 
kmWrite32(0x8013BB7C,0x4181003C);
kmWrite32(0x802ee628,0x00000006);
kmWrite32(0x802EE664,0x000000AA);
kmWrite32(0x802EE6AC,0x000000AA);
kmWrite32(0x80022884,0x281F00AA);
kmWrite32(0x80022B88,0x280500AA);
kmWrite32(0x800221ac,0x28000003);
kmWrite32(0x80A2BE98,0x28000003);
kmWrite32(0x80A28598,0x28000003);
kmWriteNop(0x800611C4);
kmWriteNop(0x8006122C);
kmWrite32(0x802F5AEC,0x00000001);

// interactions
// rest of this file is mostly interactions

extern "C" void ReturnTrue();
extern "C" void ReturnFalse();

kmWrite32(0x80ACE8E4,0x0008820C);
kmWrite32(0x80ACF9D0,0x0008820e);
kmWrite32(0x80ACF9F4,0x0008820e);
kmWrite32(0x80AD4AA0,0x0008a80e);
kmWrite32(0x80AD4AA4,0x20020000);
kmWrite32(0x80ACE17C,0x00080a04);
kmWrite32(0x80AD4D88,0x00080006);
kmWrite32(0x80ACDD50,0x00080006);
kmWrite32(0x80AD4F48,0x00088a1e);
kmWrite32(0x80AD5214,0x00088206);
kmWrite32(0x80ACFBC4,0x00088206);
kmWrite32(0x80AD2748,0x0008881e);
kmWrite32(0x80AD3C60,0x00088a0e);
kmWrite32(0x80AD3C3C,0x00088a0e);
kmWrite32(0x80ACEC60,0x00088a0e);
kmWrite32(0x80ACECF8,0x0008828e);
kmWrite32(0x80ACED1C,0x0008828e);
kmWrite32(0x80AD4158,0x0008880e);
kmWrite32(0x80AD5538,0x003AFFFE);
kmWrite32(0x80ACD9A0,0x0008A2BE);
kmWrite32(0x80ACDC8C,0x0000004F);
kmWrite32(0x80ACDC90,0xFFBAFFBC);
kmWrite32(0x80AD2618,0x0000004F);
kmWrite32(0x80AD261C,0x00088806);
kmWrite32(0x80AD22B8,0x03000000);
kmWrite32(0x80ad22Dc,0x03000000);
kmWrite32(0x80AD3ADC,0x00000047);
kmWrite32(0x80AD3B00,0x00000047);
kmWrite32(0x8095C668,0x00000010);
kmWrite32(0x80AD0EB4,0x0000004F);
kmWrite32(0x80AD0ED8,0x0000004F);
kmWrite32(0x80ACFD08,0x0000004F);
kmWrite32(0x80ACFD2C,0x0000004F);
kmWritePointer(0x80B76CD8, ReturnTrue);
kmWritePointer(0x80B81F8C, ReturnTrue);
kmWritePointer(0x80B777F0, ReturnTrue);
kmWritePointer(0x80B82E38, ReturnTrue);
kmWritePointer(0x80B7ADB8, ReturnTrue);
kmWritePointer(0x80B8768C, ReturnTrue);
kmWritePointer(0x80B783C8, ReturnTrue);
kmWritePointer(0x80B84120, ReturnTrue);
kmWritePointer(0x80B75FC8, ReturnTrue);
kmWritePointer(0x80B7BC70, ReturnTrue);
kmWritePointer(0x80B790A8, ReturnTrue);
kmWritePointer(0x80B853F0, ReturnTrue);
kmWritePointer(0x80B79E10, ReturnTrue);
kmWritePointer(0x80B86458, ReturnTrue);
kmWritePointer(0x80B7CC24, ReturnTrue);
kmWritePointer(0x80B7E848, ReturnTrue);
kmWritePointer(0x80B804FC, ReturnTrue);
kmWritePointer(0x80B80C04, ReturnTrue);
kmWritePointer(0x80B814B0, ReturnTrue);

// Red ring
kmWrite32(0x80A942EC,0x28000005);

// Fix toad house items
kmWrite32(0x8086b278,0x88bf0969);

// clear new itemsf
kmWrite32(0x80789040,0x2c110008);

// STOCK ITEM BULLSHIT

// expand struct
kmWrite32(0x807AF378,0x38600980);
// stockitem shadow struct special edition
kmWrite32(0x807B2038,0x38600290);

// disable useless powerup id redirection
kmWriteNop(0x807af790);
kmWriteNop(0x807af794);

kmWrite32(0x8001E668,0x38A00008);

// another SI patch (change amount to 8 on some while loops)
kmWrite32(0x809272d0,0x2c190008);

//BiggerWmPlayer
kmWrite32(0x80902798,0x38600310);
kmWrite32(0x808C5108,0x38600388);

// carpal tunnel here i come

// fix anims
kmWrite32(0x807AFB08,0x2C040020);
kmWrite32(0x807AFB20,0x38000020);
kmWrite32(0x807B0994,0x38000020);

// UpCounts 
kmWrite32(0x807B02D8,0x80850900);
kmWrite32(0x807B02E0,0x90050900);
kmWrite32(0x807B02F0,0x80840900);
kmWrite32(0x807B0304,0x80030900);
// ItemPtr
kmWrite32(0x807B0310,0x806308E0);

// UpCounts 2
kmWrite32(0x807B0908,0x80050900);
kmWrite32(0x807B0934,0x2C000008);
kmWrite32(0x807B0944,0x80050900);
kmWrite32(0x807B0954,0x2C000008);
kmWrite32(0x807B0A74,0x809D0900);
kmWrite32(0x807B0A8C,0x2C1B0008);

// UpCounts 3
kmWrite32(0x807B0B68,0x807C08E0);
kmWrite32(0x807B0B74,0x801C0900);
kmWrite32(0x807B0B80,0x807C08E0);
kmWrite32(0x807B0B8C,0x807C08E0);
kmWrite32(0x807B0B9C,0x2C1D0008);
kmWrite32(0x807B0C28,0x80030900);
kmWrite32(0x807B0C64,0x801E0900);
kmWrite32(0x807B0C78,0x801E0904);
kmWrite32(0x807B0C90,0x801E0908);
kmWrite32(0x807B0CA8,0x801E090C);
kmWrite32(0x807B0CC0,0x801E0910);
kmWrite32(0x807B0CD8,0x801E0914);

// UpCounts FINAL
kmWrite32(0x807B1478,0x807E08E0);
kmWrite32(0x807B148C,0x2C1D0008);

// get counts for powerups fix
// changed by surrealism a bit: this patch is weird but it still loads
// 8 items now rather than 7, which was causing crashes
kmWrite32(0x807AF7A8, 0x2C1C0008);
kmWrite32(0x807af7ac, 0x901E0900);

void ThwompHammer(dEn_c *thwomp, ActivePhysics *apThis, ActivePhysics *apOther) {
	if (thwomp->profileId == ProfileId::EN_DOSUN) {
		thwomp->dEn_c::collisionCat13_Hammer(apThis, apOther);
	}
	return;
}
kmWritePointer(0x80AE8360, &ThwompHammer);

void BooHammer(dEn_c *boo, ActivePhysics *apThis, ActivePhysics *apOther) {
	if (boo->profileId == ProfileId::EN_TERESA) {
		boo->dEn_c::collisionCat13_Hammer(apThis, apOther);
	}
	return;
}

void UrchinHammer(dEn_c *urchin, ActivePhysics *apThis, ActivePhysics *apOther) {
	return;
}
kmWritePointer(0x80B0CCC0, &UrchinHammer);

void SetCullModeForMaterial(m3d::mdl_c *model, int materialID, u32 cullMode);

dHammerSuitRenderer_c *dHammerSuitRenderer_c::build() {
	return new dHammerSuitRenderer_c;
}

dHammerSuitRenderer_c::dHammerSuitRenderer_c() { }
dHammerSuitRenderer_c::~dHammerSuitRenderer_c() { }

void dHammerSuitRenderer_c::setup(dPlayerModelHandler_c *handler) {
	setup(handler, 0);
}

void dHammerSuitRenderer_c::setup(dPlayerModelHandler_c *handler, int sceneID) {
	victim = (dPlayerModel_c*)handler->mdlClass;

	allocator.link(-1, GameHeaps[0], 0, 0x20);

	nw4r::g3d::ResFile rf(getResource("hammerM", "g3d/suit.brres"));

	if (victim->player_id_2 <= 1) {
		helmet.setup(rf.GetResMdl((victim->player_id_2 == 0) ? "marioHelmet" : "luigiHelmet"), &allocator, 0, 1, 0);
		SetupTextures_Player(&helmet, sceneID);
	}

	const char *shellNames[] = {
		"shell", "shell", "shell", "shell", "shell"
	};
	shell.setup(rf.GetResMdl(shellNames[victim->player_id_2]), &allocator, 0, 1, 0);
	SetupTextures_Player(&shell, sceneID);
	allocator.unlink();

	victimModel = &victim->models[0].body;
	nw4r::g3d::ResMdl *playerResMdl =
		(nw4r::g3d::ResMdl*)(((u32)victimModel->scnObj) + 0xE8);

	if (victim->player_id_2 <= 1) {
		nw4r::g3d::ResNode face_1 = playerResMdl->GetResNode("face_1");
		headNodeID = face_1.GetID();
	}

	nw4r::g3d::ResNode skl_root = playerResMdl->GetResNode("spin");
	rootNodeID = skl_root.GetID();
	
	this->sceneNum = sceneID;
}

void dHammerSuitRenderer_c::draw() {
	if (victim->powerup_id != 7) {
		return;
	}

	if (victim->player_id_2 <= 1) {
		// Materials: 2=hair 3=hat; Modes: BACK=visible ALL=invisible
		SetCullModeForMaterial(&victim->getCurrentModel()->head, 3, GX_CULL_ALL);
		SetCullModeForMaterial(&victim->getCurrentModel()->head, 2, GX_CULL_ALL);

		Mtx headMtx;
		victimModel->getMatrixForNode(headNodeID, &headMtx);

		helmet.setDrawMatrix(&headMtx);
		helmet.setScale(1.0f, 1.0f, 1.0f);
		helmet.calcWorld(false);
		SetupTextures_Player(&helmet, sceneNum);

		helmet.scheduleForDrawing();
	}

	Mtx rootMtx;
	victimModel->getMatrixForNode(rootNodeID, &rootMtx);

	shell.setDrawMatrix(&rootMtx);
	shell.setScale(1.0f, 1.0f, 1.0f);
	shell.calcWorld(false);
	SetupTextures_Player(&shell, sceneNum);

	shell.scheduleForDrawing();
}

// NEW VERSION
void CrapUpPositions(Vec *out, const Vec *in);

kmBranchDefCpp(0x807AFBC0, NULL, void, dStockItem_c* self) {
//void dStockItem_c::setScalesOfSomeThings() {
	nw4r::lyt::Pane *ppos = self->N_forUse_PPos[self->playerCount];

	int howManyPlayers = 0;
	for (int i = 0; i < 4; i++) {
		if (self->isPlayerActive[i]) {
			int picID = self->getIconPictureIDforPlayer(howManyPlayers);
			int charID = Player_ID[i];

			if (picID != 24) {
				nw4r::lyt::Picture *pic = self->P_icon[picID];

				Vec in, out;

				in.x = pic->effectiveMtx[0][3];
				in.y = pic->effectiveMtx[1][3];
				in.z = pic->effectiveMtx[2][3];

				CrapUpPositions(&out, &in);

				u8 *wmp = (u8*)self->player2d[charID];
				*((float*)(wmp+0xAC)) = out.x;
				*((float*)(wmp+0xB0)) = out.y;
				*((float*)(wmp+0xB4)) = out.z;
				*((float*)(wmp+0x220)) = 0.89999998f;
				*((float*)(wmp+0x224)) = 0.89999998f;
				*((float*)(wmp+0x228)) = 0.89999998f;
				*((float*)(wmp+0x25C)) = 26.0f;
			}
			howManyPlayers++;
		}
	}

	for (int i = 0; i < 8; i++) {
		u8 *item = (u8*)self->newItemPtr[i];

		nw4r::lyt::Pane *icon = self->newIconPanes[i];

		Vec in, out;
		in.x = icon->effectiveMtx[0][3];
		in.y = icon->effectiveMtx[1][3];
		in.z = icon->effectiveMtx[2][3];

		CrapUpPositions(&out, &in);

		*((float*)(item+0xAC)) = out.x;
		*((float*)(item+0xB0)) = out.y;
		*((float*)(item+0xB4)) = out.z;
		*((float*)(item+0x1F4)) = self->P_buttonBase[i]->scale.x;
		*((float*)(item+0x1F8)) = self->P_buttonBase[i]->scale.y;
		*((float*)(item+0x1FC)) = 1.0f;
	}

	nw4r::lyt::Pane *shdRoot = self->shadow->rootPane;
	shdRoot->trans.x = self->N_stockItem->effectiveMtx[0][3];
	shdRoot->trans.y = self->N_stockItem->effectiveMtx[1][3];
	shdRoot->trans.z = self->N_stockItem->effectiveMtx[2][3];
	shdRoot->scale.x = self->N_stockItem_01->effectiveMtx[0][0];
	shdRoot->scale.y = self->N_stockItem_01->effectiveMtx[1][1];
}