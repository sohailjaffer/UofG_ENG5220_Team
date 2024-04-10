#include<iostream>
#include<omp.h>
int main(){
	std::cout<<"Thread Test 1\n";
	long m;
	#pragma omp parallel
	{
		m=omp_get_num_threads();
	}
	std::cout<<"The number of threads is "<<m<<"\n";
	return 0;
}
