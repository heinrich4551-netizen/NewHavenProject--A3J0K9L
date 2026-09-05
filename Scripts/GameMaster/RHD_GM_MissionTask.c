class RHD_GM_MissionTask
{
    string Id;
    string Title;
    string Description;
    bool Completed;
    bool Failed;

    void RHD_GM_MissionTask(string id, string title, string description = "")
    {
        Id = id;
        Title = title;
        Description = description;
        Completed = false;
        Failed = false;
    }

    void Complete()
    {
        if (Failed)
            return;

        Completed = true;
    }

    void Fail()
    {
        if (Completed)
            return;

        Failed = true;
    }
}
