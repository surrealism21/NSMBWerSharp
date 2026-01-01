#include <game.hpp>
#include <profileid.hpp>
#include <stage.hpp>

extern char CurrentLevel, CurrentWorld;
extern u8 MaybeFinishingLevel[2];
extern "C" void ExitStageReal(int scene, int sceneParams, int powerupStoreType, int wipe);

// is this needed now that cutscenes are gone?
extern "C" void ExitStageWrapper(int scene, int sceneParams, int powerupStoreType, int wipe) {
	ExitStageReal(scene, sceneParams, powerupStoreType, wipe);
}

extern "C" void EnterOpeningLevel() {
	DontShowPreGame = true;
	RESTART_CRSIN_LevelStartStruct.purpose = 0;
	RESTART_CRSIN_LevelStartStruct.world1 = 1;
	RESTART_CRSIN_LevelStartStruct.world2 = 1;
	RESTART_CRSIN_LevelStartStruct.level1 = 40;
	RESTART_CRSIN_LevelStartStruct.level2 = 40;
	RESTART_CRSIN_LevelStartStruct.areaMaybe = 0;
	RESTART_CRSIN_LevelStartStruct.entrance = 0xFF;
	RESTART_CRSIN_LevelStartStruct.unk4 = 0; // load replay
	DoSceneChange(ProfileId::RESTART_CRSIN, 0, 0);
}

