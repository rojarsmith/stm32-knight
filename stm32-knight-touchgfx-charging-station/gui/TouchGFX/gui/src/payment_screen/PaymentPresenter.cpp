#include <gui/payment_screen/PaymentView.hpp>
#include <gui/payment_screen/PaymentPresenter.hpp>

PaymentPresenter::PaymentPresenter(PaymentView& v)
    : 
    BasePresenter(v),
    view(v)
{

}

void PaymentPresenter::activate()
{

}

void PaymentPresenter::deactivate()
{

}

//int PaymentPresenter::getWeather()
//{
//	return model->getWeather();
//}