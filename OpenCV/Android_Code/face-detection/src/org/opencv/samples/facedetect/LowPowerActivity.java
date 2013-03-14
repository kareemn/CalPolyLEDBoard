package org.opencv.samples.facedetect;

import java.util.Calendar;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.support.v4.app.NavUtils;
import android.annotation.TargetApi;
import android.os.Build;

public class LowPowerActivity extends Activity {

    //my variables
    protected static final int HIGH_HOUR = 19;
    private static final int MINUTES_BTWN_CHECKS = 10;
    private static final int MS_PER_MIN = 60000;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_low_power);
        // Show the Up button in the action bar.
        //setupActionBar(); //this causes a nullPointerException
        
        new Handler().postDelayed(new Runnable() {
            public void run() {
                wakeOnTime();
            }
        }, 1000);
           
    }

    /**
     * Set up the {@link android.app.ActionBar}, if the API is available.
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    private void setupActionBar() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            getActionBar().setDisplayHomeAsUpEnabled(true);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.low_power, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
        case android.R.id.home:
            // This ID represents the Home or Up button. In the case of this
            // activity, the Up button is shown. Use NavUtils to allow users
            // to navigate up one level in the application structure. For
            // more details, see the Navigation pattern on Android Design:
            //
            // http://developer.android.com/design/patterns/navigation.html#up-vs-back
            //
            NavUtils.navigateUpFromSameTask(this);
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
    
    /*
     * My Functions: 
     * Most of above was automatically generated by eclipse
     */    
    public void wakeOnTime() {
        Calendar cal = Calendar.getInstance();
        System.out.println("entering while loop");
        while(cal.get(Calendar.HOUR) >= HIGH_HOUR) {
            cal = Calendar.getInstance();
            //debug info
            System.out.println(cal.get(Calendar.HOUR));
            //dont check too often
            try { Thread.currentThread().sleep(MINUTES_BTWN_CHECKS * MS_PER_MIN); }
            catch ( Exception e ) { }
        }
        finish();
    }
    
    /*@Override
    public void onBackPressed() {
        finish();
    }*/

}
