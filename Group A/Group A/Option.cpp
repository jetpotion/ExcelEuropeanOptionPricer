#include"Option.hpp"
//Set the default option to be a Call option 
//Give the user a security type that gives a right but the not obligation to seel the underlying type
Option::Option(): type(CALL)
{

}
//Destructor
Option::~Option()
{

}
//Constructor defined with certain type
Option::Option(const enum OptionType& optiontype): type(optiontype)
{
}
//Copy constructor
Option::Option(const Option& option): type(option.type)
{
}
//Assignment operator
Option& Option ::operator=(const Option& option)
{
	//Prevent reassignemtn
	if (this == &option)
		return *this;
	type = option.type;
	return *this;

}
//A way to toggle between call and put easily
void Option::Toggle()
{
	type = ((type == CALL) ? PUT : CALL);
}