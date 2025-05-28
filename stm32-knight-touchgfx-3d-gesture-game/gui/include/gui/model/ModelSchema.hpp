#ifndef MODEL_SCHEMA_HPP
#define MODEL_SCHEMA_HPP

typedef struct MachineStatusProperties
{
	int device = 0;
	int act = 0;
	int* eve = nullptr;
	int op1 = 0;
	int op2 = 0;
	int op3 = 0;
	int op4 = 0;

	bool mouse_mode = false;
	int tick = 0;
	int score[3] = { 0 };
} MachineStatus;

static unsigned short SIM_DEEP = 1000;

#endif /* MODEL_SCHEMA_HPP */