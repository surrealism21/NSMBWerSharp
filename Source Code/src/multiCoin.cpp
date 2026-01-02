#include <common.hpp>
#include <game.hpp>
#include <g3dhax.hpp>
#include <sfx.hpp>
#include <profile.hpp>

extern "C" void incCoin(int playerID); // 0x80060250
extern "C" void addScore(int score, int playerID); // 0x80060690
extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);
extern "C" void displayScoreAddPopup(Vec pos, int smallScoreID, int playerID, bool showForever);  // https://note.com/reaz0n23/n/nb504e036da6d#143de39b-221f-4909-94f8-cc11e4dbdfdd

// types:
// 0 - 10-Coin
// 1 - 100-Coin
// feel free to add your own type(s), it shouldn't be that difficult depending on what you're doing

class dMultiCoin_c : public dEn_c {
	public:
		static dActor_c *build();
	
	// these are all also public since they don't really need to be anything else,
	// i'm just gonna keep the above function the only indented one since that's the one that NEEDS to be public
	
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	int type;
	int coinsToGive;
	int rotSpeed;

	bool collected;

	mHeapAllocator_c allocator;
	m3d::mdl_c bodyModel;
	void updateModelMatrices();

	void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	void yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther); 
    bool collisionCat5_Mario(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat8_FencePunch(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat11_PipeCannon(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther); 
	bool collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther); 
};

const SpriteData MultiCoinSpriteData = {ProfileId::EN_COIN_MULTI, 0, 0, 0, 0, 0x100, 0x100, 0, 0, 0, 0, 2};
Profile MultiCoinProfile(&dMultiCoin_c::build, SpriteId::EN_COIN_MULTI, &MultiCoinSpriteData, ProfileId::EN_COIN_MULTI, ProfileId::EN_COIN_MULTI, "EN_COIN_MULTI");

dActor_c *dMultiCoin_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(dMultiCoin_c));
	return new(buffer) dMultiCoin_c;
}

int dMultiCoin_c::onCreate() {
	// get our coin type from nybble 5
	type = (this->settings >> 28);

	if (type == 0) {
		allocator.link(-1, GameHeaps[0], 0, 0x20);
		nw4r::g3d::ResFile rf(getResource("obj_coin", "g3d/obj_coin.brres"));
    	bodyModel.setup(rf.GetResMdl("obj_coin_ten"), &allocator, 0x224, 1, 0);
    	SetupTextures_MapObj(&bodyModel, 0);
		allocator.unlink();
	}
	else if (type == 1) {
		allocator.link(-1, GameHeaps[0], 0, 0x20);
		nw4r::g3d::ResFile rf(getResource("obj_coin", "g3d/obj_coin.brres"));
    	bodyModel.setup(rf.GetResMdl("obj_coin_hundred"), &allocator, 0x224, 1, 0);
    	SetupTextures_MapObj(&bodyModel, 0);
		allocator.unlink();
	}

	ActivePhysics::Info HitMeBaby;
	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = -3.0;
	HitMeBaby.xDistToEdge = 12.0;
	HitMeBaby.yDistToEdge = 15.0;
	HitMeBaby.category1 = 0x5;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0xFFFFFFFF;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	// model scale
	if (type == 0) {
		this->scale.x = 0.0625;
		this->scale.y = 0.0625;
		this->scale.z = 0.0625;
	}
	else {
		this->scale.x = 0.09375;
		this->scale.y = 0.09375;
		this->scale.z = 0.09375;
	}

	this->rotSpeed = 0x400;
	this->collected = false;

	// how many coins to give per type
	if (type == 0) { this->coinsToGive = 10; }
	else if (type == 1) { this->coinsToGive = 100; }

	this->onExecute();
	return true;
}

int dMultiCoin_c::onDelete() {
	return true;
}

int dMultiCoin_c::onDraw() {
    bodyModel.scheduleForDrawing();
	return true;
}

void dMultiCoin_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int dMultiCoin_c::onExecute() {
	updateModelMatrices();
	this->rot.y += this->rotSpeed; // Notes: X is the vertical axis here. Y is the horizontal. Z... is an axis. General coin movement is in the X axis.
	return true;
}

// Player collision

void dMultiCoin_c::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
    if (!collected) {
        this->collected = true;
        for (int i=0; i < this->coinsToGive; i++) {
            incCoin(1);
        }
		if (type == 0) {
			SpawnEffect("Wm_ob_starcoinget", 0, &this->pos, &(S16Vec){0,0,0}, &(Vec){1.0, 1.0, 1.0});
        	PlaySoundAsync(this, SE_OBJ_GOAL_GET_COIN_BONUS);
			displayScoreAddPopup(this->pos, 0, apOther->owner->which_player, false);
        	addScore(100, apOther->owner->which_player);
		}
		else if (type == 1) {
			SpawnEffect("Wm_ob_starcoinget", 0, &this->pos, &(S16Vec){0,0,0}, &(Vec){1.5, 1.5, 1.5});
        	PlaySoundAsync(this, SE_OBJ_GOAL_GET_COIN_BONUS);
        	displayScoreAddPopup(this->pos, 4, apOther->owner->which_player, false);
			addScore(1000, apOther->owner->which_player);
		}
        this->Delete(1);
    }
}

void dMultiCoin_c::yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
	return this->playerCollision(apThis, apOther);
}

bool dMultiCoin_c::collisionCat5_Mario(ActivePhysics *apThis, ActivePhysics *apOther) {
    if (!collected) {
        this->collected = true;
        for (int i=0; i < this->coinsToGive; i++) {
            incCoin(1);
        }
		if (type == 0) {
			SpawnEffect("Wm_ob_starcoinget", 0, &this->pos, &(S16Vec){0,0,0}, &(Vec){1.0, 1.0, 1.0});
        	PlaySoundAsync(this, SE_OBJ_GOAL_GET_COIN_BONUS);
			displayScoreAddPopup(this->pos, 0, apOther->owner->which_player, false);
        	addScore(100, apOther->owner->which_player);
		}
		else if (type == 1) {
			SpawnEffect("Wm_ob_starcoinget", 0, &this->pos, &(S16Vec){0,0,0}, &(Vec){1.5, 1.5, 1.5});
        	PlaySoundAsync(this, SE_OBJ_GOAL_GET_COIN_BONUS);
        	displayScoreAddPopup(this->pos, 4, apOther->owner->which_player, false);
			addScore(1000, apOther->owner->which_player);
		}
        this->Delete(1);
    }
	return true;
}

bool dMultiCoin_c::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) {
	return this->collisionCat5_Mario(apThis, apOther);
}

bool dMultiCoin_c::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
    return this->collisionCat5_Mario(apThis, apOther);
}

bool dMultiCoin_c::collisionCat8_FencePunch(ActivePhysics *apThis, ActivePhysics *apOther) {
    return true;
}

bool dMultiCoin_c::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
    return this->collisionCat5_Mario(apThis, apOther);
}

bool dMultiCoin_c::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
    return this->collisionCat5_Mario(apThis, apOther);
}

bool dMultiCoin_c::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
    return this->collisionCat5_Mario(apThis, apOther);
}

bool dMultiCoin_c::collisionCat11_PipeCannon(ActivePhysics *apThis, ActivePhysics *apOther) {
    return this->collisionCat5_Mario(apThis, apOther);
}

bool dMultiCoin_c::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
    return this->collisionCat5_Mario(apThis, apOther);
}

bool dMultiCoin_c::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
	PlaySound(this, SE_OBJ_FIREBALL_DISAPP);
	return true;
}

bool dMultiCoin_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {
	PlaySound(this, SE_OBJ_EMY_ICEBALL_DISAPP);
	return true;
}

bool dMultiCoin_c::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}

bool dMultiCoin_c::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	PlaySound(this, SE_OBJ_FIREBALL_DISAPP);
	return true;
}