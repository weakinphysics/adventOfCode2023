#include "/Users/icero/CodeandDevelopment/Compi/stdc++.h"
#include <fstream>

using namespace std;

class RangeNode
{
    // you can completely amputate a node, or you can partially change it
public:
    long long int range_start;
    long long int range_end;
    bool visited;

    RangeNode(long long int rs, long long int re)
    {
        this->range_start = rs;
        this->range_end = re;
        this->visited = false;
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
        return seebs;
    }
    for (int i = 0; i < rangeCount; i += 2)
    {
        RangeNode *thisRange = new RangeNode(seebraw[i], seebraw[i] + seebraw[i + 1] - 1);
        seebs.push_back(thisRange);
    }
    return seebs;
}

int binarySearcher(vector<RangeNode *> &ranges, int start, int end, long long int target)
{
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (target >= ranges[mid]->range_start)
        {
            if (target > ranges[mid]->range_end)
            {
                if (mid == ranges.size() - 1)
                {
                    if (ranges[mid]->range_end < target)
                        return -1;
                    return mid;
                }
                if (ranges[mid + 1]->range_start > target)
                    return mid;
                return binarySearcher(ranges, mid + 1, end, target);
            }
            return mid;
        }
        return binarySearcher(ranges, start, mid - 1, target);
    }
    return -1;
}

vector<RangeNode *> createRanges(vector<RangeNode *> &ranges, vector<long long int> &range)
{
    int k = ranges.size();
    int index = binarySearcher(ranges, 0, k - 1, range[0]);
    vector<RangeNode *> news;
    if (index == -1)
    {
        index = 0;
        if (range[0] > ranges.back()->range_end)
            return news;
        while (index < k && range[1] >= ranges[index]->range_start)
        {
            if (ranges[index]->visited)
            {
                index++;
                continue;
            }
            long long int d = ranges[index]->range_start - range[0];
            if (range[1] < ranges[index]->range_end)
            {
                RangeNode *new_ranger = new RangeNode(range[2] + d, range[3]);
                news.push_back(new_ranger);
                ranges[index]->range_start = range[1] + 1;
                break;
            }
            else if (range[1] == ranges[index]->range_end)
            {
                RangeNode *new_ranger = new RangeNode(range[2] + d, range[3]);
                news.push_back(new_ranger);
                ranges[index]->visited = true;
                break;
            }
            else
            {
                RangeNode *new_ranger = new RangeNode(range[2] + d, range[2] + ranges[index]->range_end - range[0]);
                news.push_back(new_ranger);
                ranges[index]->visited = true;
                index++;
                continue;
            }
        }
    }
    else
    {
        if (ranges[index]->range_end < range[0])
            index++;
        // look for all nodes that fall into this range
        while (index < k && ranges[index]->range_start <= range[1])
        {
            if (ranges[index]->range_start < range[0])
            {
                if (ranges[index]->range_end > range[1])
                {
                    // fix this one
                    RangeNode *mm = new RangeNode(range[2], range[3]);
                    long long int temp = ranges[index]->range_end;
                    ranges[index]->range_end = range[0] - 1;
                    news.push_back(mm);
                    vector<RangeNode *> copy;
                    int j = 0;
                    while (j <= index)
                    {
                        copy.push_back(ranges[j]);
                        j++;
                    }
                    copy.push_back(new RangeNode(range[1] + 1, temp));
                    while (j < ranges.size())
                    {
                        copy.push_back(ranges[j]);
                        j++;
                    }
                    while (!ranges.empty())
                        ranges.pop_back();
                    while (!copy.empty())
                    {
                        ranges.push_back(copy.back());
                        copy.pop_back();
                    }
                    reverse(ranges.begin(), ranges.end());
                    return news;
                }
                else if (ranges[index]->range_end == range[1])
                {
                    RangeNode *mm = new RangeNode(range[2], range[3]);
                    ranges[index]->range_end = range[0] - 1;
                    news.push_back(mm);
                    return news;
                }
                else
                {
                    RangeNode *mm = new RangeNode(range[2], range[2] + ranges[index]->range_end - range[0]);
                    news.push_back(mm);
                    ranges[index]->range_end = range[0] - 1;
                    index++;
                    continue;
                }
            }
            else if (ranges[index]->range_start == range[0])
            {
                if (ranges[index]->range_end > range[1])
                {
                    RangeNode *mm = new RangeNode(range[2], range[3]);
                    ranges[index]->range_start = range[1] + 1;
                    news.push_back(mm);
                    return news;
                }
                else if (ranges[index]->range_end == range[1])
                {
                    RangeNode *mm = new RangeNode(range[2], range[3]);
                    ranges[index]->visited = true;
                    news.push_back(mm);
                    return news;
                }
                else
                {
                    RangeNode *mm = new RangeNode(range[2], range[2] + ranges[index]->range_end - range[0]);
                    news.push_back(mm);
                    ranges[index]->visited = true;
                    index++;
                    continue;
                }
            }
            if (ranges[index]->visited)
            {
                index++;
                continue;
            }
            long long int d = abs(ranges[index]->range_start - range[0]);
            if (range[1] < ranges[index]->range_end)
            {
                RangeNode *new_ranger = new RangeNode(range[2] + d, range[3]);
                news.push_back(new_ranger);
                ranges[index]->range_start = range[1] + 1;
                break;
            }
            else if (range[1] == ranges[index]->range_end)
            {
                RangeNode *new_ranger = new RangeNode(range[2] + d, range[3]);
                news.push_back(new_ranger);
                ranges[index]->visited = true;
                break;
            }
            else
            {
                RangeNode *new_ranger = new RangeNode(range[2] + d, range[2] + ranges[index]->range_end - range[0]);
                news.push_back(new_ranger);
                ranges[index]->visited = true;
                index++;
                continue;
            }
        }
    }
    return news;
}

static bool comparator(RangeNode *a, RangeNode *b)
{
    return (a->range_start < b->range_start);
}

int newProcess(vector<RangeNode *> &ranges, vector<string> &inputlines, int line)
{
    int n = inputlines.size();
    vector<RangeNode *> new_ranges;
    int close = n;
    for (int i = line + 1; i < n; i++)
    {
        if (inputlines[i] == "")
        {
            close = i;
            break;
        }
        vector<long long int> temp = processline(inputlines[i]);
        vector<long long int> range_temp = {temp[1], temp[1] + temp[2] - 1, temp[0], temp[0] + temp[2] - 1};
        vector<RangeNode *> badAlgorithm = createRanges(ranges, range_temp);
        for (auto it : badAlgorithm)
        {
            new_ranges.push_back(it);
        }
    }
    n = ranges.size();
    for (int i = 0; i < n; i++)
    {
        if (ranges[i]->visited)
        {
            continue;
        }
        else
        {
            new_ranges.push_back(ranges[i]);
        }
    }
    sort(new_ranges.begin(), new_ranges.end(), comparator);
    while (!ranges.empty())
        ranges.pop_back();

    int h = new_ranges.size();
    for (int i = 0; i < h; i++)
        ranges.push_back(new_ranges[i]);
    return close;
}

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
    sort(birbia.begin(), birbia.end(), comparator);
    for (int i = 0; i < k; i++)
    {
        std::cout << birbia[i]->range_start << " " << birbia[i]->range_end << endl;
    }

    int lines = inputlines.size();
    for (int line = 1; line < lines; line++)
    {
        if (!inputlines[line].empty())
        {
            int x = newProcess(birbia, inputlines, line);
            line = x;
        }
    }

    cout << birbia[0]->range_start << endl;

    // let us now test the algorithm by inserting a bogus range

    // okay the seeds have been correctly loaded
    // now we must process the input line by line

    return 0;
}