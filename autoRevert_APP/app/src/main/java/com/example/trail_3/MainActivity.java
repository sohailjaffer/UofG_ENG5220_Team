package com.example.trail_3;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    Button Left;
    Button Right;
    Button Forward;
    Button Backward;

    Button Stop;
    Button Reverse;

    ImageView wifi;

    WifiSocket wifiSocket;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Left = this.findViewById(R.id.button);
        Right = this.findViewById(R.id.button3);
        Forward = this.findViewById(R.id.button2);
        Backward = this.findViewById(R.id.button4);

        Stop = this.findViewById(R.id.button5);
        Reverse = this.findViewById(R.id.button6);

        Left.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "left", Toast.LENGTH_SHORT).show();
            }
        });
        Right.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "Right", Toast.LENGTH_SHORT).show();
            }
        });
        Forward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "Forward", Toast.LENGTH_SHORT).show();
            }
        });
        Backward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "Backward", Toast.LENGTH_SHORT).show();
            }
        });


        Stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "Stop", Toast.LENGTH_SHORT).show();

            }
        });
        Reverse.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "Reverse", Toast.LENGTH_SHORT).show();
            }
        });

        wifi=this.findViewById(R.id.imageView);
        wifi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showIPInputDialog();
              //  wifiSocket.App2CarWifi(v);
            }
        });
//.

    }


    private AlertDialog alertDialog;
    private EditText editText;


    private void showIPInputDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
        builder.setTitle("Enter IP Address");

        final EditText input = new EditText(MainActivity.this);
        builder.setView(input);

        builder.setPositiveButton("Save", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                String ipAddress = input.getText().toString();
            }
        });
        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                dialogInterface.dismiss();
            }
        });

        AlertDialog dialog = builder.create();
        dialog.show();
    }



}