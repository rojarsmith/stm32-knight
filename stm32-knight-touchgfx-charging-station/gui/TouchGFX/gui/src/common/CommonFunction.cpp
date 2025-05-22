#include <gui/common/CommonFunction.h>

void CommonFunction::flipHorizontalARGB8888(int width, int height, const uint8_t * source, uint8_t * distribute)
{
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			*(distribute + (r * width * 4 + c * 4 + 0)) = *(source + (r * width * 4 + (width - 1) * 4 - c * 4 + 0));
			*(distribute + (r * width * 4 + c * 4 + 1)) = *(source + (r * width * 4 + (width - 1) * 4 - c * 4 + 1));
			*(distribute + (r * width * 4 + c * 4 + 2)) = *(source + (r * width * 4 + (width - 1) * 4 - c * 4 + 2));
			*(distribute + (r * width * 4 + c * 4 + 3)) = *(source + (r * width * 4 + (width - 1) * 4 - c * 4 + 3));
		}
	}
}

void CommonFunction::convertTime(int sec, DateTime * dist)
{
	int sec_year = 31536000;
	int sec_day = 86400;

	dist->year = (sec / 31536000);
	int day = (sec - (dist->year * 31536000)) / 86400;

	int m = 0;
	int md = 0;
	int mm[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for (int i = 0; i < day && i < 12; i++)
	{
		m++;
		md += mm[i];
	}
	dist->month = m;
	if (m >= 2) 
	{
		dist->day = day - mm[m - 1];
	}
	else 
	{
		dist->day = day;
	}
	
	int rem_sec = sec - day * sec_day - dist->year * 31536000;
	dist->hour = rem_sec / 3600;
	dist->minute = (rem_sec - dist->hour * 3600) / 60;
	dist->second = rem_sec - dist->hour * 3600 - dist->minute * 60;
	dist->year = dist->year + 2000;
}