import java.net.*;
import java.io.*;
import java.util.Random;

public class QuoteClient {
    public static final int PORT = 10000;

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
        Socket socket = new Socket();
        Random rnd = new Random();
        try {
            socket.connect(new InetSocketAddress("localhost", PORT));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            int numQuotes = 1 + rnd.nextInt(4);
            System.out.println("Sending " + numQuotes + " random quotes to "
                + "server.");
            while(numQuotes > 0) {
                String randomQuote = quotes[rnd.nextInt(quotes.length)];
                System.out.println("Sending random quote: " + randomQuote);
                out.println(randomQuote);
                Thread.sleep(rnd.nextInt(3000));
                numQuotes--;
            }
        } finally {
            socket.close();
        }
    }
}

