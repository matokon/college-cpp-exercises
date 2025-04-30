#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct one_line
{
    int line_nbr;
    string start;
    string stop;
    string operator_name;
};

one_line line_to_struct(const string& line)
{
    istringstream line_1(line);
    string current_word;
    one_line data;

    getline(line_1, current_word, ',');
    data.line_nbr = stoi(current_word);
    getline(line_1, data.start, ',');
    getline(line_1, data.stop, ',');
    getline(line_1, data.operator_name, ',');

    return data;
}

void save_to_file(const vector<one_line>& lines, const string& filename)
{
    ofstream file(filename);
    file << "lineNumber,startStop,EndStop,operator" << endl;
    for(const auto& line : lines)
    {
        file << line.line_nbr << "," << line.start << "," << line.stop << "," << line.operator_name << endl;
    }
}

int main()
{
    ifstream input("dataNoQ.csv");
    string line;
    getline(input, line);

    vector<one_line> tram_lines;
    vector<one_line> bus_lines;
    unordered_map<string, int> end_stop_counter;

    while(getline(input, line))
    {
        one_line data = line_to_struct(line);
        if(data.line_nbr < 100)
            tram_lines.push_back(data);
        else
            bus_lines.push_back(data);
        end_stop_counter[data.stop]++;
    }
    for(const auto& pair : end_stop_counter)
    {
        cout << pair.first << " - " << pair.second << " lines end here" << endl;
    }
    save_to_file(tram_lines, "tram_lines.csv");
    save_to_file(bus_lines, "bus_lines.csv");
    return 0;
}