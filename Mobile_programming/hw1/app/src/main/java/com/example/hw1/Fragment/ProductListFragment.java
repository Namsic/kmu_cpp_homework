package com.example.hw1.Fragment;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.example.hw1.Activity.MainActivity;
import com.example.hw1.Activity.PurchaseActivity;
import com.example.hw1.ListViewAdapter;
import com.example.hw1.Procuct;
import com.example.hw1.R;

public class ProductListFragment extends Fragment {
    ListView lv;
    ListViewAdapter adapter = new ListViewAdapter();
    LinearLayout layout_action;
    TextView tv_clickedProduct;
    Button btn_addBag, btn_purchase;

    int clickedPosition = -1;

    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState){
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_product, container, false);

        lv = rootView.findViewById(R.id.lv_product);
        lv.setAdapter(adapter);
        layout_action = rootView.findViewById(R.id.layout_action);
        tv_clickedProduct = rootView.findViewById(R.id.tv_clickedProductName);
        btn_addBag = rootView.findViewById(R.id.btn_addBag);
        btn_purchase = rootView.findViewById(R.id.btn_purchase);

        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                tv_clickedProduct.setVisibility(View.VISIBLE);
                btn_addBag.setVisibility(View.VISIBLE);
                btn_purchase.setVisibility(View.VISIBLE);
                tv_clickedProduct.setText(MainActivity.product_list.get(position).p_name);
                clickedPosition = position;
            }
        });

        btn_addBag.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Procuct temp = MainActivity.product_list.get(clickedPosition);
                if(MainActivity.bag_list.contains(temp)) {
                    Toast.makeText(getContext(), "이미 장바구니에 추가된 상품입니다.", Toast.LENGTH_SHORT).show();
                }else {
                    MainActivity.bag_list.add(temp);
                    Toast.makeText(getContext(), "장바구니에 추가되었습니다.", Toast.LENGTH_SHORT).show();
                }
            }
        });

        btn_purchase.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getActivity().getApplicationContext(), PurchaseActivity.class);
                intent.putExtra("name", MainActivity.product_list.get(clickedPosition).p_name);
                intent.putExtra("price", MainActivity.product_list.get(clickedPosition).price);
                startActivity(intent);
            }
        });

        return rootView;
    }
}
