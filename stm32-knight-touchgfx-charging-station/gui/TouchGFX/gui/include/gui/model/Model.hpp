#ifndef MODEL_HPP
#define MODEL_HPP

#include <gui/model/ModelSchema.hpp>

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

    MachineStatus* getMachineStatus();
protected:
    ModelListener* modelListener;
private:
    MachineStatus mstatus_;
};

#endif // MODEL_HPP
