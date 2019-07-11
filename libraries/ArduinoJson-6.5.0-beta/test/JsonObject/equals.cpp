// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonObject::operator==()") {
  DynamicJsonDocument doc1;
  JsonObject obj1 = doc1.to<JsonObject>();
  JsonObjectConst obj1c = obj1;

  DynamicJsonDocument doc2;
  JsonObject obj2 = doc2.to<JsonObject>();
  JsonObjectConst obj2c = obj2;

  SECTION("should return false when objs differ") {
    obj1["hello"] = "coucou";
    obj2["world"] = 1;

    REQUIRE_FALSE(obj1 == obj2);
    REQUIRE_FALSE(obj1c == obj2c);
  }

  SECTION("should return false when objs differ") {
    obj1["hello"] = "world";
    obj1["anwser"] = 42;
    // insert in different order
    obj2["anwser"] = 42;
    obj2["hello"] = "world";

    REQUIRE(obj1 == obj2);
    REQUIRE(obj1c == obj2c);
  }
}
