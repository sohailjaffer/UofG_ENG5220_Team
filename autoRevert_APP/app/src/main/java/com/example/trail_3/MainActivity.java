package com.example.trail_3;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    private static final String HOST = "192.168.1.104";  // Raspberry Pi IP
    private static final int PORT = 12345;  // Port for communication
    private Socket socket;
    private DataOutputStream dataOutputStream;

    Button Left;
    Button Right;
    Button Forward;
    Button Backward;
    Button Stop;
    Button Reverse;
    ImageView wifi;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize buttons and image view
        Left = findViewById(R.id.button);
        Right = findViewById(R.id.button3);
        Forward = findViewById(R.id.button2);
        Backward = findViewById(R.id.button4);
        Stop = findViewById(R.id.button5);
        Reverse = findViewById(R.id.button6);
        wifi = findViewById(R.id.imageView);

        // Set up socket connection
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    socket = new Socket(HOST, PORT);
                    dataOutputStream = new DataOutputStream(socket.getOutputStream());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();

        // Button click listeners
        Left.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCommand("$3"); // Send Left command
            }
        });

        Right.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCommand("$4"); // Send Right command
            }
        });

        Forward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCommand("$1"); // Send Forward command
            }
        });

        Backward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCommand("$2"); // Send Backward command
            }
        });

        Stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCommand("$0"); // Send Stop command
            }
        });

        Reverse.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCommand("$5"); // Send Reverse command
            }
        });

        wifi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showIPInputDialog();
            }
        });
    }

    private void showIPInputDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
        builder.setTitle("Enter IP Address");

        final EditText input = new EditText(MainActivity.this);
        builder.setView(input);

        builder.setPositiveButton("Save", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                String ipAddress = input.getText().toString();
                // Update HOST with the entered IP address
               // HOST = ipAddress;
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

    // Method to send command to the Python server
    private void sendCommand(final String command) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    if (dataOutputStream != null) {
                        dataOutputStream.writeUTF(command);
                        dataOutputStream.flush();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
}
