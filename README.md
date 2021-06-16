# ExcelEuropeanOptionPricer
-__Utilities DJD__ is an embedded project folder library that supports ExcelVisualization,Exceptions,Matrix Operations(overloaded), and Range libraries. They supply the necessary vital Operations in the other project folders.

-__Group A__ calculates European options  with no dividend and prints out the output to console. It is also capable of pricing European Options with just an array of stockprices or interest rates or volatility or Time to Expiration(given every other parameter being constants).  It also calculates Option Greeks such as Deltas,Vegas and Gammas. All the calculations and pricing uses the black scholes-merton model and boost libraries to speed up computations.

-__Group B__ prices the Perpetual American option with a closed solution and prints out to console. This again uses the black scholes model for the perptual American Option.

-__Group C__ uses the Monte Carlo method to price European option and test out the Euler-Maruyama scheme to approximate the Black Scholes schotastic differential equations

-__Group D__ calculates Standard deviation and Standard Error of Monte Carlo method as described in Group C

-__Group E__ calculates the European Option and prints/graph them in Excel. It uses the COM binary scheme for Excel Visualization used in the UtilitiesDJD folder

-__Group F__ ises the Finite Difference method to calculate an approximation of Option Prices.

# Formula Used 

![ScreenShot](https://github.com/jetpotion/ExcelEuropeanOptionPricer/blob/master/Capture.PNG)
![New](https://github.com/jetpotion/ExcelEuropeanOptionPricer/blob/master/Capture1.PNG)
![Euler](https://github.com/jetpotion/ExcelEuropeanOptionPricer/blob/master/Capture3.PNG)
![MonteCarlo](https://github.com/jetpotion/ExcelEuropeanOptionPricer/blob/master/Capture4.PNG)
![Stock Price](https://github.com/jetpotion/ExcelEuropeanOptionPricer/blob/master/stockprice.PNG)

# Build instruction
- The Projects only support MSVC compilers and thus it is recommended that Visual Studio IDE is used.
- Clone from git or download the .zip file.
- Make sure you have the latest version of boost  C++ library installed. Follow these instructions to sucessfully build boost. 
https://www.boost.org/doc/libs/1_55_0/doc/html/bbv2/installation.html. The version of boost I used is 1_73_0.
- Make sure dependencies in the "Include additional directories" include the boost library and make sure you direct the path to UtilitiesDJD. Download all the folders at once.

