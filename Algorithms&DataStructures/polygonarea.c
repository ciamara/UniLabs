#include <stdlib.h>
#include <stdio.h>

int main() {

    int l, a, n, i, j;
    double area;
    double sum;
    int *coords;

    scanf("%d", &l);

    for (i=0; i<l; i++) {

        area = 0;
        scanf("%d", &n);
        coords = (int*) malloc(n*sizeof(int));

        for(j=0; j<n; j++) {

            scanf("%d", &a);
            coords[j]=a;
        }

        for(j=0; j<=n-2; j++) {

            if (j==n-2) {area = area + (coords[j]*coords[1]-coords[0]*coords[j+1]);continue;}
            if (j%2==0) area = area + (coords[j]*coords[j+3]-coords[j+2]*coords[j+1]);
        }

        sum = area/2;
        printf("%d\n", (int)sum);
    }
    
return 0;
}