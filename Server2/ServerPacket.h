#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <inttypes.h>

const int16_t StartOfPacketId;
const int16_t ClientId;
const int16_t EndOfPacketId;
const int16_t NotPaid;
const int16_t NotExist;
const int16_t AccessOk;
const int16_t Length;
const int32_t SourceSubscriberNo;

char* permitted(int segmentNumber, int tech, uint32_t sourceSubNo);
char* doesNotExist(int segmentNumber, int tech, uint32_t sourceSubNo);
char* hasNotPaid(int segmentNumber, int tech, uint32_t sourceSubNo);
void printMessagePacket(char* message);