#include <iostream>
#include <cmath>
using namespace std;


int countprofit(int items[3][15], int itemcount, int maxweight) {

    int weight=0, profit=0;

    for (int n=0;n<itemcount;n++) {

        if (items[2][n]==1) {

            profit = profit + items[0][n];
            weight = weight + items[1][n];
        }
    }

    if (weight<=maxweight) {

        return profit;
    }

    else return 0;
}

int checkmaxprofit(int itemcount, int items[3][15], int maxweight) {

    int profit=0, maxprofit=0, i;

    for (int n=0;n<pow(2,itemcount);n++) {

        i=n;

        for (int k=0;k<itemcount;k++) {

            items[2][itemcount-1-k]= i&1;
            i = i>>1;
        }

        profit = countprofit(items, itemcount, maxweight);

        if (profit> maxprofit) {

            maxprofit = profit;
        } 
    }

    return maxprofit;
}

int main() {

    int maxprofit=0, maxweight=0, itemcount=0, k, n;
    int profits[500]={0};

    for (k=0; k<500;k++) {

        cin>>itemcount;
        int items[3][15]={0};

        for (n=0;n<itemcount;n++) {

            cin>>items[0][n];
        }
        for (n=0;n<itemcount;n++) {

            cin>>items[1][n];
        }
        for (n=0;n<itemcount;n++) {

            items[2][n]=0;
        }

        cin>>maxweight;
        maxprofit = checkmaxprofit(itemcount, items, maxweight);
        profits[k]= maxprofit;
        maxprofit=0;
    }

    for (k=0;k<500;k++) {

        cout<<profits[k]<<endl;
    }
    
return 0;
}