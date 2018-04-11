package com.acm.bicycleshare;

import android.content.Intent;
import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.ProgressBar;

public class location extends AppCompatActivity {

    private ProgressBar progressBar;
    WebView webview;
    Button button;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_location);
        progressBar=(ProgressBar) findViewById(R.id.progressBar);
        progressBar.setMax(100);
        webview=(WebView) findViewById(R.id.web);
        //getSupportActionBar().setHomeButtonEnabled(true);
        //getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        webview.setVisibility(View.VISIBLE);
        progressBar.setVisibility(View.VISIBLE);
        webview.getSettings().setJavaScriptEnabled(true);
        webview.setWebChromeClient(new WebChromeClient(){
            public void onProgressChanged(WebView view, int progress)
            {
                progressBar.setProgress(progress);
                if(progress == 100)
                {
                    progressBar.setVisibility(View.GONE);
                }
                super.onProgressChanged(view, progress);
            }
        });
        webview.setWebViewClient(new WebViewClient(){
            @Override
            public void onPageStarted(WebView view, String url, Bitmap favicon) {
                super.onPageStarted(view,url, favicon);
            }
            @Override
            public void onPageFinished(WebView view, String url) {
                super.onPageFinished(view, url);
                progressBar.setVisibility(View.GONE);
                webview.setVisibility(View.VISIBLE);
            }

        });
        webview.loadUrl(getIntent().getStringExtra("url"));
        progressBar.setProgress(0);
        button=(Button) findViewById(R.id.button3);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                Intent intent = new Intent(location.this, startRide.class);
                startActivity(intent);


            }
        });
    }
}
