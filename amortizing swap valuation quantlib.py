#example amortizing swap valuation 
#http://www.pricederivatives.com   for educational purposes only
from  QuantLib import *
import numpy as np
from math import *

todaysDate=Date(31,12,2013)
startDate=todaysDate
Settings.instance().evaluationDate=todaysDate;
crvToday=FlatForward(todaysDate,0.0121,Actual360())
forecastTermStructure = RelinkableYieldTermStructureHandle()
index = Euribor(Period("6m"),forecastTermStructure)
maturity = Date(31,12,2018);
schedule = Schedule(startDate, maturity,Period("6m"),TARGET(),ModifiedFollowing,ModifiedFollowing,DateGeneration.Forward, False)
nominals=[100.0]*10
couponRates=[0.05]*10
floatingleg=IborLeg(nominals,schedule,index,Actual360())
fixedleg=FixedRateLeg(schedule,Actual360(),nominals,couponRates)
firstPeriodDayCount = DayCounter())
index.addFixing(index.fixingDate(schedule[0]),0)
swap1=Swap(floatingleg,fixedleg)
discountTermStructure = RelinkableYieldTermStructureHandle()
swapEngine = DiscountingSwapEngine(discountTermStructure)
swap1.setPricingEngine(swapEngine)
discountTermStructure.linkTo(crvToday)
forecastTermStructure.linkTo(crvToday)
npv=swap1.NPV()
print npv
