#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main()
{
  vector<int> v;
  for (int i=0;i<20;i++)
    {
      v.push_back(i);
    }
  for (int j=0;j<20;j++)
    {
      cout<<v.size()<<endl;
      cout<<v[j]<<endl;      
    }
  return 0;
}
