# Financial Engineering.
 This is an ongoing project.
 
 There are two goals:
 
 	1. The main aim of this project is to create a C++ library for financial engineering. 
  	The reasoning is purely selfish, a library for financial engineering would allow me to more easily conduct my academic research.
   
  	2. Once the library is constructed the next goal is to build it into a desktop application.

This project is written in C++ as it's my "native" programming language and is well suited to the performance demanding tasks of financial engineering. It also allows me to utitilise GPGPU programming for the more advanced tasks such as monte carlo and Fourier transforms.
 
## The project codebase.
The main Codebase is in the ***Codebase*** folder. The Codebase includes:

	stats.cpp/.h
	linearInterpolation.cpp/.h
	histogram.cpp/.h
	date.cpp/.h
  	numericalIntegration.cpp/.h
   	pdf.cpp/.h
	rootFinding.cpp/.h
	portfolioManagement.cpp/.h
	gilt.cpp/.h
	options.cpp/.h

Detailed information about each of these classes is included after _Defunct Code_.

## The project unit tests.
The unit tests for these classes are situated in the ***Unit Tests*** folder. This is WITHIN the Codebase folder. The testing files are labelled using the convention:

	test_FILENAME.cpp/.h
Where FILENAME is the name of the class being tested.

## Defunct code.
Code that is defunct or obsolete (for example, code that has been replaced with a better implementation) that is still used for old project work or for reference is contained within the ***Defunct*** folder. This code serves no use to you unless you're curious about the history of the project.

Currently defunct code includes the classes in:

	euroOption.cpp/.h
 	payoff.cpp/.h
  and their unit tests.

## Project Classes.
```stats``` is a class that allows the addition of data observations (both single observations and pair observation) and includes methods that returns certain summary statistics of the data so far. These include covariance and correlation. It also includes a Random number generator for generating instances of a Standard Normally distributed random variable.

```linearInterpolation``` is a class that provides a method for adding your data programmatically and a method for finding, by linear interpolation, the value at a specified coordinate.

```date``` is a class that implements Microsoft Excel style date objects. It allows you to modify the date, find the difference in days between two dates, determine whether or not a date is a good business day, and to roll to the next good business day if not. Included with this class is the calendar class which allows the user to add known holidays (as the dates for which can change year to year).

## Project Roadmap.
Future modifications will include:

	Extending the numerical integration class, removing limitations/adding user choice.
 	Extending the portfolio class, adding writing functionality to reflect trader made changes.
 	Extending the options class, adding an assortment of options.
  	Extending the pdf class, adding an assortment of PDFs.
   
   	Introducing Monte Carlo pricing.
	Introducing Finite Difference Method pricing.
	Introducing stochastic parameter and jump diffusion models.

Up next is: **Introducing Finite Difference Method pricing**.
