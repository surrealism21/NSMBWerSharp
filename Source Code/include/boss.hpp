#ifndef __PLAYER_H
#define __PLAYER_H

#include <common.hpp>
#include <game.hpp>
#include <g3dhax.hpp>
#include <stage.hpp>
#include <sfx.hpp>


extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);

extern "C" u32 GenerateRandomNumber(int max);
extern "C" char usedForDeterminingStatePress_or_playerCollision(dEn_c* t, ActivePhysics *apThis, ActivePhysics *apOther, int unk1);

extern "C" void *StopBGM();
extern "C" void *StartBGM();

extern "C" void *MakeMarioEnterDemoMode();
extern "C" void *MakeMarioExitDemoMode();
extern "C" void *UpdateGameMgr();

class daBoss : public dEn_c {
public:
	u32 timer;
	char dying;
	int damage;

	daKameckDemo *Kameck;
};

// Functions

void DamagePlayer(dEn_c* actor, ActivePhysics *apThis, ActivePhysics *apOther);

void SetupKameck(daBoss* actor, daKameckDemo *Kameck);
void CleanupKameck(daBoss* actor, daKameckDemo *Kameck);

void OutroSetup(daBoss* actor);
void PlayerVictoryCries(daBoss* actor);
void BossExplode(daBoss* actor, Vec *pos);
void BossGoalForAllPlayers();

bool GrowBoss(daBoss* actor, daKameckDemo *Kameck, float initialScale, float endScale, float yPosModifier, int timer);
bool ShrinkBoss(daBoss *actor, Vec *pos, float scale, int timer);

#endif

