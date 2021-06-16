#include "UtilitiesDJD/ExcelDriver/ExcelDriverLite.hpp"
#include "UtilitiesDJD/ExcelDriver/Utilities.hpp"
#include "EuropeanOption.hpp"
#include <cmath>
#include <list>
#include <string>
#include <vector>
int main()
{


	EuropeanOptionData data;
	typedef boost::tuple<double, double, double, double, double> batches;
	vector<batches> vecBatch;
	//Load the data of tuples.
	vecBatch.push_back(boost::make_tuple(0.25, 65.0, 0.30, 0.08, 60.0));
	vecBatch.push_back(boost::make_tuple(1.0, 100.0, 0.2, 0.0, 100.0));
	vecBatch.push_back(boost::make_tuple(1.0, 10.0, 0.50, 0.12, 5.0));
	vecBatch.push_back(boost::make_tuple(30.0, 100.0, 0.30, 0.08, 100.0));
	ExcelDriver visualiser;
	vector<double> stockprices = generateMesh(10.0, 50.0, 41);



	std::list<std::string> labels;
	std::list<std::vector<double> > curves;
	double T, K, sig, r, S, b;
	int batch_number = 0;
	for (batches batch : vecBatch)
	{
		T = batch.get<0>();
		K = batch.get<1>();
		sig = batch.get<2>();
		r = batch.get<3>();
		S = batch.get<4>();
		b = r;
		//First create a European option data struct and initialize them 
		data.T = T;
		data.K = K;
		data.sig = sig;
		data.r = r;
		data.S = S;
		data.b = b;
		data.type = CALL;

		EuropeanOption d1(data);
		labels.push_back("Batch: " + to_string((batch_number + 1)) + "(C)");
		vector<double>call_optionprice = d1.calculatewithParameter(stockprices, STOCKPRICE);
		curves.push_back(call_optionprice);
		//switch  optiontype 
		d1.Toggle();
		labels.push_back("Batch: " + to_string((batch_number + 1)) + "(P)");
		vector<double>put_optionprice = d1.calculatewithParameter(stockprices, STOCKPRICE);
		//increment

		curves.push_back(put_optionprice);
		batch_number++;

	}
	visualiser.MakeVisible(true);
	visualiser.CreateChart(stockprices, labels, curves, "Option_Price vs Stock_Price", "Stock Prices", "OptionPrices");
}