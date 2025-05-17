#include <gui/widget/TaskBarWheel.hpp>
#include <touchgfx/Color.hpp>

TaskBarWheel::TaskBarWheel()
	:
	itemsInList(0),
	taskBarItemClickedCallback(this, &TaskBarWheel::taskBarItemClickedHandler)
{
}

TaskBarWheel::~TaskBarWheel()
{
}

void TaskBarWheel::handleTickEvent()
{
}

void TaskBarWheel::addTaskBarItem(BitmapId buttonId, BitmapId selectedImageId, TEXTS label, uint8_t callbackId, bool active)
{
	int y = item_spacing_size;
	if (0 != itemsInList){
		y += itemsInList * (Bitmap(buttonId).getHeight() + item_label_spacing_size + item_label_height_size + item_spacing_size);
	}
	taskBarItems[itemsInList].button.setBitmaps(Bitmap(buttonId), Bitmap(selectedImageId));
	taskBarItems[itemsInList].button.setXY(0, y);
	taskBarItems[itemsInList].button.setAction(taskBarItemClickedCallback);
	taskBarItems[itemsInList].button.setVisible(true);
	taskBarItems[itemsInList].disableImage.setBitmap(Bitmap(BITMAP_ITEM_DISABLE_100X100_ID));
	taskBarItems[itemsInList].disableImage.setXY(0, y);
	taskBarItems[itemsInList].disableImage.setVisible(false);
	taskBarItems[itemsInList].selectedImage.setBitmap(Bitmap(selectedImageId));
	taskBarItems[itemsInList].selectedImage.setXY(0, y);
	taskBarItems[itemsInList].selectedImage.setVisible(false);
	taskBarItems[itemsInList].iconLabel.setPosition(0, y + Bitmap(buttonId).getHeight() + item_label_spacing_size, Bitmap(buttonId).getWidth(), item_label_height_size);
	taskBarItems[itemsInList].iconLabel.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	taskBarItems[itemsInList].iconLabel.setTypedText(TypedText(label));
	taskBarItems[itemsInList].callbackId = callbackId;
	taskBarItems[itemsInList].active = active;

	itemsInList++;

	if (Bitmap(buttonId).getWidth() > taskBarItemContainer.getWidth())
	{
		taskBarItemContainer.setWidth(Bitmap(buttonId).getWidth());
	}
	taskBarItemContainer.setHeight(y + Bitmap(buttonId).getHeight() + item_label_spacing_size + item_label_height_size + item_spacing_size);
}

void TaskBarWheel::initialize(int16_t width, int16_t height)
{
	scrollableContainer.setXY(0, 0);
	scrollableContainer.setWidth(width);
	scrollableContainer.setHeight(height);
	scrollableContainer.setScrollbarsVisible(false);
	scrollableContainer.add(taskBarItemContainer);
	scrollableContainer.setScrollThreshold(10);
	scrollableContainer.enableHorizontalScroll(false);
	scrollableContainer.enableVerticalScroll(true);

	add(scrollableContainer);

	for (int i = 0; i < items_size; i++)
	{
		if (taskBarItems[i].active)
		{
			taskBarItemContainer.add(taskBarItems[i].button);
			taskBarItemContainer.add(taskBarItems[i].selectedImage);
			taskBarItemContainer.add(taskBarItems[i].iconLabel);
		}
		else{
			taskBarItems[i].disableImage.setVisible(true);
			taskBarItemContainer.add(taskBarItems[i].disableImage);
			taskBarItemContainer.add(taskBarItems[i].iconLabel);
		}
	}

	setWidth(width);
	setHeight(height);
	scrollableContainer.setTouchable(false);
}

void TaskBarWheel::setScrollable(bool active)
{
	scrollableContainer.setTouchable(active);
}

void TaskBarWheel::setTaskBarItemClickedThroughAction(GenericCallback<const uint8_t>& callback)
{
	taskBarItemClickedThroughCallback = &callback;
}

void TaskBarWheel::taskBarItemClickedHandler(const AbstractButton& source)
{
	uint8_t id = 0;

	for (int i = 0; i < items_size; i++){
		if (&taskBarItems[i].button == &source){
			id = taskBarItems[i].callbackId;
			taskBarItems[i].selectedImage.setVisible(true);
		}
		else
		{
			taskBarItems[i].selectedImage.setVisible(false);
		}
		taskBarItems[i].selectedImage.invalidate();
	}

	if (taskBarItemClickedThroughCallback && taskBarItemClickedThroughCallback->isValid())
	{
		taskBarItemClickedThroughCallback->execute(id);
	}
}
