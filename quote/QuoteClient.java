import java.net.InetSocketAddress;
import java.net.Socket;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.Random;

public class QuoteClient {
    public static final int PORT = 10000;

    // Array of quotes
    private static String[] quotes = {
       "Knowledge comes, but wisdom lingers.",
       "A joke is a very serious thing.",
       "Where there is love there is life.",
       "Brevity is the soul of wit.",
       "Be not afraid of going slowly, be afraid only of standing still.",
       "In teaching others we teach ourselves.",
       "Computers are useless. They can only give you answers.",
       "Never trust a computer you can’t throw out a window.",
       "Portability is for people who cannot write new programs."
    };

    public static void main(String[] args)
        throws IOException, InterruptedException
    {
        // Create a socket
        Socket socket = new Socket();

        // Create a random number source
        Random rnd = new Random();

        try {
            // Connect to the localhost on PORT
            socket.connect(new InetSocketAddress("localhost", PORT));

            // PrintWriter is a wrapper class to print lines to a stream, in
            // this case output stream of the socket.
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            // Pick a random number of quotes from 1 to 5
            int numQuotes = 1 + rnd.nextInt(4);

            System.out.println("Sending " + numQuotes + " random quotes to "
                + "server.");

            // While there are quotes to post
            while(numQuotes > 0) {

                // Pick a random quote from the array
                String randomQuote = quotes[rnd.nextInt(quotes.length)];

                System.out.println("Sending random quote: " + randomQuote);

                // Write quote to the socket
                out.println(randomQuote);

                // Wait for some random time between 0-3 secs
                Thread.sleep(rnd.nextInt(3000));

                // Reduce number of quotes left
                numQuotes--;
            }
        } finally {
            // Close the socket before leave
            socket.close();
        }
    }
}

