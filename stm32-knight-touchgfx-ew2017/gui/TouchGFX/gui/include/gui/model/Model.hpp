#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/hal/Types.hpp>

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

    typedef enum
    {
        MODE_LED = 1,
        MODE_FAN,
        MODE_MP3,
        MODE_PNT,
        MODE_RECV,
        MODE_PWM
    } mode_ID;

    void setdata(mode_ID id, uint8_t index, uint8_t value);
    uint8_t getdata(mode_ID id, uint8_t index);
    bool senddata(mode_ID id);
    bool senddata(mode_ID id, int playmode, int songValue, int  playstatus, int  volumeValue);
protected:
    ModelListener* modelListener;
private:
    uint8_t mp3[10];
    uint8_t fan[10];
};

#endif // MODEL_HPP
