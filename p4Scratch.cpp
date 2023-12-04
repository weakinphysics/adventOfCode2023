#include <bits/stdc++.h>
#include <fstream>

using namespace std;


int process(string &s){

    int power = 0;
    unordered_map <int, int> hash;
    int n = s.size();
    bool mode = 0;
    int count = 0;
    int start = 0;
    while(s[start] != ':') start++;

    for(int i  = start; i < n; i++){
        if(s[i] >= '0' && s[i] <= '9'){
            int this_num = 0;
            while(i < n && (s[i] >= '0' && s[i] <= '9')){
                this_num *= 10;
                this_num += s[i] - '0';
                i++;
            }
            if(mode){
                if(hash.find(this_num) != hash.end()){
                    count++;
                }
            }
            else{
                hash[this_num] = 1;
            }
        }
        else if(s[i] == '|'){
            mode = 1;
            continue;
        }
        else{
            continue;
        }
    }
    return count;
}

int main(){
    fstream fileHandle;
    fileHandle.open("./testcase.txt", ios::in);
    string s;
    vector <string> input;
    while(fileHandle.peek() != EOF){
        getline(fileHandle, s);
        input.push_back(s);
    }
    int sum = 0;    
    int n = input.size();
    vector <int> counts(n, 1);
    int count;
    for(int i = 0; i < n; i++){
        count = process(input[i]);
        for(int j = i + 1; ((j < (i + 1 + count)) && j < n); j++) counts[j] += counts[i];
        sum += counts[i];
    }
    cout<<sum<<endl;
    return 0;
}
