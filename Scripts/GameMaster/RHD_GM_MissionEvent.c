enum RHD_GM_MissionEventType
{
    STARTED = 0,
    OBJECTIVE_COMPLETED = 1,
    OBJECTIVE_FAILED = 2,
    REINFORCEMENT_DEPLOYED = 3,
    COMPLETED = 4,
    FAILED = 5,
    TIMED_OUT = 6
}

class RHD_GM_MissionEvent
{
    RHD_GM_MissionEventType Type;
    string MissionId;
    string ObjectiveId;
    int ReinforcementIndex;
    string Message;

    void RHD_GM_MissionEvent(RHD_GM_MissionEventType type, string missionId, string message = "")
    {
        Type = type;
        MissionId = missionId;
        Message = message;
        ObjectiveId = "";
        ReinforcementIndex = 0;
    }
}

class RHD_GM_MissionEventListener
{
    void OnMissionEvent(RHD_GM_MissionEvent eventData)
    {
    }
}
