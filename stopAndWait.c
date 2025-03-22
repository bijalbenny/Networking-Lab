#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct frame {
    int seq;
} packet;

int ak, disconnect = 0, t = 5;
int errorack = 1, errorframe = 0;
char turn = 's';

void sender();
void receiver();

int main() {
    packet.seq = 0;

    while (!disconnect) {
        sender();
        usleep(500000);  // 1-second delay
        receiver();
    }

    printf("\nTransmission complete. Disconnecting...\n");
    return 0;
}

void sender() {
    static int flag = 0;

    if (turn == 's') {
        if (errorack == 0) {
            printf("SENDER: Sent packet with seq NO: %d\n", packet.seq);
            errorframe = rand() % 4;
            if (errorframe == 0)
                printf("SENDER: Error while sending packet!\n");
            turn = 'r';  // Give turn to receiver
        } else {
            if (flag == 1) {
                printf("SENDER: Received ACK for packet %d\n", ak);
            }

            if (packet.seq == 5) {
                disconnect = 1;
                return;
            }

            packet.seq++;
            printf("SENDER: Sent packet with seq NO: %d\n", packet.seq);
            errorframe = rand() % 4;
            if (errorframe == 0)
                printf("SENDER: Error while sending packet!\n");

            turn = 'r';  // Receiver's turn
            flag = 1;
        }
    }
    //not necessary
 else {
        t--;
        printf("SENDER: Timeout countdown: %d\n", t);

        if (t == 0) {
            printf("SENDER: Timeout! Resending last packet...\n");
            turn = 's';
            errorack = 0;
            t = 5;
        }
    }
}

void receiver() {
    static int frameExp = 1;  // Expect sequence from 1

    if (turn == 'r') {
        if (errorframe != 0) {  // If no error in received packet
            if (packet.seq == frameExp) {
                printf("RECEIVER: Received packet with seq %d\n", packet.seq);
                ak = packet.seq;
                frameExp++;  // Expect next frame
                turn = 's';
                errorack = rand() % 4;
                if (errorack == 0)
                    printf("RECEIVER: Error while sending ACK!\n");
            } else {
                printf("RECEIVER: Duplicate packet detected (seq %d). Resending ACK for seq %d\n", packet.seq, frameExp - 1);
                ak = frameExp - 1;  // Send ACK for last correct packet
                turn = 's';
                errorack = rand() % 4;
                if (errorack == 0)
                    printf("RECEIVER: Error while sending ACK!\n");
            }
        }
    }
}

/*
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
*/
