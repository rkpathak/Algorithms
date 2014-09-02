#include<iostream>
#include<string>
using namespace std;

void Permute(string soFar, string left)
{
    if(left.length() == 0)
    {
        cout<<"Permutation: "<<soFar<<endl;
        return;
    }

    for(int i =0; i<left.length(); ++i)
    {
        //uncomment following line for unique permutations
        //if(left.find(left[i], i+1) == string::npos) 
        {
            string next = soFar + left[i];
            string rem = left.substr(0, i)+left.substr(i+1);
            Permute(next, rem);
        }
    }
}
void Permute(string s)
{
    Permute("", s);
}
int main()
{
    string s;
    cout<<"Enter String: ";
    cin>>s;
    Permute(s);

    return 0;
}
