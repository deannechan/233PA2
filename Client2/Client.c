// Deanne Chan W1393868

#include "RequestPacket.h"

#define BUFLEN 512  //Max length of buffer

int main_thread(int s, struct sockaddr_in server, char **error);
char *read_input(char *buffer, int bufSize, char segmentNo);

int main(void){
    struct sockaddr_in server, client;
    struct hostent *hp;
    int s, slen = sizeof(client);
    char* buf;
    char* packet;
    char* error;
    struct timeval tv;

    //build socket
    s = socket(AF_INET, SOCK_DGRAM, 0);

    //setup address
    memset((char *) &client, 0, sizeof(client));
    
    //client address struct
	client.sin_family = AF_INET;
	client.sin_port = htons(22345);
	hp = gethostbyname("localhost");
    bcopy( hp->h_addr, &(client.sin_addr.s_addr), hp->h_length);

	//bind info to socket
	bind(s, (struct sockaddr *) &client, sizeof(client));

    //server address struct
	server.sin_family = AF_INET;
	server.sin_port = htons(12345);
	bcopy( hp->h_addr, &(server.sin_addr.s_addr), hp->h_length);

    tv.tv_usec = 0;
	tv.tv_sec = 3;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*) &tv, sizeof(struct timeval));

    printf("\nclient started, waiting for input...");
    if (main_thread(s, server, &error) != 0){
        fprintf(stderr, "main_thread: %s\n", error);
        return 1;
    }

    printf("Transmission Complete \n");

    return 0;
}

int main_thread(int s, struct sockaddr_in server, char **error){
    char input_buffer[256], currentSegmentNo = 1, *message, *buf, *response;

    while (1){
        // read input
        message = read_input(input_buffer, 256, currentSegmentNo);
        if (message == NULL)
            continue;
        // send and get response 
        buf = sendPacket(s, message, server); 
        if (buf != NULL){
            response = checkResponse(buf);
            currentSegmentNo++;
            printf("Response from server is: %s\n", response);
            printf("-----------------------------\n\n");
            printf("client started, waiting for input...");
        }else{
            printf("Server does not respond.\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

char *read_input(char *buffer, int bufSize, char segmentNo){
    char *pos, technology;
    long subscriberNo;

    // read technology input 
    printf("\n-----------\n");
    printf("|02 = 2G  |\n");
    printf("|03 = 3G  |\n");
    printf("|04 = 4G  |\n");
    printf("|05 = 5G  |\n");
    printf("-----------\n"); 
    printf("Please input the technology: ");
    if (fgets(buffer, bufSize, stdin) == NULL)
        return NULL;
    if ((pos = strchr(buffer, '\n')) != NULL)
        *pos = '\0';
    if (strlen(buffer) == 0)
        return NULL;
    if (strcmp(buffer, "02") == 0)
        technology = 2;
    else if (strcmp(buffer, "03") == 0)
        technology = 3;
    else if (strcmp(buffer, "04") == 0)
        technology = 4;
    else if (strcmp(buffer, "05") == 0)
        technology = 5;
    else
        return NULL;

    // read subscriber number input 
    printf("Please input the subscriber no: ");
    if (fgets(buffer, bufSize, stdin) == NULL)
        return NULL;
    if ((pos = strchr(buffer, '\n')) != NULL)
        *pos = '\0';
    if (strlen(buffer) == 0)
        return NULL;
    subscriberNo = atol(buffer);
    if (subscriberNo < 1000000000)
        return NULL;

    char* toSend = permission(segmentNo, technology, subscriberNo);
    return toSend;
}
