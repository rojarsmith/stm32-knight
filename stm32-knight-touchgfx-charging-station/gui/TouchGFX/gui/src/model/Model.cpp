#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

MachineStatus* Model::getMachineStatus()
{
	return &mstatus_;
}
