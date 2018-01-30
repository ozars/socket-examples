# Socket Examples

There are three examples to demonstrate sockets in this project.

## hello_tcp

A hello server/client implemented on top of TCP. Client connects and server
says hello. It uses port 10000 by default.

Implemented in C.

Usage:
```
make
./helloserver
./helloclient
```

## hello_udp

A hello server/client implemented on top of UDP. Client connects and says
hello to server. It uses port 10000 by default.

Implemented in C.

Usage:
```
make
./helloserver
./helloclient
```

## quote

A quote server/client implemented on top of TCP. Clients connects to server and sends random number of quotes.

Implemented in Java.

Usage:
```
javac QuoteServer.java QuoteClient.java
java QuoteServer
java QuoteClient
```

## Author

Omer Ozarslan
<omer@utdallas.edu>

