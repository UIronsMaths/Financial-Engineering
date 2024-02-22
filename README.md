# Financial Engineering.
 This is an ongoing project creating a set of comprehensive programs, written in C++, to demonstrate the implementation of a variety of techniques in financial engineering such as options pricing.
 
## The project codebase.
The main Codebase is in the ***Codebase*** folder. The Codebase includes:

	stats.cpp/.h
	linearInterpolation.cpp/.h
	histogram.cpp/.h
	date.cpp/.h
 	calendar.cpp/.h
  	numericalIntegration.cpp/.h
   	pdf.cpp/.h

Detailed information about each of these classes is included after _Defunct Code_.

## The project unit tests.
The unit tests for these classes are situated in the ***Unit Tests*** folder. This is WITHIN the Codebase folder. The testing files are labelled using the convention:

	test_FILENAME.cpp/.h
Where FILENAME is the name of the class being tested.

## Defunct code.
Code that is defunct or obsolete (for example, code that has been replaced with a better implementation) that is still used for old project work is contained within the ***Defunct*** folder. This code serves no use to you unless you're curious about the history of the project.

Currently defunct code includes the classes in:

	euroOption.cpp/.h
 	payoff.cpp/.h
  and their unit tests.

## Project Roadmap.
Future modifications will include:

	Extending the portfolio class, adding writing functionality to reflect trader made changes.
 	Extending the options class, adding an assortment of options.
  	Extending the pdf class, adding an assortment of PDFs.
   	Introducing Monte Carlo pricing.
    	Introducing Finite Difference Method pricing.
     	Introducing stochastic parameter and jump diffusion models.

## Project Classes.
```stats``` is a class that allows the addition of data observations and includes methods that returns certain summary statistics of the data so far. It also includes a Random number generator for generating instances of a Standard Normally distributed random variable.
