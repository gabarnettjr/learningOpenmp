#include <iostream>
#include <omp.h>

void simple( int n, float a[], float b[] );

int main()
{
	int n=5;
	float a[] = { 1, 2, 3, 4, 5 };
	float b[n];
	b[0] = 0;
	simple( n, a, b );
}

void simple( int n, float a[], float b[] )
{
	int i;

#pragma omp parallel for
	for( i=1; i<n; i++ )
	{
		b[i] = ( a[i] + a[i-1] ) / 2.0;
	}

	for( i=0; i<n; i++ )
	{
		std::cout << "a[" << i << "] = " << a[i] << ",  "
		          << "b[" << i << "] = " << b[i] << std::endl;
	}
}
