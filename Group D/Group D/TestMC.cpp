// HardCoded.cpp
//
// C++ code to price an option, essential algorithms.
//
// We take CEV model with a choice of the elaticity parameter
// and the Euler method. We give option price and number of times
// S hits the origin.
//
// (C) Datasim Education BC 2008-2011
//

#include "OptionData.hpp" 
#include "UtilitiesDJD/RNG/NormalGenerator.hpp"
#include "UtilitiesDJD/Geometry/Range.cpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/tuple/tuple.hpp"
#include <cmath>
#include <numeric>
#include <iostream>
#include <vector>
using namespace std;
template <class T> void print(const std::vector<T>& myList)
{  // A generic print function for vectors

	std::cout << std::endl << "Size of vector is " << myList.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	typename std::vector<T>::const_iterator i;
	for (i = myList.begin(); i != myList.end(); ++i)
	{
		std::cout << *i << ",";

	}

	std::cout << "]\n";
}
//Create a single method of standard error that returns the SD/SE inside a single tuple
template<typename T = double>
boost::tuple <T,T> standardError(const vector<T>& price,const T& r,const T& Time)
{
	T values_squared(0),sum_values(0);
	for (int i = 0; i < price.size(); i++)
	{
		values_squared += pow(price[i],2);
		sum_values += price[i];
	}

	int M = price.size();
	T sd = sqrt(values_squared - 1 / M * pow(sum_values,2)) * exp(-r * Time) / ((double)(M - 1.0));
	T se = sd / sqrt(M);

	return boost::make_tuple(sd, se);
}
namespace SDEDefinition
{ // Defines drift + diffusion + data

	OptionData* data;				// The data for the option MC

	double drift(double t, double X)
	{ // Drift term

		return (data->r) * X; // r - D
	}


	double diffusion(double t, double X)
	{ // Diffusion term

		double betaCEV = 1.0;
		return data->sig * pow(X, betaCEV);

	}

	double diffusionDerivative(double t, double X)
	{ // Diffusion term, needed for the Milstein method

		double betaCEV = 1.0;
		return 0.5 * (data->sig) * (betaCEV)*pow(X, 2.0 * betaCEV - 1.0);
	}
	
} // End of namespace


int main()
{
	std::cout << "1 factor MC with explicit Euler\n";
	typedef boost::tuple<double, double,double,double,double> batches;
	vector<batches>batch;
	batch.push_back(boost::make_tuple(0.25, 65, 0.3, 0.08, 60));
	batch.push_back(boost::make_tuple(1.0,100, 0.2, 0.00, 100));

	// NormalGenerator is a base class
	NormalGenerator* myNormal = new BoostNormal();
	vector<double>optionprice;
	int batch_number= 0;
	for (batches bucket : batch)
	{
		double T = bucket.get<0>();
		double K = bucket.get<1>();
		double sig = bucket.get<2>();
		double r = bucket.get<3>();
		double S_0 = bucket.get<4>();
		OptionData myOption;
		myOption.T = T;
		myOption.K = K;
		myOption.sig = sig;
		myOption.r = r;
		
		long N = 100;
		std::cout << "Number of subintervals in time: ";
		std::cin >> N;

		// Create the basic SDE (Context class)
		Range<double> range(0.0, myOption.T);
		double VOld = S_0;
		double VNew = 0;

		std::vector<double> x = range.mesh(N);


		// V2 mediator stuff
		long NSim = 50000;
		std::cout << "Number of simulations: ";
		std::cin >> NSim;

		double k = myOption.T / double(N);
		double sqrk = sqrt(k);

		// Normal random number
		double dW;
		double price = 0.0;	// Option price


		using namespace SDEDefinition;
		SDEDefinition::data = &myOption;

		//std::vector<double> res;
		int coun = 0; // Number of times S hits origin

		vector<double>optionprice1;
		vector<double>optionprice2;
		double price1 = 0;
		double price2 = 0;
		// A.
		for (long i = 1; i <= NSim; ++i)
		{ // Calculate a path at each iteration

			if ((i / 10000) * 10000 == i)
			{// Give status after each 1000th iteration

				std::cout << i << std::endl;
			}

			VOld = S_0;
			for (unsigned long index = 1; index < x.size(); ++index)
			{

				// Create a random number
				dW = myNormal->getNormal();

				// The FDM (in this case explicit Euler)
				VNew = VOld + (k * drift(x[index - 1], VOld))
					+ (sqrk * diffusion(x[index - 1], VOld) * dW);

				VOld = VNew;
				// Spurious values
				if (VNew <= 0.0) coun++;
			}
			//Make it Call
			myOption.type = 1;
			double tmp = myOption.myPayOffFunction(VNew);
			price1 += ((tmp) / (double)NSim) * exp(-myOption.r * myOption.T);
			
			optionprice1.push_back(price1);
			//Make it a put
			myOption.type = -1;
			tmp = myOption.myPayOffFunction(VNew);
			price2 += ((tmp) / (double)NSim) * exp(-myOption.r * myOption.T);
			optionprice2.push_back(price2);
		}
		std::cout << "Price, after discounting: Call = " << price1 << ", Put = " << price2 << std::endl;
		std::cout << "Number of times origin is hit: " << coun << endl;
		//Now get the vector with SD/SE
		boost::tuple<double, double>sd_se = standardError<>(optionprice1, myOption.r, myOption.T);
		boost::tuple<double, double>sd_se1 = standardError<>(optionprice2, myOption.r, myOption.T);
		std::cout << "CALL SD " << "(Batch Number: " << batch_number + 1 <<  ")" << endl;
		std::cout << " SD: " << sd_se.get<0>()<< endl;
		std::cout << " SE: " << sd_se.get<1>() << endl;
		std::cout << "Put SD " << "(Batch Number: " << batch_number + 1 << ")" << endl;
		std::cout << " SD: " << sd_se1.get<0>() << endl;
		std::cout << " SE: " << sd_se1.get<1>() << endl;
		batch_number++;
		price1= 0;
		price2 = 0;
		optionprice1.clear();
		optionprice2.clear();
		
	}

	// Cleanup; V2 use scoped pointer
	delete myNormal;

	
	return 0;
}