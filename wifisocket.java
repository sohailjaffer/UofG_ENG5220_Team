import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class wifisocket {

    public void App2CarWifi() {

        String serverIp = "192.168.1.123"; //lab ip
        int serverPort = 12345;

        try {
            // Create a socket connection to the server
            Socket socket = new Socket(serverIp, serverPort);

            // Get input and output streams
            InputStream inputStream = socket.getInputStream();
            OutputStream outputStream = socket.getOutputStream();
            String messageToSend = "$1";

            // Send data to the server
            try {
                outputStream.write(messageToSend.getBytes());
            } catch (Exception e) {
                e.printStackTrace();
            }

            // Receive data from the server
            byte[] buffer = new byte[1024];
            int bytesRead = inputStream.read(buffer);
            String receivedMessage = new String(buffer, 0, bytesRead);
            System.out.println("Received from server: " + receivedMessage);

            // Close the socket
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
