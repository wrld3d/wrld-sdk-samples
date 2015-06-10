package com.eegeo.mobilesdkharness.embeddedapp;

import com.eegeo.mobilesdkharness.BackgroundThreadActivity;

import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;

public class FragmentController implements ListView.OnItemClickListener 
{
    private BackgroundThreadActivity m_activity;
    public ImageViewFragment m_imageFrag;
    public TextViewFragment m_textFrag;
    public MapViewFragment m_mapFrag;

    public FragmentController(BackgroundThreadActivity activity) 
    {
    	m_activity = activity;
        
    	m_imageFrag = new ImageViewFragment();
        m_textFrag = new TextViewFragment();
        m_mapFrag = new MapViewFragment(m_activity);

        // Little bit of a hack here -- need to make the map view created 
        // in the view hierarchy so the surface is available for binding.
        selectItem(2);
        
        // We can then switch back to the real 'default' view.
        selectItem(0); 
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) 
    {
        selectItem(position);
    }

    private void selectItem(int position) 
    {
        switch(position) 
        {
            case 0:
            	m_activity.switchFragment(m_imageFrag, position);
                break;
            case 1:
            	m_activity.switchFragment(m_textFrag, position);
                break;
            case 2:
            	m_activity.switchFragment(m_mapFrag, position);
               break;
            default: break;
        }
    }
}
