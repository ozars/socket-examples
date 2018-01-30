import java.net.*;
import java.io.*;
import java.util.Date;
import java.text.SimpleDateFormat;

public class QuoteServer {
    public static final int PORT = 10000;

    public static void main(String[] args) throws IOException
    {
        ServerSocket serverSocket = new ServerSocket(PORT);
        int clientId = 0;
        try {
            while(true) {
                Socket clientSocket = serverSocket.accept();
                (new Thread(
                    new QuoteReceiver(clientSocket, clientId++))).start();
            }
        } finally {
            serverSocket.close();
        }
    }

    private static class QuoteReceiver implements Runnable {

        private Socket clientSocket;
        private int clientId;

        public QuoteReceiver(Socket clientSocket, int clientId)
        {
            this.clientSocket = clientSocket;
            this.clientId = clientId;
        }

        public void run()
        {
            try {
                log("Thread started.");
                realRun();
                log("Thread finished.");
            } catch(Exception ex) {
                log("Thread exception.");
                Thread t = Thread.currentThread();
                t.getUncaughtExceptionHandler().uncaughtException(t, ex);
            }
        }

        private void realRun() throws IOException
        {
            try {
                BufferedReader in = new BufferedReader(
                    new InputStreamReader(clientSocket.getInputStream()));
                while(true)
                {
                    String line = in.readLine();
                    if(line == null) {
                        log("Connection has been closed by the client.");
                        break;
                    }
                    log("\"" + line + "\"");
                }
            } finally {
                clientSocket.close();
            }
        }

        private void log(String msg)
        {
            System.out.println(
                new SimpleDateFormat("[HH:mm:ss.SSS]").format(new Date())
                + "[Client-" + clientId + "]"
                // + "[Thread" + Thread.currentThread().getId() + "]"
                // + "[" + clientSocket.getRemoteSocketAddress() + "] "
                + " " + msg
            );
        }
    }
}
