#ifndef MESSAGEBLUE_HPP
#define MESSAGEBLUE_HPP

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

using namespace touchgfx;

class MessageBlue : public AbstractMessage
{
public:
	MessageBlue();
	virtual ~MessageBlue();

	virtual void initialize(MachineStatus *status, ContentType content);

private:
	//::[UI Element]::
	FadeAnimator<Image> decorate_;

	Container pprt_view_;
	MoveAnimator<FadeAnimator<Box>> background_;
	MoveAnimator<FadeAnimator<TiledImage>> background_decorate_;

	GenericCallback<const int>* open_completed_callback_;
	GenericCallback<const int>* close_completed_callback_;

	Callback<MessageBlue, const FadeAnimator<Box>& > box_fade_ended_callback_;
	void boxFadeEndedHandler(const FadeAnimator<Box>& box);
	Callback<MessageBlue, const MoveAnimator<FadeAnimator<Box>>& > box_move_ended_callback_;
	void boxMoveEndedHandler(const MoveAnimator<FadeAnimator<Box>>& box);

	Callback<MessageBlue, const MoveAnimator<FadeAnimator<Image>>& > image_move_ended_callback_;
	void imageMoveEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image);
	Callback<MessageBlue, const FadeAnimator<Image>& > image_fade_ended_callback_;
	void imageFadeEndedHandler(const FadeAnimator<Image>& image);

	Callback<MessageBlue, const MoveAnimator<FadeAnimator<TiledImage>>& > tiledimage_move_ended_callback_;
	void tiledimageMoveEndedHandler(const MoveAnimator<FadeAnimator<TiledImage>>& tiledimage);
	Callback<MessageBlue, const FadeAnimator<TiledImage>& > tiledimage_fade_ended_callback_;
	void tiledimageFadeEndedHandler(const FadeAnimator<TiledImage>& tiledimage);

	//::[Event]::
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
};

#endif /* MESSAGEBLUE_HPP */
