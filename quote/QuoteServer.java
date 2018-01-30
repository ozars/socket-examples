import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Date;
import java.text.SimpleDateFormat;

public class QuoteServer {
    public static final int PORT = 10000;

    public static void main(String[] args) throws IOException
    {
        // Create a server socket
        ServerSocket serverSocket = new ServerSocket(PORT);

        // We will give ID to each connecting client to denote which client
        // sent a quote
        int clientId = 0;

        try {
            while(true) {
                // Accept a client
                Socket clientSocket = serverSocket.accept();

                // Create a new Thread using QuoteReceiver class defined below
                // and then start this thread.
                (new Thread(
                    new QuoteReceiver(clientSocket, clientId++))).start();
            }
        } finally {
            // Close the socket before leave
            serverSocket.close();
        }
    }

    // run() function of this class will be called when above Thread has been
    // started
    private static class QuoteReceiver implements Runnable {

        // Socket of the client handled in this thread
        private Socket clientSocket;

        // ID we assigned to this client
        private int clientId;

        // Initialize QuoteReceiver with accepted socket and client ID
        public QuoteReceiver(Socket clientSocket, int clientId)
        {
            this.clientSocket = clientSocket;
            this.clientId = clientId;
        }

        // This function is the entry point of the Thread, that is, it will be
        // called when Thread started.
        public void run()
        {
            try {
                log("Thread started.");

                // I call a helper function to avoid handling of exceptions.
                // This is not a good practice, but I did so to keep things
                // simple.
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
                // Create a buffered reader which will give us an easy way to
                // read new lines from socket stream.
                BufferedReader in = new BufferedReader(
                    new InputStreamReader(clientSocket.getInputStream()));

                while(true)
                {
                    // Read a line from the socket
                    String line = in.readLine();

                    // If this line is null that means client has left.
                    if(line == null) {
                        log("Connection has been closed by the client.");
                        break;
                    }

                    // Print the quote
                    log("\"" + line + "\"");
                }
            } finally {
                // Close the socket before leave
                clientSocket.close();
            }
        }

        // Pretty format method prints time and client info with message
        private void log(String msg)
        {
            System.out.println(
                new SimpleDateFormat("[HH:mm:ss.SSS]").format(new Date())
                + "[Client-" + clientId + "]" + " " + msg
            );
        }
    }
}
