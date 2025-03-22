#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct frame {
    int seq;  
};

void sender();
void receiver();

struct frame packet;  
int ack = 0;  
char turn = 's'; 

int main() {
    packet.seq = 0;  

    while (packet.seq < 5) {  
        sender();  
        usleep(500000);  
        receiver();
    }
    return 0;
}

void sender() {
    if (turn == 's') {  
        printf("SENDER: Sent packet with seq NO: %d\n", packet.seq);

        if (rand() % 4 == 0) {  
            printf("SENDER: Packet lost!\n");
        } else {
            turn = 'r';  
        }
    }
}

void receiver() {
    if (turn == 'r') {  
        printf("RECEIVER: Received packet with seq %d\n", packet.seq);
        ack = packet.seq;  

        if (rand() % 4 == 0) {  
            printf("RECEIVER: ACK lost!\n");
        } else {
            printf("RECEIVER: Sent ACK %d\n", ack);
            turn = 's';  
            packet.seq++;  
        }
    }
}
