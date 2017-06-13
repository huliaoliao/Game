#ifndef					__COMMON_H__
#define					__COMMON_H__

#include <string>

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

const char gameStateReady[] = "image/game/ready.png";
const char gameStateReadyBtn[] = "image/game/btn_start.png";

const char NOCALLBTN[] = "image/game/calllandlord/btn_nocall.png";
const char CALLONEBTN[] = "image/game/calllandlord/btn_one.png";
const char CALLTWOBTN[] = "image/game/calllandlord/btn_two.png";
const char CALLTHREEBTN[] = "image/game/calllandlord/btn_three.png";

const char HINT_BTN[] = "image/game/btn_hint.png";
const char HINT_DISABLE_BTN[] = "image/game/btn_hint_disabled.png";
const char OUTPOKER_BTN[] = "image/game/btn_out.png";
const char OUTPOKER_DISABLE_BTN[] = "image/game/btn_out_disabled.png";
const char PASS_BTN[] = "image/game/btn_pass.png";
const char PASS_DISABLE_BTN[] = "image/game/btn_pass_disabled.png";

const char headLandlordLeft[] = "landlord_boy_left.png";
const char headLandlordRight[] = "landlord_boy_right.png";
const char headFarmerLeft[] = "farmer_boy_left.png";
const char headFarmerRight[] = "farmer_boy_right.png";

const char NOCALLSTATE[] = "flagcall_0.png";
const char CALLONESTATE[] = "flagcall_1.png";
const char CALLTWOSTATE[] = "flagcall_2.png";
const char CALLTHREESTATE[] = "flagcall_3.png";

const char PASS_IMAGE[] = "image/game/pass.png";

const int COMMON_DIALOG_ZORDER = 1;

const int SINGLE_TYPE_CARD_NUM = 13;

const int DIALOG_WIDTH = 720;
const int DIALOG_HEIGHT = 480;

const std::string CREATE_HEADIMAGE_LAYER = "createHeadImageLayer";		//����ͷ���
const std::string DESTROY_HEADIMAGE_LAYER = "destroyHeadImageLayer";	//����ͷ���
const std::string CREATE_READY_LAYER = "createReadyLayer";		//����׼����
const std::string DESTROY_READY_LAYER = "destroyReadyLayer";	//����׼����
const std::string CREATE_POKER_LAYER = "createPokerLayer";			//�����˿˲�
const std::string DESTROY_POKER_LAYER = "destroyPokerLayer";	//�����˿˲�
const std::string CREATE_CALL_LANDLORD_LAYER = "createCallLandlordLayer";	//�����е�����
const std::string DESTROY_CALL_LANDLORD_LAYER = "destroyCallLandlordLayer";	//���ٽе�����

const std::string UPDATE_GAME_STATE = "updateGameState";		//������Ϸ״̬
const std::string UPDATE_CALL_LANDLORD_INDEX = "updateCallLandlordIndex";	//���½е���˳��
const std::string DISPLAY_CALL_LANDLORD_BTN = "displayCallLandlordBtn";			//��ʾ�ֶ���ҽе�����ť

//��ҽзֻص�
const std::string COMPUTER_ONE_NOCALL = "computerOneNoCall";
const std::string COMPUTER_ONE_CALLONE = "computerOneCallOne";
const std::string COMPUTER_ONE_CALLTWO = "computerOneCallTwo";
const std::string COMPUTER_ONE_CALLTHREE = "computerOneCallThree";

const std::string COMPUTER_TWO_NOCALL = "computerTwoNoCall";
const std::string COMPUTER_TWO_CALLONE = "computerTwoCallOne";
const std::string COMPUTER_TWO_CALLTWO = "computerTwoCallTwo";
const std::string COMPUTER_TWO_CALLTHREE = "computerTwoCallThree";

//��ʾ��ҽзֻص�
const std::string DISPLAY_COMPUTE_ONE_CALLLANDLORD_STATE = "displayComputerOneCallState";
const std::string DISPLAY_COMPUTE_TWO_CALLLANDLORD_STATE = "displayComputerTwoCallState";

const std::string GAME_CONTROLLER_RUN = "gameControllerRun";	//��Ϸ����������
const std::string DISPLAY_HOLDER_POKERS = "displayHolderPokers";	//��ʾ�ֶ���ң��Լ������е���
const std::string DISPLAY_LANDLORD_POKERS = "displayLandlordPokers";	//��ʾԤ������������
const std::string UPDATE_HOLDER_HEADIMAGE = "updateHolderHeadImage";	//�����ֶ����ͷ��Ϊ����
const std::string UPDATE_COMPUTERONE_HEADIMAHE = "updateComputerOneHeadImage";	//���µ������1ͷ��Ϊ����
const std::string UPDATE_COMPUTERTWO_HEADIMAGE = "updateComputerTwoHeadImage";	//���µ������2ͷ��Ϊ����

const std::string POKER_IMAGES = "image/game/poker/Joker.png";
const std::string POKER_IMAGE_LIST = "image/game/poker/Joker.plist";
const std::string CALL_LANDLORD_IMAGES = "image/game/calllandlord/call_landlord_state.png";
const std::string CALL_LANDLORD_IMAGE_LIST = "image/game/calllandlord/call_landlord_state.plist";

const std::string COUNTDOWN_IMAGES = "image/game/clock/clock.png";
const std::string COUNTDOWN_IMAGE_LIST = "image/game/clock/clock.plist";
const std::string COUNTDOWN_NUMS = "image/game/clock/clock_num.png";

const std::string PASS_HINT = "image/game/passhint.png";	//��ʾû�д�ù��ϼҵ���ͼƬ

const std::string DESTROY_LAST_HOLDER_OUTPOKERS = "destroyLastHolderOutPokers";
const std::string DISPLAY_HOLDER_OUTPOKERS = "displayHolderOutPokers";//��ʾ�ֶ����Ҫ������
const std::string DESTROY_LAST_COMPUTER_ONE_OUTPOKERS = "destroyLastComputerOneOutPokers";
const std::string DISPLAY_COMPUTER_ONE_OUTPOKERS = "displayComputerOneOutPokers";
const std::string DESTROY_LAST_COMPUTER_TWO_OUTPOKERS = "destroyLastComputerTwoOutPokers";
const std::string DISPLAY_COMPUTER_TWO_OUTPOKERS = "displayComputerTwoOutPokers";

const std::string ADD_POKER_IN_HOLDER_POKERSWAITFOROUT = "addPokerInHolderPokersWaitForOut";	//���ֶ����׼���������������
const std::string DELETE_POKER_IN_HOLDER_POKERSWAITFOROUT = "deletePokerInHolderPokersWaitForOut";	//���ֶ����׼����������ɾ����

const std::string UPDATE_OUT_ORDER = "updateOutOrder";	//���³���˳��
const std::string DISPLAY_HOLDER_OUTPOKERS_BTNS = "displayHolderOutPokersBtns";	//��ʾ�ֶ���ҳ�����ذ�ť
//const std::string IS_HOLDER_POKERS_CAN_OUT = "isHolderPokersCanOut";	//�ֶ����ѡ������Ƿ���Գ�
const std::string OUTPOKERS_BTN_ENABLED = "outPokersBtnEnabled";	//���ư�ť���԰���
const std::string OUTPOKERS_BTN_DISABLED = "outPokersBtnDisabled";	//���ư�ť���ɰ�
const std::string HINT_BTN_ENABLED = "hintBtnEnabled";		//��ʾ��ť�ɰ�
const std::string HOLDER_OUTPOKERS = "holderOutPokers";		//�ֶ���ҳ���
const std::string UPDATE_LAST_OUTPOKERS = "updateLastOutPokers";	//������һ����
const std::string CLICK_HINT_BTN = "clickHintBtn";	//�����ʾ��ť
const std::string MAKE_HINT_POKERS_SELECTED = "makeHintPokersSelected";	//����ʾ��ť��ѡ�У���ʾ������
const std::string SHOW_PASSHINT = "showPassHint";	

// const std::string START_COUNTDOWN = "startCountDown";		//��ʼ����ʱ
// const std::string STOP_COUNTDOWN = "stopCountDown";	//ֹͣ����ʱ
const std::string HOLDER_START_COUNTDOWN = "holderStartCountDown";	//�ֶ���Ҽ�ʱ����ʼ��ʱ
const std::string HOLDER_STOP_COUNTDOWN = "holderStopCountDown";	//�ֶ���Ҽ�ʱ��ֹͣ��ʱ
const std::string COMPUTER_ONE_START_COUNTDOWN = "computerOneStartCountDown";	//�������1��ʱ����ʼ��ʱ
const std::string COMPUTER_TWO_START_COUNTDOWN = "computerTwoStartCountDown";	//�������2��ʱ����ʼ��ʱ

#endif