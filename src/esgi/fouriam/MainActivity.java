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
import android.util.Log;
import android.widget.EditText;
import android.content.SharedPreferences;
import android.widget.Toast;
import android.app.AlertDialog;
import android.widget.LinearLayout;
import android.content.DialogInterface;

public class MainActivity extends Activity
{
    private static final String TAG = "MainActivity";
    public static final String PREFS_NAME = "SpaceWarPreferences";
	private TextView playBtn;
    private ImageView configurationBtn;
	private Intent gameIntent;
    private Intent configIntent;
    private SharedPreferences settings;
    private String playerName;
    private Toast toast;
    /** Called when the activity is first created. */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        toast = Toast.makeText(this, "", Toast.LENGTH_SHORT);
        gameIntent = new Intent(this, SDLActivity.class);
        configIntent = new Intent(this, ConfigurationActivity.class);

        configurationBtn = (ImageView) findViewById(R.id.settingsButton);
        configurationBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(configIntent);
            }
        });

        playBtn = (TextView) findViewById(R.id.jouerBtn);
        playBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (playerName == null || playerName.equals("")) {
                
                    DisplayNamePopup();
                } else { 
                    startActivity(gameIntent); 
                }
            }
        });


    }
    @Override
    protected void onResume() {
        super.onResume();
        settings = getSharedPreferences(PREFS_NAME, 0);
        playerName = settings.getString("playerName", "");
    }
    private void DisplayNamePopup() {
        AlertDialog.Builder alertDialog = new AlertDialog.Builder(MainActivity.this);
        alertDialog.setTitle(getResources().getString(R.string.playerName));
     alertDialog.setMessage(getResources().getString(R.string.playerNameText));

     final EditText input = new EditText(MainActivity.this);
     LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(
         LinearLayout.LayoutParams.MATCH_PARENT,
         LinearLayout.LayoutParams.MATCH_PARENT);
     input.setLayoutParams(lp);
     alertDialog.setView(input);

     alertDialog.setPositiveButton("YES",
         new DialogInterface.OnClickListener() {
             public void onClick(DialogInterface dialog, int which) {

                SharedPreferences.Editor prefsEditor = settings.edit();

                 prefsEditor.putString("playerName", input.getText().toString());
                 prefsEditor.apply();
                 playerName = input.getText().toString();
                 toast.setText(getResources().getString(R.string.saved));
                 toast.show();
                 dialog.cancel();
             }
         });

     alertDialog.setNegativeButton("NO",
         new DialogInterface.OnClickListener() {
             public void onClick(DialogInterface dialog, int which) {
                 dialog.cancel();
             }
         });

     alertDialog.show();
    }
}
