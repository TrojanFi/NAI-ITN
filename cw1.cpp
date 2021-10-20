#include <iostream>
#include <functional>
#include <vector>

using namespace std; // zła praktyka

auto f2(int i)
{
    int p = (2 * (i % 2) - 1) * i / 2;
    return p;
}

auto f1(int i)
{
    int p = 20 - abs(i + 7);
    return p;
}

auto calculation(function<int(int)> f1, function<int(int)> f2, int n)
{
    vector<int> v;
    int max_x = f2(0);
    int max_y = f1(max_x);
    for (int i = 1; i < n; i++)
    {
        int x = f2(i);
        int y = f1(x);
        if (y > max_y)
        {
            max_x = x;
            max_y = y;
        }
    }
    v.push_back(max_x);
    v.push_back(max_y);
    return v;
}

int main()
{
    vector<int> v = calculation(f1, f2, 403);
    cout << " max_x = " << v[0] << ", max_y = " << v[1] << endl;
    return 0;
}