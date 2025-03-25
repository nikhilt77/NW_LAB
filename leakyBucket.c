#include<stdio.h>
#include<stdlib.h>

void bucketFilling(int bucketCapacity,int leakRate,int noPackets,int Packets[]){
    int bucket=0;
    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");
    for(int i=0;i<noPackets;i++){
        printf("%d\t%10d\t",i+1,Packets[i]);
        bucket+=Packets[i];
        if(bucket>bucketCapacity){
            printf("%10d(Overflowed %d  Dropped\t",bucket,bucket-bucketCapacity);
            bucket=bucketCapacity;
        }
        else{
            printf("%10d",bucket);
        }
        int leaked=bucket>leakRate?leakRate:bucket;
        bucket-=leaked;
        printf("%10d\t%d\n",leaked,bucket);
    }
    int time=noPackets+1;
    while(bucket>0){
        int leaked=bucket>leakRate?leakRate:bucket;
        printf("%10d\t%d\t%d\t%d\t%d\n",time,0,leaked,bucket,bucket-leaked);
        bucket-=leaked;
        time++;
    }
}

int main(){
    int bucketCapacity;
    printf("Enter Bucket Capacity:");
    scanf("%d",&bucketCapacity);

    int leakR;
    printf("Enter leak rate:");
    scanf("%d",&leakR);

    int packet;
    printf("Enter no. of packets:");
    scanf("%d",&packet);

    int packets[packet];
    printf("Enter the packets:\n");
    for(int i=0;i<packet;i++){
        scanf("%d",&packets[i]);
    }

    bucketFilling(bucketCapacity,leakR, packet, packets);
}
