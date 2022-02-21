#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
}

TEST_CASE("classify cooling type") {
  CoolingType coolingtype = MED_ACTIVE_COOLING;
  REQUIRE(classifyTemperatureBreach(coolingtype, 50) == TOO_HIGH);
}

TEST_CASE("check email message") {
  BreachType breacht = TOO_HIGH;
  REQUIRE(sendToEmail(breacht) == TOO_HIGH);
}

TEST_CASE("check controller message") {
  BreachType breacht = TOO_HIGH;
  REQUIRE(sendToController(breacht) == TOO_HIGH);
}


TEST_CASE("check notification is send to correct method") {
  AlertTarget alertTarget = TO_CONTROLLER;
  CoolingType coolingtype = PASSIVE_COOLING;
  BatteryCharacter batteryChar = {coolingtype, "eduardo"};
  REQUIRE(checkAndAlert(alertTarget, batteryChar, 36) == TOO_HIGH);

}
