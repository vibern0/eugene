package myself.obernardovieira.eugeneandroid;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class MainActivity extends Activity {

    boolean connected = false;
    Socket clientSocket;
    DataOutputStream outToServer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void onResume() {
        super.onResume();

        if(!connected) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        //String sentence;
                        //String modifiedSentence;
                        //BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
                        clientSocket = new Socket("192.168.4.1", 5678);
                        outToServer = new DataOutputStream(clientSocket.getOutputStream());
                        connected = true;
                        //BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                        //sentence = inFromUser.readLine();
                        outToServer.writeBytes("hello" + '\n');
                        outToServer.flush();
                        //modifiedSentence = inFromServer.readLine();
                        //System.out.println("FROM SERVER: " + modifiedSentence);

                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }).start();
        }

    }

    @Override
    protected void onPause() {
        super.onPause();

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    clientSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();

    }

    public void onClickLigar(View v) {

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    outToServer.writeBytes("play" + '\n');
                    outToServer.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();

    }

    public void onClickDesligar(View v) {

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    outToServer.writeBytes("stop" + '\n');
                    outToServer.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();

    }
}
