#include<bits/stdc++.h>

using namespace std;

pair<string, string> splitRule(const string& rule, const string& delimiter) {
    size_t pos = rule.find(delimiter);
    if (pos != string::npos) {
        string first = rule.substr(0, pos);
        string second = rule.substr(pos + delimiter.length());
        return make_pair(first, second);
    }
    return make_pair("", "");
}

string removeSpaces(const string& line) {
    string result = line;
    result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

vector<string> RulelistFromString(const string& str)
{
    vector<string> result;
    if (str.find("->") == string::npos && str.find("<-") == string::npos)
        // String does not contain "->" or "<-" character
        return result;
    if (str.find("->") != string::npos)
    {
        // String contains "->" character
        pair<string, string> rule = splitRule(str, "->");
        istringstream iss(rule.second);
        string substring;
        while (getline(iss, substring, '|'))
            result.push_back(rule.first + "->" + substring);
    }
    else if (str.find("<-") != string::npos)
    {
        // String contains "<-" character
        pair<std::string, std::string> rule = splitRule(str, "<-");
        istringstream iss(rule.first);
        string substring;
        while (getline(iss, substring, '|'))
            result.push_back(substring + "<-" + rule.second);
    }
    return result;
}

class Rule
{
private:
    string source;
    string target;
public:
    Rule(): source(""), target(""){};
    Rule(const string& str);
    friend class RuleSet;
    bool CheckRule(string);
    bool IsBetterRule(Rule);
};

class RuleSet
{
private:
    vector<Rule> listOfRule;
public:
    RuleSet(){};
    void AddRule(string);
    void ReadFromFile(string);
    void PrintGrammar();
    bool CheckConflict(string, string);
    string ReduceCheck(string&, string);
    string CheckGrammar(string, string);
};

int main()
{
    RuleSet grammar;
    grammar.ReadFromFile("G.txt");
    ifstream in("input.txt");
    string checker;
    getline(in, checker);
    string res = grammar.CheckGrammar(checker, "temp.txt");
    ofstream out("output.txt");
    ifstream temp("temp.txt");
    if (res == "Accepted")
        out << "A\n";
    else
        out << "F\n";
    out << temp.rdbuf();
    temp.close();
    remove("temp.txt");
    out << res;
    out.close();
}

Rule::Rule(const string& str)
{
    if (str.find("->") == std::string::npos && str.find("<-") == std::string::npos)
        throw std::invalid_argument("Invalid input string: " + str);
    if (str.find("->") != std::string::npos)
    {
        std::size_t pos = str.find("->");
        std::string first = str.substr(0, pos);
        std::string second = str.substr(pos + 2);
        source = second;
        target = first;
    }
    else if (str.find("<-") != std::string::npos)
    {
        std::size_t pos = str.find("<-");
        std::string first = str.substr(0, pos);
        std::string second = str.substr(pos + 2);
        source = first;
        target = second;
    }
}

bool Rule::CheckRule(string comp)
{
    if (comp.length() < source.length())
        return false;
    return comp.compare(comp.length() - source.length(), source.length(), source) == 0;
}

bool Rule::IsBetterRule(Rule other)
{
    return source.length() > other.source.length();
}

void RuleSet::AddRule(string rule)
{
    vector<string> rules = RulelistFromString(rule);
    for (int i = 0; i < rules.size(); i++)
        listOfRule.push_back(rules[i]);
    return;
}

void RuleSet::ReadFromFile(string filename)
{
    ifstream inp(filename);
    string line;
    if (inp.is_open())
    {
        while (getline(inp, line))
        {
            line = removeSpaces(line);
            AddRule(line);
        }
        inp.close();
    }
}

void RuleSet::PrintGrammar()
{
    for (vector<Rule>::iterator iter = listOfRule.begin(); iter != listOfRule.end(); iter++)
        cout << iter->target << "->" << iter->source << '\n';
}

bool RuleSet::CheckConflict(string source, string lookAhead)
{
    string comp = source;
    comp.erase(0, comp.length() - 1);
    comp.append(lookAhead);
    for (vector<Rule>::iterator iter = listOfRule.begin(); iter != listOfRule.end(); iter++)
        if (iter->source.find(comp) != string::npos)
            return true;
    return false;
}

string RuleSet::ReduceCheck(string& stk, string lookAhead)
{
    Rule targetRule;
    for (vector<Rule>::iterator iter = listOfRule.begin(); iter != listOfRule.end(); iter++)
    {
        if (iter->CheckRule(stk) && !CheckConflict(iter->source, lookAhead) && iter->IsBetterRule(targetRule))
        {
            targetRule.source = iter->source;
            targetRule.target = iter->target;
        }
    }
    if (targetRule.source.length() != 0)
    {
        stk.replace(stk.length() - targetRule.source.length(), targetRule.source.length(), targetRule.target);
        return "Reduce: " + targetRule.target + "->" + targetRule.source;
    }
    return "Shift";
}

string RuleSet::CheckGrammar(string input, string outFile)
{
    ofstream out(outFile, ios::trunc);
    out << setw(20) << left << setfill(' ') << "Stack";
    out << setw(10) << left << setfill(' ') << "CurrSym";
    out << setw(20) << left << setfill(' ') << "Rest of Input";
    out << "Action" << '\n';
    input = removeSpaces(input);
    string stk = "$";
    string restOfInput = input + "$";
    char currSym = restOfInput[0];
    restOfInput.erase(0, 1);
    while (!restOfInput.empty())
    {
        out << setw(20) << left << setfill(' ') << stk;
        out << setw(10) << left << setfill(' ') << currSym;
        out << setw(20) << left << setfill(' ') << restOfInput;
        string temp(1, currSym);
        string action = ReduceCheck(stk, temp);
        if (action == "Shift")
        {
            stk += temp;
            currSym = restOfInput[0];
            restOfInput.erase(0, 1);
        }
        out << action << '\n';
    }

    out << setw(20) << left << setfill(' ') << stk;
    out << setw(10) << left << setfill(' ') << currSym;
    out << setw(20) << left << setfill(' ') << restOfInput;
    string lastAction = ReduceCheck(stk, " ");
    do
    {
        out << lastAction << '\n';
        out << setw(20) << left << setfill(' ') << stk;
        out << setw(10) << left << setfill(' ') << currSym;
        out << setw(20) << left << setfill(' ') << restOfInput;
        lastAction = ReduceCheck(stk, " ");
    } while (lastAction != "Shift");
    out.close();
    if (stk.length() == 2)
        return "Accepted";
    else
        return "Fail";
}
