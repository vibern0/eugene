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
                        Socket clientSocket = new Socket("192.168.4.1", 5678);
                        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
                        connected = true;   
                        //BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                        //sentence = inFromUser.readLine();
                        outToServer.writeBytes("hello" + '\n');
                        //modifiedSentence = inFromServer.readLine();
                        //System.out.println("FROM SERVER: " + modifiedSentence);
                        clientSocket.close();
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
    }

    public void onClickLigar(View v) {
    }

    public void onClickDesligar(View v) {
    }
}
