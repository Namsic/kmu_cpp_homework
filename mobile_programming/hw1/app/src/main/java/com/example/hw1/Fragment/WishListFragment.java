package com.example.hw1.Fragment;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.example.hw1.Activity.MainActivity;
import com.example.hw1.Activity.PurchaseActivity;
import com.example.hw1.Procuct;
import com.example.hw1.R;

public class WishListFragment extends Fragment {
    Button btn_purchase;
    CheckBox[] cbList = new CheckBox[3];

    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState){
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_wishlist, container, false);

        btn_purchase = rootView.findViewById(R.id.btn_wPurchase);
        cbList[0] = rootView.findViewById(R.id.checkBox1);
        cbList[1] = rootView.findViewById(R.id.checkBox2);
        cbList[2] = rootView.findViewById(R.id.checkBox3);

        for(int i=0; i<cbList.length; i++) {
            if(i < MainActivity.bag_list.size()){
                Procuct temp = MainActivity.bag_list.get(i);
                cbList[i].setText(temp.p_name + " (" + temp.price + ")");
            }else cbList[i].setText("");
        }

        btn_purchase.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getActivity().getApplicationContext(), PurchaseActivity.class);

                int cnt = 0;
                int sumPrice = 0;
                for(int i=0; i<cbList.length; i++){
                    if(cbList[i].getText() == "") continue;
                    if(cbList[i].isChecked()){
                        cnt++;
                        sumPrice += MainActivity.bag_list.get(i).price;
                    }
                }
                if(cnt == 0){
                    Toast.makeText(getContext(), "선택된 상품이 없습니다", Toast.LENGTH_SHORT).show();
                    return;
                }else if (cnt == 1)
                    intent.putExtra("name", MainActivity.bag_list.get(0).p_name);
                else
                    intent.putExtra("name", MainActivity.bag_list.get(0).p_name + "외 " + (cnt-1) + "품목");
                intent.putExtra("price", sumPrice);
                startActivity(intent);
            }
        });

        return rootView;
    }
}
