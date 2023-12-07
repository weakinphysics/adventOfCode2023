#include "/Users/icero/CodeandDevelopment/Compi/stdc++.h"
#include <fstream>

using namespace std;

class RangeNode
{
public:
    long long int range_start;
    long long int range_end;

    RangeNode(long long int rs, long long int re)
    {
        this->range_start = rs;
        this->range_end = re;
    }
};

vector<long long int> processline(string &s)
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

vector<RangeNode *> getSeeb(string &s)
{
    vector<long long int> seebraw = processline(s);
    int rangeCount = seebraw.size();
    vector<RangeNode *> seebs;
    if (rangeCount % 2)
    {
        cout << "what the f\n";
        return seebs;
    }
    for (int i = 0; i < rangeCount; i += 2)
    {
        RangeNode *thisRange = new RangeNode(seebraw[i], seebraw[i] + seebraw[i + 1] - 1);
        seebs.push_back(thisRange);
    }
    return seebs;
}

int binarySearcher(vector<RangeNode *> &ranges, int start, int end, int target)
{
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (target >= ranges[mid]->range_start)
        {
            if (target > ranges[mid]->range_end)
                return binarySearcher(ranges, mid + 1, end, target);
            return mid;
        }
        return binarySearcher(ranges, start, mid - 1, target);
    }
    return -1;
}

vector<RangeNode *> insertRange(vector<RangeNode *> &ranges, vector<long long int> &range)
{
    // copy the ranges that remain unaffected
    // we could operate on the array. or. we could do something cool
    int n = ranges.size();
    int index = binarySearcher(ranges, 0, n - 1, range[0]);
    RangeNode *thisRange = new RangeNode(range[0], range[1]);
    vector<RangeNode *> allRanges;

    int j = 0;
    if (index == -1)
    {
        /*
            Two possibilities:
                1. To be appended at the end of the array
                2. Belongs at the beginning of the array
        */
        if (range[0] < ranges[0]->range_start)
        {
            while (j < n && range[1] >= ranges[j]->range_end)
            {
                j++;
            }
            allRanges.push_back(thisRange);
            if (j < n)
            {
                if (thisRange->range_end >= ranges[j]->range_start)
                {
                    ranges[j]->range_start = thisRange->range_end + 1;
                }
                for (int i = j; i < n; i++)
                    allRanges.push_back(ranges[i]);
            }
            return allRanges;
        }
        else
        {
            allRanges.resize(n + 1);
            for (int i = 0; i < n; i++)
                allRanges[i] = ranges[i];
            ranges[n] = thisRange;
            return allRanges;
        }
    }
    else
    {
        for (int i = 0; i < index; i++)
            allRanges.push_back(ranges[i]);
        allRanges.push_back(thisRange);
        while (index < n && thisRange->range_end >= ranges[index]->range_end)
        {
            index++;
        }
        if (index < n)
        {
            if (ranges[index]->range_start <= thisRange->range_end)
                ranges[index]->range_start = thisRange->range_end + 1;
            for (int i = index; i < n; i++)
                allRanges.push_back(ranges[i]);
        }
        return allRanges;
    }
    return allRanges;
}

// int main()
// {
//     ifstream fileHandle;
//     fileHandle.open("./testcase.txt", ios::in);
//     vector<string> inputlines;
//     string s;
//     while (fileHandle.peek() != EOF)
//     {
//         getline(fileHandle, s);
//         inputlines.push_back(s);
//     }
//     int lines = inputlines.size();

//     vector<long long int> seeds = processline(inputlines[0]);

//     for (auto it : seeds)
//         cout << it << " ";
//     cout << endl;

//     int n = seeds.size();

//     for (int line = 1; line < lines; line++)
//     {
//         if (!inputlines[line].empty())
//         {
//             vector<int> processed(n, 0);
//             int x = process(inputlines, seeds, processed, line);
//             line = x;
//         }
//     }
//     cout << (*min_element(seeds.begin(), seeds.end())) << endl;

//     return 0;
// }

int main()
{
    ifstream fileHandle;
    fileHandle.open("./testcase.txt", ios::in);
    string s;
    vector<string> inputlines;
    while (fileHandle.peek() != EOF)
    {
        getline(fileHandle, s);
        inputlines.push_back(s);
    }
    vector<RangeNode *> birbia = getSeeb(inputlines[0]);
    int k = birbia.size();
    for (int i = 0; i < k; i++)
    {
        std::cout << birbia[i]->range_start << " " << birbia[i]->range_end << endl;
    }
    return 0;
}