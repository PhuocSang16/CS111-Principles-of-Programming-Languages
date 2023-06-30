#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

struct Pilot {
    int mainPrice, coPrice;
};

int main()
{
    ifstream fin("AIRCREW.IN");
    ofstream fout("AIRCREW.OUT");
    int n, n2;
    fin >> n2;
    n = n2 / 2;
    vector<Pilot> pilots(n2);
    int f[n2][n];
    for (int i = 0; i < n2; i++)
        fin >> pilots[i].mainPrice >> pilots[i].coPrice;
    memset(f, 0x3f, sizeof f);

    int res = pilots[pilots.size()-1].mainPrice + pilots[0].coPrice;
    pilots.pop_back();

    f[0][0] = 0;
    for (int i = 1; i < n2-1; i++)
        for (int j = 0; j < n; j++)
        {
            if (j)
                f[i][j] = min(f[i - 1][j - 1] + pilots[i].mainPrice, f[i][j]);
            if (i > j)
                f[i][j] = min(f[i - 1][j] + pilots[i].coPrice, f[i][j]);
        }
    for (int i = 0; i < n2-1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }

    res += f[n2-2][n-1];
    fout << res;
    fin.close();
    fout.close();
    return 0;
}
