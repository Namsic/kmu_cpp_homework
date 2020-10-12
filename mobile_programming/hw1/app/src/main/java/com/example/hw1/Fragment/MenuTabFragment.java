package com.example.hw1.Fragment;

import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.example.hw1.Activity.MainActivity;
import com.example.hw1.R;

public class MenuTabFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState){
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_tab, container, false);

        final Button btn_list = rootView.findViewById(R.id.btn_list);
        final Button btn_bag = rootView.findViewById(R.id.btn_bag);

        btn_bag.setBackgroundColor(Color.GRAY);
        btn_list.setBackgroundColor(Color.WHITE);

        btn_list.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                MainActivity activity = (MainActivity) getActivity();
                btn_bag.setBackgroundColor(Color.GRAY);
                btn_list.setBackgroundColor(Color.WHITE);
                activity.onTabChanged(0);
            }
        });
        btn_bag.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                MainActivity activity = (MainActivity) getActivity();
                btn_bag.setBackgroundColor(Color.WHITE);
                btn_list.setBackgroundColor(Color.GRAY);
                activity.onTabChanged(1);
            }
        });
        return rootView;
    }
}
