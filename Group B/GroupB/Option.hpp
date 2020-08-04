
#ifndef OPTION_HPP
#define OPTION_HPP
#include <string>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Option
{
protected:
	enum OptionType type;
	virtual void calculatePrice()= 0;	    //Calculate the price of an option. Should only be used by its classes and its classes.
public:
	Option();								//Default constructor
	virtual ~Option();						//Destructor
	Option(const enum OptionType& optiontype);//Constructor with Option type
	Option(const Option& option);			//Copy constructor
	Option& operator=(const Option& option);//Assignment operator
	virtual void Toggle();							//Switch the option type
	virtual string toString() const = 0;
};
//Type of OptionType
enum OptionType
{
	PUT,
	CALL
};
struct OptionData
{
	enum OptionType type;
	double S;	//Underlying asset price
	double K;	//Strike price
	double T;	//Time to expiration
	double r;	//Risk free interest rate
	double sig;	//Volatility
	double b;	//Cost of carry
};
#endif // !OPTION_HPP
