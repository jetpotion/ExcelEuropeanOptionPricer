#include "Option.hpp"

#include <vector>
#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP
class AmericanOption:public Option
{
	//Standard american Option pricing  parameters
private:
	double S;	//Underlying asset price
	double K;	//Strike price
	double r;	//Risk free interest rate
	double sig;	//Volatility
	double b;	//Cost of carry
	double OptionPrice;		///The option price


protected:
	virtual void calculatePrice();	//The overridden virutal Option method
public:
	AmericanOption();	                            //Generate american Option
	virtual ~AmericanOption();                      //Destructor
	AmericanOption(const struct OptionData& data);	//a constructor with overloaded parameters
	AmericanOption(const AmericanOption& source);	//Copy constructor of AmericanOption
	AmericanOption& operator=(const AmericanOption& source);	//Equality operator
	vector<double>CalculateWithParameter(vector<double>mesh, const enum ParameterType param); //Calculates the array of stock prices
	virtual string toString() const;				//A tostring representaion of AmericanOption
	virtual void Toggle();							//The toggle
	
};
//Allow the user to specify which type of parameter to price by in Caclulate with parameter type
enum ParameterType
{
	STRIKEPRICE,
	VOLATILITY,
	IR,
	STOCKPRICE
};
//Global functions
double CalculateOptionPrice(double S, double k, double r, double sig, double b,const enum OptionType type);
vector<double>GenerateMeshArray(double begin, double end, int n);
void print(vector<double> vec,const  enum OptionType type, string datatype);
#endif // !AMERICANOPTION_HPP

