#include <gui/widgets/loading/Loading.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

Loading::Loading()	
	:
	ms_(0),
	isOk_(false),
	animation_duration_(60),
	scale_(0.0f),
	frequency_divider_1_(0),
	z_angle_(0.0f),
	delta_z_angle_(-0.0625f),
	event_trigger_callback_(this, &Loading::eventTriggerHandler),
	zoomanimationimageAnimationEndedCallback1(this, &Loading::zoomanimationimageAnimationEndedHandler1),
	zoomanimationimageAnimationEndedCallback2(this, &Loading::zoomanimationimageAnimationEndedHandler2),
	zoomanimationimageAnimationEndedCallback3(this, &Loading::zoomanimationimageAnimationEndedHandler3),
	open_completed_callback_(0),
	close_completed_callback_(0)
{
	em_.setEventTriggerCallback(event_trigger_callback_);
	add(em_);

	background_.setVisible(false);
	//add(background_);

	front_image_.setVisible(false);
	add(front_image_);

	front_zoom_.setVisible(false);
	add(front_zoom_);
}

Loading::~Loading()
{
	Container::~Container();
}

void Loading::initialize(MachineStatus *status)
{	
	ms_ = status;
}

void Loading::setOpenCompletedCallback(GenericCallback<const int>& callback)
{
	this->open_completed_callback_ = &callback;
}

void Loading::setHideCompletedCallback(GenericCallback<const int>& callback)
{
	this->hide_completed_callback_ = &callback;
}

void Loading::setCloseCompletedCallback(GenericCallback<const int>& callback)
{
	this->close_completed_callback_ = &callback;
}

void Loading::open()
{	
	ms_->ux_loading_status = UXLoadingStatus::UX_LOADING_RUNNING;
	em_.addOneTimeEvent(20);
}

void Loading::hide()
{
	em_.addLoopChainEvent(13, ANIMATION_LOADING_HIDE_DURATION, 14);
}

void Loading::close()
{
	em_.addOneTimeEvent(6);	
}

void Loading::checked()
{
	em_.addOneTimeEvent(22);
}

void Loading::hideChecked()
{
	em_.addOneTimeEvent(23);
}

void Loading::setAnimationDuration(uint32_t duration)
{
	animation_duration_ = duration;
}

void Loading::zoomanimationimageAnimationEndedHandler1(const ZoomAnimationImage& image)
{		
	background_.setVisible(false);

	em_.addCountDownEvent(11, ANIMATION_LOADING_OK_DURATION);
}

void Loading::zoomanimationimageAnimationEndedHandler2(const ZoomAnimationImage& image)
{
	ms_->ux_loading_status = UXLoadingStatus::UX_LOADING_NONE;

	if (0 != close_completed_callback_ && close_completed_callback_->isValid())
	{
		this->close_completed_callback_->execute(0);
	}	
}

void Loading::zoomanimationimageAnimationEndedHandler3(const ZoomAnimationImage& image)
{
	background_.setVisible(false);	
}

void Loading::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 2:
		event2(); 
		break;
	case 3:
		event3(); 
		break;
	case 4:
		event4(); 
		break;
	case 5:
		event5();
		break;
	case 6:
		event6(); 
		break;
	case 7:
		event7(); 
		break;
	case 8:
		event8(); 
		break;
	case 9:
		event9(); 
		break;
	case 10:
		event10();
		break;
	case 11:
		event11();
		break;
	case 12:
		event12();
		break;
	case 13:
		event13();
		break;
	case 14:
		event14();
		break;
	case 20:
		event20();
		break;
	case 22:
		event22();
		break;
	case 23:
		event23();
		break;
	case 24:
		event24();
		break;
	case 25:
		event25();
		break;
	case 26:
		event26();
		break;
	}
}

void Loading::event2()
{
	int width_ = front_image_.getBitmap().getWidth();
	int height_ = front_image_.getBitmap().getHeight();

	front_image_.setXY(0, 0);
	front_image_.setCameraDistance(100.0f);
	front_image_.setCamera(
		front_image_.getBitmapPositionX() + (width_ / 2),
		front_image_.getBitmapPositionY() + (height_ / 2));
	front_image_.setOrigo(
		front_image_.getBitmapPositionX() + (width_ / 2),
		front_image_.getBitmapPositionY() + (height_ / 2),
		front_image_.getCameraDistance());
	front_image_.setVisible(true);
	front_image_.setScale(scale_);

	z_angle_ += delta_z_angle_;
	front_image_.updateAngles(0.0F, 0.0F, z_angle_);

	scale_ += 1.0f / ANIMATION_LOADING_OPEN_DURATION;
}

void Loading::event3()
{
	front_image_.setScale(0.97f);

	background_.setBitmap(Bitmap(BITMAP_CHECKING_BACKGROUND_THIN_ID));
	background_.setXY(0, 0);
	background_.setVisible(true);

	if (0 != open_completed_callback_ && open_completed_callback_->isValid())
	{
		this->open_completed_callback_->execute(1);
	}

	em_.addAlwaysKeepEvent(4, 1);
}

void Loading::event4()
{
	z_angle_ += delta_z_angle_;

	if (0 == (frequency_divider_1_ % FREQUENCY_DIVIDER_1))
	{
		front_image_.updateAngles(0.0F, 0.0F, z_angle_);
	}

	frequency_divider_1_++;
}

void Loading::event5()
{
}

void Loading::event6()
{	
	background_.setBitmap(Bitmap(BITMAP_CHECKING_BACKGROUND_ID));
	background_.setXY(0, 0);
	background_.setVisible(true);

	front_image_.setBitmap(Bitmap(BITMAP_CHECKING_SPINNER_ID));
	int width_ = front_image_.getBitmap().getWidth();
	int height_ = front_image_.getBitmap().getHeight();

	front_image_.setXY(0, 0);
	front_image_.setCameraDistance(100.0f);
	front_image_.setCamera(
		front_image_.getBitmapPositionX() + (width_ / 2),
		front_image_.getBitmapPositionY() + (height_ / 2));
	front_image_.setOrigo(
		front_image_.getBitmapPositionX() + (width_ / 2),
		front_image_.getBitmapPositionY() + (height_ / 2),
		front_image_.getCameraDistance());
	front_image_.setScale(0.97f);
	front_image_.setVisible(true);
	front_image_.invalidate();

	//em_.addAlwaysKeepEvent(7, 1);
	em_.addOneTimeEvent(8);
	//em_.addLoopChainEvent(7, 60, 8);
}

void Loading::event7()
{	
	//z_angle_ += delta_z_angle_;
	//front_image_.updateAngles(0.0F, 0.0F, z_angle_);
}

void Loading::event8()
{
	scale_ = 1.0f;
	em_.addLoopChainEvent(9, ANIMATION_LOADING_HIDE_DURATION, 10);
}

void Loading::event9()
{
	front_image_.setScale(scale_);

	//z_angle_ += delta_z_angle_;
	//front_image_.updateAngles(0.0F, 0.0F, z_angle_);

	float scale_delta = 1.0f / ANIMATION_LOADING_HIDE_DURATION;

	if (0 < (scale_ - scale_delta))
	{
		scale_ -= scale_delta;
	}	
}

void Loading::event10()
{
	em_.removeEvent(4);

	front_image_.setVisible(false);

	front_zoom_.setBitmaps(Bitmap(BITMAP_CHECKING_TICK_SMALL_ID), Bitmap(BITMAP_CHECKING_TICK_ID));
	front_zoom_.setPosition(31, 31, 0, 0);
	//front_zoom_.setPosition(51, 51, 0, 0);
	front_zoom_.setVisible(true);
	front_zoom_.setAnimationEndedCallback(zoomanimationimageAnimationEndedCallback1);
	front_zoom_.startZoomAndMoveAnimation(
		0,
		0,
		63,
		63,
		//102,
		//102,
		ANIMATION_LOADING_OPEN_DURATION,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
}

void Loading::event11()
{
	front_zoom_.setBitmaps(Bitmap(BITMAP_CHECKING_TICK_SMALL_ID), Bitmap(BITMAP_CHECKING_TICK_ID));
	front_zoom_.setPosition(0, 0, 63, 63);
	//front_zoom_.setPosition(0, 0, 102, 102);
	front_zoom_.setVisible(true);
	front_zoom_.setAnimationEndedCallback(zoomanimationimageAnimationEndedCallback2);
	front_zoom_.startZoomAndMoveAnimation(
		31,
		31,
		//51,
		//51,
		0,
		0,
		ANIMATION_LOADING_HIDE_DURATION,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
}

void Loading::event12()
{
}

void Loading::event13()
{
	background_.setVisible(false);

	front_image_.setScale(scale_);

	z_angle_ += delta_z_angle_;
	front_image_.updateAngles(0.0F, 0.0F, z_angle_);

	float scale_delta = 1.0f / ANIMATION_LOADING_HIDE_DURATION;

	if (0 < (scale_ - scale_delta))
	{
		scale_ -= scale_delta;
	}
}

void Loading::event14()
{
	front_image_.setVisible(false);

	ms_->ux_loading_status = UXLoadingStatus::UX_LOADING_NONE;

	if (0 != hide_completed_callback_ && hide_completed_callback_->isValid())
	{
		this->hide_completed_callback_->execute(0);
	}
}

void Loading::event20()
{
	front_image_.setBitmap(Bitmap(BITMAP_CHECKING_SPINNER_ID));

	em_.addLoopChainEvent(2, ANIMATION_LOADING_OPEN_DURATION, 3);
}

void Loading::event22()
{
	em_.removeEvent(4);

	front_image_.setVisible(false);

	front_zoom_.setBitmaps(Bitmap(BITMAP_CHECKING_TICK_SMALL_ID), Bitmap(BITMAP_CHECKING_TICK_ID));
	front_zoom_.setPosition(31, 31, 0, 0);
	//front_zoom_.setPosition(51, 51, 0, 0);
	front_zoom_.setVisible(true);
	front_zoom_.setAnimationEndedCallback(zoomanimationimageAnimationEndedCallback3);
	front_zoom_.startZoomAndMoveAnimation(
		0,
		0,
		63,
		63,
		//102,
		//102,
		animation_duration_,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone);
}

void Loading::event23()
{
	em_.removeAllEvent();

	front_zoom_.setBitmaps(Bitmap(BITMAP_CHECKING_TICK_SMALL_ID), Bitmap(BITMAP_CHECKING_TICK_ID));
	front_zoom_.setPosition(0, 0, 63, 63);
	//front_zoom_.setPosition(0, 0, 102, 102);
	front_zoom_.setVisible(true);
	front_zoom_.setAnimationEndedCallback(zoomanimationimageAnimationEndedCallback2);
	front_zoom_.startZoomAndMoveAnimation(
		31,
		31,
		//51,
		//51,
		0,
		0,
		animation_duration_,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
}
void Loading::event24()
{

}
void Loading::event25()
{

}
void Loading::event26()
{

}