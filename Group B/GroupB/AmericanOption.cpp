#include "AmericanOption.hpp"
//Empty constructor
AmericanOption::AmericanOption():S(0),K(0),r(0),sig(0),b(0),OptionPrice(0),Option()
{

}
//AmericanOption with fixed data
AmericanOption::AmericanOption(const struct OptionData& data):S(data.S),K(data.K),r(data.r),sig(data.sig),b(data.b),Option(data.type)
{
	OptionPrice = CalculateOptionPrice(S, K, r, sig, b, type);
}
//Copy constructor
AmericanOption::AmericanOption(const AmericanOption& source): S(source.S), K(source.K), r(source.r), sig(source.sig), b(source.b), Option(source)
{
	OptionPrice  = CalculateOptionPrice(S, K, r, sig, b, type);
}
//Destructor
AmericanOption::~AmericanOption()
{
}
//Operator 
AmericanOption& AmericanOption::operator=(const AmericanOption& source)
{
	if (this != &source)
	{
		Option::operator=(source);
		S = source.S;
		K = source.K;
		r = source.r;
		b = source.b;
		sig = source.sig;
		OptionPrice = source.OptionPrice;
		return *this;
	}
	return *this;
}
//To string representation of the object
string AmericanOption::toString() const
{
	if (type == CALL)
	{
		return string("\nType: Call") + 
			          "\nAsset Price: " + to_string(S)+
					  "\nStrike Price: " + to_string(K) + 
					  "\nRisk Free interest:" + to_string(r) + 
			          "\nCost of Carry:" + to_string(b) + 
			           "\nVolatility: " + to_string(sig) + 
			           "\nCall Price: " + to_string(OptionPrice) ;
	}
	else
	{
		return string("\nType: Put") +
			"\nAsset Price: " + to_string(S) +
			"\nStrike Price: " + to_string(K) +
			"\nRisk Free interest:" + to_string(r) +
			"\nCost of Carry:" + to_string(b) +
			"\nVolatility: " + to_string(sig) +
			"\nPut Price: " + to_string(OptionPrice);
	}
}
//StandardToggle that is Overloaded
void AmericanOption::Toggle()
{
	Option::Toggle();
	calculatePrice();
}
//Calculates an americanOptionprice from an array of fixed parameters nad a parameter type that the user specifies
vector<double> AmericanOption::CalculateWithParameter(vector<double>mesh, const enum ParameterType param)
{
	vector<double>optionprice;
	switch (param)
	{
	case IR:
		//The psuedo code is the same in the European Optionprice schemes
		//Loop through the parameters
		for (double r : mesh)
		{
			//Calculate price
			double price = CalculateOptionPrice(S, K, r, sig, b, type);
			//Push back the Optionprice
			optionprice.push_back(price);
		}
		break;
	case STOCKPRICE:
		for (double S : mesh)
		{
			double price = CalculateOptionPrice(S, K, r, sig, b, type);
			optionprice.push_back(price);
		}
		break;
	case STRIKEPRICE:
		for (double K : mesh)
		{
			double price = CalculateOptionPrice(S, K, r, sig, b, type);
			optionprice.push_back(price);
		}
		break;
	
	case VOLATILITY:
		for (double sig : mesh)
		{
			double price = CalculateOptionPrice(S, K, r, sig, b, type);
			optionprice.push_back(price);
		}
		break;
	}
	return optionprice;
}
//CalculatePrice
void AmericanOption::calculatePrice()
{
	double OP_PRICE = CalculateOptionPrice(S, K, r, sig, b, type);
	OptionPrice = OP_PRICE;
}
//Calculating Optionprice wtih parameters
double CalculateOptionPrice(double S, double K,double r, double sig, double b, const enum OptionType type)
{

	if (type == CALL)
	{
		double bsigmsquared = b / (sig * sig);
		double y1 = 0.5 - bsigmsquared + sqrt(pow((bsigmsquared - 0.5), 2) + (2 * r) / (sig * sig));
		return (K / (y1 - 1)) * pow((((y1-1)/y1) * (S/K)),y1);
	}
	else
	{
		double bsigmsquared = b / (sig * sig);
		double y2 = 0.5 - bsigmsquared  - sqrt(pow((bsigmsquared - 0.5), 2) + (2 * r) / (sig * sig));
		return (K / (1-y2)) * pow((((y2 - 1) / y2) * (S / K)), y2);
	}
}
//Generates a mesh of size n 
vector<double> GenerateMeshArray(double begin, double end, int n)
{
	vector<double> mesh(n + 1);
	mesh[0] = begin; mesh[mesh.size() - 1] = end;

	double h = (end - begin) / static_cast<double>(n);
	for (int j = 1; j < mesh.size() - 1; ++j)
	{
		mesh[j] = mesh[j - 1] + h;
	}

	return mesh;

}
//global function to Print
void print(vector<double> vec, const enum OptionType type, string datatype)
{
	int counter = 0;
	if (type == CALL)
	{
		cout << "(CALL)" << datatype << endl;
		for (double values : vec)
		{
			if (counter == 7)
			{
				cout << endl;
				counter = 0;
			}
			cout << values << "  ";
			counter++;

		}
		cout << endl;
		cout << endl;
	}
	else
	{
		cout << "(PUT)" << datatype << endl;
		for (double values : vec)
		{
			if (counter == 7)
			{
				cout << endl;
				counter = 0;
			}
			cout << values << "  ";
			counter++;

		}
		cout << endl;
		cout << endl;
	}
}