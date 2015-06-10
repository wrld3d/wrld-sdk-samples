package com.eegeo.mobilesdkharness.embeddedapp;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.eegeo.mobilesdkharness.R;

public class TextViewFragment extends CustomFragment 
{
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) 
    {
    	return inflater.inflate(R.layout.embedded_app_text_fragment, container, false);
    }
}
