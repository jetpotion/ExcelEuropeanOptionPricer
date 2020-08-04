#include "EuropeanOption.hpp"
//Set it to default call option and set all the data fields to be zero and set it a default call option
EuropeanOption::EuropeanOption():T(0),K(0),sig(0),r(0),S(0),b(0),optionPrice(0), Option()
{
}
//Constructor with fixed parameters and create a type of Option
EuropeanOption::EuropeanOption(const struct EuropeanOptionData& optiondata): 
	T(optiondata.T),K(optiondata.K),sig(optiondata.sig),
	r(optiondata.r),S(optiondata.S),b(optiondata.b),Option(optiondata.type)
{
	optionPrice = CalculateOptionPrice(T, K, sig, r, S, b, optiondata.type);
}
//Copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& option): 
	T(option.T),K(option.K),sig(option.sig),
	r(option.r),S(option.S),b(option.b),Option(option)
{
	optionPrice = CalculateOptionPrice(T, K, sig, r, S, b, option.type);
}
//Destructor
EuropeanOption::~EuropeanOption()
{

}
EuropeanOption& EuropeanOption:: operator=(const EuropeanOption& option)
{
	if (this != &option)
	{
		Option::operator=(option);
		double T = option.T;   // Expiry time
		double K =  option.K;   // Strike price
		double sig = option.sig; // volatility
		double r = option.r;   // Risk free interest rate
		double S = option.S;   // Current price of the underlying asset
		double b = option.b;   // Cost of carry
		double optionPrice = option.optionPrice;	//The price of the option
		return *this;
	}
	return *this;
}
double EuropeanOption::Parity() const
{
	
	if (type == CALL)
	{
		double parity = optionPrice + K * exp(-r * T) - S;
		double rounded = (int)(parity * 10000000.0) / 10000000.0;
		return rounded;
	}
	//Calculate the parity of Put option
	else
	{
		double parity = optionPrice + S - K * exp(-r * T);
		double rounded = (int)(parity * 10000000.0) / 10000000.0;
		return rounded;
	}
}
//A single function to calculate an array of optionprices depending the option parameter that hte user specifies
vector<double>EuropeanOption::calculatewithParameter(vector<double>mesh,const enum ParameterType param) const
{
	vector<double>arraystock;
	double PriceOfOption;
	switch (param)
	{
	case IR:
		//(IMPORTANT OPTIONTYPE)
		 /* The following is the same psuedo code for each case type

		 case:  OptionType
		 for(double paramtype:mesh)
		 {
			//store option prce into arraystock
		 }
		 */
		for (double r : mesh)
		{
				PriceOfOption = CalculateOptionPrice(T, K, sig, r, S, b, type);
				arraystock.push_back(PriceOfOption);
			
		}
		break;
	case TIME:
		for (double T : mesh)
		{
			PriceOfOption = CalculateOptionPrice(T, K, sig, r, S, b, type);
			arraystock.push_back(PriceOfOption);
		}
		break;
	case STRIKEPRICE:
		for (double K : mesh)
		{
			PriceOfOption = CalculateOptionPrice(T, K, sig, r, S, b, type);
			arraystock.push_back(PriceOfOption);
		}
		break;
	case VOLATILITY:
		for (double sig : mesh)
		{
			PriceOfOption = CalculateOptionPrice(T, K, sig, r, S, b, type);
			arraystock.push_back(PriceOfOption);
		}
		break;
	case STOCKPRICE:
		for (double S : mesh)
		{
			PriceOfOption = CalculateOptionPrice(T, K, sig, r, S, b, type);
			arraystock.push_back(PriceOfOption);
		}
		break;
	}
	
	return arraystock;
}
//Calculate Delta of the Option Via through the Delta Global function
double EuropeanOption::Delta() const
{
	return CalculateDelta(T, K, sig, r, S, b, type);
 }
//Calculate Gamma of the Option through the Gamma global function
 double EuropeanOption::Gamma() const
 {
	 return CalculateGamma(T, K, sig, r, S, b);
 }
 //Calculate Vega of the Option throug hthe vega Global function
 double EuropeanOption::Vega() const
 {
	 return CalculateVega(T, K, sig, r, S, b);
 }
 //Calculate The theta of the option through Theta global function
 double EuropeanOption::Theta() const
 {
	 return CalculateTheta(T, K, sig, r, S, b, type);
 }
 //Compute all Price of options with global function 
 double EuropeanOption::DeltaDiff(double S, double h) const
 {
	 return (CalculateOptionPrice(T, K, sig, r, S + h, b, type)
		 - CalculateOptionPrice(T, K, sig, r, S - h, b, type))/(2*h) ;
	 
 }
 //Calculate the Gamma by an approxmization
 double EuropeanOption::GammaDiff( double S,double h) const
 {
	 return ((CalculateOptionPrice(T, K, sig, r, S + h, b, type)
		 + (2.0*CalculateOptionPrice(T, K, sig, r, S, b, type))
		 - CalculateOptionPrice(T, K, sig, r, S - h, b, type))) / (h * h);
 }
 //A single function to calculate an array of greeks and calculate a specific greek arrya type depending on the user
 vector<double> EuropeanOption::greekswithParameter(vector<double>mesh, const enum ParameterType arg, const enum GREEKARRAYTYPE greektype) const	//Calculates Greeks from an array  of optiontype
 {
	 vector<double>arrayofgreeks;
	 //Switch through withc parameters
	 switch (arg)
	 {
		 //(IMPORTANT OPTIONTYPE)
		 /* The following is the same psuedo code for each case type

		 case:  OptionType
		 for(double paramtype:mesh)
		 {
			if the user wants an array of Gamma: Calculate Gamma and store into array of greeks
			if the user wants array of Delta:  Specify which option type he has; Then calculate Delta and store into array of greeks
		 }
		 */
	 case IR:

		 
		 for (double r : mesh)
		 {
			
			 if (greektype == GAMMA)
				 arrayofgreeks.push_back(CalculateGamma(T,K,sig,r,S,b));
			 else
				 arrayofgreeks.push_back(CalculateDelta(T, K, sig, r, S, b, type));

		 }
			 break;
	 case TIME:
		 for (double T : mesh)
		 {
			 if (greektype == GAMMA)
				 arrayofgreeks.push_back(CalculateGamma(T, K, sig, r, S, b));
			 else
				 arrayofgreeks.push_back(CalculateDelta(T, K, sig, r, S, b, type));
			 
			 
		 }
			 break;
	 case STRIKEPRICE:
		 for (double K : mesh)
		 {
			 if (greektype == GAMMA)
				 arrayofgreeks.push_back(CalculateGamma(T, K, sig, r, S, b));
			 else
				 arrayofgreeks.push_back(CalculateDelta(T, K, sig, r, S, b, type));
			
			 
		 }
			 break;
	 case VOLATILITY:
		 for (double sig : mesh)
		 {
			 if (greektype == GAMMA)
				 arrayofgreeks.push_back(CalculateGamma(T, K, sig, r, S, b));
			 else
				 arrayofgreeks.push_back(CalculateDelta(T, K, sig, r, S, b, type));
			 
		 }
			 break;
	 case STOCKPRICE:
		 for (double S : mesh)
		 {
			 if (greektype == GAMMA)
				 arrayofgreeks.push_back(CalculateGamma(T, K, sig, r, S, b));
			 else
				 arrayofgreeks.push_back(CalculateDelta(T, K, sig, r, S, b, type));
			 
		 }
			 break;
	 }
	 return arrayofgreeks;
 }
void EuropeanOption::Toggle()
{
	Option::Toggle();	//Call the parent class Toggle but also recalculate the prices
	calculatePrice();
}

//calculate the price of both calls and Puts. Return the price specification
void EuropeanOption::calculatePrice()
{
	
	optionPrice= CalculateOptionPrice(T, K, sig, r, S, b, type);
}
//To string representation of the object
string EuropeanOption:: toString() const
{
	if (type == CALL)
	{
		return string("Type : CALL\n")  + 
				"Time to expiration:" + to_string(T) 
		    	+ "\nVolatility:" + to_string(sig) +  
				"\nRisk Free interest:" + to_string(r) + 
				"\nUnderlying stock price:" + to_string(S) +
				"\nStike Price:" + to_string(K) + 
				"\nCost of carry:" + to_string(b) + 
			    "\n(Call Price:" + to_string(optionPrice);
	}
	return string("Type : PUT\n") +
		"Time to expiration:" + to_string(T)
		+"\nVolatility:" + to_string(sig) +
		"\nRisk Free interest:" + to_string(r) +
		"\nUnderlying stock price:" + to_string(S) +
		"\nStike Price:" + to_string(K) +
		"\nCost of carry:" + to_string(b) +
		"\nPut Price:" +  to_string(optionPrice);}
//Calculate The  OptionPrice with standard option parameters with a given option type
double CalculateOptionPrice(double T, double K, double sig, double r, double S, double b, const enum OptionType type)
{
	normal_distribution<double> Guassian(0.0, 1.0);
	//Calaculate d1
	double d1 = (log(S / K) + (b + pow(sig, 2) / 2) * T) / (sig * sqrt(T));

	//Calculate d2
	double d2 = d1 - sig * sqrt(T);
	if (type == CALL)
		return  S * exp((b - r) * T) * cdf(Guassian, d1) - K * exp(-r * T) * cdf(Guassian, d2);
	else
		return K * exp(-r * T) * cdf(Guassian, -d2) - S * exp((b - r) * T) * cdf(Guassian, -d1);

}
//Global function to calculate Delta with standard option parameters but with a optiontype
double CalculateDelta(double T, double K, double sig, double r, double S, double b, const enum OptionType type)
{
	normal_distribution<double> Guassian(0.0, 1.0);
	double d1 = (log(S / K) + (b + pow(sig, 2) / 2) * T) / (sig * sqrt(T));
	double CallDelta = exp((b - r) * T) * cdf(Guassian, d1);
	return ((type == CALL) ? CallDelta : CallDelta - exp((b - r) * T));
}
//Global function to calculate Gamma with standard option Price parameters
double CalculateGamma(double T, double K, double sig, double r, double S, double b)
{
	normal_distribution<double> Guassian(0.0, 1.0);
	double d1 = (log(S / K) + (b + pow(sig, 2) / 2) * T) / (sig * sqrt(T));
	return (pdf(Guassian, d1) * exp((b - r) * T)) / (S * sig * sqrt(T));
}
//Global function to Calculate Vega with standard option Price paramters
double CalculateVega(double T, double K, double sig, double r, double S, double b)
{
	normal_distribution<double> Guassian(0.0, 1.0);
	double d1 = (log(S / K) + (b + pow(sig, 2) / 2) * T) / (sig * sqrt(T));
	return S * sqrt(T) * exp((b - r) * T) * cdf(Guassian, d1);
}
//Global function to Calculate delta with the standard Option price parameters
double CalculateTheta(double T, double K, double sig, double r, double S, double b, const enum OptionType type)
{
	normal_distribution<double > Guassian(0, 1);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - sig * sqrt(T);
	double callTheta = -S * sig * exp((b - r) * T) * pdf(Guassian, d1) / (2 * sqrt(T))
		- (b - r) * S * exp((b - r) * T) * cdf(Guassian, d1) - r * K * exp(-r * T) * cdf(Guassian, d2);
	double putTheta = callTheta + r * K * exp(-r * T) + S * exp((b - r) * T) * (b - r);
	return ((type == CALL) ? callTheta : putTheta);
}
//A boolean function to return if its satisifies parity, given other option parameters in the object instance
//call: The Call price of a function
//Put: The Put price of a function
bool statisfyParity(double call, double put, const EuropeanOption& option)
{
	double TOLERANCE = 0.01;
	double LEFTPRICE = call + option.K * exp(-option.r * option.T);
	double RIGHTPRICE = put + option.S;
	double difference = abs(abs(LEFTPRICE) - abs(RIGHTPRICE));
	
	if(difference  <= TOLERANCE)
		return true;
	
	return false;
}
//Create a  vector mesh seperated by size n
//Begin:The beging start point of the function
//End: The start point of the vector
//N: How many equal distributed data points between begin and end 
vector<double> generateMesh(double begin, double end, int n)
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
//Generic Print function to print array type
//Vec: The vector to print out
//Type: To indicate if its a call/put option
//Datatype: The string title

void print(vector<double> vec, enum OptionType type, string datatype)
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