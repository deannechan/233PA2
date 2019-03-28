// Deanne Chan W1393868

#include "ServerPacket.h"

#define BUFLEN 265  //length of buffer

int lookup_subscriber(char technology, long telNo);

int main(){
    int s;
    struct sockaddr_in server, client;
    int slen, recv_len;
    char buf[BUFLEN];
    char technology;
    char segNo;
    const int16_t END = 0xFFFF;
    slen = sizeof(client);
    uint32_t recvNum;

    // Create the socket
	// 1) Internet Domain 2) Datagram 3) Default protocol (UDP)
	s = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket was Created.\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(12345);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind info to socket
	bind(s, (struct sockaddr *) &server, sizeof(server));
    puts("Bind done");

    //keep listening for data
    int count = 1; //count packet order
    while(1){
        printf("----------------------\n");
        printf("Server is Listening!!\n");
        fflush(stdout);
        //clear the buffer
        memset(buf,'\0', BUFLEN);

        //receive data
        recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &client, (socklen_t *) &slen);
        printf("Received Packet From %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        memcpy(&segNo, buf+5, 1); 
        int segNum = (int)segNo; //segment number
        printf("Received Segment No.: %d\n",segNum);

        memcpy(&technology, buf + 7, 1);
        int techType = (int)technology;
        memcpy(&recvNum, buf + 8, 4) ;
        printf("Calling Number: %"PRIu32"\n", recvNum);
        printf("Technology: %d\n", techType);

        char* notPaidYet;
        char* notExisting;
        char* isPermitted;
        
        // check if number/technology exist and if paid or unpaid
        int res = lookup_subscriber(technology, recvNum);

        if (res == 1) // not exist
        {
            printf("Number doesn't exist\n\n");
            notExisting = doesNotExist(segNum, techType, recvNum);
            sendto(s, notExisting, strlen(notExisting), 0, (struct sockaddr*) &client, slen);
        }
        else if (res == 2) // not paid
        {
            printf("Unpaid Number\n\n");
            notPaidYet = hasNotPaid(segNum, techType, recvNum);
            sendto(s, notPaidYet, strlen(notPaidYet), 0, (struct sockaddr*) &client, slen);
        }
        else // OK
        {
            printf("Permitted\n\n");
            isPermitted = permitted(segNum, techType, recvNum);
            sendto(s, isPermitted, strlen(isPermitted), 0, (struct sockaddr*) &client, slen);
        }
    }
    return 0;
}

// open Verification_Database.txt to see if number and technology exist and if paid or unpaid
int lookup_subscriber(char technology, long telNo){
    FILE *file;
    char search[16], *buf= NULL;
    int read, found = 0;
    size_t len;

    sprintf(search, "%d-%d-%d\t%02d", (int)(telNo / 10000000),
            (int)(telNo / 10000 % 1000), (int)(telNo % 10000), technology);

    file = fopen("data/Verification_Database.txt", "r");
    printf("Opening verification_database\n");
    printf("search: %s\n", search);
    
    if (file == NULL)
        return 1; // error|not exist
    while ((read = getline(&buf, &len, file)) != -1){
        if (strncmp(search, buf, strlen(search)) == 0){
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found){
        free(buf);
        return 1; // not exist
    }
    for (char *line = buf+ strlen(search); *line; line++){
        if (*line == '1')
        {
            free(buf);
            return 0; // paid
        }
    }
    free(buf);
    return 2; // not paid
}