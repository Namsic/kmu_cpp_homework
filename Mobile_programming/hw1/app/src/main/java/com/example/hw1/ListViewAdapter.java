package com.example.hw1;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import com.example.hw1.Activity.MainActivity;

public class ListViewAdapter extends BaseAdapter {
    public ListViewAdapter(){}

    @Override
    public int getCount(){
        return MainActivity.product_list.size();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent){
        final Context context = parent.getContext();

        if(convertView == null){
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.each_listview, parent, false);
        }
        TextView pName = (TextView) convertView.findViewById(R.id.tv_pname);
        TextView price = (TextView) convertView.findViewById(R.id.tv_price);

        Procuct listViewItem;
        listViewItem = MainActivity.product_list.get(position);
        pName.setText(listViewItem.p_name);
        price.setText(Integer.toString(listViewItem.price));

//        convertView.setOnClickListener(new View.OnClickListener(){
//            @Override
//            public void onClick(View view){
//                //
//            }
//        });
        return convertView;
    }

    @Override
    public long getItemId(int position){
        return position;
    }

    @Override
    public Object getItem(int position){
        return MainActivity.product_list.get(position);
    }
}