package com.example.hw1.Activity;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import com.example.hw1.Fragment.MenuTabFragment;
import com.example.hw1.Fragment.ProductListFragment;
import com.example.hw1.Fragment.WishListFragment;
import com.example.hw1.Procuct;
import com.example.hw1.R;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    DatabaseReference mDatabase = FirebaseDatabase.getInstance().getReference();
    public static ArrayList<Procuct> product_list = new ArrayList<Procuct>();
    public static ArrayList<Procuct> bag_list = new ArrayList<Procuct>();

    MenuTabFragment menuTabFragment;
    Fragment[] fragments = new Fragment[2];
    public static int fragment_type;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        menuTabFragment = new MenuTabFragment();
        fragments[0] = new ProductListFragment();
        fragments[1] = new WishListFragment();
        fragment_type = 0;

        getSupportFragmentManager().beginTransaction().add(R.id.container, fragments[fragment_type]).commit();

        mDatabase.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                product_list.clear();
                for(DataSnapshot eachProduct : snapshot.getChildren())
                    product_list.add(eachProduct.getValue(Procuct.class));
                if(fragment_type == 0)
                    getSupportFragmentManager().beginTransaction().detach(fragments[0]).attach(fragments[0]).commit();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }

    public void onTabChanged(int index){
        if(index != fragment_type){
            fragment_type = index;
            getSupportFragmentManager().beginTransaction().replace(R.id.container, fragments[fragment_type]).commit();
        }
    }
}