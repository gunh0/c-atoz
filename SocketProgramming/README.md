### Code Explanation

This code implements a simple TCP/IP server. It creates a socket, sets a port number, and demonstrates responding to client requests. When you run this example code, it waits for client requests on the specified port. Upon a client connection, it sends a message "Hello from server." This example code serves as a basic illustration, and in practice, additional features and security measures would be necessary.

<br/>

### Execution

```bash
make run_server
./server
Client message: Hello from client
Response sent: Hello from server!
```

```bash
make run_client
./client
Hello message sent
Hello from server!
```
