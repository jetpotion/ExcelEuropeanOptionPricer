#include <string>

#include "boost/tuple/tuple.hpp"
#ifndef OPTION_HPP
#define OPTION_HPP
using namespace std;
class Option
{
protected:
	enum OptionType type;
	virtual void calculatePrice() = 0;	    //Calculate the price of an option. Should only be used by its classes and its classes.
public:
	Option();								//Default constructor
	virtual ~Option();						//Destructor
	Option(const enum OptionType& optiontype);//Constructor with Option type
	Option(const Option& option);			//Copy constructor
	Option& operator=(const Option& option);//Assignment operator
	virtual void Toggle();							//Switch the option type
	virtual string toString() const = 0;
};
enum OptionType
{
	PUT,
	CALL
};

#endif // !OPTION_HPP
