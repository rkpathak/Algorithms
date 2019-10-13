#include <iostream>
#include <string>
#include <vector>
using namespace std;
void printv(const vector<int> &v)
{
    for(auto i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}
int maxSum(const vector<int> &v)
{
    int maxSum = 0;
    int sum = v[0];
    int i = 1;
    while(i<v.size())
    {
        if(sum > maxSum)
        {
            maxSum = sum;
        }
        if(sum < 0)
        {
            sum = 0;
        }
        sum += v[i];
        ++i;
    }
    return maxSum;
}
int main()
{
    vector<int> v = {-4, 3, 23, -8, 9, -12, -17, 14};
    printv(v);
    cout<<"Max sum:"<<maxSum(v);
}
