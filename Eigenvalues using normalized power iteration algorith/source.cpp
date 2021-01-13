#include<iostream>
#include<fstream>
#include <iomanip>
#include<cmath>
#include <iomanip> 

using namespace std;

class matrix{
	public:	
	int row,coloumn;
	float** matrixA;
	matrix(int size_x,int size_y);
	matrix& operator = (const matrix m2){matrixA= m2.matrixA;}
	matrix operator* (const matrix m2);
	matrix operator- (const matrix m2);
};
matrix::matrix(int size_x,int size_y):matrixA(new float*[size_x]) // construction of a matrix
	{
		for(int i=0;i<size_x;i++)
		{
			matrixA[i]=new float[size_y];
		}
		row=size_x;
		coloumn=size_y;
	}
matrix matrix::operator*(const matrix m2) // multiplication of two matrix
{
	matrix result(row,m2.coloumn);
		for (int i=0; i<row; i++){
			for (int j=0; j<m2.coloumn; j++){
				result.matrixA[i][j]=0;
			}
		}
	for(int i=0;i<row;i++)
		{		
		for(int j=0;j<m2.row;j++)
		{
			for(int k=0;k<m2.coloumn;k++)
			{
				result.matrixA[i][k]+=matrixA[i][j]*m2.matrixA[j][k];
			}
		}
	}
	return result;
}
matrix matrix::operator- (const matrix m2){ // subtraction of two matrix
		matrix result(row,coloumn); 
		for (int i=0; i<row; i++){
			for (int j=0; j<coloumn; j++){
				result.matrixA[i][j]=matrixA[i][j]-m2.matrixA[i][j];
			}
		}
		return result;
	}
int main(int argc, char* argv[])
{
	if(argc !=4){                                      //to run the program with exactly 3 arguments 
	
	cout<<"3 argument line arguments are necessary. \n 1- Input File name with extension 2- tolerance 3- Output File name \n i.e. source.exe Inputfile.txt 1e-6 Outputfile.txt  ";
	cout<<"Now, do you want to try again?";
	return 99;
	}
	string line;
	int counter=0; // I created a counter to count eigenvalues
	float lvalue=0; // largest value for normalization
	float tolerance=atof(argv[2]);
	int sA=0; // row number of A matrix. I didn't defined coloumn number because it is square.
	ifstream matrixAd (argv[1]); 
	if(matrixAd.is_open())
	{
		while(!matrixAd.eof())
		{
			getline(matrixAd,line);
			sA=sA+1;
		}
		matrixAd.seekg(0,ios::beg);
	}
	else // A precaution to indicate file error if it wasn't found
	{
	cout<<"error! couldn't find file name"<<argv[1];
	}
	matrix A(sA,sA);
	for(int a=0;a<sA;a++)
	{
		for(int b=0;b<sA;b++)
		{
			matrixAd>>A.matrixA[a][b]; // defining A matrix
		}
	}
	matrixAd.close();
	
	matrix vectorb(sA,1);
	for(int i=0;i<sA;i++){
		vectorb.matrixA[i][0]=1;
	}
	
	matrix vectorc(sA,1);
	vectorc=A*vectorb;
	float lnumber=0;  // Power iteration and normalization
	for(int i=0;i<sA;i++){
		if(abs(lnumber)<abs(vectorc.matrixA[i][0])){lnumber=vectorc.matrixA[i][0];} // finding largest number for normalization
	}
	for(int i=0;i<sA;i++){
		vectorc.matrixA[i][0]=vectorc.matrixA[i][0]/lnumber; // normalization
	}
	float oldlnumber=0; 
	int flag=0;
	matrix vectord(sA,1);
	ofstream matrixxd(argv[3]); 
	while(flag==0){   // applying power iteration untill the ratio change is less than tolerance
		
	for(int i=0;i<sA;i++){
		vectord.matrixA[i][0]=0;
	}
	for(int i=0;i<sA;i++){
		for(int j=0;j<sA;j++){
			vectord.matrixA[i][0]+=A.matrixA[i][j]*vectorc.matrixA[j][0];
		}	
	}
	for(int i=0;i<sA;i++){
		if(abs(vectord.matrixA[i][0])<tolerance){vectorc.matrixA[i][0]=0;}
		else{vectorc.matrixA[i][0]=vectord.matrixA[i][0];}
	}
	float lnumber=0;
	for(int i=0;i<sA;i++){
		if(lnumber<abs(vectorc.matrixA[i][0])){lnumber=vectorc.matrixA[i][0];}
	}
	for(int i=0;i<sA;i++) {
		vectorc.matrixA[i][0]=vectorc.matrixA[i][0]/lnumber;
	}
	
	if(abs(lnumber-oldlnumber)<tolerance){
		flag=1;
		counter++;
		cout<<setprecision(2)<<fixed<<"Eigenvalue "<<counter<<" is: "<<lnumber<<"\t"<<"\n\n"; //printing eigenvalue 1
	if(matrixxd.is_open())
	{
		matrixxd<<setprecision(2)<<fixed<<"Eigenvalue"<<counter<<" is: "<<lnumber<<"\t"<<"\n\n";
	}
	else 
	{
	cout<<"failure! could not find output file "; // defining new largest number
	}
		lvalue=lnumber;
	}
	oldlnumber=lnumber; // to save the old largest number right after defining new largest number
	}
	cout<<"Eigenvector#1 is: \n\n";  //printing eigenvector
	matrixxd<<"Eigenvector#1 is: \n\n";
		for(int i=0;i<sA;i++)
	{
		cout<<setprecision(2)<<fixed<<vectorc.matrixA[i][0]<<"\n";
		matrixxd<<setprecision(2)<<fixed<<vectorc.matrixA[i][0]<<"\n";
	}
	cout<<"\n";
	matrixxd<<"\n";
	matrix vectors(1,sA); //deflation vector --> x(transpose)*eigenvector= 1
	for(int i=0;i<sA;i++)
	{
		if(vectorc.matrixA[i][0]==0){vectors.matrixA[0][i]=0;}
		else{vectors.matrixA[0][i]=1/(vectorc.matrixA[i][0]*sA);}
	} 
	matrix B(sA,sA);  // Deflation matrix I used second method in our book --> x(transpose)*eigenvector= 1
	B=vectorc*vectors;
	for(int i=0;i<sA;i++)
	{
		for(int j=0;j<sA;j++)
		{
			B.matrixA[i][j]*=lvalue;
		}
	}
	A=A-B; // new A matrix after deflation
	vectorc=A*vectorb; // Power iteration and normalization
	lnumber=0;
	for(int i=0;i<sA;i++)
	{
		if(abs(lnumber)<abs(vectorc.matrixA[i][0])){lnumber=vectorc.matrixA[i][0];} // finding largest number
	}
	for(int i=0;i<sA;i++)
	{
		vectorc.matrixA[i][0]=vectorc.matrixA[i][0]/lnumber; // normalization
	}
	oldlnumber=0;
	flag=0;
	while(flag==0) // applying power iteration untill the ratio change is less than tolerance
	{
	for(int i=0;i<sA;i++)
	{
		vectord.matrixA[i][0]=0;
	}
	for(int i=0;i<sA;i++)
	{
		float sum=0;
		for(int j=0;j<sA;j++)
		{
			vectord.matrixA[i][0]+=A.matrixA[i][j]*vectorc.matrixA[j][0];
		}	
	}
	for(int i=0;i<sA;i++){
		if(abs(vectord.matrixA[i][0])<tolerance){vectorc.matrixA[i][0]=0;}
		else{vectorc.matrixA[i][0]=vectord.matrixA[i][0];}
		
	}
	float lnumber=0;
	for(int i=0;i<sA;i++){
		if(lnumber<abs(vectorc.matrixA[i][0])){lnumber=vectorc.matrixA[i][0];}
	}
	for(int i=0;i<sA;i++){
		vectorc.matrixA[i][0]=vectorc.matrixA[i][0]/lnumber;
	}	
	if(abs(lnumber-oldlnumber)<tolerance){
		flag=1;
		counter++;
		cout<<setprecision(2)<<fixed<<"Eigenvalue "<<counter<<" is: "<<lnumber<<"\t"<<"\n\n"; // printing eigenvalue 2
			if(matrixxd.is_open())
	{
		matrixxd<<"Eigenvalue"<<counter<<" is: "<<lnumber<<"\t"<<"\n\n";
	}
	}
	oldlnumber=lnumber;
	}
}


// I wrote a second code just with class functions that can compute all eigen values no matter how many it is but I didn't implement 3 command line arguments
/*

#include<iostream>
#include<fstream>
#include <iomanip>
#include<cmath>

using namespace std;

class matrix{
	private:
	int row,coloumn;
	float lvalue;
	int counter=0;
	float** matrixA;
	float** matrixB;
	float* vectorb;
	float* vectorc;
	float* vectord;
	float* vectore;
	public:	
		void values();
		void printfunc();
		void transposem();
		void multi();
		void deflation();
		void minus();

};

void matrix::minus()
{
	for(int i=0;i<row;i++)
	{
			for(int j=0;j<row;j++)
			{
				matrixA[i][j]=matrixA[i][j]-matrixB[i][j];
			}		
	}
	
}
void matrix::deflation()
{
	for(int i=0;i<row;i++)
	{
		if(vectorc[i]==0){vectore[i]=0;}
		else{vectore[i]=1/(vectorc[i]*row);}
	}
	for(int i=0;i<row;i++)
	{
			for(int k=0;k<row;k++)
			{
				matrixB[i][k]=vectorc[i]*vectore[k]*lvalue;
			}
	}
}
void matrix::values()
{
			string line;
			int sA=0; // row number of A matrix. I didn't defined coloumn number because it is square.
			ifstream matrixAd("A.txt"); 
			if(matrixAd.is_open())
			{
				while(!matrixAd.eof())
				{
					getline(matrixAd,line);
					sA=sA+1;
				}
				matrixAd.seekg(0,ios::beg);
			}
			else // A precaution to indicate file problem if it wasn't opened
			{
			cout<<"hata!";
			}
			matrixA= new float*[sA]; //dynamic memory of A matrix
			matrixB=new float*[sA];
			vectorb=new float[row];
			vectorc=new float[row];
			vectord=new float[row];
			vectore=new float[row];
			for(int c=0;c<sA;c++)
			{
				matrixA[c]= new float[sA]; // limiting row length
				matrixB[c]=new float[sA];
			}
			for(int a=0;a<sA;a++)
			{
				for(int b=0;b<sA;b++)
				{
					matrixAd>>matrixA[a][b]; // defining A matrix
				}
			}
			row=sA;
			coloumn=sA;
			for (int k=0;k<row;k++)
			{
				if(k%2==0){vectorb[k]=1;}
				else{vectorb[k]=1;}
			}
			matrixAd.close();
}
void matrix::printfunc()
		{
		cout<<"\n"<<"Eigenvector #1 is: "<<"\n\n";	
		for (int k=0;k<row;k++)
		{
			cout<<vectorc[k]<<"\n";
		}
		cout<<endl;		
		}

void matrix::multi()
{
	for(int i=0;i<row;i++)
	{
		float sum=0;
		for(int j=0;j<coloumn;j++)
		{
			sum+=matrixA[i][j]*vectorb[j];
		}
		vectorc[i]=sum;
	}
	float lnumber=0;
	for(int i=0;i<row;i++)
	{
		if(lnumber<abs(vectorc[i])){lnumber=vectorc[i];}
	}
	for(int i=0;i<row;i++)
	{
		vectorc[i]=vectorc[i]/lnumber;
	}
	float x=0;
	int flag=0;
	while(flag==0)
	{
	for(int i=0;i<row;i++)
	{
		
		float sum=0;
		for(int j=0;j<coloumn;j++)
		{
			sum+=matrixA[i][j]*vectorc[j];
		}
		vectord[i]=sum;
	}
	for(int i=0;i<row;i++)
	{if(abs(vectord[i])<1E-6){vectorc[i]=0;}
			else{vectorc[i]=vectord[i];}
		
	}
	float lnumber=0;
	for(int i=0;i<row;i++)
	{
		if(lnumber<abs(vectorc[i])){lnumber=vectorc[i];}
	}
	for(int i=0;i<row;i++)
	{
		vectorc[i]=vectorc[i]/lnumber;
	}
	
	if(abs(lnumber-x)<1E-6)
	{
		flag=1;
		counter++;
		cout<<"Eigenvalue "<<counter<<" is: "<<lnumber<<"\t"<<"\n";
		lvalue=lnumber;
	}
	
	x=lnumber;
	}
}
int main()
{

	matrix A;
	A.values();
	A.multi();
	A.printfunc();
	A.deflation();
	A.minus();
	A.multi();
	
	//if you copy and paste this code it will calculate all eigenvalues
	//A.deflation(); 
	//A.minus();
	//A.multi();
	
}*/

