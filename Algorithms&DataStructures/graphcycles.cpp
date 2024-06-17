#include <iostream>
using namespace std;

int main() {

    int grafs, spaces, countones;
    char c;
    bool iscycle=true;

    cin>>grafs;
    int* out = (int*)malloc(grafs * sizeof(int));

    for(int p=0; p<grafs; p++) {

        cin>>spaces;
        c=getchar();

        int** matrix = (int**)malloc(spaces * sizeof(int*));
        int* ones = (int*)malloc(spaces * sizeof(int));

        for (int i = 0; i < spaces; i++){

            matrix[i] = (int*)malloc(spaces * sizeof(int)); 
        }

        for (int i = 0; i < spaces; i++){

            for (int j = 0; j < spaces; j++){

                c = getchar();
                matrix[i][j] = c-'0';
            }
        }

        for (int i = 0; i < spaces; i++){

            for (int j = 0; j < spaces; j++){
                    
                if (matrix[i][j]==1) countones++;
            }

            ones[i]=countones;
            countones=0;
        }

        for(int i=0; i< spaces; i++) {

            if(ones[i]!=2) {iscycle=false; out[p]=0; break;}
        }

        if (iscycle==true) out[p]=1;
        int visited = 0;
        int curr = 0;

        for (int j = 0; j < spaces; j++) {

            if (matrix[curr][j] == 1) {

                visited++;
                matrix[curr][j] = 0;
                matrix[j][curr] = 0;
                curr = j;
                j = -1;
            }
        }

        if(visited!=spaces) out[p]=0;

        for (int i = 0; i < spaces; i++){

            bool isone=false;

            for(int j = 0; j<spaces; j++){

                if(matrix[i][j]==1) isone=true;
                if(isone==true) out[p]=0;
            }
        }

        iscycle=true;

        for (int i = 0; i < spaces; i++) {

            free(matrix[i]);
        }

        free(matrix);

    }

    for(int i=0; i<grafs; i++){
        cout<<out[i]<<endl;
    }

return 0;
}