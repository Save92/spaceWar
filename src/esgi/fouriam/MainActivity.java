package esgi.fouriam;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import esgi.fouriam.R;
import android.content.Intent;
import android.widget.TextView;
import android.widget.Button;
import android.view.View;

public class MainActivity extends Activity
{
	private TextView playBtn;
	private Intent gameIntent;
    /** Called when the activity is first created. */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        gameIntent = new Intent(this, SDLActivity.class);
        playBtn = (TextView) findViewById(R.id.jouerBtn);
        playBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	startActivity(gameIntent);
            
            }
        });
    }
}
