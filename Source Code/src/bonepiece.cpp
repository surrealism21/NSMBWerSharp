#include <game.hpp>
#include <profile.hpp>

class daBonePiece_c : public dStageActor_c {
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	int color;

	StandOnTopCollider collider;

	mHeapAllocator_c allocator;
	nw4r::g3d::ResFile resFile;
	m3d::mdl_c model;

	public: static dActor_c *build();
};

const char* BonePieceNameList [] = {"lift_torokko", NULL};
const SpriteData BonePieceSpriteData = { ProfileId::AC_BONE_PIECE, 0, 0 , 0 , 0, 0x100, 0x100, 0, 0, 0, 0, 2};
// #      -ID- ----  -X Offs- -Y Offs-  -RectX1- -RectY1- -RectX2- -RectY2-  -1C- -1E- -20- -22-  Flag ----
Profile BonePieceProfile(&daBonePiece_c::build, SpriteId::AC_BONE_PIECE, &BonePieceSpriteData, ProfileId::WM_BOSS_IGGY, ProfileId::AC_BONE_PIECE, "AC_BONE_PIECE", BonePieceNameList);

// Glue Code
dActor_c  *daBonePiece_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daBonePiece_c));
	daBonePiece_c *c = new(buffer) daBonePiece_c;
	return c;
}

int daBonePiece_c::onCreate() {
	// Load the model
	color = (this->settings >> 16) & 0xF;

	// figure out which spritetex model to use
	allocator.link(-1, GameHeaps[0], 0, 0x20);
	char colorThingForGetResource[32];
	sprintf(colorThingForGetResource, "g3d/t0%i.brres", color);
	resFile.data = getResource(BonePieceNameList[0], colorThingForGetResource);

	// figure out which model to use (which body piece we're on)
	static char thing[] = "lift_torokko?";
	thing[0xC] = 'A' + (settings & 3);

	nw4r::g3d::ResMdl resmdl = resFile.GetResMdl(thing);
	model.setup(resmdl, &allocator, 0, 1, 0);
	SetupTextures_MapObj(&model, 0);

	allocator.unlink();

	// If rotation is off, do nothing else
	if ((settings >> 28) & 1) {
		// OK, figure out the rotation
		u8 sourceRotation = (settings >> 24) & 0xF;

		// 0 is up. -0x4000 is right, 0x4000 is left ...
		s16 rotation;

		// We'll flip it later.
		// Thus: 0..7 rotates left (in increments of 0x800),
		// 8..15 rotates right (in increments of 0x800 too).
		// To specify facing up, well.. just use 0.

		if (sourceRotation < 8) {
			rotation = (sourceRotation * 0x800) - 0x4000;
		}
		else {
			rotation = (sourceRotation * 0x800) - 0x3800;
		}
		rot.z = -rotation;
	}

	if ((settings >> 20) & 1) {
		rot.y = 0x8000;
	}

	float xOffs, yOffs;

	if (-0x2000 <= rot.z && rot.z <= 0x2000) {
		xOffs = 8.0f * sin(rot.z) * cos(rot.z);
	}
	else {
		xOffs = 5.0f * sin(rot.z);
	}
	if (rot.z < 0) {
		yOffs = -xOffs;
	}
	else {
		yOffs = xOffs;
	}

	collider.init(this, xOffs, yOffs, 0, 16.0f, -16.0f, rot.z, 1); // X Offset, Y Offset, Top Y Offset, Right Size, Left Size, Rotation, _45
	collider._47 = 0;
	collider.flags = 0x80180 | 0xC00;
	collider.addToList();
	return true;
}

int daBonePiece_c::onDelete() {
	return true;
}

int daBonePiece_c::onExecute() {
	matrix.translation(pos.x, pos.y - 8.0f, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	model.setDrawMatrix(matrix);
	model.setScale(&scale);
	model.calcWorld(false);

	collider.update();
	return true;
}

int daBonePiece_c::onDraw() {
	model.scheduleForDrawing();
	return true;
}