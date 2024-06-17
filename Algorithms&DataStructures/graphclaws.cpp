#include <iostream>
using namespace std;

int main() {

    int grafs, spaces;
    char c;
    bool isclaw=false;

    cin>>grafs;
    int* out = (int*)malloc(grafs * sizeof(int));

    for(int p=0; p<grafs; p++) {

        	cin>>spaces;
            c=getchar();

            int** matrix = (int**)malloc(spaces * sizeof(int*));

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
                    
                    for (int k = 0; k < spaces; k++){

                        for (int l = 0; l < spaces; l++){

                            if((i==j)||(i==k)||(i==l)||(j==k)||(j==l)||(k==l)){
                                continue;
                            }
                            else{

                                if((matrix[i][j]==1)&&(matrix[i][k]==1)&&(matrix[i][l]==1)&&(matrix[j][k]!=1)&&(matrix[j][l]!=1)&&(matrix[k][l]!=1)){
                                    isclaw=true;
                                }
                            }
                        }
                    }
                    
                }
            }

            if (isclaw==true){

                out[p]=0;
            } 

            if (isclaw==false){

                out[p]=1;
            }

            isclaw=false;

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