#ifndef PAYMENTVIEW_HPP
#define PAYMENTVIEW_HPP

#include <gui_generated/payment_screen/PaymentViewBase.hpp>
#include <gui/payment_screen/PaymentPresenter.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <mvp/View.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/common/BaseView.hpp>
#include <gui/payment_screen/PaymentPresenter.hpp>
#include <gui/widgets/backto/Backto.hpp>
#include <gui/widgets/language/Language.hpp>
#include <gui/widgets/footer/Footer.hpp>
#include <gui/widgets/plugin/Plugin.hpp>
#include <gui/widgets/socket/Socket.hpp>
#include <touchgfx/widgets/QRCode.hpp>
//#include <gui/widgets/qrcode/QRCodeWidget.hpp>
#include <gui/widgets/info/MessageYellow.hpp>
#include <gui/widgets/loading/Loading.hpp>
#include <gui/widgets/information/Information.hpp>
#include <gui/widgets/title/Title.hpp>
#include <gui/widgets/wallpaper/Wallpaper.hpp>
#include <gui/widgets/button_with_label_ex/ButtonWithLabelEx.hpp>

class PaymentView : public BaseView<PaymentPresenter, PaymentViewBase>
{
public:
    PaymentView();
    virtual ~PaymentView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void afterTransition();
    //virtual void updateGraphic();
protected:
	FrontendApplication& application()
	{
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}
private:
	Wallpaper wallpaper_;
	ZoomAnimationImage pole_;
	Socket socket_right_;
	Socket socket_left_;
	Plugin plugin_right_;
	Plugin plugin_left_;
	Footer footer_;
	Information information_;
	Language language_;
	Backto backto_;
	Title title_;

	int16_t plugin_in_y_ = -158; // 480x640 @ 800x480

	//Payment Logo - QR Code
	Box bottom_mask_;
	uint8_t qrBuffer_qrCode_[QRCODE_BUFFER_SIZE(2)];
	uint8_t qrScratchBuffer_qrCode_[QRCODE_BUFFER_SIZE(2)];
	MoveAnimator<QRCode> qrcode_;
	//QRCode qrcode_;
	//QRCode code_;
	//MoveAnimator<QRCodeWidget> qr_code_;
	MoveAnimator<Box> qr_code_bg_;
	int16_t qr_code_end_x_;
	int16_t qr_code_end_y_;
	int16_t qr_code_bg_end_x_;
	int16_t qr_code_bg_end_y_;
	FadeAnimator<TextArea> plo_char_title_;
	FadeAnimator<Image> plo_char_icon_2_;

	MoveAnimator<FadeAnimator<ButtonWithLabelEx>> button_qr_;
	MoveAnimator<FadeAnimator<ButtonWithLabelEx>> button_char_;
	MoveAnimator<FadeAnimator<ButtonWithLabelEx>> button_cred_;

	//Down
	FadeAnimator<Image> arrow_;
	Box bottom_arrow_2_mask_;
	int16_t bottom_arrow_2_sy_;
	int bottom_arrow_2_tick_;
	static int cam_[];
	int pla_select_;
	//	int pla_select_prv_;
	int payment_method_prv;
	Loading checking_;

	int animation_locker_;
	int animation_locker_count_;

	Callback<PaymentView, const int> button_clicked_callback_;
	void buttonClickedHandler(const int source);

	Callback<PaymentView, const int> backto_button_clicked_callback_;
	void backtoButtonClickedHandler(const int source);

	Callback<PaymentView, const AbstractButton&> on_button_clicked_;
	void buttonClickedHandler(const AbstractButton& source);

	Callback<PaymentView, const ZoomAnimationImage&> poleAnimationEndedCallback;
	void poleAnimationEndedHandler(const ZoomAnimationImage& image);

	Callback<PaymentView, const uint8_t> footerMoveAnimationEndedCallback;
	void footerMoveAnimationEndedHandler(const uint8_t source);

	Callback<PaymentView, const int> message_open_end_callback_;
	void messageOpenEndHandler(const int source);

	Callback<PaymentView, const int> message_close_end_callback_;
	void messageCloseEndHandler(const int source);

	Callback<PaymentView, const int> checking_open_end_callback_;
	//	void checkingOpenEndHandler(const int source);

	Callback<PaymentView, const int> checking_hide_end_callback_;
	//	void checkinghideEndHandler(const int source);

	Callback<PaymentView, const int> checking_close_end_callback_;

#pragma region Event
	enum EventList
	{
		EVENT_1TICK_LOOP = 1,
		EVENT_RENDER_GRAPHIC = 4,
		EVENT_ARROW_ANI = 6,
		EVENT_TRAN_IN = 10,
		EVENT_TRAN_IN_END = 11,
		EVENT_SEND_COMMAND_TO_0200 = 13,
		EVENT_CHANGE_SCREEN_TO_0200 = 14,
		EVENT_CHANGE_SCREEN_TO_0230 = 18,
		EVENT_CHANGE_SCREEN_TO_0231 = 19,
		EVENT_CHANGE_SCREEN_TO_0232 = 20,
		EVENT_POP_OPEN_BTN = 22,
		EVENT_CHANGE_PAYMENT_METHOD_IN = 26,
		EVENT_CHANGE_PAYMENT_METHOD_OUT = 27,
		EVENT_WAIT_ACTIVE_PAY = 28,
		EVENT_ACCEPTED_PAYMENT = 29,
		EVENT_WAIT_VERIFY = 30,
		EVENT_ACCEPTED_WAIT_PAYMENT = 31,
		EVENT_CHANGE_PAYMENT_METHOD_IN_END = 32,
		EVENT_ACCEPTED_PAYMENT_QR = 33,
		EVENT_UNLOCK_SELECTED_PLUG = 34,
		EVENT_TRAN_OUT = 35
	};
	Callback<PaymentView, const int> event_trigger_callback_;
	virtual void eventTriggerHandler(const int source);
	virtual void event1();
	//	virtual void event2();
	virtual void eventRenderGraphic();
	virtual void eventArrowAni();
	//	virtual void event7();
	//	virtual void event8();
	//	virtual void event9();
	virtual void eventTranIn();
	virtual void eventTranInEnd();
	//	virtual void event12();
	virtual void eventSendCommandTo0200();
	virtual void eventChangeScreenTo0200();
	//	virtual void eventChangeScenarioTo0230();
	//	virtual void eventChangeScenarioTo0231();
	//	virtual void eventChangeScenarioTo0232();
	//	virtual void event21();
	//	virtual void eventPopOpenBtn();
	virtual void event23();
	virtual void event24();
	virtual void eventChangePaymentMethodIn();
	virtual void eventChangePaymentMethodOut();
	virtual void eventWaitActivePay();
	virtual void eventAcceptedPayment();
	virtual void eventWaitVerify();
	virtual void eventAcceptedWaitPayment();
	//	virtual void eventChangePaymentMethodInEnd();
	virtual void eventAcceptedPaymentQR();
	virtual void eventUnlockSelectedPlug();
	virtual void eventTranOut();
	//	virtual void event40();
	//	virtual void event41();
#pragma endregion Event

#pragma region Style Resource
	const int16_t getPoleNextX();
	const int16_t getSocketRightNextX();
	const int16_t getSocketLeftNextX();
	const int16_t getPluginRightNextWidth();
	const int16_t getPluginLeftNextWidth();
	const int16_t getPluginRightNextHeight();
	const int16_t getPluginLeftNextHeight();
	const int16_t getPluginRightNextX();
	const int16_t getPluginLeftNextX();
	const int16_t getPoleStaticX();
	const uint16_t getPluginStaticBitmap();
	const int16_t getPluginStaticX();
	const int16_t getPLOQrCodeX();
	const int16_t getPLOQrIdxX();
	const uint8_t getPLOQrR();
	const uint8_t getPLOQrG();
	const uint8_t getPLOQrB();
	const uint8_t getPLOQrMaskR();
	const uint8_t getPLOQrMaskG();
	const uint8_t getPLOQrMaskB();
	const int16_t getPLOCharIconX();
	const int16_t getPLOCharIdxX();
	const int16_t getPLOCredIconX();
	const int16_t getPLOCredIdxX();
	const int16_t getCheckingX();
#pragma endregion Style Resource
};

#endif // PAYMENTVIEW_HPP
