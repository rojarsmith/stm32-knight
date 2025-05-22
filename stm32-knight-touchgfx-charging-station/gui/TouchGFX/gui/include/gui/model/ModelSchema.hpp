#ifndef MODEL_SCHEMA_HPP
#define MODEL_SCHEMA_HPP

extern "C" 
{
	enum UXSocketStatus
	{
		UX_SOCKET_AVAILABLE = 1,
		UX_SOCKET_CHARGING = 3,
		UX_SOCKET_FULL = 2,
		UX_SOCKET_ERROR = 4,
		UX_SOCKET_WARNING = 0                		 
	};

	enum UXPlugStatusBitDef
	{
		UX_PLUGIN_IN_OUT     = 0, //IN=0   , OUT=1
		UX_PLUGIN_BLACK_BLUE = 1  //BLACK=0, BLUE=1
	};

	enum UXPlugInOutStatus
	{
		UX_PLUGIN_IN = 0,
		UX_PLUGIN_OUT = 1,
	};

	enum UXPlugUsabilityStatus
	{
		UX_PLUGIN_BLACK = 0,
		UX_PLUGIN_BLUE = 1
	};

	enum UXPlugStatus
	{
		UX_PLUGIN_IN_BLACK  = 0,
		UX_PLUGIN_OUT_BLACK = 1,
		UX_PLUGIN_IN_BLUE   = 2,
		UX_PLUGIN_OUT_BLUE  = 3		
	};

	enum UXLoadingStatus
	{
		UX_LOADING_NONE,
		UX_LOADING_RUNNING
	};

	enum UXCommandStatus
	{
		UX_COMMAND_OFF,
		UX_COMMAND_ON,
		UX_COMMAND_END
	};

	enum UXScreenStatus
	{
		UX_NOT_OPERABLE,
		UX_OPERABLE
	};
      
	enum ScreenNumber
	{
		NULL_SCREEN     = 0, //0x9999,
		SCREEN_BOOT     = 1, //0x9998,
		SCREEN_STANDBY  = 2, //0x0000,
		SCREEN_INTRO  = 3, //0x0100,
		SCREEN_HOME     = 4, //0x0200,
		SCENARIO_2_1    = 0x0201, //DEC=513
		SCENARIO_2_2    = 0x0202,
		SCENARIO_2_3    = 0x0203,
		SCENARIO_2_4    = 0x0204,		
		SCENARIO_2_5    = 0x0205,
		SCENARIO_2_6    = 0x0206,
		SCENARIO_2_7    = 0x0207,
		SCENARIO_2_8    = 0x0208,
		SCREEN_PAYMENT  = 5, //0x0300,
		SCENARIO_3_2    = 0x0302,
		SCENARIO_3_3    = 0x0303,
		SCENARIO_2_30   = 0x0230, //2.10.A
		SCENARIO_2_31   = 0x0231, //2.10.B
		SCENARIO_2_32   = 0x0232, //2.10.C
		SCENARIO_2_33   = 0x0233, //2.12
		SCENARIO_2_34   = 0x0234, //2.13
		SCENARIO_2_36   = 0x0236, //2.11.A
		SCENARIO_2_37   = 0x0237, //2.11.B
		SCENARIO_2_38   = 0x0238, //2.11.C
		SCREEN_PAY_RFID = 6,  //0x0400, //DEC=1024
		SCENARIO_4_1 = 0x0401,
		SCENARIO_4_2 = 0x0402,
		SCENARIO_4_3 = 0x0403,
		SCENARIO_4_4 = 0x0404,
		SCREEN_CONNECT  = 7, //0x0500,
		SCENARIO_5_1    = 0x0501,
		SCENARIO_5_2    = 0x0502,
		SCENARIO_5_3    = 0x0503,
		SCENARIO_5_4    = 0x0504,
		SCREEN_SCREEN1  = 8, //
		SCENARIO_9_1    = 0x0901,
		SCENARIO_9_2    = 0x0902,
		SCENARIO_9_3    = 0x0903,
		SCENARIO_9_4    = 0x0904,
		SCENARIO_9_5    = 0x0905,
		SCENARIO_9_6    = 0x0906
	};

	enum ScenarioGroup
	{
		SGROUP_1,
		SGROUP_4,
		SGROUP_5,
	};

	enum MessageNumber
	{	
		MESSAGE_0  = 0,
		MESSAGE_21 = 201,
		MESSAGE_22,
		MESSAGE_23,
		MESSAGE_24,
		MESSAGE_25,
		MESSAGE_26,
		MESSAGE_27,
		MESSAGE_28,
		MESSAGE_31 = 301,
		MESSAGE_32 = 302,
		MESSAGE_33 = 303,
		MESSAGE_41 = 401,
		MESSAGE_42,
		MESSAGE_43,
		MESSAGE_44 = 404,
		MESSAGE_51 = 501,
		MESSAGE_52,
		MESSAGE_53,
		MESSAGE_54 = 504,
		MESSAGE_E1 = 901,
		MESSAGE_E2, 
		MESSAGE_E3, 
		MESSAGE_E4,	 
		MESSAGE_E5, 
		MESSAGE_E6
	};

	enum ReturnValue
	{
		RETURN_NONE,
		RETURN_OK,
		RETURN_NO
	};

	enum WeatherStyle
	{
		DAY,
		NIGHT
	};

	enum ChargeSocketSelected
	{
		CHARGE_SOCKET_NONE,
		CHARGE_SOCKET_RIGHT,
		CHARGE_SOCKET_LEFT
	};	

	enum ConnectionStatus
	{
		CONNECTION_AVAILABLE,
		CONNECTION_PREPARING,
		CONNECTION_CHARGING,
		CONNECTION_SUSPENDED_EVSE,
		CONNECTION_SUSPENDED_EV,
		CONNECTION_FINISHING
	};

	enum ErrorNumber
	{
		NULL_ERROR,
		ERROR_INVALID_CARD,
		ERROR_CHARGER_IN_USE,
		ERROR_SYSTEM_OFFLINE,
		ERROR_SYSTEM_NOT_AVAILABLE,
		ERROR_CHECK_PLUG,
		ERROR_CABLE_CONNECT_TIMEOUT,
		ERROR_CARD_AUTHORISATION_TIMEOUT
	};
	   
	enum ViewStage
	{		
		VIEW_TRANSITION_IN,
		VIEW_TRANSITION_IN_RUNNING,
		VIEW_TRANSITION_OUT, 
		VIEW_TRANSITION_OUT_RUNNING,
		VIEW_TRANSITIONING,
		VIEW_STANDBY
	};
	   
	enum FooterLayout
	{
		PHONE_AND_CLOCK		
	};

	enum AnimationStyle
	{
		SLIDE_IN,
		SLIDE_OUT,
		SLIDE_IN_FROM_BOTTON,
		SLIDE_OUT_TO_BOTTON,
		STATIC_IN
	};

	enum PlugLockStatusList
	{
		PLUG_UNLOCKED,
		PLUG_LOCKED_IN_STATION		
	};

	enum BrakeStatusList
	{
		CABLE_BREAK_RELEASED,
		CABLE_BREAK_ACTIVE		
	};

	enum LanguageList
	{
		ENGISH = 0,
		SPANISH = 1,
		FRENCH = 2,
		GERMAN =3
	};

	typedef struct ChargeStatusList
	{
		int station_idle;             	//station available, no transaction running
		int authorisation_requested;  	//authorisation request is send to ChargePoint and/or Back Office
		int authorisation_accepted;  	//ChargePoint or Back Office authorised the card
		int plug_unlocked;              //station has unlocked plug
		int plug_removed_from_station;	//plug is taken out of the station
		int plug_connected_to_car;	    //plug is connected to a car
		int start_requested;   	        //start request is send to ChargePoint and/or Back Office
		int start_accepted;         	//ChargePoint or Back Office authorised start of a transaction
		int remote_start;          	    //Back Office has send a remote start to the station
		int charging_state_b;         	//car is connected to the station but is not charging
		int charging_state_c;        	//car is charging
		int charging_on_hold;        	//charging has stoped, transaction still running.
										//Wait for disconnecting car or by using card or app.
		int car_disconnected;        	//plug is removed from the car
		int stop_with_card;        	    //transaction is stoped using card
		int remote_stop;          	    //transaction is stoped using app
		int transaction_ended;       	//transaction is ended
		int remove_plug_from_car;      	//waiting for user to remove plug from the car
		int put_cable_in_station;    	//waiting for user to put plug back in the station
		int thanks_and_goodbye;    	    //plug is put into the station
	} ChargeStatus;
}

typedef struct MachineStatusProperties
{
	//UX Status	
	ScreenNumber ux_screen_id_current;
	ScreenNumber ux_screen_id_previous;
	ScreenNumber ux_screen_id_next;
	ScreenNumber ux_screen_id_current_bk1;
	ScreenNumber ux_screen_id_previous_bk1;
	ScreenNumber ux_screen_id_next_bk1;

	ReturnValue ux_return_value;

	ChargeSocketSelected operation_charge_socket_selected; //Operating side.
	WeatherStyle ux_weather; //decdided by date-time.
	WeatherStyle ux_weather_prev;

	LanguageList ui_language;
	LanguageList ux_culture;

	int ux_drag_selector_vx;
	int ux_drag_selector_vx_prev;
	int ux_drag_selector_x;
	int ux_drag_selector_x_prev;

	bool ux_return_button_clicked;
	bool ux_return_s02button1_clicked;
	bool ux_return_s02button2_clicked;

	int ux_loading_status;
	
	int ux_pop_tran_in_time;
	int ux_pop_tran_out_time;
	int ux_pop_stay_time;
	int ux_delay_0100_to_0200;
	int ux_delay_0200_to_0201;
	int ux_delay_0200_to_0000;
	int ux_socket_status_right;
	int ux_socket_status_right_prev;
	int ux_socket_status_left;
	int ux_socket_status_left_prev;
	bool ux_socket_status_limit;
	int ux_socket_status_limit_target;
	int ux_plugin_in_out_status_right;
	int ux_plugin_in_out_status_right_prev;
	int ux_plugin_in_out_status_left;
	int ux_plugin_usability_status_right;
	int ux_plugin_usability_status_left;
	int ux_plugin_lock_into_car;
	int ux_plugin_lock_into_car_prev;

	bool ux_prox_sensor_detect_user;
	bool ux_prox_sensor_detect_user_prev;
	int ux_home_rfid_status;
	int ux_home_rfid_status_prev;
	int ux_payment_user_selector;
	int ux_payment_user_selector_prev;
	int ux_payment_selector;
	int ux_payment_selector_prev;
	int ux_open_checked;
	int ux_open_checked_prev;
	int ux_payment_checked;
	int ux_payment_checked_prev;
	int ux0400_plug_right_status;
	int ux0400_plug_left_status;
	char ux_qr_data[257];
	char ux_phone[21];
	char ux_datetime[21];
	char ux_per_kwh[6];
	char ux_max_kw[6];
	bool ux_popup_command_lock;
	bool ux_popup_command_lock_time;
	int ux_change_screen;
	int ux_change_screen_prev;
	bool ux_popup_trigger_;
	bool ux_popup_trigger_prev_;
	int ux_popup_number;
	int ux_popup_number_prev;
	int ux_popup_number_bk1;
	int ux_close_popup;
	int ux_close_popup_prev;
	bool ux_popup_number_virtual;
	char ux_duration_h[3];
	char ux_duration_m[3];
	char ux_energy[7];
	char ux_paid[7];
	char ux_charger_id[21];
	UXCommandStatus ux_output_command_trigger;
	UXCommandStatus ux_output_command_trigger_prev;
	int ux_output_command_trigger_count;
	UXScreenStatus ux_screen_status;
	UXScreenStatus ux_screen_status_prev;
	bool popup_opened;
	int ui_tick;

	//Pole status	
	int pole_alpha;
	int pole_previous_x;
	int pole_previous_y;
	int pole_previous_width;
	int pole_previous_height;

	//Socket status
	int socket_right_previous_x;
	int socket_right_previous_y;
	int socket_right_previous_width;
	int socket_right_previous_height;
	int socket_right_previous_alpha;
	int socket_right_image_id_small;
	int socket_right_image_id_large;	
	int socket_left_previous_x;
	int socket_left_previous_y;
	int socket_left_previous_width;
	int socket_left_previous_height;
	int socket_left_previous_alpha;
	int socket_left_image_id_small;
	int socket_left_image_id_large;
	
	//Plug status
	int plugin_right_x;
	int plugin_right_y;
	int plugin_right_width;
	int plugin_right_height;
	int plugin_right_alpha;
	int plugin_right_image_id_small;
	int plugin_right_image_id_large;
	int plugin_left_x;
	int plugin_left_y;
	int plugin_left_width;
	int plugin_left_height;
	int plugin_left_alpha;
	int plugin_left_image_id_small;
	int plugin_left_image_id_large;

	//title status
	int title_alpha;
	int subtitle_alpha;

	//footer status
	int footer_y;

	//bus => display
	//int charge_status;
	//int connection_status;
	//int plug_lock_status;
	//int brake_status;
	//int error_number;

	//int connection_sataus;
	//int current_power;
	//int charged_energy;
	//int charge_time;

	//int price_kwh;
	//int currency;
	//int language;
	//char chargepoint_serial[9];
	//char chargebox_serial_no_master[9];
	//char chargebox_serial_no_slave[9];

	//display => bus
	//int screen_selection;
	//int current_screen_number;

	int ack; //Reserve
} MachineStatus;

class SchemaFunction
{
public:
	static ScenarioGroup getScenarioGroup(ScreenNumber scenario)
	{
		switch (scenario)
		{
		case NULL_SCREEN:
		case SCREEN_BOOT:
		case SCREEN_STANDBY:
		case SCREEN_INTRO:
			break;		
		case SCREEN_PAY_RFID:
			return SGROUP_4;
			break;
		case SCREEN_CONNECT:
		case SCENARIO_5_2:
		case SCENARIO_5_3:
		case SCENARIO_5_4:
			return SGROUP_5;
			break;			
		case SCREEN_SCREEN1:
		case SCENARIO_9_1:
		case SCENARIO_9_2:
		case SCENARIO_9_3:
		case SCENARIO_9_4:
		case SCENARIO_9_5:
		case SCENARIO_9_6:
			break;		
		}		

		return SGROUP_1;
	}
};


#endif /* MODEL_SCHEMA_HPP */