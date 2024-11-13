modded class SCR_MapMarkerBase
{
	protected WorldTimestamp m_fInitTimeStamp;
	protected float m_fLifetimeInSeconds = 5.0;//3600.0;
	
	protected int m_iAutoDeleteTimer = 0;
	protected int m_iAutoDeleteTimerLimit = 120;
	
	// Checks if the marker has exceeded its lifetime
	// returns true if it is still in its lifetime
	// returns false if it has exceeded its lifetime
	bool IsInLifeTime()
	{
		float fDifferenceInSeconds = m_fInitTimeStamp.PlusSeconds(m_fLifetimeInSeconds).DiffMilliseconds(GetCurrentTime()) / 1000;
		m_wRoot.SetOpacity(fDifferenceInSeconds / m_fLifetimeInSeconds);
		Print(fDifferenceInSeconds / m_fLifetimeInSeconds);
		
		if (GetCurrentTime().GreaterEqual(m_fInitTimeStamp.PlusSeconds(m_fLifetimeInSeconds)))
			return false;
		else
			return true;
	}
	
	protected WorldTimestamp GetCurrentTime()
	{
		ChimeraWorld world = GetGame().GetWorld();
		if (!world)
			return null;
		
		return world.GetServerTimestamp();
	}
	
	override void OnCreateMarker()
	{
		if (m_bIsServerSideDisabled)
			return;
		
		m_MapEntity = SCR_MapEntity.GetMapInstance();
		if (!m_MapEntity)
			return;
		
		Widget mapRoot = m_MapEntity.GetMapMenuRoot();
		if (!mapRoot)
			return;
		
		Widget mapFrame = mapRoot.FindAnyWidget(SCR_MapConstants.MAP_FRAME_NAME);
		if (!mapFrame)
			return;
		
		m_ConfigEntry = SCR_MapMarkerManagerComponent.GetInstance().GetMarkerConfig().GetMarkerEntryConfigByType(m_eType);
		if (!m_ConfigEntry)
			return;
		
		m_wRoot = GetGame().GetWorkspace().CreateWidgets(m_ConfigEntry.GetMarkerLayout(), mapFrame);
		if (!m_wRoot)
			return;

		m_MarkerWidgetComp = SCR_MapMarkerWidgetComponent.Cast(m_wRoot.FindHandler(SCR_MapMarkerWidgetComponent));
		m_MarkerWidgetComp.SetMarkerObject(this);
		m_ConfigEntry.InitClientSettings(this, m_MarkerWidgetComp);
		m_MarkerWidgetComp.SetRotation(m_iRotation);
		
		SCR_MapEntity.GetOnMapClose().Insert(OnMapClosed);
		SCR_MapEntity.GetOnLayerChanged().Insert(OnMapLayerChanged);
		OnMapLayerChanged(m_MapEntity.GetLayerIndex());
		
		m_fInitTimeStamp = GetCurrentTime();
	}
}