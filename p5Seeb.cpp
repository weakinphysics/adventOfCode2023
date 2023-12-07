#include "/Users/icero/CodeandDevelopment/Compi/stdc++.h"
#include <fstream>

using namespace std;

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

int process(vector<string> &v, vector<long long int> &seeb, vector<int> &processed, int pos)
{
    int n = v.size();
    int m = seeb.size();
    for (int i = pos + 1; i < n; i++)
    {
        if (v[i] == "")
            return i;
        vector<long long int> temp = processline(v[i]);
        long long int rs = temp[1];
        long long int re = rs + temp[2];

        for (int j = 0; j < m; j++)
        {
            if (seeb[j] >= rs && seeb[j] < re)
            {
                if (!processed[j])
                    seeb[j] = temp[0] + (seeb[j] - rs);
                processed[j] = 1;
            }
        }
    }
    return n;
}

// vector<pair<long long int, long long int>> getSeeds(string &s)
// {
//     vector<long long int> nums = processline(s);
//     if (nums.size() % 2)
//         return {{}};
//     int n = nums.size();
//     vector<pair<long long int, long long int>> seeb;
//     for (int i = 0; i < n / 2; i += 2)
//     {
//         seeb.push_back({nums[i], nums[i] + nums[i + 1] - 1});
//     }
//     return seeb;
// }

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
    int lines = inputlines.size();

    vector<long long int> seeds = processline(inputlines[0]);

    for (auto it : seeds)
        cout << it << " ";
    cout << endl;

    int n = seeds.size();

    for (int line = 1; line < lines; line++)
    {
        if (!inputlines[line].empty())
        {
            vector<int> processed(n, 0);
            int x = process(inputlines, seeds, processed, line);
            line = x;
        }
    }
    cout << (*min_element(seeds.begin(), seeds.end())) << endl;

    return 0;
}
