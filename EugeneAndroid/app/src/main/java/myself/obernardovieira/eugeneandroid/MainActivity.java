package myself.obernardovieira.eugeneandroid;

import android.app.Activity;
import android.os.Bundle;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        new Thread(new Runnable() {
            @Override
            public void run() {
                String serverName = "192.168.4.15";
                int port = 8888;
                try {
                    System.out.println("Connecting to " + serverName + " on port " + port);
                    Socket client = new Socket(serverName, port);
                    System.out.println("Just connected to " + client.getRemoteSocketAddress());
                    OutputStream outToServer = client.getOutputStream();
                    DataOutputStream out = new DataOutputStream(outToServer);
                    //
                    out.writeUTF("Hello from");
                    client.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();


    }
}
