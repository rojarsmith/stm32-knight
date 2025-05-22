#ifndef MESSAGEE5_HPP
#define MESSAGEE5_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TiledImage.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/common/EventManager.hpp>
#include <gui/model/ModelSchema.hpp>
#include <gui/widgets/info/AbstractMessage.hpp>
//#include <gui/widgets/info/MessageE5.hpp>

using namespace touchgfx;

class MessageE5 : public AbstractMessage
{
public:
	MessageE5();
	virtual ~MessageE5();

	virtual void initialize(MachineStatus *status, ContentType content);

private:
	//::[UI Element]::
	FadeAnimator<Image> decorate_;

	Container pprt_view_;
	MoveAnimator<FadeAnimator<Box>> background_;
	MoveAnimator<FadeAnimator<TiledImage>> background_decorate_;

	GenericCallback<const int>* open_completed_callback_;
	GenericCallback<const int>* close_completed_callback_;

	Callback<MessageE5, const FadeAnimator<Box>& > box_fade_ended_callback_;
	void boxFadeEndedHandler(const FadeAnimator<Box>& box);
	Callback<MessageE5, const MoveAnimator<FadeAnimator<Box>>& > box_move_ended_callback_;
	void boxMoveEndedHandler(const MoveAnimator<FadeAnimator<Box>>& box);

	Callback<MessageE5, const MoveAnimator<FadeAnimator<Image>>& > image_move_ended_callback_;
	void imageMoveEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image);
	Callback<MessageE5, const FadeAnimator<Image>& > image_fade_ended_callback_;
	void imageFadeEndedHandler(const FadeAnimator<Image>& image);

	Callback<MessageE5, const MoveAnimator<FadeAnimator<TiledImage>>& > tiledimage_move_ended_callback_;
	void tiledimageMoveEndedHandler(const MoveAnimator<FadeAnimator<TiledImage>>& tiledimage);
	Callback<MessageE5, const FadeAnimator<TiledImage>& > tiledimage_fade_ended_callback_;
	void tiledimageFadeEndedHandler(const FadeAnimator<TiledImage>& tiledimage);	

	//::[Event]::
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
};

#endif /* MESSAGEE5_HPP */
