#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Vector
{
public: double x[3];
       
       Vector(double x1,double y1,double z1)
       {
                  x[0] = x1;
                  x[1] = y1;
                  x[2] = z1;

       //           L = sqrt(x1*x1 + y1*y1 + z1*z1);

       }
       Vector()
       {
       }


       Vector& operator = (const Vector &n)
       {
              x[0] = n.x[0];
              x[1] = n.x[1];
              x[2] = n.x[2];

 //                 L = sqrt(x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
       return *this;
       }
       bool operator == (const Vector &n)
       {
       if(x[0] == n.x[0] && x[1] == n.x[1] && x[2] == n.x[2])
       {
       return true;
       }
       else
       {
       return false;
       }
       }
       double len()
       {
       return sqrt(x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
       }
       double sqlen()
       {
           return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
       }
/*
        Vector getReal()
        {
            Vector tmp;
            for(int i = 0; i < 3; i++)
            {

            tmp.x[i]=x[i]-SIZE[i]*floor(x[i]/SIZE[i]);


            }

        return tmp;
        }
*/
        bool inBounds(Vector r0, Vector r1)
		{
			for(int i = 0; i < 3; i++)
			{
				if(x[i] < r0.x[i] || x[i] > r1.x[i])
				{
					return false;
					
				}
				
			}
			return true;
		}


};

Vector operator+(const Vector &a,const Vector &b)
       {

          Vector c(a.x[0]+b.x[0],a.x[1]+b.x[1],a.x[2]+b.x[2]);
          return c;
       }
Vector operator-(const Vector &a,const Vector &b)
       {
          Vector c(a.x[0]-b.x[0],a.x[1]-b.x[1],a.x[2]-b.x[2]);
          return c;
       }



double operator*(const Vector &a,const Vector &b)
{
     double c = a.x[0]*b.x[0] +a.x[1]*b.x[1]+a.x[2]*b.x[2];
          return c;

}

Vector operator*(const double a,const Vector &b)
{
 Vector tmp;
 tmp = b;
 for(int i = 0; i < 3; i++)
        {

        tmp.x[i]=a*tmp.x[i];


        }
return tmp;
}

const double MAXLEN=1.6;
const double MINLEN=1.3;
const double PARTSIZE = 1;
int main()
{
	int N = 500; // Chain length
	srand(time(0)); //first generate chain with same length in chain.c, then generate coordinates and replace simulation box sizes and atom coordinates
	FILE *f = fopen("conformation.txt","w");
	Vector chain[3000];
	const int Bounds[3] = {1000,1000,1000}; 
	Vector b0(0,0,0); Vector b1(1000,1000,1000); // bounds of simulation cell
	chain[0].x[0] = Bounds[0]/2;
	chain[0].x[1] = Bounds[1]/2;
	chain[0].x[2] = Bounds[2]/2; //generating chain from the middle of the cell to get good movies
	Vector temp;
	bool restart = true;
	fprintf(f,"\t%i\t%i\t%i\t%lf %lf %lf\n",1,1,1,chain[0].x[0], chain[0].x[1], chain[0].x[2]); 
	for(int i = 1; i < N; i++)
	{
	    restart = true;
		
		while(restart == true)
		{
		restart = false;	
		
		for(int j = 0 ; j  < 3; j++) 
		{
	    temp.x[j] = 1.5 - 3.0*(double)rand()/(double)RAND_MAX;
		printf("%f\n",temp.x[j]);
		
		}
		Vector tmx = temp + chain[i-1];
		if(temp.len() > MAXLEN || temp.len() < MINLEN)
		{
			restart = true;
		}
		if(tmx.inBounds(b0,b1) == false)
		{
     	restart = true;
		}	
		
		
		for(int j = 0; j < i ; j ++)
		{
			if((tmx-chain[j]).len() < 1)
			{
				restart = true;
				
			}
				
			
		}
		
		
		
		}
		chain[i] = chain[i-1]+temp;
		fprintf(f,"\t%i\t%i\t%i\t%lf %lf %lf\n",i+1,1,1,chain[i].x[0], chain[i].x[1], chain[i].x[2]);
		
	}
	



	
	
	
	
	
	return 0;
}
