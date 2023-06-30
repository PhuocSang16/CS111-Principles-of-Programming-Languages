#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string order = "23456789TJQKA";
string suits = "CBRN";

bool Sosanh(string card1, string card2)
{
    if (order.find(card1[0]) > order.find(card2[0])) return true;
    else if (order.find(card1[0]) == order.find(card2[0]))
    {
        if (suits.find(card1[1]) < suits.find(card2[1])) return true;
    }
    return false;
}

int main()
{
    ifstream fin("CARD.INP");
    ofstream fout("CARD.OUT");

    int t;
    fin >> t;

    while (t--)
    {
        int n;
        fin >> n;

        vector<string> adam(n);
        vector<string> eva(n);

        for (int i = 0; i < n; ++i)
        {
            fin >> adam[i];
        }

        for (int i = 0; i < n; ++i)
        {
            fin >> eva[i];
        }

        sort(eva.begin(), eva.end(), Sosanh);
        int score = 0;
        for (int i = 0; i < n; ++i)
        {
            bool found = false;
            int minDiff = 100;
            int minIndex = -1;
            for (int j = 0; j < eva.size(); ++j)
            {
                if (Sosanh(eva[j], adam[i]))
                {
                    int diff = order.find(eva[j][0]) - order.find(adam[i][0]);
                    if (diff < minDiff)
                    {
                        minDiff = diff;
                        minIndex = j;
                    }
                    found = true;
                }
            }
            if (found)
            {
                score++;
                eva.erase(eva.begin() + minIndex);
            }
            else eva.erase(eva.begin());
        }
        fout << score << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
