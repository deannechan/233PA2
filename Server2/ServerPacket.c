#include "ServerPacket.h"

const int16_t StartOfPacketId = 0xFFFF;
const int16_t ClientId = 1;//0xFF;
const int16_t EndOfPacketId = 0xFFFF;
const int16_t NotPaid = 0xFFF9;
const int16_t NotExist = 0xFFFA;
const int16_t AccessOk = 0xFFFB;
const int16_t Length = 5;//0xFF;
const int32_t SourceSubscriberNo = 0xFFFFFFFF;

// permitted packet
char* permitted(int segmentNumber, int tech, uint32_t sourceSubNo){
    char* onePacket= malloc(15);
    memset(onePacket,'\0',15);
    memcpy(onePacket, &StartOfPacketId, 2);
    memcpy(onePacket+2, &ClientId, 1);
    memcpy(onePacket+3, &AccessOk, 2);
    memcpy(onePacket+5, &segmentNumber,1);
    memcpy(onePacket+6, &Length,1);
    memcpy(onePacket+7, &tech,1);
    memcpy(onePacket+8, &sourceSubNo,4);
    memcpy(onePacket+12, &EndOfPacketId, 2);
    printMessagePacket(onePacket);
    return onePacket;
}

// does not exist error packet
char* doesNotExist(int segmentNumber, int tech, uint32_t sourceSubNo){
    char* onePacket= malloc(15);
    memset(onePacket,'\0',15);
    memcpy(onePacket, &StartOfPacketId, 2);
    memcpy(onePacket+2, &ClientId, 1);
    memcpy(onePacket+3, &NotExist, 2);
    memcpy(onePacket+5, &segmentNumber,1);
    memcpy(onePacket+6, &Length,1);
    memcpy(onePacket+7, &tech,1);
    memcpy(onePacket+8, &sourceSubNo,4);
    memcpy(onePacket+12, &EndOfPacketId, 2);
    printMessagePacket(onePacket);
    return onePacket;
}

// not paid error packet
char* hasNotPaid(int segmentNumber, int tech, uint32_t sourceSubNo){
    char* onePacket= malloc(15);
    memset(onePacket,'\0',15);
    memcpy(onePacket, &StartOfPacketId, 2);
    memcpy(onePacket+2, &ClientId, 1);
    memcpy(onePacket+3, &NotPaid, 2);
    memcpy(onePacket+5, &segmentNumber,1);
    memcpy(onePacket+6, &Length,1);
    memcpy(onePacket+7, &tech,1);
    memcpy(onePacket+8, &sourceSubNo,4);
    memcpy(onePacket+12, &EndOfPacketId, 2);
    printMessagePacket(onePacket);
    return onePacket;
}

void printMessagePacket(char* message){
    int msg;
    int subNo;
    printf("Packet Info:\n");
    memcpy(&msg, &message[0], 2);
    printf("Start of Packet id: %#X \n", msg);
    printf("Client id: %d \n", message[2]);
    memcpy(&msg, &message[3], 2);
    printf("Permission: %#X \n", msg);
    printf("Received Segment No: %d \n", message[5]);
    printf("Length: %d \n", message[6]);
    printf("Technology: %d \n", message[7]);
    memcpy(&subNo, &message[8], 4); 
    printf("Source Subscriber No: %"PRIu32"\n", subNo);
    memcpy(&msg, &message[12], 2); 
    printf("End of Packet id: %#X \n", msg);  
}