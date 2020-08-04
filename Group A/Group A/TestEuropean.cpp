#include "EuropeanOption.hpp"

#include "Option.hpp"
#include <list>

int main()
{
	//Create a tuple of EuropeanOption data
	EuropeanOptionData data;
	typedef boost::tuple<double, double, double, double, double> batches;
	vector<batches> vecBatch;
	vecBatch.push_back(boost::make_tuple(0.25, 65, 0.30, 0.08, 60));
	vecBatch.push_back(boost::make_tuple(1, 100, 0.2, 0.0, 100));
	vecBatch.push_back(boost::make_tuple(1, 10, 0.50, 0.12, 5));
	vecBatch.push_back(boost::make_tuple(30, 100, 0.30, 0.08, 100));
	
	vector<double> stockprices = generateMesh(10.0, 50.0, 40);
	vector<double> expiry_time = generateMesh(0.1, 1.0, 40);
	vector<double> volatility = generateMesh(0.1, 1.0, 40);
	
	
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
		//Calculate Call parity price
		double call_parity = d1.Parity();
		cout << "Batch " << batch_number + 1 << endl;
		cout << d1.toString() << endl;
		//Calculate  put option prices with with an array of stockprice,expirytime,volatility with all other parameters fixed
		vector<double>call_option_STOCKRPICE= d1.calculatewithParameter(stockprices, STOCKPRICE);
		vector<double>call_option_IR = d1.calculatewithParameter(expiry_time, IR);
		vector<double>call_option_volatility = d1.calculatewithParameter(volatility, VOLATILITY);
		d1.Toggle();
		//Calculate Put parity price
		double put_parity = d1.Parity();
		//Calculate  put option prices with with an array of stockprice,expirytime,volatility with all other parameters fixed
		vector<double>put_option_STOCKRPICE = d1.calculatewithParameter(stockprices, STOCKPRICE);
		vector<double>put_option_IR = d1.calculatewithParameter(expiry_time, IR);
		vector<double>put_option_volatility = d1.calculatewithParameter(volatility, VOLATILITY);
		cout << endl;
		cout << d1.toString() << endl;
		cout << endl;
		cout << "Call Parity price: " << call_parity << endl;
		cout << "Put Parity Price: " << put_parity << endl;
		cout << "Satisfy parity?: " <<std::boolalpha  << statisfyParity(call_parity, put_parity, d1) << endl;
		print(call_option_STOCKRPICE, CALL, "(Array_stockPrice)");
		print(call_option_IR, CALL, "(Array_InterestRate)");
		print(call_option_volatility, CALL, "(Array_Volatility)");
		print(put_option_STOCKRPICE, PUT, "(Array_stockPrice)");
		print(put_option_IR, PUT, "(Array_InterestRate)");
		print(put_option_volatility, PUT, "(Array_Volatility)");
		
		batch_number++;
		
	}
	data.K = 100.0;
	data.S = 105.0;
	data.T = 0.5;
	data.r = 0.1;
	data.b = 0;
	data.sig = 0.36;
	data.type = CALL;
	EuropeanOption d2(data);
	cout << d2.toString() << endl;
	cout << "Call Delta: " << d2.Delta() << endl;
	

	d2.Toggle(); //Were now in put
	cout << "Put Delta: " << d2.Delta() << endl;

	vector<double>delta_put = d2.greekswithParameter(stockprices, STOCKPRICE, DELTA);
	vector<double>gamma_put = d2.greekswithParameter(stockprices, STOCKPRICE, GAMMA);
	d2.Toggle(); //Were now in Call
	vector<double>delta_call = d2.greekswithParameter(stockprices, STOCKPRICE, DELTA);
	vector<double>gamma_call = d2.greekswithParameter(stockprices, STOCKPRICE, GAMMA);
	print(delta_call, CALL, "(Delta_CALL_Stockprice");
	print(gamma_call, CALL, "(Gamma_CALL_Stockprice");
	print(delta_put, PUT, "(Delta_PUT_Stockprice");
	print(gamma_put, PUT, "(Gamma_PUT_Stockprice");
	//Now redo calculations for part A,B) with the difference methodd
	vector<double>h = { 0.001,0.01,0.1 };
	for (double hval : h)
	{
		cout << "S = " << data.S << ", h = " << hval << ", Gamma of Call = " << d2.GammaDiff(data.S,hval) << endl;
		d2.Toggle(); //Turn into Put
		cout << "S = " << data.S << ", h = " << hval << ",Delta of Put = " << d2.DeltaDiff(data.S,hval) << endl;
		d2.Toggle();	//Put it back to call

	}
	//Part B with the divided difference
	cout << endl;
	for (double price : stockprices)
	{
		for (double hval : h)
		{
			cout << "S = " << price << ", h = " << hval << ", Gamma of Call = " << d2.GammaDiff(price, hval) << endl;
			d2.Toggle(); //Turn into Put
			cout << "S = " << price << ", h = " << hval << ", Delta of Put = " << d2.DeltaDiff(price, hval) << endl;
			d2.Toggle();	//Put it back to call
		}
	}


	

	
}