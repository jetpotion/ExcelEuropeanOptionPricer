#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP
//Import necessary directives
#include "Option.hpp"
#include "boost/math/distributions/normal.hpp"
#include "boost/math/distributions.hpp"
#include <vector>
#include <cmath>
#include <iostream>
using namespace boost::math;

class EuropeanOption : public Option
	//The private data fields of Option
{
private:
	double T;   // Expiry time
	double K;   // Strike price
	double sig; // volatility
	double r;   // Risk free interest rate
	double S;   // Current price of the underlying asset
	double b;   // Cost of carry
	double optionPrice;	//The price of the option

protected:
	virtual void calculatePrice();								//Calculate the price of an Option
public:
	EuropeanOption();											//Default constructor
	virtual ~EuropeanOption();									//Destructor of EuropeanOption
	EuropeanOption(const struct EuropeanOptionData& optiondata);//Constructor with fixed parameters and a type
	EuropeanOption(const EuropeanOption& option);				//Copy constructor
	EuropeanOption& operator=(const EuropeanOption& option);	//Assignment operator
	double Parity() const;										//Calculate parity
	double DeltaDiff(double S, double h) const;
	double GammaDiff(double S, double h) const;
	vector<double>calculatewithParameter(vector<double> mesh, const enum ParameterType type) const; //calculates option price from an array of parameters with all other data being constant
	vector<double>greekswithParameter(vector<double>mesh, const enum ParameterType type, const enum GREEKARRAYTYPE greek) const;		//Calculates Greeks from an array  of optiontype
	virtual string toString()const;
	virtual void Toggle();			//Override Toggle
	friend bool statisfyParity(double call, double put, const EuropeanOption& option);	//Calculate parity
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Vega() const;
	virtual double Theta() const;


};
/*Global functions*/
vector<double> generateMesh(double begin, double end, int n);
double CalculateOptionPrice(double T, double K, double sig, double r, double S, double b, const enum OptionType type);
double CalculateDelta(double T, double K, double sig, double r, double S, double b, const enum OptionType type);
double CalculateGamma(double T, double K, double sig, double r, double S, double b);
double CalculateVega(double T, double K, double sig, double r, double S, double b);
double CalculateTheta(double T, double K, double sig, double r, double S, double b, const enum OptionType type);
void print(vector<double> vec, enum OptionType type, string datatype);
//EuropeanOptionData structure
struct EuropeanOptionData
{
	enum OptionType type;
	double T; // Expiry time
	double K; // Strike price
	double sig; // volatility
	double r; // Risk free interest rate
	double S; // Current price of the underlying asset
	double b; //Cost of carry
};
enum ParameterType
{
	TIME,
	STRIKEPRICE,
	VOLATILITY,
	IR,
	STOCKPRICE
};
enum GREEKARRAYTYPE
{
	DELTA,
	GAMMA
};
#endif // ! OPTION_HPP

