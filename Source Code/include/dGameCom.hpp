#ifndef __DGAMECOM
#define __DGAMECOM

#include <game.hpp>

enum SCLanguage {
	SC_LANG_JAPANESE = 0,
	SC_LANG_ENGLISH,
	SC_LANG_GERMAN,
	SC_LANG_FRENCH,
	SC_LANG_SPANISH,
	SC_LANG_ITALIAN,
	SC_LANG_DUTCH,
	SC_LANG_SIMP_CHINESE,
	SC_LANG_TRAD_CHINESE,
	SC_LANG_KOREAN,
};

enum GameStop {
	GAME_STOP_PAUSE = 0,
	GAME_STOP_WARNING,
	GAME_STOP_OTASUKE_PAUSE,
	GAME_STOP_HOME_MENU,
	GAME_STOP_ANY = -1,
};

// Game Common
namespace dGameCom {
	void calcXY(int param_1, int param_2, Vec2 *param_3, short param_4);

	// checks if WPAD_ONE was pressed, or WPAD_ONE/WPAD_B if a Nunchuk is connected
	int chkCancelButton(int controllerID);

	// checks player lives to see if it should increment Continues
	bool chkContinue();


	void EasyPairingResume();
	void EasyPairingStop();

	// returns 1 for widescreen, 0 for 4:3
	bool getAspectRatio();

	SCLanguage getLanguageX();

	int getCourseNum(int world, int level);

	// gets center of screen
	float getDispCenterX();
	float getDispCenterY();


	int getRandomSeed();
	void setRandomSeed(u32 seed);

	u32 getRandom(u32 max);
	u32 rndInt(u32 max);

	float getRandomDp(); // between -0.5 and 0.5
	float rndFX(float param);
	float getRandomFloat(); // between 0 and 1
	float rndF(float param);


	// initializes savefile, dInfo_c, player data, etc.
	void initGame();


	// checks if game is stopped with flag from GameStop
	bool isGameStop(u32 flag);
	void clearGameStop(); // 800b3a20
	// checks for a reason to stop the game
	void setGameStop(); // 800b3a30


	bool isNowCourseClear();

	bool isWorldClear(int world, u8 saveSlot = -1);

	bool playerEnterCheck(int playerID);

	// lightmaps
	void SetSoftLight_Boss(m3d::mdl_c *model, int sceneID);
	void SetSoftLight_Enemy(m3d::mdl_c *model, int sceneID);
	void SetSoftLight_Item(m3d::mdl_c *model, int sceneID);
	void SetSoftLight_Map(m3d::mdl_c *model, int sceneID);
	void SetSoftLight_MapObj(m3d::mdl_c *model, int sceneID);
	void SetSoftLight_Player(m3d::mdl_c *model, int sceneID);

	// shows "THE END"
	void TheEndStart();

	void StaffCreditStart();
	void StaffCreditAddCoin();
	void StaffCreditHighScore();
	void StaffCreditHighScoreCheck();
	void StaffCreditKiMe(); // ???
	
	void MovieMessageDisp(int message);
	void MovieMessageClose();

	void MiniGameMessageDisp(int message);
	void MiniGameMessageClose();

	void MiniGameCannonStart();
	void MiniGameCannonTitle();
	void MiniGameCannonResult();
	void MiniGameCannonEndCheck();

	void MiniGameWireStart();
	void MiniGameWireTitle();
	void MiniGameWireTitleCloseRequest();
	void MiniGameWireOperateCloseRequest();
	void MiniGameWireTurnOverCloseRequest();
	void MiniGameWireResultCloseRequest();
	void MiniGameWireEndCheck();

	static u32 m_rnd;  // 0x8042A224
	static u32 gameStop; // 0x8042A228
};

#endif