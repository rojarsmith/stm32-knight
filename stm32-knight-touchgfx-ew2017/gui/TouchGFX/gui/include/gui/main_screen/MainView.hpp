#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/Color.hpp>

class MainView : public MainViewBase
{
public:
	MainView();
	virtual ~MainView() {}
	virtual void setupScreen();
	virtual void tearDownScreen();

	void buttonClicked(const AbstractButton &source);
	virtual void handleTickEvent();

protected:
	Image imgBackground, imgDemotitle, imglogo;
	Image btnWatch, btnWeather;
	Button btnFan, btnLighting, btnMusic, btnFood, btnBacklight;

	uint32_t screenwidthreal = 0;

	TextureMapper textureMapperImage3D;
	float xAngle3D;
	float yAngle3D;
	float zAngle3D;

	float deltaXangle3D;
	float deltaYangle3D;
	float deltaZangle3D;

	TextArea txtCopyRight;

	Callback<MainView, const AbstractButton &> buttonClickedCallback;
};

#endif // MAINVIEW_HPP
