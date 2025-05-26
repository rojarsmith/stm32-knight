#ifndef COMMONCONSTANT_HPP
#define COMMONCONSTANT_HPP

#include <string>

using namespace std;

extern "C"
{	
	//Element status.
	const int DAY_BG_MODE_R = 0xD9;
	const int DAY_BG_MODE_G = 0xD9;
	const int DAY_BG_MODE_B = 0xD9;
	const int NIGHT_BG_MODE_R = 0x1E;
	const int NIGHT_BG_MODE_G = 0x20;
	const int NIGHT_BG_MODE_B = 0x21;
	static int DISPLAY_WIDTH_HALF;
	const int PLUGIN_RIGHT_SCREEN_HOME_ORIGINAL_POINT_Y = -158;
	//const int PLUGIN_RIGHT_SCREEN_HOME_ORIGINAL_POINT_Y = -254;		
	const int POLE_SCREEN_30_RIGHT_X = -173; // 800*480
	const int POLE_SCREEN_30_LEFT_X = 353;
	//const int POLE_SCREEN_30_RIGHT_X = -278;
	//const int POLE_SCREEN_30_LEFT_X = 566;
	const int POLE_SCREEN_40 = 190;
	//const int POLE_SCREEN_40 = 305;
	const int POLE_DEBUG_Y_SHIFT = 0; //Debug=400

	//Scan time.
	const int MODEL_DATA_SCAN_TIME = 30;

	//Animation duration.
	const int ANIMATION_MESSAGE_IN_DURATION = 30; //Message+Content
	const int ANIMATION_MESSAGE_OUT_DURATION = 30;
	//const int ANIMATION_TRANSITION_IN_DURATION = 10; //1 = close for low hardware
	//const int ANIMATION_TRANSITION_OUT_DURATION = 10; //1 = close for low hardware
	const int ANIMATION_TRANSITION_IN_DURATION = 30; //1 = close for low hardware
	const int ANIMATION_TRANSITION_OUT_DURATION = 30; //1 = close for low hardware
	const int ANIMATION_SHAKE_BUTTON = 15;
	const int ANIMATION_PLUGIN_EXG_DURATION = 30;	

	const int ANIMATION_LOADING_OPEN_DURATION = 30;
	const int ANIMATION_LOADING_HIDE_DURATION = 30;
	const int ANIMATION_LOADING_OK_DURATION = 60;
}

class CommonConstant
{
private:	
	CommonConstant() {}	
	~CommonConstant(void) {}
	CommonConstant(const CommonConstant&) { return; };
	CommonConstant& operator=(CommonConstant const&) {};
public:	
	static CommonConstant& getInstance() 
	{
		static CommonConstant instance;
		return instance;
	}

	int After1Tick = 1;
	int After2Tick = 2;
	uint8_t After30Tick = 30;
	uint8_t After60Tick = 60;
	uint8_t After120Tick = 120;
	uint8_t After240Tick = 240;
	int AfterXSec = (int)(3* 60);
	
	uint16_t DisplayWidthHalf; //384
	uint16_t DisplayHeightHalf; //512

	uint16_t TitleX;
	uint16_t TitleY;
	uint16_t TitleWidth;
	uint16_t TitleHeight;

	//Pole Status
	uint16_t PoleSmallWidth; //320
	uint16_t PoleSmallHeight; //1404
	int16_t Pole20X = 90; // 800x480
	//int16_t Pole20X = 144;
	int16_t Pole20Y = 0;

	int16_t PluginLargeEndY = -158;
	int16_t PluginRightLargeXShift = 58;
	int16_t PluginLeftLargeXShift = 428;
	//int16_t PluginLargeEndY = -254;
	//int16_t PluginRightLargeXShift = 93;
	//int16_t PluginLeftLargeXShift = 686;

	int16_t PopX = 40;
	int16_t PopY = 87;
	int16_t PopWidth = 398;
	int16_t PopHeight = 536;
	//int16_t PopX = 65;
 //   int16_t PopY = 140;
 //   int16_t PopWidth = 638;
 //   int16_t PopHeight = 858;

	//Socket status
	uint8_t SocketAlphaHomeBegin = 60;
	uint8_t SocketAlphaGeneral = 255;
	int16_t SocketHomeXR = 300;
	int16_t SocketHomeXL = 120;
	int16_t SocketHomeY = 263;
	uint16_t SocketHomeW = 60;
	uint16_t SocketHomeH = 112;
	//int16_t SocketHomeXR = 480;	
	//int16_t SocketHomeXL = 192;
	//int16_t SocketHomeY = 421;
	//uint16_t SocketHomeW = 96;
	//uint16_t SocketHomeH = 180;

	//Plugin status
	//int16_t PluginHomeInXR = 

	//Payment status
	int16_t PaymentBtnXRight = 287;
	int16_t PaymentBtnStartShiftY = 18;
	int16_t PaymentBtnQrEndY = 106;
	int16_t PaymentBtnSplitY = 62;
	//int16_t PaymentBtnXRight = 460;
	//int16_t PaymentBtnStartShiftY = 30;
	//int16_t PaymentBtnQrEndY = 170;
	//int16_t PaymentBtnSplitY = 100;
	uint8_t PaymentAlphaBegin = 0;
	uint8_t PaymentAlphaEnd = 255;

	int16_t arrowBeginY = 493;
	//int16_t arrowBeginY = 790;

	const int ScreenTranInDuration = 30;
	const int ScreenTranOutDuration = 30;
	const int SubScreenTranDuration = 30;

	const uint8_t CheckingOutDuration = 30;
};
#endif