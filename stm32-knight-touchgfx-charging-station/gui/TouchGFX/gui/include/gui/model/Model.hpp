#ifndef MODEL_HPP
#define MODEL_HPP

#include <gui/model/ModelSchema.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/common/CommonConstant.hpp>

#ifdef __cplusplus
extern "C"
{
#endif 
#ifdef SIMULATOR
#include <sys/stat.h>
#endif
#ifdef __cplusplus
}
#endif 

class ModelListener;
// 14.548ms/tick
#define TimeOut_5sec    344
#define TimeOut_10sec   687     //714
#define TimeOut_20sec   1375    //1428
#define TimeOut_30sec   2062    //2142
#define TimeOut_120sec  8248    //8568
#define TFT_FPS         1100    //1097
#define FPS_DIV         4
#define GO_STANDBY      2
#define GO_HOME         4
#define GO_PAYMENT      5
#define L_side           1
#define R_side           0

/**
 * The Model class defines the data model in the model-view-presenter paradigm.
 * The Model is a singular object used across all presenters. The currently active
 * presenter will have a pointer to the Model through deriving from ModelListener.
 *
 * The Model will typically contain UI state information that must be kept alive
 * through screen transitions. It also usually provides the interface to the rest
 * of the system (the backend). As such, the Model can receive events and data from
 * the backend and inform the current presenter of such events through the modelListener
 * pointer, which is automatically configured to point to the current presenter.
 * Conversely, the current presenter can trigger events in the backend through the Model.
 */
class Model
{
public:
    Model();

    /**
     * Sets the modelListener to point to the currently active presenter. Called automatically
     * when switching screen.
     */
    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    /**
     * This function will be called automatically every frame. Can be used to e.g. sample hardware
     * peripherals or read events from the surrounding system and inject events to the GUI through
     * the ModelListener interface.
     */
    void tick();

    MachineStatus* getMachineStatus();

    unsigned short GetRS485();
    void SetBacklight(bool enable);
    bool GetBacklight();
    bool GetProximity();
    void Msg_Conver(bool RL);
    void ScrSel(bool RL, unsigned short sel, unsigned short scr);
    unsigned short CheckScrId(ScreenNumber scr_id);
    bool PopUpProcess(bool pop_status, int enter_delay, int exit_delay, MessageNumber mesg);
    bool PopUp_Close(int exit_delay);
    bool PopUp_Open(int enter_delay, MessageNumber mesg);
protected:
    /**
     * Pointer to the currently active presenter.
     */
    ModelListener* modelListener;

    static const int COMMUNICATIONTIMER_DURATION = 5;
    int Communictaion_WaitCtn;
    bool ux_weather_Init, PopTrigger;
    bool pop_status = false;
    unsigned short ScreenNumberBuf, ScrNumBuf, CancelScr, cancel_select;
private:
    int tick_, time_out;
    unsigned short charge_stop, Errpopup = 0, idx;
    unsigned short EnterPopupDelay, ExitPopupDelay, ccount = 0, pp_timeout, pp_count = 0;
    MachineStatus mstatus_;
    CommonConstant& cc_ = CommonConstant::getInstance();
    DateTime datetime_;
    bool User_detected, pop_one = true, enter_standby = false;
    bool pop1[3];
    bool popup_flag = false, session_stop = false, home_flag = false;
    bool Use_App_L, Use_App_R, Use_CreditCard, drag_flag;
#ifdef SIMULATOR
    const static string input_json_filename;
    const static string output_json_filename;
    const static string path_output;
    time_t mod_json_time_prev_;

    void readJsonToMS();
    void writeMSToJson();
#endif
};

#endif // MODEL_HPP
