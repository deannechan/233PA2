#include "RequestPacket.h"

const int16_t StartOfPacketId = 0xFFFF;
const int16_t EndOfPacketId = 0xFFFF;
const int16_t ClientId = 1;//0xFF;
const int16_t AccPer = 0xFFF8;
const int16_t Length = 0xFF;
const int32_t SourceSubscriberNo = 0xFFFFFFFF;
const int16_t NotPaid = 0xFFF9;
const int16_t NotExist = 0xFFFA;
const int16_t AccessOk = 0xFFFB;

// permission packet
char* permission(int segmentNumber, int tech, uint32_t sourceSubNo){
    char* onePacket= malloc(15);
    int len = 5;
    memset(onePacket,'\0',15);
    memcpy(onePacket, &StartOfPacketId, 2);
    memcpy(onePacket+2, &ClientId, 1);
    memcpy(onePacket+3, &AccPer, 2);
    memcpy(onePacket+5, &segmentNumber,1);
    memcpy(onePacket+6, &len,1);
    memcpy(onePacket+7, &tech,1);
    memcpy(onePacket+8, &sourceSubNo,4);
    memcpy(onePacket+12, &EndOfPacketId, 2);
    printMessagePacket(onePacket);
    return onePacket;
}

// send packet to server
char* sendPacket(int s, char* packet, struct sockaddr_in server){
	int size = 10;
	char* buf = malloc(265);

	for(int i = 0; i < 4; i++){
		sendto(s, packet, strlen(packet), 0, (struct sockaddr *) &server, sizeof(server) );
        memset(buf,'\0', 265);
		int rc = recv(s, buf, 265, 0);
		
		if(rc > 0){
			return buf;
		}else if(i != 0 && rc <= 0){
			printf("Resend packet to server %d\n", i);	
            sleep(3);
		}
	}
	return NULL;
}

// check response if OK or error
char* checkResponse(char* packet){
    int16_t flag;
    memcpy(&flag, packet + 3, 2);

    if(flag == NotPaid){
        return "This number is unpaid!";
    }
    if(flag == NotExist){
        return "This number does not exist!";
    }
    if(flag == AccessOk){
        return "Permitted";
    }
    return "Error";
    
}

void printMessagePacket(char* message){
    int msg;
    int subNo;
    printf("Request Packet Info:\n");
    memcpy(&msg, &message[0], 2);
    printf("Start of Packet id: %#X \n", msg);
    printf("Client id: %d \n", message[2]);
    memcpy(&msg, &message[3], 2);
    printf("Permission: %#X \n", msg);
    printf("Segment No: %d \n", message[5]);
    printf("Length: %d \n", message[6]);
    printf("Technology: %d \n", message[7]);
    memcpy(&subNo, &message[8], 4); 
    printf("Source Subscriber No: %"PRIu32"\n", subNo);
    memcpy(&msg, &message[12], 2); 
    printf("End of Packet id: %#X \n", msg);  
}