#include "clientdef.h"

int main(int argc, char *argv[])
{
    int run = 1;
    int client_mode;
    
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);

    // Display client mode selection menu
    printf("\n========================================\n");
    printf("      TCP CLIENT - MODE SELECTION\n");
    printf("========================================\n");
    printf("1. Normal client\n");
    printf("2. MONO client (simple single session)\n");
    printf("========================================\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &client_mode) != 1) {
        fprintf(stderr, "ERROR: Invalid input\n");
        exit(1);
    }
    
    // Clear input buffer
    while (getchar() != '\n');

    // 1. Create a socket
    new_socket(argv[1]) ;

    socket_init(portno) ;

    // 2. Connect to the server
    connect_server() ;

    // 3. Communicate based on selected mode
    if (client_mode == 2) {
        // MONO client mode - simpler single session
        run_mono_client();
    } else {
        // Normal client mode
        run_normal_client();
    }

    close_connection() ;
    return 0;
}
