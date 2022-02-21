#include "typewise-alert.h"
#include <stdio.h>
int lookupCoolingTypeUpLimit[3] ={35, 45, 40};
const char* breachMessage[] = {"Normal","too LOW", "too HIGH"};
BreachType (*funcptr)(BreachType); 

BreachType (*sender_selector[])(BreachType) =    //pointers to functions
{
  sendToController,
  sendToEmail
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  BreachType inferbreach;
  inferbreach = ((value - lowerLimit) < 0) ? TOO_LOW:NORMAL;
  if(inferbreach == NORMAL && (value - upperLimit) > 0) {
    inferbreach = TOO_HIGH;
  }
  return inferbreach;
}

BreachType classifyTemperatureBreach(
  CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = lookupCoolingTypeUpLimit[coolingType];
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

BreachType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  funcptr = sender_selector[alertTarget];
  return funcptr(breachType);
}

BreachType sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return breachType;
}

BreachType sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  printf("To: %s\n", recepient);
  printf("Hi, the temperature is ");
  printf("%s\n", breachMessage[breachType]);
  return breachType;
}
