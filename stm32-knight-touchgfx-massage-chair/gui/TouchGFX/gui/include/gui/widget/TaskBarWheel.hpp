#ifndef TASK_BAR_WHEEL_HPP
#define TASK_BAR_WHEEL_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

class TaskBarWheel : public Container
{
public:
	TaskBarWheel();
	virtual ~TaskBarWheel();

	/**
	* @brief Initialize.
	*
	* @param width       The width of the container.
	* @param height      The height of the container.
	*/
	virtual void initialize(int16_t width, int16_t height);

	void addTaskBarItem(BitmapId buttonId, BitmapId selectedImageId, TEXTS label, uint8_t callbackId, bool active = true);
	void setTaskBarItemClickedThroughAction(GenericCallback<const uint8_t>& callback);
	void setScrollable(bool active = true);

	virtual void handleTickEvent();

private:
	static const uint8_t items_size = 15;
	static const int16_t item_spacing_size = 25;
	static const int16_t item_label_height_size = 20;
	static const int16_t item_label_spacing_size = 5;
	
	uint8_t itemsInList;

	struct TaskBarItem
	{
		Button button;
		Image disableImage;
		Image selectedImage;
		TextArea iconLabel;		
		uint8_t callbackId;
		bool active;
	} taskBarItems[items_size];

	uint8_t clickedCallbackId;

	Container taskBarItemContainer;
	ScrollableContainer scrollableContainer;

	Callback<TaskBarWheel, const AbstractButton&> taskBarItemClickedCallback;
	void taskBarItemClickedHandler(const AbstractButton& source);

	GenericCallback<const uint8_t >* taskBarItemClickedThroughCallback;
};

#endif /* TASK_BAR_WHEEL_HPP */
