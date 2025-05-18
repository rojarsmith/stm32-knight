#ifndef MODEL_HPP
#define MODEL_HPP

#include <gui/model/Time.hpp>
#include <touchgfx/hal/HAL.hpp>

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
		return currentTime;
	}

	bool getMCULoadActive() const
	{
		return mcuLoadActive;
	}
	void setMCULoadActive(bool active)
	{
		mcuLoadActive = active;
	}

	void setData(uint16_t value);
	uint16_t readData();

protected:
    ModelListener* modelListener;

	bool mcuLoadActive;

private:
	Time currentTime;
	Time previousTime;
};

#endif // MODEL_HPP
