#ifndef TEXTURE_MAPPER_ANIMATION_HPP
#define TEXTURE_MAPPER_ANIMATION_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>

using namespace touchgfx;

class TextureMapperAnimation : public TextureMapper
{
public:
	TextureMapperAnimation();
	virtual ~TextureMapperAnimation();

	virtual void handleTickEvent();

	virtual void setBitmaps(BitmapId start, BitmapId end);

	void setAnimationStoppedCallback(GenericCallback<const TextureMapperAnimation&>& callback);

	/**
	* @fn Start show animation.
	*
	* @brief Updates the animation described by ticks.
	*
	* @param inventory PNGs want to show.
	*        frequency Ticks mod frequency, 60 ticks is 1 second.
	*        alpha Target alpha.
	*        scale Target scale.
	*/
	void startAnimation(const int inventory, const int frequency, const int alpha, const float scale);
protected:
	BitmapId startId;
	BitmapId endId;
	int inventory;
	int inventoryCach;
	int frequency;
	int currentAlpha;
	int targetAlpha;
	float currentScale;
	float targetScale;
	int frameTick;

	void renderAnimation(const int tick);

	GenericCallback<const TextureMapperAnimation&>* animationStoppedCallback;
};

#endif /* TEXTURE_MAPPER_ANIMATION_HPP */
