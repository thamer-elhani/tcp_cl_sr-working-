#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define MAX_BUFFER 256


int sockfd, portno, n;

struct sockaddr_in serv_addr;

struct hostent *server;

char buffer[MAX_BUFFER];

void new_socket(char *arg) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(arg);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
}

void socket_init(int portn) {
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
}

void connect_server() {
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
}

char send_question(){
    bzero(buffer,MAX_BUFFER);
    fgets(buffer,MAX_BUFFER-1,stdin);

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0){
        perror("ERROR reading from socket");
    }
    return buffer[0] ;
}

int show_answer(){
    char response[1024];  // Larger buffer for file content
    bzero(response, sizeof(response)); 
    while(n = read(sockfd, response, sizeof(response)-1) == 1023){
        response[1023] = '\0' ;
    if (n < 0){
        perror("ERROR reading from socket");
        return 0 ;
    }
    if (n == 0){
        printf("Server closed connection\n");
        return 0 ;
    }
    printf("%s\n", response) ;
}
    printf("%s\n", response) ;
    return 1 ;
}

int reseve_answer(char answer){
    switch (answer)
    {
        case '1' :
            show_answer() ;
            return 1 ;
        case '2':
            show_answer() ;
            return 1 ;
        case '3' :
            // Option 3: Ask for file path
            bzero(buffer, MAX_BUFFER);
            printf("Enter file path in data directory: ");
            fgets(buffer, MAX_BUFFER-1, stdin);
            
            // Remove newline if present
            buffer[strcspn(buffer, "\n")] = 0;
            
            // Send filepath to server
            n = write(sockfd, buffer, strlen(buffer));
            if (n < 0) {
                perror("ERROR writing to socket");
            }
            
            // Receive and display the file content
            show_answer();
            return 1 ;
        case '4' :
            show_answer();
            return 1;
        case '5' :
            return 0 ;
        default:
            return 1 ;
    }

}

void close_connection(){
    close(sockfd);
}

void run_normal_client() {
    int run = 1;
    
    printf("\n[INFO] Connected to server in NORMAL mode.\n");
    
    while (run)
    {
        bzero(buffer,MAX_BUFFER);

        printf("\n========================================\n") ;
        printf("         SERVER MENU\n") ;
        printf("========================================\n") ;
        printf("1. Show date and time\n") ;
        printf("2. List directory files\n") ;
        printf("3. Display file content (specify path)\n") ;
        printf("4. Show session elapsed time\n") ;
        printf("5. Exit\n") ;
        printf("========================================\n") ;
        printf("Enter your choice: ") ;

        char answer = send_question() ;

        run = reseve_answer(answer) ;
    }
}

void run_mono_client() {
    printf("\n[INFO] Connected to server in MONO mode.\n");
    printf("[INFO] Single session - make one request and disconnect.\n\n");
    
    bzero(buffer,MAX_BUFFER);

    printf("========================================\n") ;
    printf("         SERVER MENU (MONO)\n") ;
    printf("========================================\n") ;
    printf("1. Show date and time\n") ;
    printf("2. List directory files\n") ;
    printf("3. Display file content (specify path)\n") ;
    printf("4. Show session elapsed time\n") ;
    printf("5. Exit\n") ;
    printf("========================================\n") ;
    printf("Enter your choice: ") ;

    char answer = send_question() ;

    reseve_answer(answer) ;
}
