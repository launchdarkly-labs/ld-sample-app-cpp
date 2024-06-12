// #include <launchdarkly/context_builder.hpp>
// #include <launchdarkly/server_side/client.hpp>
// #include <launchdarkly/server_side/config/config_builder.hpp>

#include <cstring>
#include <iostream>
#include "LDClient.h"

LDClient::LDClient()
{
    const char *sdk_key = getSdkKey();

    auto config = ConfigBuilder(sdk_key).build();
    if (!config)
    {
        std::cout << "*** config is invalid: " << config.error() << std::endl;
        std::exit(1);
    }

    auto client = Client(std::move(*config)) auto start_result = client.StartAsync();
    auto const status = start_result.wait_for(std::chrono::milliseconds(INIT_TIMEOUT_MILLISECONDS));

    if (status == std::future_status::ready)
    {
        if (start_result.get())
        {
            std::cout << "*** SDK started successfully" << std::endl;
        }
        else
        {
            std::cout << "*** SDK failed to start" << std::endl;
            std::exit(1);
        }
    }
    else
    {
        std::cout << "*** SDK failed to start within " << INIT_TIMEOUT_MILLISECONDS << "ms" << std::endl;
        std::exit(1);
    }
}

const char *LDClient::getSdkKey()
{
    const char *envvar = std::getenv("LD_SDK_KEY");
    if (envvar && strlen(envvar))
    {
        return envvar;
    }
    std::cout << "*** SDK key not found" << std::endl;
    std::exit(1);
}

static LDClient *LDClient::getInstance()
{
    if (!instance)
    {
        instance = new LDClient();
    }
    return instance;
}
