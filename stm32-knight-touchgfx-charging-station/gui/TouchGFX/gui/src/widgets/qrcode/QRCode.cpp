#include <gui/widgets/qrcode/QRCode.hpp>
#include <stdlib.h>

const char *text = "http://www.edtc.com/sb_readmore.php?id=23#buy";

QRCode::QRCode()
	: pcount_(0)
{

}

QRCode::~QRCode()
{
	QrCode::gc();
	gc();
}

void QRCode::test()
{	
	if (0 == pcount_)
	{
		QrCode::encodeText(text, QrCode::Ecc::MEDIUM);
		pcount_++;
		qrcode_ = new QrCode(QrCode::encodeText(text, QrCode::Ecc::MEDIUM));
	}
}

void QRCode::setRawData(const char * data)
{	
	if (0 == pcount_)
	{
		QrCode::encodeText(data, QrCode::Ecc::MEDIUM);
		pcount_++;
		qrcode_ = new QrCode(QrCode::encodeText(data, QrCode::Ecc::MEDIUM));
	}
}

bool QRCode::at(uint16_t x, uint16_t y) const
{
	return qrcode_ == nullptr ? false : qrcode_->getModule(x, y);
}

uint16_t QRCode::getWidth() const
{	
    return qrcode_ == nullptr ? 0 : qrcode_->getSize();
}

uint16_t QRCode::getHeight() const
{
    return qrcode_ == nullptr ? 0 : qrcode_->getSize();	
}

bool QRCode::gc()
{
	if (1 == pcount_)
	{
		pcount_--;		
		delete qrcode_;
		return true;
	}
	return false;
}