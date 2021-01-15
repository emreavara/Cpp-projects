#include<iostream>
#include<cmath>
using namespace std;

class Poly_class{ // Polynomial class 
	int power;
	public:
		float* coefficient; // coefficients of Polynomial
		Poly_class():coefficient(new float[power+1]){} // constructor of class
		void set_power(int a); // setting power 
		float set_poly(float x){ // Calculation of given value in Polynomial
			float sum=0;
			int j=power;
			for(int i=0;i<power+1;i++){
				sum+=coefficient[i]*pow(x,j);
				j--;
			}
			return sum;
		}
		float secant(float a,float b,float c,int d); // Secant method -- I used this function in hybrid too
};
void Poly_class::set_power(int a){
	power=a;
}
float Poly_class::secant(float a,float b,float c,int d){ // Secant method -- 1 for secant 2 for hybrid method I didnt write seperate code for hybrid method
		int secantcounter;
		switch(d){
		case 1 :secantcounter=0;
		break;
		case 2 :secantcounter=2;
		break;
		}
		float temp=0;
		while(abs(a-b)>c){ // Iteration in secant method
		temp=a-(set_poly(a))*(a-b)/(set_poly(a)-set_poly(b));
		a=b;
		b=temp;
		secantcounter++;
		}
		cout<<(a/2+b/2)<<"  "<<secantcounter<<endl;
}
int sign(float a, float c){ // deciding sign of root and function in Bisection method to put new value instead of it
	if((a>0 && c>0) || (a<0 && c<0)){return 1;}
	else{return 0;}
}

int main(int argc,char* argv[])
{
	if(argc<5){ // If there are less then 5 comman line arguments the code doesnt work
		cout<<" At least 5 command line arguments are necessary ! 2 or more for coefficients and 2 for initial guesses and 1 for tolerance! ";
	}
	else{ 
		if(atof(argv[argc-3])<atof(argv[argc-2])){ // if initial guesses x1 < x0 the code doesnt work
	Poly_class fpoly; // fpoly value in Polynomial class
	int power; 
	float atemp=0,btemp=0; // temprory values to use in hybrid method
	power=argc-5;
	fpoly.set_power(power); // defining power of Polynomial
	
	for(int i=1;i<=power+1;i++){
	fpoly.coefficient[i-1]=atof(argv[i]); // defining coefficirnts
	}
	
	float a=atof(argv[argc-3]); // initial guesses and tolerance
	float b=atof(argv[argc-2]);
	float tolerance=atof(argv[argc-1]);
	float c=(a+b)/2;
	
	float fa=fpoly.set_poly(a),fb=fpoly.set_poly(b),fc=fpoly.set_poly(c); //Bisection Method
	int counterBisection=1;
	if(fa==0){c=0;counterBisection=1;}
	else if(fb==0){c=0;counterBisection=1;}
	else{
	while(abs(a-c)>tolerance){ // Iteration in Bisection method
	fa=fpoly.set_poly(a);
	fb=fpoly.set_poly(b);
	fc=fpoly.set_poly(c);
	if((sign(fa,fc))==1){a=c;}
	else if((sign(fb,fc))==1){b=c;}
	c=(a+b)/2;
	counterBisection++;
	if(counterBisection==2){ // defining temporary values in 2nd iteration to use in hybrid method
		atemp=a;
		btemp=b;
	}
	}
	}
	cout<<c<<"  "<<counterBisection<<endl;
	
	a=atof(argv[argc-3]); // initializing a&b again because they were changed in Bisection Method
 	b=atof(argv[argc-2]);
	
	fpoly.secant(a,b,tolerance,1); // Secant Method
	
	fpoly.secant(atemp,btemp,tolerance,2); // Hybrid Method I saved atemp and btemp in Bisecant method
	}
	else{ // indication of error if x1 is smaller than x0
		cout<<" x0 is greater than x1 !!! x1 must be greater than x0.";
	}
}
}
