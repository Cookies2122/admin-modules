#include <stdio.h>
#include "as_antisliv.h"
#include "metamod_oslink.h"
#include "schemasystem/schemasystem.h"

as_antisliv g_as_antisliv;

IAdminApi* g_pAdminApi = nullptr;
IUtilsApi* g_pUtils = nullptr;
IPlayersApi* g_pPlayers = nullptr;

IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem* g_pEntitySystem = nullptr;
CGlobalVars* gpGlobals = nullptr;

PLUGIN_EXPOSE(as_antisliv, g_as_antisliv);

// Конфигурация
int g_iRoundRefresh = 2;
int g_iMaxMutes = 5;
int g_iMaxBans = 3;
std::string g_szFlagsImmunity = "z";

// Статистика администраторов
struct AdminStats {
    int iBans;
    int iMutes;
    int iRoundsLeft;
};

AdminStats g_AdminStats[64];

CGameEntitySystem* GameEntitySystem()
{
    return g_pUtils ? g_pUtils->GetCGameEntitySystem() : nullptr;
}

void StartupServer()
{
    g_pGameEntitySystem = GameEntitySystem();
    g_pEntitySystem = g_pUtils->GetCEntitySystem();
    gpGlobals = g_pUtils->GetCGlobalVars();
}

void LoadConfig()
{
    KeyValues* pKV = new KeyValues("AntiSliv");
    const char* szPath = "addons/configs/admin_system/antisliv.ini";
    
    if (!pKV->LoadFromFile(g_pFullFileSystem, szPath))
    {
        ConColorMsg(Color(255, 255, 0, 255), "[AntiSliv] Config not found, using defaults\n");
        delete pKV;
        return;
    }
    
    g_iRoundRefresh = pKV->GetInt("round_refresh", 2);
    g_iMaxMutes = pKV->GetInt("max_mutes", 5);
    g_iMaxBans = pKV->GetInt("max_bans", 3);
    g_szFlagsImmunity = pKV->GetString("flags_immunity", "z");
    
    delete pKV;
    
    ConColorMsg(Color(0, 255, 0, 255), "[AntiSliv] Loaded: refresh=%d, max_bans=%d, max_mutes=%d, immunity=%s\n", 
        g_iRoundRefresh, g_iMaxBans, g_iMaxMutes, g_szFlagsImmunity.c_str());
}

bool HasImmunityFlag(int iSlot)
{
    if (iSlot == -1) return true;
    
    for (size_t i = 0; i < g_szFlagsImmunity.length(); i++)
    {
        char szFlag[2] = {g_szFlagsImmunity[i], '\0'};
        if (g_pAdminApi->HasFlag(iSlot, szFlag))
        {
            return true;
        }
    }
    
    return false;
}

void BanAdmin(int iAdminSlot, const char* szReason)
{
    if (iAdminSlot < 0 || iAdminSlot >= 64) return;
    
    uint64 iSteamID64 = g_pPlayers->GetSteamID64(iAdminSlot);
    if (iSteamID64 == 0) return;
    
    char szSteamID[64];
    g_SMAPI->Format(szSteamID, sizeof(szSteamID), "%llu", iSteamID64);
    
    const char* szAdminName = g_pAdminApi->GetAdminName(iAdminSlot);
    
    // Permanent ban через Admin System
    g_pAdminApi->AddOfflinePlayerPunishment(szSteamID, szAdminName, RT_BAN, 0, szReason, -1);
    
    // Логируем
    g_pUtils->LogToFile("antisliv.log", "[AntiSliv] Admin %s (SteamID: %s) banned | Reason: %s | Bans: %d/%d | Mutes: %d/%d", 
        szAdminName, szSteamID, szReason,
        g_AdminStats[iAdminSlot].iBans, g_iMaxBans,
        g_AdminStats[iAdminSlot].iMutes, g_iMaxMutes);
    
    // Уведомляем админов
    for (int i = 0; i < 64; i++)
    {
        if (!g_pAdminApi->IsAdmin(i)) continue;
        if (i == iAdminSlot) continue;
        
        g_pUtils->PrintToChat(i, " \x02[AntiSliv]\x01 Admin \x07%s\x01 banned: \x10%s", szAdminName, szReason);
    }
    
    // Кикаем
    engine->DisconnectClient(CPlayerSlot(iAdminSlot), NETWORK_DISCONNECT_KICKED);
}

void CheckAdminAbuse(int iAdminSlot)
{
    if (iAdminSlot < 0 || iAdminSlot >= 64) return;
    if (!g_pAdminApi->IsAdmin(iAdminSlot)) return;
    if (HasImmunityFlag(iAdminSlot)) return;
    
    if (g_AdminStats[iAdminSlot].iBans >= g_iMaxBans)
    {
        BanAdmin(iAdminSlot, "AntiSliv: Too many bans");
        return;
    }
    
    if (g_AdminStats[iAdminSlot].iMutes >= g_iMaxMutes)
    {
        BanAdmin(iAdminSlot, "AntiSliv: Too many mutes");
        return;
    }
}

void ResetAdminStats(int iSlot)
{
    if (iSlot < 0 || iSlot >= 64) return;
    
    g_AdminStats[iSlot].iBans = 0;
    g_AdminStats[iSlot].iMutes = 0;
    g_AdminStats[iSlot].iRoundsLeft = g_iRoundRefresh;
}

void OnPlayerPunish(int iSlot, int iType, int iTime, const char* szReason, int iAdminID)
{
    if (iAdminID < 0 || iAdminID >= 64) return;
    if (!g_pAdminApi->IsAdmin(iAdminID)) return;
    if (HasImmunityFlag(iAdminID)) return;
    
    if (iType == RT_BAN)
    {
        g_AdminStats[iAdminID].iBans++;
    }
    else if (iType == RT_MUTE || iType == RT_GAG || iType == RT_SILENCE)
    {
        g_AdminStats[iAdminID].iMutes++;
    }
    
    CheckAdminAbuse(iAdminID);
}

void OnOfflinePlayerPunish(const char* szSteamID64, const char* szName, int iType, int iTime, const char* szReason, int iAdminID)
{
    if (iAdminID < 0 || iAdminID >= 64) return;
    if (!g_pAdminApi->IsAdmin(iAdminID)) return;
    if (HasImmunityFlag(iAdminID)) return;
    
    if (iType == RT_BAN)
    {
        g_AdminStats[iAdminID].iBans++;
    }
    else if (iType == RT_MUTE || iType == RT_GAG || iType == RT_SILENCE)
    {
        g_AdminStats[iAdminID].iMutes++;
    }
    
    CheckAdminAbuse(iAdminID);
}

void OnRoundStart(const char* szName, IGameEvent* pEvent, bool bDontBroadcast)
{
    for (int i = 0; i < 64; i++)
    {
        if (!g_pAdminApi->IsAdmin(i)) continue;
        if (HasImmunityFlag(i)) continue;
        
        g_AdminStats[i].iRoundsLeft--;
        
        if (g_AdminStats[i].iRoundsLeft <= 0)
        {
            ResetAdminStats(i);
        }
    }
}

void OnAdminConnected(int iSlot)
{
    ResetAdminStats(iSlot);
}

bool as_antisliv::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
    PLUGIN_SAVEVARS();
    
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetServerFactory, g_pSource2Server, ISource2Server, SOURCE2SERVER_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetServerFactory, g_pSource2GameClients, IServerGameClients, SOURCE2GAMECLIENTS_INTERFACE_VERSION);
    
    g_SMAPI->AddListener(this, this);
    
    ConVar_Register(FCVAR_SERVER_CAN_EXECUTE | FCVAR_GAMEDLL);
    
    for (int i = 0; i < 64; i++)
    {
        ResetAdminStats(i);
    }
    
    return true;
}

bool as_antisliv::Unload(char *error, size_t maxlen)
{
    if (g_pUtils)
        g_pUtils->ClearAllHooks(g_PLID);
    ConVar_Unregister();
    return true;
}

void as_antisliv::AllPluginsLoaded()
{
    int ret;
    
    g_pUtils = (IUtilsApi*)g_SMAPI->MetaFactory(Utils_INTERFACE, &ret, nullptr);
    if (ret == META_IFACE_FAILED)
    {
        ConColorMsg(Color(255, 0, 0, 255), "[%s] Missing Utils system plugin\n", GetLogTag());
        engine->ServerCommand(("meta unload " + std::to_string(g_PLID)).c_str());
        return;
    }
    
    g_pAdminApi = (IAdminApi*)g_SMAPI->MetaFactory(Admin_INTERFACE, &ret, nullptr);
    if (ret == META_IFACE_FAILED)
    {
        ConColorMsg(Color(255, 0, 0, 255), "[%s] Missing Admin System plugin\n", GetLogTag());
        engine->ServerCommand(("meta unload " + std::to_string(g_PLID)).c_str());
        return;
    }
    
    g_pPlayers = (IPlayersApi*)g_SMAPI->MetaFactory(PLAYERS_INTERFACE, &ret, nullptr);
    if (ret == META_IFACE_FAILED)
    {
        ConColorMsg(Color(255, 0, 0, 255), "[%s] Missing Players plugin\n", GetLogTag());
        engine->ServerCommand(("meta unload " + std::to_string(g_PLID)).c_str());
        return;
    }
    
    LoadConfig();
    
    // Хуки
    g_pAdminApi->OnPlayerPunish(g_PLID, OnPlayerPunish);
    g_pAdminApi->OnOfflinePlayerPunish(g_PLID, OnOfflinePlayerPunish);
    g_pAdminApi->OnAdminConnected(g_PLID, OnAdminConnected);
    g_pUtils->HookEvent(g_PLID, "round_start", OnRoundStart);
    
    g_pUtils->StartupServer(g_PLID, StartupServer);
    
    ConColorMsg(Color(0, 255, 0, 255), "[%s] Plugin loaded!\n", GetLogTag());
}

const char *as_antisliv::GetLicense()
{
    return "GPL";
}

const char *as_antisliv::GetVersion()
{
    return "1.0";
}

const char *as_antisliv::GetDate()
{
    return __DATE__;
}

const char *as_antisliv::GetLogTag()
{
    return "[AntiSliv]";
}

const char *as_antisliv::GetAuthor()
{
    return "_ded_cookies";
}

const char *as_antisliv::GetDescription()
{
    return "Protection against admin abuse";
}

const char *as_antisliv::GetName()
{
    return "[AS] AntiSliv";
}

const char *as_antisliv::GetURL()
{
    return "";
}