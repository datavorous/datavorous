Creating a simple web server in C++ can be accomplished using various libraries. For this example, we will use the **Boost.Asio** library, which provides networking functionality in a cross-platform manner. This server will be able to handle basic HTTP GET requests.

### Prerequisites
Before proceeding, ensure you have the Boost library installed on your system. You can install it via a package manager or download it from the [Boost website](https://www.boost.org/).

### Code Implementation

Here's a simple HTTP server implemented in C++ using Boost.Asio:

```cpp
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp; // Using tcp from boost::asio

// Function to handle client connection
void handle_client(tcp::socket& socket) {
    try {
        char buffer[1024]; // Buffer to read data from client
        std::size_t length = socket.read_some(boost::asio::buffer(buffer)); // Read request

        // Print the received request to the console
        std::cout << "Received request:\n";
        std::cout.write(buffer, length);
        std::cout << std::endl;

        // Prepare HTTP response
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/plain\r\n"; // Setting content type
        response += "Content-Length: 13\r\n"; // Length of response body
        response += "Connection: close\r\n\r\n"; // Close connection after response
        response += "Hello, World!"; // Response body

        // Send the response to the client
        boost::asio::write(socket, boost::asio::buffer(response));
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context; // I/O context for asynchronous operations

        // Create an acceptor to listen for incoming connections
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080)); // Listening on port 8080

        std::cout << "Server is running on http://localhost:8080...\n";

        while (true) {
            // Create a socket to hold the connection
            tcp::socket socket(io_context);
            acceptor.accept(socket); // Accept incoming connection

            // Handle the client connection
            handle_client(socket);
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Catch and display any exceptions
    }

    return 0; // Indicate that the program ended successfully
}
```

### Explanation of the Code

1. **Includes and Namespace**:
   ```cpp
   #include <iostream>
   #include <string>
   #include <boost/asio.hpp>

   using boost::asio::ip::tcp; // Using tcp from boost::asio
   ```
   - We include necessary headers: `<iostream>` for console output, `<string>` for string manipulation, and `<boost/asio.hpp>` for networking functionalities.
   - The `tcp` type from Boost.Asio is brought into the current namespace for convenience.

2. **Handling Client Connections**:
   ```cpp
   void handle_client(tcp::socket& socket) {
       // Function implementation...
   }
   ```
   - This function takes a socket reference and handles communication with a connected client.

3. **Reading Client Requests**:
   ```cpp
   char buffer[1024]; // Buffer to read data from client
   std::size_t length = socket.read_some(boost::asio::buffer(buffer)); // Read request
   ```
   - We declare a buffer to store incoming data and read the client's request using `socket.read_some()`. This function reads some data from the socket into the buffer.

4. **Preparing HTTP Response**:
   ```cpp
   std::string response = "HTTP/1.1 200 OK\r\n";
   response += "Content-Type: text/plain\r\n"; // Setting content type
   response += "Content-Length: 13\r\n"; // Length of response body
   response += "Connection: close\r\n\r\n"; // Close connection after response
   response += "Hello, World!"; // Response body
   ```
   - A simple HTTP response is created indicating a successful request (`200 OK`). 
   - It includes the content type, content length, and a "Hello, World!" message in the body.

5. **Sending the Response**:
   ```cpp
   boost::asio::write(socket, boost::asio::buffer(response));
   ```
   - The response is sent back to the client using `boost::asio::write()`.

6. **Setting Up the Server**:
   ```cpp
   int main() {
       boost::asio::io_context io_context; // I/O context for asynchronous operations

       // Create an acceptor to listen for incoming connections
       tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080)); // Listening on port 8080

       std::cout << "Server is running on http://localhost:8080...\n";

       while (true) {
           // Create a socket to hold the connection
           tcp::socket socket(io_context);
           acceptor.accept(socket); // Accept incoming connection

           // Handle the client connection
           handle_client(socket);
       }
   }
   ```
   - The server listens for incoming connections on port 8080 using a `tcp::acceptor`.
   - It enters an infinite loop, accepting and handling client connections.

### Running the Server

1. **Build the Program**:
   Ensure you link against Boost libraries when compiling the program. For example:
   ```bash
   g++ -o simple_server simple_server.cpp -lboost_system -lpthread
   ```

2. **Run the Server**:
   Execute the server:
   ```bash
   ./simple_server
   ```

3. **Testing the Server**:
   Open a web browser or use `curl` to send a GET request:
   ```bash
   curl http://localhost:8080
   ```

You should see `Hello, World!` as the response.

### Conclusion
This example demonstrates a simple web server in C++ using Boost.Asio. You can expand it by adding features like handling different HTTP methods, serving static files, or managing multiple clients using threads. This basic structure serves as a foundation for building more complex web applications in C++.