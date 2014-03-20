#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <iostream>
#include <ql/quantlib.hpp>


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
	
	int numberSimulations=10000;

	std::vector<double> S0(2);
	S0[0]=100.0;// S1(0) - spot price of first stock
	S0[1]=100.0;//S2(0) - spot price of second stock

	std::vector<double> sigma(2);
	sigma[0]=0.2; //volatility of S1
	sigma[1]=0.2;//volatility of S2

	double T=1.0;//maturity in years
	double K=100.0;//strike of option
	double sum=0;//for monte-carlo averaging
	double payoff=0;
	double NT=100;//number of time intervals
	double dt=T/NT;
	
	QuantLib::Matrix rho(2,2);//correlation matrix

	rho[0][0]=1;rho[0][1]=0.5;
	rho[1][0]=0.5;rho[1][1]=1;

	QuantLib::Matrix cholesky=QuantLib::CholeskyDecomposition(rho);
	
	for(int iSim=0;iSim<numberSimulations;iSim++) //outer loop for simulations
	{
	
		std::vector<double> Sprev(S0); //create a vector equal to S0 with its values
		std::vector<double> Snext(2);//create vector with 2 elemens

		for(double t=0;t<T;t+=dt) //inner loop for constructing one stock price from time 0 to T
		{
			QuantLib::Array epsilon(2);//create a vector with 2 elements .we'll put here independent gaussians
			epsilon[0]=(*normal)();
			epsilon[1]=(*normal)();

			QuantLib::Array x(2);
			x=cholesky*epsilon; //correlated gaussians

			for(int iStock=0;iStock<2;iStock++) //loop over all stocks 
			{
				Snext[iStock]=Sprev[iStock]*std::exp(-0.5*sigma[iStock]*sigma[iStock]*dt+sigma[iStock]*std::sqrt(dt)*x[iStock]);
				Sprev[iStock]=Snext[iStock];
			}
		}

		payoff=pp(Snext[0]+Snext[1]-K);

		sum+=payoff;
	}
	
	
	std::cout<<"\nBasket Call="<<sum/numberSimulations<<std::endl;
	
	
}