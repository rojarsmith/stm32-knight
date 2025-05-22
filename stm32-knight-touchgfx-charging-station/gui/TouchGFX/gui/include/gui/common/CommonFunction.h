#ifndef COMMONFUNCTION_HPP
#define COMMONFUNCTION_HPP

#include <cstdint>

typedef struct StructDateTime {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
} DateTime;

class CommonFunction
{
public:
	static void flipHorizontalARGB8888(int width, int height, const uint8_t * source, uint8_t * distribute);
	static void convertTime(int sec, DateTime * dist);	
};

#endif