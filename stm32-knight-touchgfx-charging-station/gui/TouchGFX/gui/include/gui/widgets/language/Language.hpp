#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/model/ModelSchema.hpp>
#include <gui/widgets/ContainerEx.hpp>
#include <gui/widgets/Integration.hpp>

using namespace touchgfx;

class Language : public ContainerEx
{
public:
	Language();
	virtual ~Language();

	virtual void handleTickEvent();	
	
	void initialize(MachineStatus* status);	
	virtual void openContainer();
	virtual void closeContainer();
	virtual void setBeginAnimationCallback(GenericCallback<const int>& callback);
	virtual void lock();
protected:
	virtual void event_1();
	virtual void event_2();
private:
	MachineStatus *ms_;
	int tick_;
	int gap_ = 20;
	bool is_opened;

	Integration integration_;
	Box mask_;
	FadeAnimator<Image> background_left_;
	Container view_port_;
	MoveAnimator<FadeAnimator<Image>> background_right_;

	MoveAnimator<FadeAnimator<Button>> america_;
	MoveAnimator<FadeAnimator<Button>> spain_;
	MoveAnimator<FadeAnimator<Button>> germany_;
	MoveAnimator<FadeAnimator<Button>> france_;

	MoveAnimator<FadeAnimator<TextAreaWithOneWildcard>> menu_;	

	Callback<Language, const AbstractButton&>button_clicked_;
	void buttonClickedHandler(const AbstractButton& source);	

	Callback<Language, const FadeAnimator<Image>&> image_fade_ended_callback_;
	void imageFadeEndedHandler(const FadeAnimator<Image>& image);
	   	 
	Callback<Language, const MoveAnimator<FadeAnimator<Image>>&> image_move_ended_callback_;
	void imageMoveEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image);

	Callback<Language, const FadeAnimator<Button>&> button_fade_ended_callback_;
	void buttonFadeEndedHandler(const FadeAnimator<Button>& button);

	Callback<Language, const MoveAnimator<FadeAnimator<Button>>&> button_move_ended_callback_;
	void buttonMoveEndedHandler(const MoveAnimator<FadeAnimator<Button>>& button);

	Callback<Language, const FadeAnimator<TextAreaWithOneWildcard>& > textareawithonewildcard_fade_ended_callback_;
	void textareawithonewildcardFadeEndedHandler(const FadeAnimator<TextAreaWithOneWildcard>& text);

	Callback<Language, const MoveAnimator<FadeAnimator<TextAreaWithOneWildcard>>& > textareawithonewildcard_move_ended_callback_;
	void textareawithonewildcardMoveEndedHandler(const MoveAnimator<FadeAnimator<TextAreaWithOneWildcard>>& text);

	Callback<Language, const int> integration_closed_callback_;
	void integrationClosedHandler(const int source);

	GenericCallback<const int>* begin_animation_callback_;
};

#endif /* LANGUAGE_HPP */
