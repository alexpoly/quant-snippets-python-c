#include <ql/quantlib.hpp>

using namespace std;
using namespace QuantLib;
using namespace boost;

int main()
{

vector<Date> dates; 
vector<DiscountFactor> discountFactor; 

Date valuationDate(31,December,2012);

dates.push_back(valuationDate); discountFactor.push_back(1.0); 

dates.push_back(Date(30,December, 2013));  discountFactor.push_back(0.99); 
dates.push_back(Date(30,December, 2014));  discountFactor.push_back(0.98); 

shared_ptr<YieldTermStructure> curve(new InterpolatedDiscountCurve<LogLinear>(dates,discountFactor,Actual360())); 

//discount factor
Date datex(25,June,2013);
double discount=curve->discount(datex);

//euribor forward
Period period(6*Months);
boost::shared_ptr<IborIndex> euribor(new Euribor(period));
double forward6m=curve->forwardRate(datex,period,curve->dayCounter(),QuantLib::Compounding::Simple);

}
