#include "/Users/icero/CodeandDevelopment/Compi/stdc++.h"
#include <fstream>

using namespace std;

vector<long long int> fivers;
vector<long long int> fourers;
vector<long long int> fullHouses;
vector<long long int> threes;
vector<long long int> two_pairs;
vector<long long int> pairs;
vector<long long int> distinct;
vector<string> inputlines;

long long int processline(std::string &s)
{
    int n = s.size();
    int index = 0;
    string hand = "";
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ')
        {
            index = i;
            break;
        }
        hand.push_back(s[i]);
    }
    long long int num = 0;
    for (int i = index + 1; i < n; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            num *= 10;
            num += (s[i] - '0');
        }
    }
    s = hand;
    return num;
}

int calcIndex(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    if (c == 'T')
        return 10;
    if (c == 'J')
        return 1;
    if (c == 'Q')
        return 12;
    if (c == 'K')
        return 13;
    if (c == 'A')
        return 14;
    return 0;
}

bool isFiveofakind(string &hand)
{
    vector<int> alphabet(15, 0);
    int n = hand.size();
    for (int i = 0; i < n; i++)
    {
        alphabet[calcIndex(hand[i])]++;
    }
    int jc = alphabet[1];
    for (int i = 2; i < 15; i++)
        if (alphabet[i] + jc == 5)
            return true;
    return false;
}

bool isFourofakind(string &hand)
{
    vector<int> alphabet(15, 0);
    int n = hand.size();
    for (int i = 0; i < n; i++)
    {
        alphabet[calcIndex(hand[i])]++;
    }
    int jc = alphabet[1];
    for (int i = 2; i < 15; i++)
        if (alphabet[i] + jc == 4)
            return true;
    return false;
}

bool isFullHouse(string &hand)
{
    vector<int> alphabet(15, 0);
    int n = hand.size();
    for (int i = 0; i < n; i++)
    {
        alphabet[calcIndex(hand[i])]++;
    }
    int two = 0;
    int three = 0;
    int jc = alphabet[1];
    for (auto it : alphabet)
    {
        if (it == 3)
            three++;
        if (it == 2)
            two++;
    }
    if (two && three)
        return true;
    if (two == 2 && jc)
        return true;
    return false;
}

bool isThreeofakind(string &hand)
{
    vector<int> alphabet(15, 0);
    int n = hand.size();
    for (int i = 0; i < n; i++)
    {
        alphabet[calcIndex(hand[i])]++;
    }
    int jc = alphabet[1];
    for (int i = 2; i < 15; i++)
        if (alphabet[i] + jc == 3)
            return true;
    return false;
}

int countPairs(string &hand)
{
    vector<int> alphabet(15, 0);
    int n = hand.size();
    for (int i = 0; i < n; i++)
    {
        alphabet[calcIndex(hand[i])]++;
    }
    int jc = alphabet[1];
    int count = 0;
    for (int i = 2; i < 15; i++)
        if (alphabet[i] == 2)
            count++;
    if (count == 2)
        return count;
    return count + jc;
}

// int highestCard(string &hand)
// {
//     int n = hand.size();
//     int maxCard = 2;
//     for (int i = 0; i < n; i++)
//     {
//         maxCard = max(maxCard, calcIndex(hand[i]));
//     }
//     return maxCard;
// }

static bool cmp1(int a, int b)
{
    for (int i = 0; i < 5; i++)
    {
        int x = calcIndex(inputlines[a][i]);
        int y = calcIndex(inputlines[b][i]);
        if (x != y)
            return (x > y);
    }
    return false;
}

// static bool cmp2(int a, int b)
// {
//     int x = highestCard(inputlines[a]);
//     int y = highestCard(inputlines[b]);
//     if (x == y)
//     {
//         return cmp1(a, b);
//     }
//     return (x > y);
// }

void bubbleSort(vector<long long int> &a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (!cmp1(a[i], a[j]))
            {
                long long int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void processHand(string &s, int index)
{

    if (isFiveofakind(s))
    {
        fivers.push_back(index);
        return;
    }
    if (isFourofakind(s))
    {
        fourers.push_back(index);
        return;
    }
    if (isFullHouse(s))
    {
        fullHouses.push_back(index);
        return;
    }
    if (isThreeofakind(s))
    {
        threes.push_back(index);
        return;
    }
    int pair_count = countPairs(s);
    if (pair_count == 2)
    {
        two_pairs.push_back(index);
        return;
    }
    if (pair_count == 1)
    {
        pairs.push_back(index);
        return;
    }
    distinct.push_back(index);
    return;
}

int main()
{
    ifstream fileHandle;
    ofstream babaBoltaHai;
    ofstream abhiBasHogaya;
    fileHandle.open("./testcase.txt", ios::in);
    babaBoltaHai.open("./one.txt", ios::app);
    abhiBasHogaya.open("./two.txt", ios::app);
    string s;
    while (fileHandle.peek() != EOF)
    {
        getline(fileHandle, s);
        inputlines.push_back(s);
    }
    int n = inputlines.size();
    vector<long long int> bids(n);
    for (int i = 0; i < n; i++)
    {
        bids[i] = processline(inputlines[i]);
        if (inputlines[i] == "77772")
            cout << "WTF" << endl;
    }

    for (int i = 0; i < n; i++)
        processHand(inputlines[i], i);

    for (auto it : fourers)
        if (inputlines[it] == "77772")
            cout << "WTAF" << endl;

    // vector<long long int> f1c = fivers;
    // vector<long long int> f2c = fourers;
    // vector<long long int> f3c = fullHouses;
    // vector<long long int> tc = threes;
    // vector<long long int> tpc = two_pairs;
    // vector<long long int> pc = pairs;
    // vector<long long int> dc = distinct;

    sort(fivers.begin(), fivers.end(), cmp1);
    sort(fourers.begin(), fourers.end(), cmp1);
    sort(fullHouses.begin(), fullHouses.end(), cmp1);
    sort(threes.begin(), threes.end(), cmp1);
    sort(two_pairs.begin(), two_pairs.end(), cmp1);
    sort(pairs.begin(), pairs.end(), cmp1);
    sort(distinct.begin(), distinct.end(), cmp1);

    // bubbleSort(f1c, 1);
    // bubbleSort(f2c, 1);
    // bubbleSort(f3c, 1);
    // bubbleSort(tc, 1);
    // bubbleSort(tpc, 1);
    // bubbleSort(pc, 1);
    // bubbleSort(dc, 1);

    // for (auto it : distinct)
    // {
    //     babaBoltaHai << inputlines[it] << " ";
    // }
    // babaBoltaHai << std::endl;
    // for (auto it : dc)
    // {
    //     abhiBasHogaya << inputlines[it] << " ";
    // }
    // abhiBasHogaya << std::endl;

    // cout << (f1c == fivers) << endl;
    // cout << (f2c == fourers) << endl;
    // cout << (f3c == fullHouses) << endl;
    // cout << (tc == threes) << endl;
    // cout << (tpc == two_pairs) << endl;
    // cout << (pc == pairs) << endl;
    // cout << (dc == distinct) << endl;

    long long int sum = 0ll;
    long long int count = n;

    for (auto it : fivers)
    {
        sum += count * (bids[it]);
        count--;
    }
    for (auto it : fourers)
    {
        sum += count * (bids[it]);
        count--;
    }
    for (auto it : fullHouses)
    {
        sum += count * (bids[it]);
        count--;
    }
    for (auto it : threes)
    {
        sum += count * (bids[it]);
        count--;
    }
    for (auto it : two_pairs)
    {
        sum += count * (bids[it]);
        count--;
    }
    for (auto it : pairs)
    {
        sum += count * (bids[it]);
        count--;
    }

    for (auto it : distinct)
    {
        sum += count * (bids[it]);
        count--;
    }

    cout << sum << endl;
    // gittu
    return 0;
}