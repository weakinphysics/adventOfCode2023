#include "/Users/icero/CodeandDevelopment/Compi/stdc++.h"
#include <fstream>

using namespace std;

long long int processlinenew(std::string &s)
{
    long long int num = 0;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            num *= 10;
            num += (s[i] - '0');
        }
    }
    return num;
}

vector<long long int> processline(std::string &s)
{
    int n = s.size();
    vector<long long int> nums;
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            long long int temp = 0;
            while (i < n && (s[i] >= '0' && s[i] <= '9'))
            {
                temp *= 10;
                temp = temp + (long long int)(s[i] - '0');
                i++;
            }
            nums.push_back(temp);
        }
    }
    return nums;
}

int main()
{
    ifstream fileHandle;
    fileHandle.open("./testcase.txt", ios::in);
    vector<string> inputlines;
    string s;
    while (fileHandle.peek() != EOF)
    {
        getline(fileHandle, s);
        inputlines.push_back(s);
    }

    vector<long long int> times = processline(inputlines[0]);
    vector<long long int> distances = processline(inputlines[1]);

    int n = times.size();
    // int ways = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     int count = 0;
    //     int jay = times[i] + 1;
    //     for (int j = 0; j < jay; j++)
    //     {
    //         if (j * (times[i] - j) > distances[i])
    //             count++;
    //     }
    //     cout << count << endl;
    //     if (!ways)
    //         ways = count;
    //     else
    //         ways *= count;
    // }

    long long int time = processlinenew(inputlines[0]);
    long long int distance = processlinenew(inputlines[1]);

    cout << "TSD: " << time << " " << distance << endl;

    long long int minima = 0;
    long long int maxima = time;

    long long int n1 = -1;

    while (minima <= maxima)
    {
        long long int midima = (maxima + minima) / 2;
        if (midima * (time - midima) > distance)
        {
            n1 = midima;
            maxima = midima - 1;
        }
        else
        {
            minima = midima + 1;
        }
    }

    long long int n2 = -1;
    minima = 0;
    maxima = time;
    while (minima <= maxima)
    {
        long long int midima = (maxima + minima) / 2;
        if (midima * (time - midima) > distance)
        {
            n2 = midima;
            minima = midima + 1;
        }
        else
        {
            maxima = midima - 1;
        }
    }
    if (n1 == -1 || n2 == -1)
        cout << -1 << endl;
    cout << (n2 - n1 + 1) << endl;
    // k^2 - k*n - d < 0
    return 0;
}