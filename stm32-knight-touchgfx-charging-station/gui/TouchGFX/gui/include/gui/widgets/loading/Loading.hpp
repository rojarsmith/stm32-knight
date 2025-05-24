#ifndef LOADING_HPP
#define LOADING_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/common/CommonConstant.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/common/EventManager.hpp>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class Loading : public Container
{
public:
	Loading();
	virtual ~Loading();

	virtual void initialize(MachineStatus *status);
	virtual void setOpenCompletedCallback(GenericCallback<const int>& callback);		                
	virtual void setHideCompletedCallback(GenericCallback<const int>& callback);
	virtual void setCloseCompletedCallback(GenericCallback<const int>& callback);
	virtual void open();	
	virtual void hide();
	virtual void close();
	virtual void checked();
	virtual void hideChecked();
	virtual void setAnimationDuration(uint32_t duration);

	uint32_t animation_duration_;
	EventManager em_;	
	MachineStatus *ms_;

	//::[Event]::
	Callback<Loading, const int> event_trigger_callback_;
	virtual void eventTriggerHandler(const int source);
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
	virtual void event6();
	virtual void event7();
	virtual void event8();
	virtual void event9();
	virtual void event10();
	virtual void event11();
	virtual void event12();
	virtual void event13();
	virtual void event14();
	virtual void event20();
	virtual void event22();
	virtual void event23();
	virtual void event24();
	virtual void event25();
	virtual void event26();
private:
	const static int FREQUENCY_DIVIDER_1 = 3;
	CommonConstant& cc_ = CommonConstant::getInstance();

	bool isOk_;

	ZoomAnimationImage front_zoom_;
	AnimationTextureMapper front_image_;
	Image background_;

	float scale_;	
	float z_angle_;
	float delta_z_angle_;
	int frequency_divider_1_;

	GenericCallback<const int>* open_completed_callback_;
	GenericCallback<const int>* hide_completed_callback_;
	GenericCallback<const int>* close_completed_callback_;

	Callback<Loading, const ZoomAnimationImage&> zoomanimationimageAnimationEndedCallback1;
	void zoomanimationimageAnimationEndedHandler1(const ZoomAnimationImage& image);

	Callback<Loading, const ZoomAnimationImage&> zoomanimationimageAnimationEndedCallback2;
	void zoomanimationimageAnimationEndedHandler2(const ZoomAnimationImage& image);

	Callback<Loading, const ZoomAnimationImage&> zoomanimationimageAnimationEndedCallback3;
	void zoomanimationimageAnimationEndedHandler3(const ZoomAnimationImage& image);
};

#endif /* LOADING_HPP */
