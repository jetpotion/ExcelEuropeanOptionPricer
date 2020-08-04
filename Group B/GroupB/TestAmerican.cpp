#include "AmericanOption.hpp"

int main()
{
	//First compute individual stockPrices
	OptionData data;
	data.K = 100;
	data.sig = 0.1;
	data.r = 0.1;
	data.b = 0.02;
	data.S = 110;
	data.type = CALL;
	AmericanOption american(data);
	cout << american.toString() << endl;
	//Turn into Put
	american.Toggle(); 
	cout << american.toString() << endl;
	//Now do part C,D(Were still in put mode)
	vector<double>stockprices = GenerateMeshArray(10, 50, 40);
	vector<double>optionprice = american.CalculateWithParameter(stockprices, STOCKPRICE);
	print(optionprice, PUT, "(Put price with Array of StockPrice)");
	american.Toggle();
	print(optionprice, CALL, "(Call Price with Array of StockPrice");
	

}