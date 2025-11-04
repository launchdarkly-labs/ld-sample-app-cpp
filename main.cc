#include <drogon/drogon.h>

#include <cstring>
#include <iostream>

#define FEATURE_FLAG_KEY "test-flag"

int main()
{
    // Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", 5555);
    // Load config file
    // drogon::app().loadConfigFile("../config.json");
    // drogon::app().loadConfigFile("../config.yaml");
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
