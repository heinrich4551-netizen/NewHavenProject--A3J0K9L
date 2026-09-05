class RHD_GM_MissionObjective
{
    string Id;
    string Title;
    string Description;
    bool Required;
    bool Completed;
    bool Failed;

    void RHD_GM_MissionObjective(string id, string title, string description = "", bool required = true)
    {
        Id = id;
        Title = title;
        Description = description;
        Required = required;
        Completed = false;
        Failed = false;
    }

    void Complete()
    {
        if (!Failed)
            Completed = true;
    }

    void Fail()
    {
        if (!Completed)
            Failed = true;
    }

    bool IsFinished()
    {
        return Completed || Failed;
    }
}
