package com.acm.bicycleshare;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    EditText usernameEditText;
    EditText passwordEditText;

    Button button;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        usernameEditText=(EditText)findViewById(R.id.editText);
        passwordEditText=(EditText)findViewById(R.id.editText2);
        final String username=usernameEditText.getText().toString();
        final String password=passwordEditText.getText().toString();
        button=(Button) findViewById(R.id.login_button);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {


                //if(password.equals("Adeep")) {
                    Intent intent = new Intent(MainActivity.this, homePage.class);
                    startActivity(intent);
                /*}
                else
                {
                    Toast.makeText(MainActivity.this, "Incorrect Login Credentials", Toast.LENGTH_SHORT).show();
                }*/


            }
        });
    }
}
