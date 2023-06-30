#include <bits/stdc++.h>
#include <locale>
#include <codecvt>
#include <fcntl.h>
using namespace std;

set<wstring> make_list(wstring s)
{
    wstring x;
    set<wstring> list_word;
    for (auto i: s)
    {
        if ((i >= 65 && i <= 90) || (i >= 192 && i <= 8000)) x += i;
        else
        {
            if (!x.empty()) list_word.insert(x);
            x.clear();
        }
    }
    return list_word;
}

int main()
{
    //_setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    locale loc(locale(), new codecvt_utf8_utf16<wchar_t>);
    wifstream is;

    is.open("file A.txt");
    is.imbue(loc);
    wstring x;
    map<wstring, int> m;
    while (!is.eof())
    {
        getline(is, x);
        m.insert({x, 1});
    }
    is.close();

    is.open("fileTest2.txt");
    int dem = 0;
    wstring y;
    while (!is.eof())
    {
        getline(is, y);
        set<wstring> list_w = make_list(y);
        for (auto i: list_w)
        {
            if (m[i] == 1) dem++;
        }
    }
    is.close();
    //wcout << L"Noi dung File B: \n" << y << "\n";
    wcout << L"Cau a: Dem xem co bao nhieu tieng trong File A xuat hien khong lap lai trong File B\n";
    wcout << L"Tra loi: " << dem << "\n";
    wcout << L"Cau b: Tinh ty le phan tram\n";
    wcout << L"Tra loi: " << (dem / float(m.size()) * 100) << "%";

    return 0;
}
