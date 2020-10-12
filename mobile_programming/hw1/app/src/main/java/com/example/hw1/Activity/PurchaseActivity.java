package com.example.hw1.Activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.hw1.R;

public class PurchaseActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_purchase);

        Button btnPurchase = (Button) findViewById(R.id.btn_purchaseOK);
        TextView purchaseName = (TextView) findViewById(R.id.tv_purchaseName);
        TextView purchasePrice = (TextView) findViewById(R.id.tv_purchasePrice);

        Intent recvIntent = getIntent();
        purchaseName.setText(recvIntent.getStringExtra("name"));
        purchasePrice.setText("" + recvIntent.getIntExtra("price", 0));

        btnPurchase.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });
    }
}
