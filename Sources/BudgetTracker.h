#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

const int WEEK_DAY = 7;
class BudgetTracker {
private:

    struct Transaction {
        string category;
        string trade;
        double price;
    };

    string week[WEEK_DAY] = { "��", "ȭ", "��", "��", "��", "��", "��" };
    vector<string> category = {
        "1.�ĺ�",       "2.ī��",       "3.��/����",    "4.��Ȱ",      "5.����",
        "6.�̿�",       "7.����",       "8.�ְ�/���",  "9.�Ƿ�/�ǰ�", "10.����",
        "11.��ȭ/����", "12.����/����", "13.����/�н�", "14.����/����" };

    vector<Transaction> trade_data[WEEK_DAY];

    void DisplayTransactionDetails(int dayIndex);
    double CalculateAverageConsumption();
    vector<double> AnalyzeCategoryPercentage(double total_consumption);
    double Result(const vector<string>& excluded_categories,
        double& average_consumption, vector<double>& category_percentage);
    void ListBudget();

public:
    void RunBudgetTracker();
};