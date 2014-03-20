#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <iostream>


double pp(double x) //positive part   x+   
{
if(x>0) return x;
return 0;
}

void main()
{

	boost::mt19937 mt; 
	boost::normal_distribution<> distribution;
	boost::variate_generator<boost::mt19937&,boost::normal_distribution<>>* normal(new boost::variate_generator<boost::mt19937&,boost::normal_distribution<>>(mt,distribution));
	
	int numberSimulations=100000;

	double S0=100.0;
	double sigma=0.2;
	double T=1.0;
	double K=100.0;
	double sum=0;
	double payoff=0;

	for(int iSim=0;iSim<numberSimulations;iSim++)
	{
		double x=(*normal)();
		payoff=pp(S0*std::exp(-0.5*sigma*sigma*T+sigma*std::sqrt(T)*x)-K);
		sum+=payoff;
	}
	
	
	std::cout<<"\nCall="<<sum/numberSimulations<<std::endl;
	
	
}
