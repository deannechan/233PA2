#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include <inttypes.h>

const int16_t StartOfPacketId;
const int16_t EndOfPacketId;
const int16_t ClientId;
const int16_t AccPer;
const int16_t Length;
const int32_t SourceSubscriberNo;
const int16_t NotPaid;
const int16_t NotExist;
const int16_t AccessOk;

char* permission(int segmentNumber, int tech, uint32_t sourceSubNo);
char* sendPacket(int s, char* packet, struct sockaddr_in server);
char* checkResponse(char* packet);
void printMessagePacket(char* message);