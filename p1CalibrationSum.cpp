#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

/*
    Please note that the usage of Rabin-Karp is fruitless in this case as the strings are of limited length(s.size() < 100), and is interspersed with numbers, 
    and the "number strings contained in the vector straw" of size atmost 5, therefore Rabin Karp would be at a disadvantage here, since T(m*n) is decidedly better in this case 
    compared to Rabin Karp (T(26*n)? -> best case indicating no match of rolling hash?). 

    
*/

using namespace std;


vector <string> straws = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int positions(string &s, string &t, bool where){
    int x = s.size();
    int y = t.size();
    int ps = -1;
    for(int i = 0; i <= x - y; i++){
        bool chck = true;
        for(int j = 0; j < y; j++){
            if(s[i + j] != t[j]){
                chck = false;
                break;
            }
        }
        if(chck){
            if(where) return i;
            ps = i;
        }
    }
    return ps;
}


int main(){


    ifstream fileHandle; // create an fstream object with a file pointer such that it is set to read mode, give it a file path     
    fileHandle.open("./testcase.txt", ios::in);
    string s;
    int sum = 0;
    while(fileHandle.peek() != EOF){
        getline(fileHandle, s);
        int i = 0;
        int j = s.size() - 1;
        int num1 = 0, num2 = 0, ind1 = INT_MAX, ind2 = INT_MIN;
        while(i < s.size()){
            if(s[i] >= '0' && s[i] <= '9'){
                num1 = s[i] - '0';
                ind1 = i;
                break;
            }
            i++;
        }
        while(j >= 0){
            if(s[j] >= '0' && s[j] <= '9'){
                num2 = s[j] - '0';
                ind2 = j;
                break;
            }
            j--;
        }

        for(int i = 0; i < 10; i++){
            int fps = positions(s, straws[i], true);
            int lps = positions(s, straws[i], false);
            if(fps == -1) continue;
            if(fps < ind1){
                ind1 = fps;
                num1 = i;
            }
            if(lps > ind2){
                ind2 = lps;
                num2 = i;
            }
        }

        sum  += num1*10 + num2;
    }
    cout<<sum<<endl;
    return 0;
}