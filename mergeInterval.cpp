#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
struct Interval
{
    int start;
    int end;
    bool operator<(const Interval &rhs)
    {
        return (start < rhs.start);
    }
    void print()
    {
        std::cout << "{" << start << ", " << end << "} ";
    }
};

bool isOverlap(Interval t1, Interval t2)
{
    return (t1.start <= t2.start && t2.start <= t1.end) || (t2.start <= t1.start && t1.start <= t2.end);
}

Interval merge(Interval t1, Interval t2)
{
    return Interval{min(t1.start,t2.start), max(t1.end,t2.end)};
}

//template<typename T>
void printv(vector<Interval> &vec)
{
    for (const auto& item : vec) {
        std::cout << "{" << item.start << ", " << item.end << "} ";
    }
    cout<<endl;
}
int main()
{
    vector<Interval> intervals {{1,3}, {3,4}, {2,6}};
    sort(intervals.begin(), intervals.end());
    printv(intervals);
    vector<Interval> result;
    Interval current = intervals[0];

    for(int i=1; i<intervals.size();++i)
    {
        if(isOverlap(current, intervals[i]))
        {
            current = merge(current, intervals[i]);
        }
        else{
            result.push_back(current);
            current = intervals[i];
        }
    }
    result.push_back(current);
    cout<<"result:";
    printv(result);
    return 0;
}
