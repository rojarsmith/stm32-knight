#ifndef SCANVIEW_HPP
#define SCANVIEW_HPP

#include <gui_generated/scan_screen/ScanViewBase.hpp>
#include <gui/scan_screen/ScanPresenter.hpp>
#include <mvp/View.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/scan_screen/ScanPresenter.hpp>
#include <gui/widget/RectangleFluxion.hpp>
#include <gui/container/LineFluxion.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/Snapper.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
//#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/Shape.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class ScanView : public ScanViewBase
{
public:
    ScanView();
    virtual ~ScanView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	virtual void afterTransition();
	virtual void handleTickEvent();
protected:
	FrontendApplication& getApplication() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}
private:
	class CustomShape : public Shape<5>
	{
	public:
		CustomShape()
		{
			ShapePoint<float> points[5] = { { -3.5f, 0 },{ -.7f, -47 },{ 0, -50 },{ .7f, -47 },{ 3.5f, 0 } };
			setShape(points);
		}
	};

	int frameTick;

	enum AniManStates
	{
		ANIMAN_NONE,
		ANIMAN_RUNNING,
		ANIMAN_2,
		ANIMAN_3,
		ANIMAN_4,
		ANIMAN_5,
		ANIMAN_6,
		ANIMAN_7,
		ANIMAN_8,
		ANIMAN_9
	} aniManState, aniManStateCach;

	Box backgroundColor;

	bool scanningDotRe;
	FadeAnimator<TextArea> scanningTitle;
	FadeAnimator<TextArea> scanningDot[3];
	Callback<ScanView, const FadeAnimator<TextArea>& >textAreaFadeAnimationEndedCallback;
	void textAreaFadeAnimationEndedHandler(const FadeAnimator<TextArea>& source);

	TextureMapper aniMan;
	void startAniMan(const int inventory, const int frequency, const int alpha, const float scale, AniManStates next);
	void renderAniMan(const int tick);
	void setMoveAniMan(const int inventory, AniManStates next);
	void moveAniMan(const int tick);
	int aniManCurrent;
	int aniManInventory;
	int aniManInventoryCach;
	int aniManFrequency;
	int aniManCurrentAlpha;
	int aniManTargetAlpha;
	float aniManCurrentScale;
	float aniManTargetScale;
	int aniManMoveInventory;
	int aniManMoveInventoryCach;
	bool aniManMov;

	int sleepTicks;
	void setSleepTick(const int inventory, AniManStates next);
	void sleepTick();

	uint32_t screenwidthreal = 0;

	RectangleFluxion indicator;
	RectangleFluxion indicator2;
};

#endif // SCANVIEW_HPP
