package com.example.projekiot4;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef = database.getReference();

    final DatabaseReference btnStatusDB = myRef.child("Node1").child("Power");
    final DatabaseReference txtAdrValue = myRef.child("Node1").child("LDR");

    private String onOff = "OFF";
    private Button iBottonOnOff;
    private TextView iTxtValue;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        iBottonOnOff = findViewById(R.id.buttonPower);
        iTxtValue = findViewById(R.id.txtAdrValue);

        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                String value = snapshot.child("Node1/LDR").getValue().toString();
                iTxtValue.setText(String.valueOf(value));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });

        iBottonOnOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(onOff == "OFF"){
                    btnStatusDB.setValue("ON");
                    onOff = "ON";
                }else{
                    btnStatusDB.setValue("OFF");
                    onOff = "OFF";
                }
            }
        });
    }

}
