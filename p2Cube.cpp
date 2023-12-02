#include <bits/stdc++.h>
#include <fstream>

using namespace std;

vector <int> positions(string &s, string t){
    int x = s.size();
    int y = t.size();
    vector <int> p;
    for(int i = 0; i <= x - y; i++){
        bool chck = true;
        for(int j = 0; j < y; j++){
            if(s[i + j] != t[j]){
                chck = false;
                break;
            }
        }
        if(chck){
            p.push_back(i);
        }
    }
    return p;
}

int nearbyNumber(string &s, int pos){
    int num = 0;
    int mult = 1;
    while(pos >= 0){
        if(s[pos] == ' ') break;
        num += mult*(s[pos] - '0');
        mult *= 10;
        pos--;
    }
    return num;
}

int main(){
    ifstream fileHandle;
    fileHandle.open("./testcase.txt", ios::in); // init file handle
    string s;
    long long int sum = 0;
    // int r_count = 12; 
    // int g_count = 13;
    // int b_count = 14;
    int ctr = 0;
    while(fileHandle.peek() != EOF){
        getline(fileHandle, s);
        vector <int> reds = positions(s, "red");
        vector <int> greens = positions(s, "green");
        vector <int> blues = positions(s, "blue");

        int x = reds.size();
        long long int max_r = 0, max_g = 0, max_b = 0;
        for(int i = 0; i < x; i++){
            long long int ret_val = (long long int)nearbyNumber(s, reds[i] - 2);
            max_r = max(max_r, ret_val);
        }
        x = greens.size();
        for(int i = 0; i < x; i++){
            long long int ret_val = (long long int)nearbyNumber(s, greens[i] - 2);
            max_g = max(max_g, ret_val);
        }
        x = blues.size();
        for(int i = 0; i < x; i++){
            long long int ret_val = (long long int)nearbyNumber(s, blues[i] - 2);
            max_b = max(max_b, ret_val);
        }
        ctr++;
        // if(max_b > b_count || max_r > r_count || max_g > g_count) continue; solution to the first question
        // sum += ctr;
        sum += max_r*max_g*max_b;
    }
    cout<<sum<<endl;
    return 0;
}