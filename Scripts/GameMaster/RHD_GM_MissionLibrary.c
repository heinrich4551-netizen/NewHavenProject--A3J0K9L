class RHD_GM_MissionLibrary
{
    protected ref array<ref RHD_GM_MissionComposition> m_Compositions;

    void RHD_GM_MissionLibrary()
    {
        m_Compositions = new array<ref RHD_GM_MissionComposition>();
    }

    bool Add(RHD_GM_MissionComposition composition)
    {
        if (!RHD_GM_MissionValidation.ValidateComposition(composition))
            return false;

        for (int i = 0; i < m_Compositions.Count(); i++)
        {
            if (m_Compositions[i] && m_Compositions[i].Id == composition.Id)
            {
                m_Compositions[i] = composition;
                return true;
            }
        }

        m_Compositions.Insert(composition);
        return true;
    }

    RHD_GM_MissionComposition Find(string missionId)
    {
        if (!missionId)
            return null;

        foreach (RHD_GM_MissionComposition composition : m_Compositions)
        {
            if (composition && composition.Id == missionId)
                return composition;
        }

        return null;
    }

    array<ref RHD_GM_MissionComposition> GetAll()
    {
        return m_Compositions;
    }

    array<string> GetMissionIds()
    {
        ref array<string> result = new array<string>();

        foreach (RHD_GM_MissionComposition composition : m_Compositions)
        {
            if (composition)
                result.Insert(composition.Id);
        }

        return result;
    }
}
