#ifndef CONTEXTNAMEVALUE_HPP
#define CONTEXTNAMEVALUE_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

using namespace touchgfx;

class ContextNameValue : public Container
{
public:
	ContextNameValue();
	virtual ~ContextNameValue();

	void initialize(char * name, float value);
	void updateValue(float value);
	void updateValue(int value);
private:
	static const uint16_t NAME_TXT_SIZE = 20;
	static const uint16_t VALUE_TXT_SIZE = 10;

	TextAreaWithOneWildcard name_;
	Unicode::UnicodeChar name_txt_buffer_[NAME_TXT_SIZE];
	TextAreaWithOneWildcard value_;
	Unicode::UnicodeChar value_txt_buffer_[VALUE_TXT_SIZE];
};

#endif /* CONTEXTNAMEVALUE_HPP */