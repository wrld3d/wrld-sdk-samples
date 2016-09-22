package com.eegeo.mobilesdkharness;

import android.util.Log;

import com.google.vrtoolkit.cardboard.CardboardDeviceParams;
import com.google.vrtoolkit.cardboard.FieldOfView;
import com.google.vrtoolkit.cardboard.HeadMountedDisplayManager;
import com.google.vrtoolkit.cardboard.ScreenParams;
import com.google.vrtoolkit.cardboard.CardboardDeviceParams.VerticalAlignmentType;
import com.google.vrtoolkit.cardboard.sensors.HeadTracker;
import com.google.vrtoolkit.cardboard.sensors.MagnetSensor;
import com.google.vrtoolkit.cardboard.sensors.MagnetSensor.OnCardboardTriggerListener;

public class VRModule
{
	private BackgroundThreadActivity m_backgroundActivity;
	private HeadTracker m_headTracker; 
	private MagnetSensor m_magnetSensor;
	
	public VRModule(final BackgroundThreadActivity mBackgroundActivity)
	{
		this.m_backgroundActivity = mBackgroundActivity;
		m_headTracker = HeadTracker.createFromContext(this.m_backgroundActivity);
		m_headTracker.setGyroBiasEstimationEnabled(true);
		m_headTracker.startTracking();
		
		m_magnetSensor = new MagnetSensor(this.m_backgroundActivity);
		m_magnetSensor.setOnCardboardTriggerListener(new OnCardboardTriggerListener() {
			
			@Override
			public void onCardboardTrigger() {
				mBackgroundActivity.runOnNativeThread(new Runnable() {
					public void run() {
						NativeJniCalls.magnetTriggered();
					}
				});
			}
		});
		m_magnetSensor.start();
	}
	
	public void resetTracker()
	{
		m_headTracker.resetTracker();
	}
	
	public void stopTracker()
	{
		m_headTracker.stopTracking();
		m_headTracker = null;
	}
	
	public float[] getUpdatedCardboardProfile()
	{
		HeadMountedDisplayManager hMDManager = new HeadMountedDisplayManager(this.m_backgroundActivity);
		ScreenParams screenParams = hMDManager.getHeadMountedDisplay().getScreenParams();
		CardboardDeviceParams cardboardDeviceParams = hMDManager.getHeadMountedDisplay().getCardboardDeviceParams();
		FieldOfView fov = cardboardDeviceParams.getLeftEyeMaxFov();
		float[] distCoef = cardboardDeviceParams.getDistortion().getCoefficients();
		
		int verticalAlign = 0; //Default bottom
		
		if (cardboardDeviceParams.getVerticalAlignment() == VerticalAlignmentType.TOP)
			verticalAlign = -1;
		else if (cardboardDeviceParams.getVerticalAlignment() == VerticalAlignmentType.BOTTOM)
			verticalAlign = 1;
		
		float cardboardProperties[] = {
                fov.getLeft(), //Outer
                fov.getTop(), //Upper
                fov.getRight(), //Inner
                fov.getBottom(), //Lower
                screenParams.getWidthMeters(), //Width
                screenParams.getHeightMeters(), //Height
                screenParams.getBorderSizeMeters(), //Border
                cardboardDeviceParams.getInterLensDistance(), //Separation
                cardboardDeviceParams.getVerticalDistanceToLensCenter(), //Offset
                cardboardDeviceParams.getScreenToLensDistance(), //Screen Distance
                verticalAlign, //Alignment
                distCoef[0], //K1
                distCoef[1]  //K2
            };
		
		Log.i("Eegeo VR", "Cardboard profile for " + cardboardDeviceParams.getModel() + " by " + cardboardDeviceParams.getVendor() + "has been loaded.");
		
		return cardboardProperties;

	}
	
	public void updateNativeCode(float deltaSeconds)
	{
		if(this.m_headTracker == null)
			return;
		float[] tempHeadTransform = new float[16];
		m_headTracker.getLastHeadView(tempHeadTransform, 0);
		if(!Float.isNaN(tempHeadTransform[0]))
		{
			NativeJniCalls.updateNativeCode(deltaSeconds, tempHeadTransform);	
		}
		else
		{
			System.out.println("Fixing NaN");
			resetTracker(); 
		}
	}

}
