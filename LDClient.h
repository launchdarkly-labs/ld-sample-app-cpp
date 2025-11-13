#pragma once

#include <launchdarkly/context_builder.hpp>
#include <launchdarkly/server_side/client.hpp>
#include <launchdarkly/server_side/config/config_builder.hpp>

#define SDK_KEY ""
#define INIT_TIMEOUT_MILLISECONDS 3000

using namespace launchdarkly;
using namespace launchdarkly::server_side;

class LDClient
{
private:
    static Config buildConfig();

protected:
    LDClient();

public:
    // LDClient(const LDClient &inst) = delete;
    static LDClient *getInstance();
    Client client;

private:
    static LDClient *instance;
};
