#ifndef MODEL_HPP
#define MODEL_HPP

#include <gui/common/Defines.hpp>
#include <gui/model/Time.hpp>

#include <string>
#include <gui/model/ModelSchema.hpp>

static int v_device_id_;
static int v_action_id_;
static int v_event_id_;
static int v_op1_;
static int v_op2_;
static int v_op3_;
static int v_op4_;

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    Time getCurrentTime() const
    {
        return current_time_;
    }

    Defines::DemoID getSelectedDemoScreen()
    {
        return selected_demo_screen_;
    }
    void setSelectedDemoScreen(Defines::DemoID demoId)
    {
        selected_demo_screen_ = demoId;
    }

    void screenSaverMinorTick();
    void gestureTick(int eve, int op4);

    MachineStatus* getMachineStatus();
protected:
    ModelListener* modelListener;

    Time current_time_;

    Defines::DemoID selected_demo_screen_;
private:
    MachineStatus mstatus_;
};

#endif // MODEL_HPP