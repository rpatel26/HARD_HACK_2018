package com.harshil.www.harshil;

import android.support.annotation.MainThread;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.URISyntaxException;

public class MainActivity extends AppCompatActivity
{
    private Socket mSocket;
    private TextView textView;
    {
        try
        {
            mSocket = IO.socket("http://54.201.9.191:3000/");
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.disp);
        mSocket.connect();
        mSocket.on(Socket.EVENT_CONNECT, onNewMessage);
    }

    public void sendMessage(View v)
    {
        Log.v("hello","qwerty");
        mSocket.emit("chat message", "hello all!");
    }

    private Emitter.Listener onNewMessage = new Emitter.Listener()
    {
        @Override
        public void call(final Object... args) {
            MainActivity.this.runOnUiThread(new Runnable()
            {
                @Override
                public void run()
                {
                    if(args.length != 0) {
                        String message;
                        JSONObject data = (JSONObject) args[0];
                        try {
                            message = data.getString("chat message");
                        } catch (JSONException e) {
                            return;
                        }
                        textView.setText(message);
                    }
                }
            });
        }

    };

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        mSocket.disconnect();
        mSocket.off("chat message", onNewMessage);
    }
}
