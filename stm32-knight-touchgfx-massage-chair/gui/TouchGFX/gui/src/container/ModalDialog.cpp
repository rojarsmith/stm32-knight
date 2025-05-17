#include <BitmapDatabase.hpp>
#include <typeinfo>
#include <gui/container/ModalDialog.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>

ModalDialog::ModalDialog()
	:
	buttonClickedCallback(this, &ModalDialog::buttonClickedHandler)
{
	backgroundColor.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, 0, 100));

	add(backgroundColor);

	dialogMessage.setXY(HAL::DISPLAY_WIDTH / 2, HAL::DISPLAY_HEIGHT / 2);
	dialogMessage.setColor(Color::getColorFromRGB(255, 255, 255));
	dialogMessage.setTypedText(TypedText(T_DIALOG_MSG));	
	add(dialogMessage);
	
	buttonOK.setBitmaps(Bitmap(BITMAP_OK_112X56_ID), Bitmap(BITMAP_OK_112X56_P_ID));
	buttonOK.setAction(buttonClickedCallback);
	buttonOK.setXY(HAL::DISPLAY_WIDTH / 2 + buttonOK.getWidth() / 2, HAL::DISPLAY_HEIGHT / 4 * 3 - dialogMessage.getHeight() * 2 / 4);
	add(buttonOK);

	buttonCancel.setBitmaps(Bitmap(BITMAP_CANCEL_112X56_ID), Bitmap(BITMAP_CANCEL_112X56_P_ID));
	buttonCancel.setAction(buttonClickedCallback);
	buttonCancel.setXY(HAL::DISPLAY_WIDTH / 2 - buttonCancel.getWidth() * 3 / 2, HAL::DISPLAY_HEIGHT / 4 * 3 - dialogMessage.getHeight() * 2 / 4);
	add(buttonCancel);
}

ModalDialog::~ModalDialog()
{
}

void ModalDialog::invalidate() const
{
	Container::invalidate();
}

void ModalDialog::setResizeText()
{
	dialogMessage.resizeToCurrentText();
	dialogMessage.setXY(HAL::DISPLAY_WIDTH / 2 - dialogMessage.getWidth() / 2, HAL::DISPLAY_HEIGHT / 2 - dialogMessage.getHeight() * 3 / 4);
}

void ModalDialog::buttonClickedHandler(const AbstractButton& source)
{
	if (&buttonOK == &source)
	{
		this->setVisible(false);

		application().drawCachedAreas();


		if (buttonClickedThroughCallback && buttonClickedThroughCallback->isValid())
		{
			buttonClickedThroughCallback->execute(1);
		}
	}
	else if (&buttonCancel == &source)
	{
		this->setVisible(false);

		application().drawCachedAreas();

		if (buttonClickedThroughCallback && buttonClickedThroughCallback->isValid())
		{
			buttonClickedThroughCallback->execute(0);
		}
	}
}

void ModalDialog::handleTickEvent()
{
}
