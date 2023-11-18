#include <iostream>
#include <string>
#include <vector>
#include <limits> // numeric_limits 사용
using namespace std;
const int WEEK_DAY = 7;

struct Transaction {
    string category;
    string trade;
    double price;
};

string week[] = { "월", "화", "수", "목", "금", "토", "일" };
vector<string> category = { "1.식비","2.카페","3.술/유흥","4.생활","5.쇼핑","6.미용",
                   "7.교통","8.주거/통신","9.의료/건강","10.금융","11.문화/여가",
                    "12.여행/숙박","13.교육/학습","14.경조/선물" };

vector<Transaction> trade_data[WEEK_DAY];

void List_Budget();
double Result(const vector<string>& excluded_categories);

int main() {
    double week_budget;
    cout << "1주일 동안 사용할 예산을 입력하세요: ";
    cin >> week_budget;
    cout << "1주일 동안 계획된 예산은 " << week_budget << " 입니다" << endl;

    List_Budget();
    vector<string> excluded_categories;
    cout << "무지출 챌린지 에서 제외할 카테고리를 선택하세요. (선택을 마치려면 0을 입력하세요)" << endl;
    for (int i = 0; i < category.size(); i++) {
        cout << category[i] << " ";
    }
    cout << endl;

    while (true) {
        int c;
        cin >> c;
        if (c == 0) {
            break;
        }

        if (c < 1 || c > category.size()) {
            cout << "올바른 카테고리를 선택하세요." << endl;
            continue;
        }

        excluded_categories.push_back(category[c - 1]);
    }

    double total_consumption = Result(excluded_categories);
    if (week_budget > total_consumption) {
        cout << "남은 예산!" << endl;
        cout << "-----------------------------" << endl;
        cout << week_budget - total_consumption << endl;
    }
    else {
        cout << "예산 초과!!" << endl;
        cout << "-----------------------------" << endl;
        cout << total_consumption - week_budget << endl;
    }
}



// 일주일 가계부 입력받음
void List_Budget() {
    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << endl;
        cout << "입력할게 있으시면 O, 입력할게 없으면 X이라고 적으세요 " << endl;
        string check1;
        cin >> check1;
        if (check1 == "x" or check1 == "X") {
            // "없음"을 입력하면 현재 요일의 입력을 종료하고 다음 요일로 이동
            continue;
        }

        while (true) {
            cout << "카테고리를 선택해주세요" << endl;
            for (int i = 0; i < category.size(); i++) {
                cout << category[i] << " ";
            }
            cout << endl;

            int c;
            cin >> c;

            if (c < 1 || c > category.size()) {
                cout << "올바른 카테고리를 선택하세요." << endl;
                continue;
            }

            string selected_category = category[c - 1];
            cout << "거래처와 금액을 입력하세요: ";
            Transaction new_transaction;
            new_transaction.category = selected_category;
            cin >> new_transaction.trade >> new_transaction.price;
            trade_data[i].push_back(new_transaction);

            cout << "더 입력하시겠습니까? ('X'를 입력하면 입력이 종료되고, 다음 날로 넘어갑니다.): ";
            string check2;
            cin >> check2;
            if (check2 == "x" or check2 == "X") {
                break;
            }
        }
    }
}

// 가계부 결과 나타냄 (무지출)
double Result(const vector<string>& excluded_categories) {
    int no_expenditure = 0;
    double total_consumption = 0;
    double percentage = 0;
    double max_price = numeric_limits<double>::min(); // 최대값 초기화

    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << "요일 거래 내역:" << endl;

        // 거래 내역이 없는 경우 처리
        if (trade_data[i].empty()) {
            cout << "거래 내역이 없습니다." << endl;
            no_expenditure++;
        }
        else {
            bool allCategoriesNoExpenditure = true; // 모든 카테고리가 무지출인지 여부

            for (const auto& transaction : trade_data[i]) {
                // 특정 카테고리가 포함되어 있으면 해당 카테고리는 무지출이 아님
                if (find(excluded_categories.begin(), excluded_categories.end(), transaction.category) != excluded_categories.end()) {
                    allCategoriesNoExpenditure = false;
                }

                cout << "카테고리: " << transaction.category << ", 거래처: " << transaction.trade << ", 금액: " << transaction.price << endl;
                total_consumption += transaction.price;
                // 최대값 갱신
                if (transaction.price > max_price) {
                    max_price = transaction.price;
                }
            }

            // 모든 카테고리가 무지출인 경우에만 no_expenditure를 증가시킴
            if (allCategoriesNoExpenditure) {
                no_expenditure++;
            }
        }
    }
    percentage = max_price / total_consumption * 100;

    cout << "무지출 일수는 " << no_expenditure << " 입니다" << endl;
    cout << "총 소비금액는 " << total_consumption << "입니다" << endl;
    cout << "최대 소비금액은 " << max_price << "입니다" << endl;
    cout << percentage << " 전체 금액에서 차지하는 비율 입니다" << endl;
    return total_consumption;
}
