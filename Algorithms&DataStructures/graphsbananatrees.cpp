#include <iostream>
#include <cstdlib>
#include <cstring>
#include <set>
using namespace std;

int countDegreeOneVertices(int** matrix, int spaces) {

    int count = 0;

    for (int i = 0; i < spaces; i++) {

        int degree = 0;

        for (int j = 0; j < spaces; j++) {

            if (matrix[i][j] == 1) {

                degree++;
            }
        }

        if (degree == 1) {
            count++;
        }
    }
    return count;
}

bool doesTabMatchAnyRow(int** matrix, int* tab, int spaces) {

    for (int i = 0; i < spaces; i++) {

        bool match = true;

        for (int j = 0; j < spaces; j++) {

            if (matrix[i][j] != tab[j]) {

                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

bool isValidTab(int* tab, int spaces, int &distinctNumber) {

    set<int> distinctNumbers;

    for (int i = 0; i < spaces; i++) {

        if (tab[i] != 0) {

            distinctNumbers.insert(tab[i]);
        }
    }

    if (distinctNumbers.size() == 1) {

        distinctNumber = *distinctNumbers.begin();
        return true;
    }

    return false;
}

bool isCyclicUtil(int** matrix, int v, bool* visited, int parent, int spaces) {

    visited[v] = true;

    for (int i = 0; i < spaces; i++) {

        if (matrix[v][i]) {

            if (!visited[i]) {

                if (isCyclicUtil(matrix, i, visited, v, spaces)) {
                    return true;
                }
            } else if (i != parent) {
                return true;
            }
        }
    }
    return false;
}

bool isCyclic(int** matrix, int spaces) {

    bool* visited = (bool*)malloc(spaces * sizeof(bool));
    memset(visited, false, spaces * sizeof(bool));

    for (int i = 0; i < spaces; i++) {

        if (!visited[i]) {
            
            if (isCyclicUtil(matrix, i, visited, -1, spaces)) {
                free(visited);
                return true;
            }
        }
    }
    free(visited);
    return false;
}

int main() {

    int grafs, spaces, bananas=0, distinctNumber = -1;
    char c;

    cin>>grafs;

    for(int p=0; p<grafs; p++) {

        cin>>spaces;
        c=getchar();

        int** matrix = (int**)malloc(spaces * sizeof(int*));
        int* tab = (int*)malloc(spaces * sizeof(int));


        for (int i = 0; i < spaces; i++){
            matrix[i] = (int*)malloc(spaces * sizeof(int)); 
            tab[i]=0;
        }

        for (int i = 0; i < spaces; i++){

            for (int j = 0; j < spaces; j++){
                c = getchar();
                matrix[i][j] = c-'0';
            }
        }

        for (int i = 0; i < spaces; i++) {

            int countOnes = 0;
            int onePosition = -1;

            for (int j = 0; j < spaces; j++) {

                if (matrix[i][j] == 1) {

                    countOnes++;
                    onePosition = j;
                }
            }
            if (countOnes == 1) {
                tab[onePosition]++;
            }
        }

        if(isValidTab(tab, spaces, distinctNumber)){

            for (int i = 0; i < spaces; i++) {

                if (tab[i] == distinctNumber) {

                    tab[i] = 1;
                }
            }

            if(doesTabMatchAnyRow(matrix, tab, spaces)){
                bananas = countDegreeOneVertices(matrix, spaces);
            }
            else{
                bananas = 0;
            }

        }
        else {
            bananas = 0;
        }


        if (isCyclic(matrix, spaces)) {
            bananas = 0;
        }

        if(spaces == 2){
            bananas = 2;
        }

        for (int i = 0; i < spaces; i++) {
            free(matrix[i]);
        }
        free(matrix);
        free(tab);

        if(bananas>0){

            cout<<bananas<<" bananas :)"<<endl;
        }
        else if(bananas==0){

            cout<<bananas<<" bananas :("<<endl;
        }

        bananas=0;
    }
return 0;
}