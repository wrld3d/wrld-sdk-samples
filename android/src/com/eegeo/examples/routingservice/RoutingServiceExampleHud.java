package com.eegeo.examples.routingservice;

import android.util.Log;

import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.mobilesdkharness.MainActivity;
import com.eegeo.mobilesdkharness.R;

public class RoutingServiceExampleHud
{
	private MainActivity m_activity;
	private View m_view;
	private ToggleExpandedOnClickListener m_toggleExpandedOnClickListener;
	private MoveUpOnClickListener m_moveUpOnClickListener;
	private MoveDownOnClickListener m_moveDownOnClickListener;
	private GetRouteOnClickListener m_getRouteOnClickListener;

	
	public RoutingServiceExampleHud(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_view = null;

		m_toggleExpandedOnClickListener = new ToggleExpandedOnClickListener(
				m_activity,
				nativeCallerPointer
		);

		m_moveUpOnClickListener = new MoveUpOnClickListener(
				m_activity,
				nativeCallerPointer
			);

		m_moveDownOnClickListener = new MoveDownOnClickListener(
				m_activity,
				nativeCallerPointer
			);
		
		m_getRouteOnClickListener = new GetRouteOnClickListener(
				m_activity,
				nativeCallerPointer
			);
				
		createHud(nativeCallerPointer);
	}

	private void createHud(final long nativeCallerPointer)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				try
				{
					final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
					m_view = m_activity.getLayoutInflater().inflate(R.layout.routing_service_menu_layout, uiRoot, false);

					final Button toggleExpanded = (Button)m_view.findViewById(R.id.toggle_expanded);
					final Button moveUp = (Button)m_view.findViewById(R.id.move_up);
					final Button moveDown = (Button)m_view.findViewById(R.id.move_down);
					final Button getRoute = (Button)m_view.findViewById(R.id.get_route);

					toggleExpanded.setOnClickListener(m_toggleExpandedOnClickListener);
					moveUp.setOnClickListener(m_moveUpOnClickListener);
					moveDown.setOnClickListener(m_moveDownOnClickListener);
					getRoute.setOnClickListener(m_getRouteOnClickListener);
					
					uiRoot.addView(m_view);
				}
				catch (Exception e)
				{
					Log.v("RoutingServiceExampleHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
				}
			}
		});
	}

	public void removeHud()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
				uiRoot.removeView(m_view);
				m_view = null;
			}
		});
	}
}