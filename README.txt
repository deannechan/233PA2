Files:
- Client2 folder
    - Client.c
    - RequestPacket.c
    - RequestPacket.h
    - obj folder
- Server2 folder
    - Server.c
    - ServerPacket.c
    - ServerPacket.h
    - obj folder
    - data folder
        - Verification_Database.txt
- client-run1.png
- client-run2.png
- client-run3.png
- server-run1.png
- server-run2.png
- ServerNotResponding.png
- README.txt

Compile and Run Instructions:

FOR SERVER:
1. Open terminal
2. cd to Server2 folder
3. gcc -c -o obj/ServerPacket.o ServerPacket.c
4. gcc -c -o obj/Server.o Server.c
5. gcc -o obj/server obj/Server.o obj/ServerPacket.o
6. run using the command: ./obj/server

FOR CLIENT:
1. Open terminal
2. cd to Client2 folder
3. gcc -c -o obj/RequestPacket.o RequestPacket.c
4. gcc -c -o obj/Client.o Client.c
5. gcc -o obj/client obj/Client.o obj/RequestPacket.o
6. run using the command: ./obj/client

Screenshots:
1. client-runs and server-runs 
- shows client program running successfully. 
- send 5 packets to server with different info:
    1. Valid and paid phone number, technology
    2. Unpaid phone number
    3. Invalid phone number - Number does not exist error
    4. Invalid technology -- Number does not exist error

2. ServerNotResponding
- no server response withint 3s so client tries to resend packets 3 times
before it displays 'Server does not respond' message
