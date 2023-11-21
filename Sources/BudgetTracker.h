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

    string week[WEEK_DAY] = { "월", "화", "수", "목", "금", "토", "일" };
    vector<string> category = {
        "1.식비",       "2.카페",       "3.술/유흥",    "4.생활",      "5.쇼핑",
        "6.미용",       "7.교통",       "8.주거/통신",  "9.의료/건강", "10.금융",
        "11.문화/여가", "12.여행/숙박", "13.교육/학습", "14.경조/선물" };

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