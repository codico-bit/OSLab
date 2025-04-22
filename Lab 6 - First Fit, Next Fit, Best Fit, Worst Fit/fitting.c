#include<stdio.h>
#include<limits.h>

#define MAX_B 10
#define MAX_P 10

void firstFit(int bs[], int nb, int ps[], int np){
    int a[MAX_P];
    for(int i = 0; i<np; i++){
        a[i] = -1;
        //printf("Entered first fit %d\n", i);
    }
    for(int i = 0; i<np; i++){
        for(int j = 0; j<nb; j++){
            if(bs[j] >=ps[i]) {
                a[i] = j; 
                bs[j] -= ps[i]; 
                break;
            }
        }
    }
    printf("\nFirst-Fit Allocation:");
    for(int i =0; i<np; i ++) printf("\nProcess %d (%d KB) -> Block %d", i+1, ps[i], (a[i] !=-1) ? a[i]+1 : -1);
}

void bestFit(int bs[], int nb, int ps[], int np){
    int a[MAX_P];
    for(int i = 0; i<np; i++) a[i] =1;
    for(int i = 0; i<np; i++){
        int bi = -1;
        for(int j = 0; j<nb; j++){
            if(bs[j] >= ps[i] && (bi == -1 || bs[j] < bs[bi])) bi = j;
        }
        if(bi!=-1){
            a[i] = bi; bs[bi] -= ps[i];
        }
    }
    printf("\nBest-Fit Allocation:");
    for(int i = 0; i<np; i++) printf("\nProcess %d (%d KB) -> Block %d", i+1, ps[i], (a[i]!=-1) ? a[i] + 1 : -1);
}

void worstFit(int bs[], int nb, int ps[], int np){
    int a[MAX_P];
    for(int i = 0; i<np; i++) a[i] = -1;
    for(int i = 0; i<np; i++){
        int wi = -1;
        for(int j = 0; j<nb; j++){
            if(bs[j] >= ps[i] && (wi ==-1 || bs[j] > bs[wi])) wi = j;
        }
        if(wi != -1) {a[i] = wi; bs[wi] -= ps[i];}
    }
    printf("\nWorst-Fit Allocation:"); 
    for(int i = 0; i<np; i++) printf("\n Process %d (%d KB) -> Block %d", i+1, ps[i],(a[i]!=-1) ? a[i]+1 : -1);
}


void nextFit(int bs[], int nb, int ps[], int np){
    int a[MAX_P], la = 0;
    for(int i = 0; i<np; i++) a[i] = -1;
    for(int i = 0; i<np; i++){
        int j = la, cnt = 0;
        while(cnt < nb){
            if(bs[j] >= ps[i]) { a[i] = j; bs[j] -= ps[i], la = j; break;}
            j = (j+1) % nb;
            cnt++;
            //printf("Entered nextfit");
        }
    }
    printf("\nNext-Fit Allocation:");
    for(int i = 0; i<np; i++) {
        printf("\n Process %d (%d KB) -> Block %d", i+1, ps[i],(a[i]!=-1) ? a[i]+1 : -1);
    }
    printf("\n");
}

int main(){
    int nb, np, bs[MAX_B], ps[MAX_P];
    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter sizes of %d memory blocks: ", nb);
    for(int i = 0; i<nb; i++) scanf("%d", &bs[i]);

    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter sizes of %d processes: ", np);
    for(int i = 0; i<np; i++) scanf("%d", &ps[i]);

    int b1[MAX_B], b2[MAX_B], b3[MAX_B], b4[MAX_B];
    for(int i = 0; i<nb; i++) b1[i] = b2[i] = b3[i] = b4[i] = bs[i];
    for(int i = 0; i<nb; i++) {
        // printf("%d %d %d %d %d", b1[i],b2[i] ,b3[i],b4[i], bs[i] );
    }
    firstFit(b1,nb,ps,np);
    bestFit(b2,nb,ps,np);
    worstFit(b3,nb,ps,np);
    nextFit(b4,nb,ps,np);
    return 0;
}
