#include <bits/stdc++.h>
using namespace std;

struct Rectangle {
    int w;
    int h;
};

bool compare(Rectangle a, Rectangle b) {
    if (a.w == b.w)
        return a.h < b.h;
    else
        return a.w < b.w;
}
int main() {
    ifstream fin("BOX.INP");
    ofstream fout("BOX.OUT");
    Rectangle r[6];
    for (int i = 0; i < 6; i++)
    {
        fin >> r[i].w >> r[i].h;
        if (r[i].w > r[i].h) swap(r[i].w, r[i].h);
    }

    sort(r, r + 6, compare);

    for (auto x : r)
        cout << x.w << " " << x.h << endl;

    if (r[0].w == r[1].w && r[2].w == r[3].w && r[4].w == r[5].w && r[0].h == r[1].h && r[2].h == r[3].h && r[4].h == r[5].h)
    {
        if (r[0].w == r[2].w)
        {
            if ((r[0].h == r[4].h && r[2].h == r[4].w) || (r[2].h == r[4].h && r[0].h == r[4].w)) fout << "YES";
            else fout << "NO";
        }
        else if (r[0].w == r[4].w)
        {
            if ((r[0].h == r[2].h && r[4].h == r[2].w) || (r[4].h == r[2].h && r[0].h == r[2].w)) fout << "YES";
            else fout << "NO";
        }
        else if (r[2].w == r[4].w)
        {
            if ((r[2].h == r[0].h && r[4].h == r[0].w) || (r[4].h == r[0].h && r[2].h == r[0].w)) fout << "YES";
            else fout << "NO";
        }
        else fout << "NO";
    }
    else fout << "NO";
    fin.close();
    fout.close();
    return 0;
}
