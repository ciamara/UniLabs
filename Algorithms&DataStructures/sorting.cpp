#include <iostream>
#include <vector>
#include <string>

using namespace std;

void swap(vector<vector<int>> *&a, vector<vector<int>> *&b) {

    vector<vector<int>> *temp = a;
    a = b;
    b = temp;
}

void sort(vector<vector<int>>& arr) {

    int n = arr.size();

    for (int i = 0; i < n; ++i) {

        bool swapped = false;

        for (int j = 0; j < n - i - 1; ++j) {

            int k = 0;
            int jsize=arr[j].size();
            int j1size=arr[j+1].size();

            while (k < jsize || k < j1size) {

                int digit1,digit2;

                if (jsize>j1size) {

                    digit1=1;
                    digit2=0;
                }
                else if (jsize<j1size) {

                    digit1=0;
                    digit2=1;
                }
                else {

                    digit1=arr[j][k];
                    digit2=arr[j+1][k];
                }
                if (digit1 > digit2) {

                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                    break;
                } else if (digit1 < digit2) {

                    break;
                }
                ++k;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

int main() {

    int n;
    cin >> n;

    vector<vector<int>> numbers(n);

    for (int i = 0; i < n; ++i) {

        string num;
        cin >> num;

        for (char digit : num) {

            numbers[i].push_back(digit - '0');
        }
    }

    sort(numbers);

    for (int i = 0; i < n; ++i) {

        for (int digit : numbers[i]) {

            cout << digit;
        }
        cout << endl;
    }

return 0;
}