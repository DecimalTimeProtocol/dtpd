//  Decimal Time Protocol Daemon (dtpd) v0.0.1
//  SPDX-FileCopyrightText: 2023 Julio Jimenez <julio@julioj.com>
//  SPDX-License-Identifier: Apache-2.0

#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"
// #include <signal.h>

void* handle_client(int client_socket) {
    int client_fd = *((int*)client_socket);
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Error receiving data");
        // Handle the error as needed
    } else if (bytes_received == 0) {
        // Connection closed by the client
        close(client_socket);
    } else {
        const char* response = "Hello, client!"; // Replace with your response data

        // Send the response to the client
        ssize_t bytes_sent = send(client_socket, response, strlen(response), 0);
        if (bytes_sent == -1) {
            perror("Error sending data to client");
            // Handle the error as needed
        }
    }
    close(client_fd);
    pthread_exit(NULL);
}

int main() {
    puts("Decimal Time Protocol Daemon");
    printf("dtpd %s\n\n", VERSION);

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(16667);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }
    
    // Set server_socket to non-blocking mode
    int flags = fcntl(server_socket, F_GETFL, 0);
    fcntl(server_socket, F_SETFL, flags | O_NONBLOCK);

    fd_set read_fds;
    int max_fd = server_socket;

    struct timespec req, rem;

    // Sleep for a decimal second
    req.tv_sec = 1;
    req.tv_nsec = 666666667L;

    // if (nanosleep(&req, &rem) < 0) {
    //     perror("Nanosleep failed");
    //     return 1;
    // }

    // Set a timeout (2 seconds in this example)
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 666666667;

    float decimalSeconds = 0;
    float decimalMinutes = 0;
    float decimalHours = 0;
    float decimalDays = 1;
    float decimalMonths = 1;
    float decimalYears = 1;

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len);

        // Create a new thread to handle the client
        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, handle_client, &client_socket) != 0) {
            perror("Error creating client thread");
            close(client_socket);
        }

        if (decimalSeconds >= 99) {
            decimalSeconds = 0;
            decimalMinutes++;
        } else {
            decimalSeconds++;
        }
        if (decimalMinutes >= 99) {
            decimalMinutes = 0;
            decimalHours++;
        }
        if (decimalHours >= 9) {
            decimalHours = 0;
            decimalDays++;
        }
        if (decimalDays >= 100) {
            decimalDays = 1;
            decimalMonths++;
        }
        if (decimalMonths >= 10) {
            decimalMonths = 1;
            decimalYears++;
        }
    
        printf("decimalSeconds:\t%f\n", decimalSeconds);
        printf("decimalMinutes:\t%f\n", decimalMinutes);
        printf("decimalHours:\t%f\n", decimalHours);
        printf("decimalDays:\t%f\n", decimalDays);
        printf("decimalMonths:\t%f\n", decimalMonths);
        printf("decimalYears:\t%f\n\n", decimalYears);

        printf("decimalEpoch:\t%lu\n\n", convertToDecimalSeconds(time(NULL)));

        fflush(stdout);

        if (nanosleep(&req, &rem) < 0) {
            perror("Nanosleep failed");
            return 1;
        }
    }
    close(client_socket);
    return 0;
}
