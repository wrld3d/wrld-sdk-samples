//Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.mobilesdkharness;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.WindowManager;

import com.google.vrtoolkit.cardboard.CardboardDeviceParams;
import com.google.vrtoolkit.cardboard.FieldOfView;
import com.google.vrtoolkit.cardboard.HeadMountedDisplayManager;
import com.google.vrtoolkit.cardboard.ScreenParams;
import com.google.vrtoolkit.cardboard.CardboardDeviceParams.VerticalAlignmentType;
import com.google.vrtoolkit.cardboard.sensors.HeadTracker;
import com.google.vrtoolkit.cardboard.sensors.MagnetSensor;
import com.google.vrtoolkit.cardboard.sensors.MagnetSensor.OnCardboardTriggerListener;


public class BackgroundThreadActivity extends MainActivity
{
	private EegeoSurfaceView m_surfaceView;
	private SurfaceHolder m_surfaceHolder;
	private long m_nativeAppWindowPtr;
	private ThreadedUpdateRunner m_threadedRunner;
	private Thread m_updater;
	private boolean m_isInVRMode;
	
	private HeadTracker m_headTracker; 
	private MagnetSensor m_magnetSensor;

	static {
		System.loadLibrary("eegeo-sdk-samples");
	}
	
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);

		m_surfaceView = (EegeoSurfaceView)findViewById(R.id.surface);
		m_surfaceView.getHolder().addCallback(this);
		m_surfaceView.setActivity(this);
		
		m_headTracker = HeadTracker.createFromContext(this);
		m_headTracker.setGyroBiasEstimationEnabled(true);
		m_headTracker.startTracking();
		
		m_magnetSensor = new MagnetSensor(this);
		m_magnetSensor.setOnCardboardTriggerListener(new OnCardboardTriggerListener() {
			
			@Override
			public void onCardboardTrigger() {
				runOnNativeThread(new Runnable() {
					public void run() {
						NativeJniCalls.magnetTriggered();
					}
				});
			}
		});
		m_magnetSensor.start();

		DisplayMetrics dm = getResources().getDisplayMetrics();
		final float dpi = dm.ydpi;
		final Activity activity = this;

		m_threadedRunner = new ThreadedUpdateRunner(false);
		m_updater = new Thread(m_threadedRunner);
		m_updater.start();

		m_threadedRunner.blockUntilThreadStartedRunning();

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_nativeAppWindowPtr = NativeJniCalls.createNativeCode(activity, getAssets(), dpi);

				if(m_nativeAppWindowPtr == 0)
				{
					throw new RuntimeException("Failed to start native code.");
				}
			}
		});
	}
	
	@SuppressLint("InlinedApi") 
	private void setScreenSettings(){
		
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		if(android.os.Build.VERSION.SDK_INT<16)
			getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION);
		else if(android.os.Build.VERSION.SDK_INT<19)
			getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_FULLSCREEN);
		else
			getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN);
		
	}
	
	public void resetTracker()
	{
		m_headTracker.resetTracker();
	}
	
	public void enterVRMode()
	{
		if(!m_isInVRMode)
		{
			this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
			m_isInVRMode = true;
		}
	}
	
	public void exitVRMode()
	{
		if(m_isInVRMode)
		{
			this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_UNSPECIFIED);
			m_isInVRMode = false;
		}
	}

	public void runOnNativeThread(Runnable runnable)
	{
		m_threadedRunner.postTo(runnable);
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		
		setScreenSettings();
		
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				NativeJniCalls.resumeNativeCode();
				m_threadedRunner.start();
				
				if(m_surfaceHolder != null && m_surfaceHolder.getSurface() != null)
				{
					NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
					NativeJniCalls.updateCardboardProfile(getUpdatedCardboardProfile());
				}
			}
		});
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_threadedRunner.stop();
				NativeJniCalls.pauseNativeCode();
			}
		});
	}

	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		m_headTracker.stopTracking();
		m_headTracker = null;
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_threadedRunner.stop();
				NativeJniCalls.destroyNativeCode();
				m_threadedRunner.destroyed();
			}
		});

		m_threadedRunner.blockUntilThreadHasDestroyedPlatform();
		m_nativeAppWindowPtr = 0;
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder)
	{
		//nothing to do
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder)
	{

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_threadedRunner.stop();
			}
		});
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		final SurfaceHolder h = holder;
		
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_surfaceHolder = h;
				if(m_surfaceHolder != null) 
				{
					NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
					m_threadedRunner.start();
					NativeJniCalls.updateCardboardProfile(getUpdatedCardboardProfile());
				}
			}
		});
	}

	private class ThreadedUpdateRunner implements Runnable
	{
		private long m_endOfLastFrameNano;
		private boolean m_running;
		private Handler m_nativeThreadHandler;
		private float m_frameThrottleDelaySeconds;
		private boolean m_destroyed;

		public ThreadedUpdateRunner(boolean running)
		{
			m_endOfLastFrameNano = System.nanoTime();
			m_running = false;
			m_destroyed = false;

			float targetFramesPerSecond = 30.f;
			m_frameThrottleDelaySeconds = 1.f/targetFramesPerSecond;
		}

		synchronized void blockUntilThreadStartedRunning()
		{
			while(m_nativeThreadHandler == null);
		}

		synchronized void blockUntilThreadHasDestroyedPlatform()
		{
			while(!m_destroyed);
		}

		public void postTo(Runnable runnable)
		{
			m_nativeThreadHandler.post(runnable);
		}

		public void start()
		{
			m_running = true;
		}

		public void stop()
		{
			m_running = false;
		}

		public void destroyed()
		{
			m_destroyed = true;
		}

		public void run()
		{
			Looper.prepare();
			m_nativeThreadHandler = new Handler();

			while(true)
			{
				runOnNativeThread(new Runnable()
				{
					public void run()
					{
						long timeNowNano = System.nanoTime();
						long nanoDelta = timeNowNano - m_endOfLastFrameNano;
						float deltaSeconds = (float)((double)nanoDelta / 1e9);
						
						if(deltaSeconds > m_frameThrottleDelaySeconds)
						{
							if(m_running && m_headTracker != null)
							{
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
							else
							{
								SystemClock.sleep(200);
							}

							m_endOfLastFrameNano = timeNowNano;
						}

						runOnNativeThread(this);
					}
				});

				Looper.loop();
			}
		}
		
	}
	
	private float[] getUpdatedCardboardProfile(){
		HeadMountedDisplayManager hMDManager = new HeadMountedDisplayManager(this);
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
}