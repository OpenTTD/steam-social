#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   define DLL_EXPORT __declspec(dllexport)
#else
#   define DLL_EXPORT
#endif /* WIN32 */

#include <string>

#include "steam/steam_api.h"
#include "openttd_social_integration_api/openttd_social_integration_api.h"

static const std::string PLUGIN_SOCIAL_PLATFORM = "Steam";
static const std::string PLUGIN_NAME = "Steam Integration";
static const std::string PLUGIN_VERSION = "dev";

bool run_callbacks()
{
    SteamAPI_RunCallbacks();

    return true;
}

void shutdown()
{
    SteamFriends()->ClearRichPresence();
    SteamAPI_Shutdown();
}

void event_enter_main_menu()
{
    SteamFriends()->SetRichPresence("steam_display", "#MainMenu");
}

void event_enter_scenario_editor(unsigned int map_width, unsigned int map_height)
{
    SteamFriends()->SetRichPresence("map_width", std::to_string(map_width).c_str());
    SteamFriends()->SetRichPresence("map_height", std::to_string(map_height).c_str());

    SteamFriends()->SetRichPresence("steam_display", "#ScenarioEditor");
}

void event_enter_singleplayer(unsigned int map_width, unsigned int map_height)
{
    SteamFriends()->SetRichPresence("map_width", std::to_string(map_width).c_str());
    SteamFriends()->SetRichPresence("map_height", std::to_string(map_height).c_str());

    SteamFriends()->SetRichPresence("steam_display", "#Singleplayer");
}

void event_enter_multiplayer(unsigned int map_width, unsigned int map_height)
{
    SteamFriends()->SetRichPresence("map_width", std::to_string(map_width).c_str());
    SteamFriends()->SetRichPresence("map_height", std::to_string(map_height).c_str());

    SteamFriends()->SetRichPresence("steam_display", "#Multiplayer");
}

void event_joining_multiplayer()
{
    SteamFriends()->SetRichPresence("steam_display", "#JoiningMultiplayer");
}

extern "C" DLL_EXPORT void SocialIntegration_v1_GetInfo(OpenTTD_SocialIntegration_v1_PluginInfo *plugin_info)
{
    static OpenTTD_SocialIntegration_v1_PluginInfo info {
        .social_platform = PLUGIN_SOCIAL_PLATFORM.c_str(),
        .name = PLUGIN_NAME.c_str(),
        .version = PLUGIN_VERSION.c_str(),
    };

    *plugin_info = info;
}

extern "C" DLL_EXPORT int SocialIntegration_v1_Init(OpenTTD_SocialIntegration_v1_PluginApi *plugin_api, const OpenTTD_SocialIntegration_v1_OpenTTDInfo *)
{
    static OpenTTD_SocialIntegration_v1_PluginApi api {
        .shutdown = shutdown,
        .run_callbacks = run_callbacks,

        .event_enter_main_menu = event_enter_main_menu,
        .event_enter_scenario_editor = event_enter_scenario_editor,
        .event_enter_singleplayer = event_enter_singleplayer,
        .event_enter_multiplayer = event_enter_multiplayer,
        .event_joining_multiplayer = event_joining_multiplayer,
    };

    *plugin_api = api;

    if (!SteamAPI_IsSteamRunning()) {
        return OTTD_SOCIAL_INTEGRATION_V1_INIT_PLATFORM_NOT_RUNNING;
    }

    if (!SteamAPI_Init()) {
        return OTTD_SOCIAL_INTEGRATION_V1_INIT_FAILED;
    }

    return OTTD_SOCIAL_INTEGRATION_V1_INIT_SUCCESS;
}

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    /* Ensure our library remains loaded. */
    return TRUE;
}
#endif /* WIN32 */
