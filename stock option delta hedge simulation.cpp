#include <iostream.h>
#include <math.h>

double pp(double z)
{if(z<=0) return 0;return z;}

double n(double z)
{
return 0.3989423*exp(-.5*z*z);
}

double normal()
{
double u=random(1000000)/1000000.;
double v=random(1000000)/1000000.;
return sqrt(-2*log(u))*cos(2*3.141592653589*v);
}

double N(double z)
{

double b1 = 0.31938153;
double b2 = -0.356563782;
double b3 = 1.781477937;
double b4 = -1.821255978;
double b5 = 1.330274429;
double p = 0.2316419;
double c2 = 0.3989423;
if (z > 6.0) return 1.0;
if (z < -6.0) return 0.0; 
double a=fabs(z);
double t = 1.0/(1.0+a*p);
double b = c2*exp((-z)*(z/2.0));
double n = ((((b5*t+b4)*t+b3)*t+b2)*t+b1)*t;
n = 1.0-b*n;
if ( z < 0.0 ) n = 1.0 - n;
return n;
}


double call(double S,double K,double T,double sigma,double r)
{
double d1=(log(S/K)+r*T)/sigma/sqrt(T)+.5*sigma*sqrt(T);
double d2=d1-sigma*sqrt(T);

return S*N(d1)-K*exp(-r*T)*N(d2);
}

double put(double S,double K,double T,double sigma,double r)
{
double d1=(log(S/K)+r*T)/sigma/sqrt(T)+.5*sigma*sqrt(T);
double d2=d1-sigma*sqrt(T);

return -S*N(-d1)+K*exp(-r*T)*N(-d2);
}




double delta_call(double S,double K,double T,double sigma,double r)
{
double d1=(log(S/K)+r*T)/sigma/sqrt(T)+.5*sigma*sqrt(T);
return N(d1);
}

double delta_put(double S,double K,double T,double sigma,double r)
{
double d1=(log(S/K)+r*T)/sigma/sqrt(T)+.5*sigma*sqrt(T);
return 1.-N(d1);
}



double deltasigma(double S,double K,double T,double sigma,double r)
{
double d1=(log(S/K)+r*T)/sigma/sqrt(T)+.5*sigma*sqrt(T);
return n(d1)*(-(r*T+log(S/K))/sigma/sigma/sqrt(T)+sqrt(T)*.5);
}

main()
{
//for(double S=10;S<190;S++)
//{cout<<S<<"\t"<<call(S,100,1,.2,.04)<<"\t"<<call(S,100,1,10,.04)<<"\t"<<call(S,100,1,.001,.04)<<"\t"<<delta(S,100,1,10,.04)<<"\n";}
//cout<<S<<"\t"<<call(S,100,1,.001,.04)<<"\t"<<deltasigma(S,100,1,.2,.04)<<"\n";
           randomize();
double sigma=.2;double r=.04;double T=1.;
double S0=100;     double S=S0;double dt=.01;
double mu=.07;
//writing a call simulation 

double c=call(S,100,T,sigma,r);
double d,dold;
dold=0;
    double Stock=0,Cash=c;
double Sold=S;

for(double t=T;t>=0;t-=dt)
{
 d=delta_call(S,100,t,sigma,r);
 //cout<<T-t<<"\t"<<S<<"\t"<<call(S,100,t,sigma,r)<<"\t"<<delta_call(S,100,t,sigma,r)<<endl;
 cout<<endl<<"-----------"<<T-t<<"--------------"<<endl;
 cout<<"S="<<S<<endl;
 cout<<"old delta="<<dold<<endl;;
 cout<<"delta="<<d<<endl;;
 cout<<"price of my stocks="<<dold*S<<endl;;
 cout<<"d-dold="<<d-dold<<endl;;
 cout<<"cost of actins to buy is "<<(d-dold)*S<<endl;;
 cout<<"cash account="<<Cash;
Cash-=(d-dold)*S;
Stock=d*S;
 dold=d;
 Sold=S;
 Cash*=exp(r*dt);
 S+=S*(mu*dt+sigma*normal()*sqrt(dt)); //change output

}

cout<<endl<<endl;
cout<<"my earning="<<Stock+Cash-pp(Sold-100)<<endl;

}