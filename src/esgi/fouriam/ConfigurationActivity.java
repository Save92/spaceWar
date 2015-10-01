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

public class ConfigurationActivity extends Activity
{
	private EditText playerName;
    /** Called when the activity is first created. */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.configuration);

        playerName = (EditText) findViewById(R.id.playerNameText);

    }
}