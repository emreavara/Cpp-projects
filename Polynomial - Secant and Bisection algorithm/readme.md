In this project secant and bisection algorithms are implemented in order to 
solve f(x)=0 for any given polynomial f. This program takes the coefficients of
the function, initial guesses and the tolerance value as command line arguments
and return the resulting values of x as well as the numbers of iterations for 
each method. I implemented both methods separately first. Then I used a hybrid
method where I started with bisection methods for the first two iterations and
then continued with secant method for the rest of the iterations. This program 
prints out the number of iterations required for each of the 3 methods 
(i.e., bisection, secant, and hybrid).

To run the program you should compile the code. This program needs at least 5
command line arguments. 2 or more for coefficients(in float),(The las 3 digits
always have the same funtion.) 2 for initial guesses(in float), and 1 for 
tolerance (in float i.e. 0.001). As a result you should write:

		"2 2 -7 1 -7 1.5 1.8 0.001"

You need to write the directory of these files in cmd.
(i.e. C:\Users\Administrator\Desktop\source.exe 2 2 -7 1 -7 1.5 1.8 0.001 )

The program will indicate problems if there is.(i.e. if there are less than 5 
line arguments or if x0<x1)
