#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct Number{
    public:
        int start_x;
        int end_x;
        int y;
        long long int value;
};


void parseString(int pos_y, string &s, vector <Number> &numbers, vector <vector<int>> &occupancy){
    int n = s.size();
    int temp = 0;
    int mult = 1;
    int end;
    for(int i = n-1; i >= 0; i--){
        if(s[i] >= '0' && s[i] <= '9'){
            end = i;
            while(i >= 0 && (s[i] >= '0' && s[i] <= '9')){
                occupancy[pos_y][i] = numbers.size();
                temp += mult*(s[i] - '0');
                mult *= 10;
                i--;
            }
            Number new_num;
            new_num.start_x = i + 1;
            new_num.end_x = end;
            new_num.value = temp;
            new_num.y = pos_y;
            numbers.push_back(new_num);

            temp = 0;
            mult = 1;
        }
    }

    return;
}



bool isSymbol(char c){
    if(!(c >= '0' && c <= '9') && !(c == '.')) return true;
    return false;
}

bool searchSymbols(vector <string> &schema, int pos_x1, int pos_x2, int pos_y){
    // we search for all numbers within diagonal range of the position;
    int n = schema[pos_y].size();
    if(pos_y > 0){
        for(int i = ((pos_x1 > 0)?(pos_x1 - 1):(pos_x1)); i <= ((pos_x2 < n-1)?(pos_x2 + 1):(pos_x2)); i++){
            if(isSymbol(schema[pos_y - 1][i])) return true;
        }
    }
    if(pos_x1 > 0 && isSymbol(schema[pos_y][pos_x1 - 1])) return true;
    if(pos_x2 < n-1 && isSymbol(schema[pos_y][pos_x2 + 1])) return true;

    if(pos_y < (schema.size() - 1)){
        for(int i = ((pos_x1 > 0)?(pos_x1 - 1):(pos_x1)); i <= ((pos_x2 < n-1)?(pos_x2 + 1):(pos_x2)); i++){
            if(isSymbol(schema[pos_y + 1][i])) return true;
        }
    }
    return false;
}

bool isValid(int a, int b, int c, int d){
    if(a >= 0 && b >= 0 && a < c && b < d) return true;
    return false;
}

long long int findGearRatio(vector<vector<int>> &occupancy, vector <Number> &numbers, int pos_x, int pos_y){
    // nine cases
    set <long long int> nearby;
    int m = occupancy.size();
    int n = occupancy[0].size();
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if(i == j){
                if(i != 0){
                    if(isValid(pos_y + i, pos_x + j, m, n) && occupancy[pos_y + i][pos_x + j] != -1) nearby.insert(numbers[occupancy[pos_y + i][pos_x + j]].value);
                }
                else continue;
            }
            else{
                if(isValid(pos_y + i, pos_x + j, m, n) && occupancy[pos_y + i][pos_x + j] != -1) nearby.insert(numbers[occupancy[pos_y + i][pos_x + j]].value);
            }
        }
    }
    long long int mult = 1;
    if(nearby.size() == 2){
        for(auto it: nearby) mult *= it;
        return mult;
    }
    return 0;
}

int main(){
    ifstream fileHandle;
    fileHandle.open("./testcase.txt", ios::in);
    string s;
    vector <string> schema;
    while(fileHandle.peek() != EOF){
        getline(fileHandle, s);
        schema.push_back(s);
    }
    vector <Number> numbers;
    int m = schema.size();
    int n = schema[0].size();
    vector <vector<int>> occupancy(m, vector <int> (n, -1));

    // okay now we have the schematic, and now we must find numbers, and assign them their respective positions
    for(int i = 0; i < m; i++){
        parseString(i, schema[i], numbers, occupancy);
    }
    long long int sum = 0;
    int k = numbers.size();

    // for(int i = 0; i < k; i++){
    //     bool chck = searchSymbols(schema, numbers[i].start_x, numbers[i].end_x, numbers[i].y);
    //     if(chck) sum += numbers[i].value;
    // }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(schema[i][j] == '*'){
                sum += findGearRatio(occupancy, numbers, j, i);
            }
            // cout<<occupancy[i][j]<<" ";
        }
        // cout<<endl;
    }
    cout<<sum<<endl;
    return 0;
}