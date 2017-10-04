#include <iostream>
#include <omp.h>

void subdomain( float *x, int istart, int ipoints );

void sub( float *x, int npoints );

int main()
{
	int n = 100;
	float array[n];
	sub( array, n );
	for( int i=0; i<n; i++ )
	{
		std::cout << "array[" << i << "] = " << array[i] << std::endl;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////

void subdomain( float *x, int istart, int ipoints )
{
	int i;
	for( i=0; i<ipoints; i++ )
	{
		x[istart+i] = 123.456;
	}
}

///////////////////////////////////////////////////////////////////////////


void sub( float *x, int npoints )
{
	int iam, nt, ipoints, istart;
#pragma omp parallel default(shared) private( iam, nt, ipoints, istart )
	{
		iam = omp_get_thread_num();
		nt = omp_get_num_threads();
		ipoints = npoints / nt;				//size of partition
		istart = iam * ipoints;				//starting array index
		if( iam == nt-1 )					//last thread may do more?
		{
			ipoints = npoints - istart;
		}
		subdomain( x, istart, ipoints );
	}
}

///////////////////////////////////////////////////////////////////////////
