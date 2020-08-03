# ExcelEuropeanOptionPricer
EuropeanOptionPricer
-Utilities DJD is an embedded project folder library that supports ExcelVisualization,Exceptions,Matrix Operations(overloaded), and Range supports for the program.
-Group A prices European Options  with given Carry and prints out the output to console. It is also capable pricing EuropeanOption option with just an array of stockprices or interest rates or volatility or Time to Expiration.  It also calculates Option Greeks such as Deltas,Vegas and Gamma in a similar fashion as European Options. All the calculations and pricing using the black scholes-merton model and boost libraries to speed up computations
-Group B prices the Perpetual American Option with a closed Solution and prints out of console. Again using the black scholes model for the perptual American Option.
-Group C uses the monte carlo method to price European Option and test out the Euler-Maruyama scheme to approximate the black scholes schotastic differential equations
-Group D calculates Standard deviation and Standard Error of monte carlo method as described in Group C
-Group E Calculates the EuropeanOption and prints them out to Excel and graph  them. It uses the COM binary scheme for Excel Visualization used in the UtilitiesDJD folder
-Group F Uses the finite difference method to calculate an approximation of OptionPrices.

# Build instruction
- The Projects only support MSVC compilers. So only visual studio is supported.
- Clone from git or download the .zip file
- Make sure you have the latest version of boost  C++ library installed. Follow these instructions to sucessfully build boost. 
https://www.boost.org/doc/libs/1_55_0/doc/html/bbv2/installation.html
- Make sure dependencies in the "Include additional directories" include the boost library

