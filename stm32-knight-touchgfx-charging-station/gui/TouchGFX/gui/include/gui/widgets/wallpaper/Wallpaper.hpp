#ifndef WALLPAPER_HPP
#define WALLPAPER_HPP

#include <cassert>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/common/CommonConstant.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class Wallpaper : public Container
{
public:
	Wallpaper();
	virtual ~Wallpaper();

	virtual void initialize(WeatherStyle& weather, WeatherStyle& weather_prev);
	virtual void renderGraphic();
protected:
	
private:
	WeatherStyle *weather_;
	WeatherStyle *weather_prev_;
	Box background_;

	void setGraphic();
};

#endif /* WALLPAPER_HPP */
