#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    // MCU Usage.
    virtual void mcuLoadUpdated(uint8_t mcuLoad) {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
