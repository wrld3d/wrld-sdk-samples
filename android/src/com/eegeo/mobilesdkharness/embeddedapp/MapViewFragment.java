package com.eegeo.mobilesdkharness.embeddedapp;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.eegeo.mobilesdkharness.BackgroundThreadActivity;
import com.eegeo.mobilesdkharness.R;

public class MapViewFragment extends CustomFragment
{
	BackgroundThreadActivity m_activity;
	View m_mapView;
	
	public MapViewFragment(BackgroundThreadActivity activity) 
	{
		m_activity = activity;
		m_mapView = null;
	}

	@Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState)
    {
		if(m_mapView == null)
		{
			m_mapView = inflater.inflate(R.layout.embedded_app_map_fragment, container, false);
			m_activity.handleMapFragmentCreated(m_mapView);
		} 
		else 
		{
			// http://stackoverflow.com/a/23519289
			if(m_mapView.getParent() != null)
			{
				((ViewGroup)m_mapView.getParent()).removeView(m_mapView);
			}
        }
		
		return m_mapView;
    }
}
