#include<stdio.h>
#define INFINITY 9999
#define max 10

int nodes;
int cost[max][max],nextHop[max][max],dist[max][max];

void initialize(int nodes){
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            dist[i][j]=cost[i][j];
            nextHop[i][j]=j;
        }
    }
}

void updateRoutes(int nodes){
    int updated;
    do{
        updated=0;
        for(int i=0;i<nodes;i++){
            for(int j=0;j<nodes;j++){
                for(int k=0;k<nodes;k++){
                    if(dist[i][j]>dist[i][k]+dist[k][j]){
                        dist[i][j]=dist[i][k]+dist[k][j];
                        nextHop[i][j]=nextHop[i][k];
                        updated=1;
                    }
                }
            }
        }
    }while(updated);
}

void display(){
    for(int i=0;i<nodes;i++){
        printf("\nRouter %d Routing Table\n",i+1);
        printf("Destination\tDistance\tNext Hop\n");
        for(int j=0;j<nodes;j++){
            printf("%d\t%d\t%d\n",j+1,dist[i][j],nextHop[i][j]+1);
        }
    }
}

int main(){
    printf("Enter no. of nodes:");
    scanf("%d",&nodes);
    printf("Enter Cost matrix:\n");
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            scanf("%d",&cost[i][j]);
            if(i==j){
                cost[i][j]=0;
            }
        }
    }
    initialize(nodes);
    updateRoutes(nodes);
    display();
}
