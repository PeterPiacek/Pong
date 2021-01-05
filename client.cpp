#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <termios.h>

class client {
private:
    int sockfd, n, width, height;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    char buffer2[2];
    cGameManager *c;
public:

    /*
     * Funkcia prevzata z webu:
     * https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
     */
    char mygetch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
            perror("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror("tcsetattr ~ICANON");
        return (buf);
    }

    void start(int width, int height) {
        c->setSize(height, width);
        c->player2Function();
    }

    void readWriteServer() {
        buffer[10] = 0;
        while (true) {
            //-------------- WRITE to server --------------
            bzero(buffer, 256);
            std::this_thread::sleep_for(0.01s);
            c->player2GetParams(buffer);
            if (c->getQuit()) {
                std::cout << "ukoncili ste hru\n";
                buffer[10] = 1;
                n = write(sockfd, buffer, strlen(buffer));
                return;
            } else {
                buffer[0] = (int)buffer[0] + 1;
                n = write(sockfd, buffer, strlen(buffer));
            }
            if (n < 0) {
                perror("Error writing to socket");
                return;
            }
            //-------------- READ from server --------------
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            buffer[0] = (int)buffer[0] - 1;
            if ((int) buffer[10] == 1) {
                std::cout << "server ukoncil hru\n";
                return;
            } else if (n < 0) {
                perror("Error reading from socket");
                std::cout << "press q to exit\n";
                return;
            } else {
                c->player1SetPosition((int) buffer[0], (int) buffer[1], (int) buffer[2], (int) buffer[3],
                                     (int) buffer[4]);
            }

        }
    }

    client(int argc, char *argv[]) {

        if (argc < 3) {
            fprintf(stderr, "usage %s hostname port\n", argv[0]);
            return;
        }

        server = gethostbyname(argv[1]);
        if (server == NULL) {
            fprintf(stderr, "Error, no such host\n");
            return;
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy(
                (char *) server->h_addr,
                (char *) &serv_addr.sin_addr.s_addr,
                server->h_length
        );
        serv_addr.sin_port = htons(atoi(argv[2]));

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Error creating socket");
            return;
        }

        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("Error connecting to socket");
            return;
        }

        bzero(buffer2, 2);
        n = read(sockfd, buffer2, 2);
        if (n < 0) {
            perror("Error reading from socket");
            return;
        }
        c = new cGameManager((int) buffer2[0], (int) buffer2[1]);
        std::thread threadGame(&client::start, this, (int) buffer2[0], (int) buffer2[1]);
        std::thread threadReadWrite(&client::readWriteServer, this);
        std::cout << "startC" << "\n";
        threadGame.join();
        threadReadWrite.join();
        std::cout << "exitC" << "\n";
        delete c;
        close(sockfd);

        return;
    }
};