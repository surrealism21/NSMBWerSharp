#include <game.hpp>
#include <levelinfo.hpp>
#include <utils.hpp>

class PregameLytHandler {
	public:
		m2d::EmbedLayout_c layout;

		nw4r::lyt::Pane *rootPane;

		nw4r::lyt::TextBox
			*T_minus_00, *T_world_00, *T_worldNum_00,
			*T_pictureFont_00, *T_corseNum_00,
			*T_remainder_00, *T_remainder_01, *T_remainder_02, *T_remainder_03,
			*T_remainder_10, *T_remainder_11, *T_remainder_12, *T_remainder_13,
			*T_x_00, *T_x_01, *T_x_02, *T_x_03, *T_x_10, *T_x_11, *T_x_12, *T_x_13,
			*T_x_00_o, *T_x_10_o,
			*T_otasukePlay_00, *T_otasukePlay_01,
			*T_recommend_00, *T_remainder_00_o, *T_remainder_10_o;

		nw4r::lyt::Picture
			*P_Wx_00[9], *P_coin_00, *P_free_00,
			*P_batB_0x[4], *P_bat_00,
			*P_batB_1x[4], *P_bat_01,
			*P_batB_2x[4], *P_bat_02,
			*P_batB_3x[4], *P_bat_03,
			*P_luijiIcon_00_o, *P_luijiIcon_10_o, *P_coinStage_00;

		nw4r::lyt::Pane
			*N_mario_00, *N_luiji_00, *N_kinoB_01, *N_kinoY_00,
			*N_zankiPos_x[4], *N_zanki_00,
			*Null_battPosxP[4], *N_batt_x[4],
			*N_batt, *N_otasukePlay_00;

		u8 layoutLoaded, somethingHasBeenDone, isVisible, hasShownLuigiThing_orSomething;

		u32 currentStateID;

		u32 _2E8;

		u32 countdownToEndabilityCopy, activePlayerCountMultBy4_maybe;
		u32 batteryLevels[4];
		u32 pgCountdown;

        void newLoadLevelNumber();
};

extern char CurrentLevel;
extern char CurrentWorld;

kmBranchDefCpp(0x80B6BDD0, NULL, void, PregameLytHandler* self) {
//void PregameLytHandler::newLoadLevelNumber() {
    const wchar_t *convWorldName;
	const wchar_t *convLevelName;

    dScript::Res_c *msgRes = GetBMG();
    GameMgr *dInfo_c = GameMgrP;
    int world = CurrentWorld;
    int level = CurrentLevel;

    if (world > 8)
        world = 9;
    
    self->P_Wx_00[world]->SetVisible(true);

    WriteBMGToTextBox(self->T_world_00, msgRes, 0x66, 0x1f, 0);
    WriteBMGToTextBox(self->T_minus_00, msgRes, 0x66, 0x29, 0);

    dLevelInfo_c::entry_s *Level = dLevelInfo_c::s_info.searchBySlot(world, level);
	if (Level) {
		convWorldName = getWorldNumber(Level->displayWorld);
		convLevelName = getLevelNumber(Level->displayLevel);

		self->T_worldNum_00->SetString(convWorldName);

		if (Level->displayLevel > 19) {
			self->T_pictureFont_00->SetVisible(true);
			self->T_corseNum_00->SetVisible(false);
			self->T_pictureFont_00->SetString(convLevelName);
		} else {
			self->T_pictureFont_00->SetVisible(false);
			self->T_corseNum_00->SetVisible(true);
			self->T_corseNum_00->SetString(convLevelName);
		}
	} else {
		self->T_pictureFont_00->SetVisible(false);
		self->T_corseNum_00->SetVisible(true);
		self->T_worldNum_00->SetString(L"?");
		self->T_corseNum_00->SetString(L"?");
	}

    return;
}