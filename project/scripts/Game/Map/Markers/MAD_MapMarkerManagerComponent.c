modded class SCR_MapMarkerManagerComponent
{
	override void Update(float timeSlice)
	{
		m_MapEntity.GetMapVisibleFrame(m_vVisibleFrameMin, m_vVisibleFrameMax);
		
		int count = m_aStaticMarkers.Count();
		for (int i = 0; i < count; i++)
		{
			if (!m_aStaticMarkers[i].OnUpdate(m_vVisibleFrameMin, m_vVisibleFrameMax))
			{
				SetStaticMarkerDisabled(m_aStaticMarkers[i], true);
				i--;
				count--;
			}
			else if (!m_aStaticMarkers[i].IsInLifeTime())
			{
				RemoveStaticMarker(m_aStaticMarkers[i]);
				i--;
				count--;
			}
		}
				
		foreach (SCR_MapMarkerEntity markerEnt : m_aDynamicMarkers)
		{
			if (markerEnt)
				markerEnt.OnUpdate();
		}
		
		#ifdef MARKERS_DEBUG
			UpdateDebug(timeSlice);
		#endif 
	}
}