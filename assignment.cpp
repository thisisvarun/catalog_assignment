#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

long long convertToDecimal(const string &value, int base) {
    return stoll(value, nullptr, base);
}

long long calculateTerm(const vector<pair<int, long long>>& points, int i, int k) {
    long long term = points[i].second;
    long long denominator = 1;

    for (int j = 0; j < k; ++j) {
        if (i != j) {
            term *= -points[j].first;
            denominator *= (points[i].first - points[j].first);
        }
    }
    return term / denominator;
}

int main() {
    ifstream inputFile("input.json");
    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    json inputJson;
    inputFile >> inputJson;

    int k = inputJson["keys"]["k"];
    vector<pair<int, long long>> points;

    for (auto &[key, value] : inputJson.items()) {
        if (key == "keys") continue;
        int x = stoi(key);
        int base = stoi(value["base"].get<string>());
        long long y = convertToDecimal(value["value"].get<string>(), base);
        points.emplace_back(x, y);
    }

    sort(points.begin(), points.end());
    points.resize(k);

    long long c = 0;
    for (int i = 0; i < k; ++i) {
        c += calculateTerm(points, i, k);
    }

    cout << "Result: " << c << endl;
    return 0;
}
