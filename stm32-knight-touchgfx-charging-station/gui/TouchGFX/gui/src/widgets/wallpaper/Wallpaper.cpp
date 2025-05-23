#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/wallpaper/Wallpaper.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/hal/HAL.hpp>

Wallpaper::Wallpaper()
	:
	weather_(nullptr)
{			
}

Wallpaper::~Wallpaper()
{
	Container::~Container();
}

void Wallpaper::initialize(WeatherStyle& weather, WeatherStyle& weather_prev)
{
	weather_ = &weather;
	weather_prev_ = &weather_prev;

	background_.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	add(background_);

	setGraphic();
}

void Wallpaper::renderGraphic()
{
	assert(weather_ != nullptr && "Lack weather.");

	if (*weather_prev_ != *weather_)
	{
		setGraphic();
	}
}

void Wallpaper::setGraphic()
{
	if (WeatherStyle::NIGHT == *weather_)
	{
		background_.setColor(Color::getColorFromRGB(0x1E, 0x20, 0x21));
	}
	else
	{
		background_.setColor(Color::getColorFromRGB(0xD9, 0xD9, 0xD9));
	}
	background_.invalidate();
}
