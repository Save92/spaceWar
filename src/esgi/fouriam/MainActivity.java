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

public class MainActivity extends Activity
{
	private TextView playBtn;
    private ImageView configurationBtn;
	private Intent gameIntent;
    private Intent configIntent;
    /** Called when the activity is first created. */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

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
            	startActivity(gameIntent); 
            }
        });

    }
}
