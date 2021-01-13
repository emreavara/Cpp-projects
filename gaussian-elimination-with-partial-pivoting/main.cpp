#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

int main()
{
	string line;
	int sA=0; // row number of A matrix. I didn't defined coloumn number because it is square.
	int sb=0; // row number of b matrix.
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
	float** matrixA= new float*[sA]; //dynamic memory of A matrix
	
	for(int c=0;c<sA;c++)
	{
		matrixA[c]= new float[sA]; // limiting row length
	}
	for(int a=0;a<sA;a++)
	{
		for(int b=0;b<sA;b++)
		{
			matrixAd>>matrixA[a][b]; // defining A matrix
		}
	}
	matrixAd.close();
	ifstream matrixbd("b.txt"); // the same process with A but because it is a vector I just used vector code
	if(matrixbd.is_open())
	{
		while(!matrixbd.eof())
		{
			getline(matrixbd,line);
			sb=sb+1;
		}
		matrixbd.seekg(0,ios::beg);
	}
	else
	{
	cout<<"hata!";
	}	
	float* matrixb= new float[sb]; // Getting b values from file and writing on b vector.
	for(int e=0;e<sb;e++)
	{
			matrixbd>>matrixb[e];		
	}
	matrixbd.close();
	
	float norm1,norminf,invnorm1,invnorminf,detA,condA1,condAinf;	
	if(sA==2) // If the matrix is 2x2 it calculates the condition numbers.
	{
	detA=matrixA[0][0]*matrixA[1][1]-matrixA[0][1]*matrixA[1][0];
	if(abs(matrixA[0][0])+abs(matrixA[1][0])>=abs(matrixA[0][1])+abs(matrixA[1][1])) {norm1=abs(matrixA[0][0])+abs(matrixA[1][0]);}
	else{norm1=abs(matrixA[0][1])+abs(matrixA[1][1]);}
	if(abs(matrixA[0][0])+abs(matrixA[0][1])>=abs(matrixA[1][0])+abs(matrixA[1][1])){norminf=abs(matrixA[0][0])+abs(matrixA[0][1]);}
	else{norminf=abs(matrixA[1][0])+abs(matrixA[1][1]);}
	
	
	if(abs(matrixA[1][1])+abs(matrixA[1][0])>=abs(matrixA[0][1])+abs(matrixA[0][0])) {invnorm1=(abs(matrixA[1][1])+abs(matrixA[1][0]))/abs(detA);}
	else{invnorm1=(abs(matrixA[0][1])+abs(matrixA[0][0]))/abs(detA);}
	if(abs(matrixA[0][0])+abs(matrixA[0][1])>=abs(matrixA[1][0])+abs(matrixA[1][1])){invnorminf=(abs(matrixA[0][0])+abs(matrixA[0][1]))/abs(detA);}
	else{invnorminf=(abs(matrixA[1][0])+abs(matrixA[1][1]))/abs(detA);}
	}
	int flag=0; // If the matrix is singular the flag becomes 1 and it didn't calculate the x values.
	for (int f=0;f<sA;f++)
	{
		float lvalue=matrixA[f][f];
		int lrow=f; // I defined the lagest value row's number. I defined f because if the number is smaller than f it fails.
		float ratio,save; // "ratio" is the ratio between the largest value and every row. "save" is the storage which saves the first value to use then
		for(int g=f+1;g<sA;g++)
		{
			if(abs(lvalue)<abs(matrixA[g][f])) // I took the absolute values.
			{
				lvalue=matrixA[g][f]; 
				lrow=g; // the row number of the largest value is saved.
			}
		}
		if(abs(lvalue)>=1E-6) // I defined the machine precision as 1E-6.
		{
		for(int j=0;j<sA;j++) // swaping the first row and the largest value row for A
		{
			save=matrixA[lrow][j]; 
			matrixA[lrow][j]=matrixA[f][j];
			matrixA[f][j]=save;
		}
			float save2; // swaping the first row and the largest value row for b
			save2=matrixb[f]; 
			matrixb[f]=matrixb[lrow];
			matrixb[lrow]=save2;
			
		for(int k=f+1;k<sA;k++) // Calculating the raito and obtaining upper triangular matrix
		{
			ratio= matrixA[k][f]/matrixA[f][f];
			for(int l=0;l<sA;l++)
			{
				matrixA[k][l]=matrixA[k][l]-ratio*matrixA[f][l]; // the machine precision may result in troubles in this part because if the significant number of the ratio is the farther than the precision it may result in problems.
			}
			matrixb[k]=matrixb[k]-ratio*matrixb[f];
		}
	}
	else if(flag==0)
		{
		cout<<"The matrix is singular!!"<<endl; // if the matrix is singular it indicates.
		flag=1;
		}
		
	
	}
	if(flag==0)
	{
	ofstream matrixxd("x.txt"); // the same process with A but because it is a vector I just used vector code
	float* matrixx= new float[sb];
	if(matrixxd.is_open())
	{
		matrixx[sA-1]=matrixb[sb-1]/matrixA[sA-1][sA-1]; // Calculation of all x values.
		for (int t=sA-2;t>=0;t--)
		{
			float sum=0;
			for(int y=sA-1;y>t;y--)
			{
				sum=sum+matrixx[y]*matrixA[t][y];
			}
			matrixx[t]=(matrixb[t]-sum)/matrixA[t][t];
		}
	}
	else
	{
	cout<<"failure!";
	}
		for(int j=0;j<sb;j++) // Writing x values in the file "x.txt".
	{
		matrixxd<<matrixx[j]<<endl;
		cout<<"X"<<j<<": "<<matrixx[j]<<endl;
	}
	}
	if(sA==2) // if the matrix is 2x2 it shows condition numbers.
	{
	condA1=norm1*invnorm1;
	condAinf=norminf*invnorminf;
	cout<<"Condition number at 1:"<<condA1<<endl<<"Condition number at infinity:"<<condAinf<<endl;
	}
	}

