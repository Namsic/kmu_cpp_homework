package com.example.hw1;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class Procuct {
    public String p_name;
    public int price;

    public Procuct(){}
    public Procuct(String name, int price){
        this.p_name = name;
        this.price = price;
    }

    public void addDatabase(String p_code){
        DatabaseReference mDatabase = FirebaseDatabase.getInstance().getReference();
        mDatabase.child(p_code).setValue(this);
    }


}
