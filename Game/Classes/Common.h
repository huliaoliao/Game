#ifndef					__COMMON_H__
#define					__COMMON_H__

const char* const pressBtnMusic = "music/btnpress.mp3";

const char dialogBgImage[] = "lobby/dialog_bg.png";
const char dialogTopBgImage[] = "lobby/dialog_bgTop.png";
const char dialogBtnImage[] = "lobby/dialog_btn.png";
const char setDialogEffect[] = "lobby/set/setting-effect.png";
const char setDialogMusic[] = "lobby/set/setting-music.png";
const char setDialogProgress[] = "lobby/set/setting-progress.png";
const char setDialogSlider[] = "lobby/set/setting-slider.png";
const char setDialogTrack[] = "lobby/set/setting-track.png";
const char dialogCloseBtn[] = "lobby/close_btn.png";
const char dialogMiddleBgImage[] = "lobby/dialog-middleBg.png";
const char startGameImage[] = "lobby/start_game.png";

const char gameSceneBg[] = "image/game/gamescene_bg.png";
const char gameSceneBorder[] = "image/game/gamescene_border.png";
const char gameSceneCorner[] = "image/game/gamescene_ corner.png";

const char headImages[] = "image/game/headimage/head_image.png";
const char headImageList[] = "image/game/headimage/head_image.plist";
const char headBox[] = "image/game/headimage/head_box.png";
const char noHead[] = "image/game/headimage/no_head.png";
const char headLandlordLeft[] = "image/game/headimage/landlord_boy_left.png";
const char headLandlordRight[] = "image/game/headimage/landlord_boy_right.png";
const char headFarmerLeft[] = "image/game/headimage/farmer_boy_left.png";
const char headFarmerRight[] = "image/game/headimage/farmer_boy_right.png";

const char gameStateReady[] = "image/game/ready.png";
const char gameStateReadyBtn[] = "image/game/btn_start.png";

const int COMMON_DIALOG_ZORDER = 1;

const int DIALOG_WIDTH = 720;
const int DIALOG_HEIGHT = 480;

const std::string CREATE_HEADIMAGE_LAYER = "createHeadImageLayer";		//创建头像层
const std::string DESTROY_HEADIMAGE_LAYER = "destroyHeadImageLayer";	//销毁头像层
const std::string CREATE_READY_LAYER = "createReadyLayer";		//创建准备层
const std::string DESTROY_READY_LAYER = "destroyReadyLayer";	//销毁准备层

const std::string GAME_CONTROLLER_RUN = "gameControllerRun";	//游戏控制器运行

#endif