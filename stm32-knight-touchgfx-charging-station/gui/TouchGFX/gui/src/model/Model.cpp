#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/model/ModelSchema.hpp>

#ifdef SIMULATOR
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <direct.h>
#include "json/json.hpp"
using namespace std;
using json = nlohmann::json;
#endif

// Communication
#ifdef __cplusplus
extern "C"
{
#endif 
#ifndef SIMULATOR       
#include <string.h>
#if 1 // USART Debug Printf examlep check
int dbg = 0;
#endif

	// extern  bool EVBOX_FORMAT_API_En;
	// extern _EVBOX_FORMAT_API R_EVBOX_FORMAT_API;
	// extern _EVBOX_FORMAT_API L_EVBOX_FORMAT_API;
	// _EVBOX_FORMAT_API* msg;

#endif
#ifdef __cplusplus
}
#endif 

#ifdef SIMULATOR       
const string Model::input_json_filename = "debug_input_data.json";
const string Model::output_json_filename = "debug_output_data.json";
const string Model::path_output = "output";
#endif 

Model::Model() : modelListener(0), tick_(0), ScreenNumberBuf(0xffff),
Communictaion_WaitCtn(COMMUNICATIONTIMER_DURATION)
{
	mstatus_.ux_return_button_clicked = false;

#ifdef SIMULATOR
	//std::ifstream ifs("debug_input_data.json", std::ios::out);
	std::ifstream ifs(input_json_filename, std::ios::out);
	if (true != ifs.is_open())
	{
		string path = "../../../../test/";
		path.append(input_json_filename, 0, sizeof(input_json_filename));
		std::ifstream src(path, std::ios::binary);
		std::ofstream dst(input_json_filename, std::ios::binary);
		dst << src.rdbuf();
		src.close();
		dst.close();
	}
	ifs.close();

	struct stat info;
	if (stat(path_output.c_str(), &info) != 0)
	{
		_mkdir(path_output.c_str());
	}

	if (stat(output_json_filename.c_str(), &info) == 0)
	{
		fstream file(output_json_filename, ios::out);
	}
#else
	if (false)
		mstatus_.ux_weather = WeatherStyle(0);
	else
		mstatus_.ux_weather = WeatherStyle::NIGHT;
	mstatus_.ux_prox_sensor_detect_user = true;
	mstatus_.ux_delay_0100_to_0200 = TimeOut_5sec;  //5sec
	mstatus_.ux_socket_status_right = UX_SOCKET_AVAILABLE;
	mstatus_.ux_socket_status_left = UX_SOCKET_AVAILABLE;
	mstatus_.ux_change_screen = 0;
	EnterPopupDelay = TimeOut_10sec;
	ExitPopupDelay = TimeOut_20sec;
	time_out = TimeOut_20sec;
	Use_App_L = false;
	Use_App_R = false;
#endif
}

void Model::tick()
{
    mstatus_.ux_weather_prev = mstatus_.ux_weather;
    mstatus_.ux_plugin_in_out_status_right_prev = mstatus_.ux_plugin_in_out_status_right;
    mstatus_.ux_home_rfid_status_prev = mstatus_.ux_home_rfid_status;
    mstatus_.ux_popup_trigger_prev_ = mstatus_.ux_popup_trigger_;
    mstatus_.ux_popup_number_prev = mstatus_.ux_popup_number;
    mstatus_.ux_change_screen_prev = mstatus_.ux_change_screen;
    mstatus_.ux_close_popup_prev = mstatus_.ux_close_popup;
    mstatus_.ux_socket_status_right_prev = mstatus_.ux_socket_status_right;
    mstatus_.ux_socket_status_left_prev = mstatus_.ux_socket_status_left;
    mstatus_.ux_open_checked_prev = mstatus_.ux_open_checked;
    mstatus_.ux_payment_checked_prev = mstatus_.ux_payment_checked;
    mstatus_.ux_plugin_lock_into_car_prev = mstatus_.ux_plugin_lock_into_car;
    mstatus_.ux_payment_user_selector_prev = mstatus_.ux_payment_user_selector;
    mstatus_.ux_payment_selector_prev = mstatus_.ux_payment_selector;
    mstatus_.ux_screen_status_prev = mstatus_.ux_screen_status;
    mstatus_.ux_prox_sensor_detect_user_prev = mstatus_.ux_prox_sensor_detect_user;
#ifdef SIMULATOR
    bool debug_input_data_modified = false;
    struct stat result;
    if (stat(Model::input_json_filename.c_str(), &result) == 0)
    {
        auto mod_time = result.st_mtime;
        if (mod_time != mod_json_time_prev_)
        {
            debug_input_data_modified = true;
        }
        mod_json_time_prev_ = mod_time;
    }

    if (0 == tick_ % (MODEL_DATA_SCAN_TIME))
    {
        readJsonToMS();
    }
    if (mstatus_.ux_return_button_clicked)
    {
        mstatus_.ux_return_button_clicked = false;
    }
    if (mstatus_.ux_return_s02button1_clicked)
    {
        mstatus_.ux_return_s02button1_clicked = false;
    }
    if (mstatus_.ux_return_s02button2_clicked)
    {
        mstatus_.ux_return_s02button2_clicked = false;
    }
#endif


#ifndef SIMULATOR

    if (mstatus_.ux_output_command_trigger == UX_COMMAND_END) {
        //  if ((mstatus_.ux_screen_status==UX_OPERABLE)&&(ScreenNumberBuf !=     \
        //      (unsigned short)mstatus_.ux_screen_id_current)) {                  

        //      if (ScreenNumberBuf != (unsigned short)mstatus_.ux_screen_id_current) {
        pp_count = 0;
        //      }
        ScreenNumberBuf = (unsigned short)mstatus_.ux_screen_id_current;
        ScrNumBuf = CheckScrId(mstatus_.ux_screen_id_current);

        switch (mstatus_.operation_charge_socket_selected) {
        case CHARGE_SOCKET_NONE:
            if (ScrNumBuf != 0) {
                if (cancel_select) {
                    CancelScr = CheckScrId(mstatus_.ux_screen_id_previous);
                    ScrSel(L_side, cancel_select, CancelScr);
                    ScrSel(R_side, cancel_select, CancelScr);
                    cancel_select = 0;
                }
                if (ScrNumBuf == 1) ScrNumBuf = 0;
                ScrSel(L_side, 1, ScrNumBuf);
                ScrSel(R_side, 1, ScrNumBuf);
            }
            break;
        case CHARGE_SOCKET_RIGHT:
            if (ScrNumBuf != 1) {
                if (cancel_select) {
                    ScrSel(R_side, cancel_select, ScrNumBuf);
                    ScrSel(L_side, cancel_select, ScrNumBuf);
                    cancel_select = 0;
                }
                else {
                    if ((ScrNumBuf == 0x0265) && (mstatus_.ux_screen_id_previous == SCREEN_HOME)) {
                        ScrSel(R_side, 1, ScrNumBuf);
                        ScrSel(R_side, 1, ScrNumBuf);
                        ScrSel(L_side, 1, ScrNumBuf);
                        ScrSel(L_side, 1, ScrNumBuf);
                    }
                    else {
                        ScrSel(L_side, 1, ScrNumBuf);
                        ScrSel(R_side, 1, ScrNumBuf);
                    }
                }
            }
            break;
        case CHARGE_SOCKET_LEFT:
            if (ScrNumBuf != 1) {
                if (cancel_select) {
                    ScrSel(L_side, cancel_select, ScrNumBuf);
                    ScrSel(R_side, cancel_select, ScrNumBuf);
                    cancel_select = 0;
                }
                else {
                    if ((ScrNumBuf == 0x0265) && (mstatus_.ux_screen_id_previous == SCREEN_HOME)) {
                        ScrSel(L_side, 1, ScrNumBuf);
                        ScrSel(L_side, 1, ScrNumBuf);
                        ScrSel(R_side, 1, ScrNumBuf);
                        ScrSel(R_side, 1, ScrNumBuf);
                    }
                    else {
                        ScrSel(L_side, 1, ScrNumBuf);
                        ScrSel(R_side, 1, ScrNumBuf);
                    }
                }
            }
            break;
        default:
            break;
        }
    }

    User_detected = GetProximity();
    //    switch(mstatus_.ux_screen_id_current){
    switch (ScreenNumberBuf) {
    case SCREEN_INTRO:
        pop_one = true;
        enter_standby = false;
        mstatus_.ux_delay_0200_to_0000 = TimeOut_30sec;
        break;

    case SCREEN_STANDBY:
        if (mstatus_.popup_opened) {
            ccount = 0;
            PopUp_Close(1);
            break;
        }
        if (home_flag) {
            mstatus_.ux_change_screen = GO_HOME;
        }
        else if ((enter_standby) && (++ccount > 10)) {
            mstatus_.ux_prox_sensor_detect_user = false;
            enter_standby = false;
            ccount = 0;
            mstatus_.ux_change_screen = 0;
        }
        else {
            mstatus_.ux_prox_sensor_detect_user = User_detected;
            mstatus_.ux_delay_0100_to_0200 = TimeOut_5sec;    //300;
        }

        break;
    case SCREEN_HOME:
        if (home_flag) {
            home_flag = false;
            pop_status = true;
            mstatus_.popup_opened = false;    // foced to change popup status
            mstatus_.ux_popup_number = MESSAGE_0;
            mstatus_.ux_prox_sensor_detect_user = true;
            mstatus_.ux_change_screen = 0;
            if (enter_standby) {
                mstatus_.ux_change_screen = GO_STANDBY;
                enter_standby = User_detected;
                ccount = 0;
            }
            time_out = TimeOut_20sec;
        }
        else {
            mstatus_.ux_prox_sensor_detect_user = User_detected;
        }
        drag_flag = (mstatus_.ux_drag_selector_vx < 2) && (mstatus_.ux_drag_selector_vx > -2);

        if (charge_stop) {
            PopUp_Open(COMMUNICATIONTIMER_DURATION + 1, (MessageNumber)charge_stop);        //MESSAGE_22 ~ 28;                          
        }
        else if (pop_one) {
            PopUp_Open(EnterPopupDelay, MESSAGE_21);
        }
        pop1[0] = true;
        pop1[1] = true;
        pop1[2] = true;

        if (tick_ & 0x10) {         //update weather status per 16 ticks
            if (false) {
                mstatus_.ux_weather = WeatherStyle(0);
            }
            else {
                mstatus_.ux_weather = WeatherStyle::NIGHT;
            }
        }
        break;

    case SCENARIO_2_2:
        cancel_select = 1;
    case SCENARIO_2_3:
    case SCENARIO_2_4:
        charge_stop = 0;
    case SCENARIO_2_5:
        session_stop = false;
    case SCENARIO_2_1:        //close MESSAGE_21
    case SCENARIO_2_36:       //-->0x026F
    case SCENARIO_2_37:       //-->0x0270
    case SCENARIO_2_38:       //-->0x0271   
        if (mstatus_.ux_return_value == RETURN_OK) {
            mstatus_.ux_popup_number = MESSAGE_0;
        }
        PopUp_Close(ExitPopupDelay);
        if (pop_status == false) {
            if (ScreenNumberBuf == SCENARIO_2_5) {
                charge_stop = MESSAGE_26;
                ccount = 0;
                break;
            }
            else charge_stop = 0;
            idx = ScreenNumberBuf - 0x0236;
            pop1[0] = true;
            pop1[1] = true;
            pop1[2] = true;
            if (idx < 3) {
                pop1[idx] = false;
            }
        }
        break;
    case SCENARIO_2_30:                 //show info. using charge cad, 2.10.A-->0x0265
        if (home_flag) {
            home_flag = false;
            pop_status = true;
            //              mstatus_.popup_opened = false;    // foced to change popup status
            mstatus_.ux_popup_number = MESSAGE_0;
            mstatus_.ux_change_screen = 0;
        }
        else if (mstatus_.ux_return_value == RETURN_OK) {
            home_flag = false;
        }
    case SCENARIO_2_31:                //show info. using credit cad, 2.10.B-->0x0266
    case SCENARIO_2_32:                //show info. using qr code, 2.10.C-->0x0267
        if (mstatus_.ux_return_button_clicked) {
            mstatus_.ux_return_button_clicked = false;
            mstatus_.ux_change_screen = GO_HOME;
            cancel_select = 1;
            pp_count = 0;
            home_flag = true;
            break;
        }
        idx = ScreenNumberBuf - 0x0230;
        if (pop1[idx]) {
            PopUp_Open(EnterPopupDelay, (MessageNumber)(ScreenNumberBuf - 259));
        }
        break;

    case SCENARIO_2_33:
        if (home_flag) {
            mstatus_.ux_change_screen = GO_PAYMENT;
        }
        break;
    case SCENARIO_4_1:
    case SCENARIO_5_2:
    case SCENARIO_5_3:
        if (home_flag) {
            mstatus_.ux_change_screen = GO_HOME;
        }
        break;
    case SCENARIO_4_3:
        if (!home_flag) {
            if (mstatus_.ux_return_button_clicked) {
                mstatus_.ux_return_button_clicked = false;
                mstatus_.ux_popup_number = MESSAGE_44;
            }
            else {
                PopUp_Open(EnterPopupDelay, MESSAGE_44);
            }
        }
        else {
            if (mstatus_.ux_screen_status == UX_OPERABLE) {
                mstatus_.ux_change_screen = GO_HOME;
            }
        }
        break;
    case SCREEN_CONNECT:        //SCREEN NUMBER :5.0  
        if (!home_flag) {
            if (mstatus_.ux_return_button_clicked) {
                mstatus_.ux_return_button_clicked = false;
                mstatus_.ux_popup_number = MESSAGE_51;
                session_stop = true;
            }
            else if (PopUp_Open(EnterPopupDelay, MESSAGE_51)) {
                session_stop = true;
            }
        }
        else {
            if (mstatus_.ux_screen_status == UX_OPERABLE) {
                mstatus_.ux_change_screen = GO_HOME;
            }
        }
        break;

    case SCENARIO_5_1:
        if ((PopUp_Close(TimeOut_20sec) == false) && session_stop) {
            home_flag = true;
            charge_stop = MESSAGE_22;
            break;
        }
    case SCENARIO_4_4:
        if (mstatus_.ux_return_value != RETURN_NONE) {
            pop_status = false;
            mstatus_.ux_popup_number = MESSAGE_0;
            session_stop = false;
            if (mstatus_.ux_return_value == RETURN_OK) {
                home_flag = true;
                session_stop = true;
                charge_stop = MESSAGE_22;
            }
        }
        break;

    case SCENARIO_2_6:
        //          if (charge_stop == MESSAGE_26) charge_stop = 0;
        if (User_detected) {
            pp_count = 0;
            //            if ((++ccount % TimeOut_120sec == 0)||       \
            //                  (mstatus_.ux_return_value == RETURN_OK)) {
            if (++ccount > TimeOut_120sec) {
                enter_standby = true;
                home_flag = true;
                PopUp_Close(1);
                charge_stop = 0;
            }
            //          } else if ((PopUp_Close(TimeOut_5sec) == false)||       \
            //                     (mstatus_.ux_return_value == RETURN_OK)) {
        }
        else if (PopUp_Close(TimeOut_5sec) == false) {
            enter_standby = false;
            home_flag = true;
            charge_stop = (Use_App_L || Use_App_R) ? MESSAGE_28 : MESSAGE_27;
        }
        break;

    case SCENARIO_2_7:
    case SCENARIO_2_8:
        charge_stop = 0;
        enter_standby = true;
    case SCENARIO_5_4:

    case SCENARIO_9_1:
    case SCENARIO_9_2:
    case SCENARIO_9_3:
    case SCENARIO_9_4:
    case SCENARIO_9_5:
    case SCENARIO_9_6:
        if ((PopUp_Close(TimeOut_20sec) == false) || \
            (mstatus_.ux_return_value == RETURN_OK)) {
            home_flag = true;
        }
        Errpopup = 0;
        break;

    case NULL_SCREEN:

    default:

        break;
    }

    if (mstatus_.ux_screen_id_next == NULL_SCREEN) {
        if (mstatus_.ux_output_command_trigger != UX_COMMAND_ON)
        {    // EVBox_CommunicationIDLE = false;   //ACK    
        }
    }
    else 
    {
        if (mstatus_.ux_output_command_trigger == UX_COMMAND_ON) {
            // EVBox_CommunicationIDLE = true;   //NACK
            Communictaion_WaitCtn = COMMUNICATIONTIMER_DURATION;
        }
    }

    if (Communictaion_WaitCtn > 0) { // waiting UI Process Used 5 tick 

        Communictaion_WaitCtn--;
        if (Communictaion_WaitCtn == 0) {

            Communictaion_WaitCtn = COMMUNICATIONTIMER_DURATION;

            if (1) {
                if (!mstatus_.popup_opened) {
                    // R_EVBOX_FORMAT_API_En = false;
                    Msg_Conver(0);
                }
                else {
                    if (1) {
                        PopUp_Close(1);
                        session_stop = false;
                    }
                }
            }
            else if (1) {
                if (!mstatus_.popup_opened) {
                    // L_EVBOX_FORMAT_API_En = false;
                    Msg_Conver(1);
                }
                else {
                    if (1) {
                        PopUp_Close(1);
                        session_stop = false;
                    }
                }
            }
        }
    }


#endif

    if (UXCommandStatus::UX_COMMAND_OFF != mstatus_.ux_output_command_trigger)
    {
#ifdef SIMULATOR
        writeMSToJson();
#endif	        
    }

    mstatus_.ux_popup_trigger_ = false;
    mstatus_.ux_output_command_trigger = UXCommandStatus::UX_COMMAND_OFF;
    mstatus_.ui_tick = tick_;

    tick_++;
    if (tick_ >= (60 * 1000))
    {
        tick_ = 0;
    }
}

#ifdef SIMULATOR
void Model::readJsonToMS()
{
    //Input to UX.
    std::ifstream ifs(input_json_filename);
    std::string content((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));
    ifs.close();

    //Debug
    //printf("%s", content.c_str());
    //fflush(0);

    json j = json::parse(content);

    int v1_test = j["edt"][0]["attribute"]["age"]["value"].get<int>();

    int ux_pop_tran_in_time = j["ux_pop_tran_in_time"].get<int>();
    int ux_pop_tran_out_time = j["ux_pop_tran_out_time"].get<int>();
    int ux_pop_stay_time = j["ux_pop_stay_time"].get<int>();
    int ux_delay_0100_to_0200 = j["ux_delay_0100_to_0200"].get<int>();
    int ux_delay_0200_to_0201 = j["ux_delay_0200_to_0201"].get<int>();
    int ux_delay_0200_to_0000 = j["ux_delay_0200_to_0000"].get<int>();
    int ux_socket_status_right = j["ux_socket_status_right"].get<int>();
    int ux_socket_status_left = j["ux_socket_status_left"].get<int>();
    int ux_plugin_in_out_status_right = j["ux_plugin_in_out_status_right"].get<int>();
    int ux_plugin_in_out_status_left = j["ux_plugin_in_out_status_left"].get<int>();
    int ux_plugin_usability_status_right = j["ux_plugin_usability_status_right"].get<int>();
    int ux_plugin_usability_status_left = j["ux_plugin_usability_status_left"].get<int>();
    int ux_plugin_lock_into_car = j["ux_plugin_lock_into_car"].get<int>();
    int ux_weather = j["ux_weather"].get<int>();
    int ux_prox_sensor_detect_user = j["ux_prox_sensor_detect_user"].get<int>();
    int ux_home_rfid_status = j["ux_home_rfid_status"].get<int>();
    int ux_payment_user_selector = j["ux_payment_user_selector"].get<int>();
    int ux_payment_selector = j["ux_payment_selector"].get<int>();
    int ux_open_checked = j["ux_open_checked"].get<int>();
    int ux_payment_checked = j["ux_payment_checked"].get<int>();
    int ux0400_plug_right_status = j["ux0400_plug_right_status"].get<int>();
    int ux0400_plug_left_status = j["ux0400_plug_left_status"].get<int>();
    string ux_qr_data = j["ux_qr_data"].get<string>();
    string ux_phone = j["ux_phone"].get<string>();
    string ux_datetime = j["ux_datetime"].get<string>();
    string ux_per_kwh = j["ux_per_kwh"].get<string>();
    string ux_max_kw = j["ux_max_kw"].get<string>();
    int ux_culture = j["ux_culture"].get<int>();
    int ux_change_screen = j["ux_change_screen"].get<int>();
    int ux_popup_number = mstatus_.ux_popup_number;
    if (!mstatus_.ux_popup_trigger_)
    {
        ux_popup_number = j["ux_popup_number"].get<int>();
    }
    int ux_close_popup = j["ux_close_popup"].get<int>();
    string ux_duration_h = j["ux_duration_h"].get<string>();
    string ux_duration_m = j["ux_duration_m"].get<string>();
    string ux_energy = j["ux_energy"].get<string>();
    string ux_paid = j["ux_paid"].get<string>();
    string ux_charger_id = j["ux_charger_id"].get<string>();

    mstatus_.ux_pop_tran_in_time = ux_pop_tran_in_time,
        mstatus_.ux_pop_tran_out_time = ux_pop_tran_out_time,
        mstatus_.ux_pop_stay_time = ux_pop_stay_time,
        mstatus_.ux_delay_0100_to_0200 = ux_delay_0100_to_0200,
        mstatus_.ux_delay_0200_to_0201 = ux_delay_0200_to_0201;
    mstatus_.ux_delay_0200_to_0000 = ux_delay_0200_to_0000;
    mstatus_.ux_socket_status_right = ux_socket_status_right,
        mstatus_.ux_socket_status_left = ux_socket_status_left,
        mstatus_.ux_plugin_in_out_status_right = ux_plugin_in_out_status_right;
    mstatus_.ux_plugin_in_out_status_left = ux_plugin_in_out_status_left;
    mstatus_.ux_plugin_usability_status_right = ux_plugin_usability_status_right;
    mstatus_.ux_plugin_usability_status_left = ux_plugin_usability_status_left;
    mstatus_.ux_plugin_lock_into_car = ux_plugin_lock_into_car;
    switch (ux_weather)
    {
    case 1:
        mstatus_.ux_weather = WeatherStyle::NIGHT;
        break;
    default:
        mstatus_.ux_weather = WeatherStyle::DAY;
        break;
    }
    mstatus_.ux_prox_sensor_detect_user = ux_prox_sensor_detect_user;
    mstatus_.ux_home_rfid_status = ux_home_rfid_status;
    mstatus_.ux_payment_user_selector = ux_payment_user_selector;
    mstatus_.ux_payment_selector = ux_payment_selector;
    mstatus_.ux_open_checked = ux_open_checked;
    mstatus_.ux_payment_checked = ux_payment_checked;
    mstatus_.ux0400_plug_right_status = ux0400_plug_right_status;
    mstatus_.ux0400_plug_left_status = ux0400_plug_left_status;
    strcpy_s(mstatus_.ux_qr_data, 257, ux_qr_data.c_str());
    strcpy_s(mstatus_.ux_phone, 21, ux_phone.c_str());
    strcpy_s(mstatus_.ux_datetime, 21, ux_datetime.c_str());
    strcpy_s(mstatus_.ux_per_kwh, 6, ux_per_kwh.c_str());
    strcpy_s(mstatus_.ux_max_kw, 6, ux_max_kw.c_str());
    if (0 > ux_culture || 4 < ux_culture)
    {
        mstatus_.ux_culture = LanguageList::ENGISH;
    }
    else
    {
        mstatus_.ux_culture = (LanguageList)ux_culture;
    }
    mstatus_.ux_change_screen = ux_change_screen;
    mstatus_.ux_popup_number = ux_popup_number;
    mstatus_.ux_close_popup = ux_close_popup;
    strcpy_s(mstatus_.ux_duration_h, 3, ux_duration_h.c_str());
    strcpy_s(mstatus_.ux_duration_m, 3, ux_duration_m.c_str());
    strcpy_s(mstatus_.ux_energy, 7, ux_energy.c_str());
    strcpy_s(mstatus_.ux_paid, 7, ux_paid.c_str());
    strcpy_s(mstatus_.ux_charger_id, ux_charger_id.c_str());
}

void Model::writeMSToJson()
{
    mstatus_.ux_output_command_trigger_count++;

    //Output from UX.
    json jo;
    //Send from display.
    jo["ux_screen_id_next"] = mstatus_.ux_screen_id_next;
    jo["ux_screen_id_current"] = mstatus_.ux_screen_id_current;
    jo["ux_screen_id_previous"] = mstatus_.ux_screen_id_previous;
    jo["ux_screen_id_next_bk1"] = mstatus_.ux_screen_id_next_bk1;
    jo["ux_screen_id_current_bk1"] = mstatus_.ux_screen_id_current_bk1;
    jo["ux_screen_id_previous_bk1"] = mstatus_.ux_screen_id_previous_bk1;
    //Command must be send.
    jo["ux_output_command_trigger"] = mstatus_.ux_output_command_trigger;
    //Each ux_output_command_trigger 0=>1 will +1
    jo["ux_output_command_trigger_count"] = mstatus_.ux_output_command_trigger_count;
    //Operable. 0=OPERABLE, 1=OPERABLE, Other=0.
    jo["ux_screen_status"] = mstatus_.ux_screen_status;

    jo["operation_charge_socket_selected"] = mstatus_.operation_charge_socket_selected;
    std::ofstream ofs(output_json_filename, std::ofstream::out | std::ofstream::app);
    ofs << std::setw(4) << jo << std::endl;
}
#endif

MachineStatus* Model::getMachineStatus()
{
    return &mstatus_;
}

#ifndef SIMULATOR  
bool Model::PopUpProcess(bool pop_en, int enter_delay, int exit_delay, MessageNumber mesg)
{
    if (!pop_en) {
        PopUp_Close(1);
        return pop_status;
    }

    if (pop_status == false) {      //Waiting timeout to popup message
        PopUp_Open(enter_delay, mesg);
    }
    else {                         //Waiting timeout to close message
        PopUp_Close(exit_delay);
    }
    return pop_status;
}
bool Model::PopUp_Open(int enter_delay, MessageNumber mesg)
{
    if ((mstatus_.popup_opened) || (mstatus_.ux_return_s02button1_clicked)) {
        pp_count = 0;
        pop_status = true;
        mstatus_.ux_return_s02button1_clicked = false;
        pop_one = false;
    }
    else if ((++pp_count >= enter_delay) && (mstatus_.ux_screen_status == UX_OPERABLE)) {
        if ((drag_flag) || (ScreenNumberBuf != SCREEN_HOME)) { //Don't allowed pop-up when sliding
            mstatus_.ux_popup_number = mesg;
        }
        pp_count = 0;
        pop_status = true;
        pop_one = false;
    }
    return pop_status;
}
bool Model::PopUp_Close(int exit_delay)
{
    if (!mstatus_.popup_opened) {
        pp_count = 0;
        pop_status = false;
        mstatus_.ux_popup_number = MESSAGE_0;
    }
    else if (++pp_count >= exit_delay) {
        if ((mstatus_.popup_opened) && (mstatus_.ux_screen_status == UX_OPERABLE)) {
            //    if ((mstatus_.popup_opened)&&(mstatus_.ux_output_command_trigger==UX_COMMAND_OFF)) {
            if (mstatus_.ux_close_popup) {
                mstatus_.ux_close_popup = 0;
            }
            else {
                mstatus_.ux_close_popup = 1;
                mstatus_.ux_popup_number = MESSAGE_0;
                pp_count = 0;
                pop_status = false;
                pop_one = false;
            }
        }
    }
    return pop_status;
}
void Model::ScrSel(bool RL, unsigned short sel, unsigned short scr)
{
    unsigned short boxid;
    if (RL) {
        // msg = (&L_EVBOX_FORMAT_API);
        // boxid = EVBOX_ChargeBox_Lplug;
    }
    else {
        // msg = (&R_EVBOX_FORMAT_API);
        // boxid = EVBOX_ChargeBox_Rplug;
    }

    // msg->FORMAT_Selecttion.Screen = sel & 0x00ff;
    // msg->FORMAT_Selecttion.Current_screen_num = scr;
    // msg->FORMAT_Selecttion.Proximity = User_detected;//(char)GetProximity();
    // msg->FORMAT_Selecttion.DayNight = (char)mstatus_.ux_weather;

    // msg->EVBox_FormatEvent |= Event_SELECT_SCREEN;
    // EVBOX_Transimt_ScreenSelect_API(boxid, &msg->FORMAT_Selecttion);
    // EVBox_CommunicationIDLE = false;
}

unsigned short Model::CheckScrId(ScreenNumber scr_id)
{
    unsigned short scrid16;

    scrid16 = (unsigned short)scr_id;
    switch (scr_id)
    {
        //    case NULL_SCREEN     : //0, //0x9999,
        //      scrid16 = 0x1;
        //      break;
        //    case SCREEN_BOOT     : // 1, //0x9998,
        //      scrid16 = 0x0;
        //      break;
    case SCREEN_STANDBY: // 2, //0x0000,
    case SCREEN_INTRO: // 3, //0x0100,
    case SCREEN_HOME: // 4, //0x0200,
    case SCREEN_PAYMENT: // 5, //0x0300,
    case SCREEN_PAY_RFID: // 6, //0x0400,
    case SCREEN_CONNECT: // 7, //0x0500,
    case SCREEN_SCREEN1: // 8 //
        scrid16 = (scrid16 - 2) << 8;
        break;
    case SCENARIO_2_30: // 0x0230, 2.10.A -> 0x0265 
    case SCENARIO_2_31: // 0x0231, 2.10.B -> 0x0266
    case SCENARIO_2_32: // 0x0232, 2.10.C -> 0x0267
        scrid16 += 0x35;
        break;
    case SCENARIO_2_36: // 0x0236, 2.11.A -> 0x026F
    case SCENARIO_2_37: // 0x0237, 2.11.B -> 0x0270
    case SCENARIO_2_38: // 0x0238, 2.11.C -> 0x0271  
        scrid16 += 0x39;
        break;
    case SCENARIO_2_33: // 0x0233, 2.12 -> 0x020C
    case SCENARIO_2_34: // 0x0234, 2.13 -> 0x020D 
        scrid16 -= 0x27;
        break;

    default:
        break;
    }
    return scrid16;
}

void Model::Msg_Conver(bool RL)
{
 

}
unsigned short  Model::GetRS485()
{
    return 0;
}
void Model::SetBacklight(bool enable)
{

}

bool Model::GetBacklight()
{
    return true;
}
bool Model::GetProximity()
{
#ifndef SIMULATOR   
    return true;
#endif  
}
#endif
