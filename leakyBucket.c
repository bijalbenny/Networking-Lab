#include <stdio.h>

void main() {
    int incoming, outgoing, bucketSize, n;
    printf("Enter the bucket size, outgoing rate, number of inputs: ");
    scanf("%d %d %d", &bucketSize, &outgoing, &n);
    int discarded=0;
    int store = 0; 
    while (n != 0) {
        printf("\nEnter the incoming packet size: ");
        scanf("%d", &incoming);
        printf("\nIncoming packet size: %d", incoming);
        
     
        if (incoming <= (bucketSize - store)) {
            store += incoming;
            printf("\nBucket buffer size: %d out of %d\n", store, bucketSize);
        } else {
            
            printf("\nDropped %d packets", incoming - (bucketSize - store));
            discarded += incoming - (bucketSize - store);
            store = bucketSize;  
            printf("\nBucket buffer size: %d out of %d\n", store, bucketSize);
        }

      
        if (store >= outgoing) {
            store -= outgoing;
        } else {
            store = 0;  
        }

        printf("\nAfter outgoing, there are %d out of %d packets in the bucket\n", store, bucketSize);
        n--;
    }
    printf("\nDiscarded : %d packets",discarded);
}
