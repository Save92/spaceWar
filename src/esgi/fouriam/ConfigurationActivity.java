package esgi.fouriam;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import esgi.fouriam.R;
import android.content.Intent;
import android.widget.TextView;
import android.widget.Button;
import android.view.View;
import android.widget.ImageView;
import android.widget.EditText;
import android.content.SharedPreferences;
import android.widget.Toast;

public class ConfigurationActivity extends Activity
{

    public static final String PREFS_NAME = "SpaceWarPreferences";

    // Sauvegarde des preferences
    private SharedPreferences settings;

	private EditText playerName;
    private TextView saveBtn;
    private TextView gyroBtn;
    private TextView touchBtn;
    private ImageView musicButton;
    private ImageView vibrationButton;

    private String name;
    private Integer commandValue;
    private Integer musicValue;
    private Integer vibrationValue;

    private Toast toast;

    /** Called when the activity is first created. */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.configuration);

        toast = Toast.makeText(this, "", Toast.LENGTH_SHORT);

        settings = getSharedPreferences(PREFS_NAME, 0);
        
        playerName = (EditText) findViewById(R.id.playerNameText);

        gyroBtn = (TextView) findViewById(R.id.gyroBtn);
        touchBtn = (TextView) findViewById(R.id.touchBtn);
        musicButton = (ImageView) findViewById(R.id.musicButton);
        vibrationButton = (ImageView) findViewById(R.id.vibrationButton);
        saveBtn = (TextView) findViewById(R.id.saveBtn);

        name = settings.getString("playerName", "");
        if (!name.equals("")) {
            SetSavedValues(settings);
        }

        if(gyroBtn.isSelected() == false && touchBtn.isSelected() == false) {
            gyroBtn.setSelected(true);
            gyroBtn.setTextColor(getResources().getColor(R.color.grenat));
            touchBtn.setSelected(false);
        }
        gyroBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!gyroBtn.isSelected()) {
                    gyroBtn.setTextColor(getResources().getColor(R.color.grenat));
                    touchBtn.setTextColor(getResources().getColor(R.color.white));
                    touchBtn.setSelected(false);
                } else {
                    gyroBtn.setTextColor(getResources().getColor(R.color.white));
                    gyroBtn.setSelected(false);
                }
            }
        });

        
        touchBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!touchBtn.isSelected()) {
                    touchBtn.setTextColor(getResources().getColor(R.color.grenat));
                    gyroBtn.setTextColor(getResources().getColor(R.color.white));
                    gyroBtn.setSelected(false);
                } else {
                    touchBtn.setTextColor(getResources().getColor(R.color.white));
                    touchBtn.setSelected(false);
                }
            }
        });

       
        musicButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(musicButton.isSelected()) {
                    musicButton.setSelected(false);
                    musicButton.setImageResource(R.drawable.ic_music_note_off_white_36dp);
                } else {
                    musicButton.setImageResource(R.drawable.ic_music_note_white_36dp);
                    musicButton.setSelected(true);
                }
            }
        });

        vibrationButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(vibrationButton.isSelected()) {
                    vibrationButton.setSelected(false);
                    vibrationButton.setImageResource(R.drawable.ic_cellphone_white_36dp);
                } else {
                    vibrationButton.setImageResource(R.drawable.ic_vibrate_white_36dp);
                    vibrationButton.setSelected(true);
                }
            }
        });

        saveBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SharedPreferences.Editor prefsEditor = settings.edit();
                prefsEditor.putString("playerName", playerName.getText().toString());
                if (gyroBtn.isSelected()) {
                    prefsEditor.putInt("command", 1);
                } else {
                    prefsEditor.putInt("command", 2);
                }
                if (musicButton.isSelected()) {
                    prefsEditor.putInt("ExtraMusic", 1);
                } else {
                    prefsEditor.putInt("ExtraMusic", 2);
                }
                if (vibrationButton.isSelected()) {
                    prefsEditor.putInt("ExtraVibrate", 1);
                } else {
                    prefsEditor.putInt("ExtraVibrate", 2);
                }
                prefsEditor.apply();
                toast.setText(getResources().getString(R.string.saved));
                toast.show();
            }
        });


    }

    public void SetSavedValues(SharedPreferences settings) {
        name = settings.getString("playerName", "");
        playerName.setText(name);
        commandValue = settings.getInt("command", 0);
        if (commandValue > 0) {
            if(commandValue == 1) {
                gyroBtn.setSelected(true);
                gyroBtn.setTextColor(getResources().getColor(R.color.grenat));
                touchBtn.setSelected(false);
                touchBtn.setTextColor(getResources().getColor(R.color.white));
            } else if(commandValue == 2){
                touchBtn.setSelected(true);
                touchBtn.setTextColor(getResources().getColor(R.color.grenat));
                gyroBtn.setSelected(false);
                gyroBtn.setTextColor(getResources().getColor(R.color.white));
            }
        } else {
            gyroBtn.setSelected(true);
            gyroBtn.setTextColor(getResources().getColor(R.color.grenat));
            touchBtn.setSelected(false);
            touchBtn.setTextColor(getResources().getColor(R.color.white));
        }
        musicValue = settings.getInt("ExtraMusic", 0);
        if (musicValue > 0) {
            if(musicValue == 1) {
                musicButton.setImageResource(R.drawable.ic_music_note_white_36dp);
                musicButton.setSelected(true);
            } else if(musicValue == 2){
                musicButton.setSelected(false);
                musicButton.setImageResource(R.drawable.ic_music_note_off_white_36dp);
            }
        }
        vibrationValue = settings.getInt("ExtraVibrate", 0);
        if (musicValue > 0) {
            if(vibrationValue == 1) {
                vibrationButton.setImageResource(R.drawable.ic_vibrate_white_36dp);
                vibrationButton.setSelected(true);
            } else if(vibrationValue == 2){
                vibrationButton.setSelected(false);
                vibrationButton.setImageResource(R.drawable.ic_cellphone_white_36dp);
            }
        }

    }
}