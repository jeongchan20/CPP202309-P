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

void Budget(double& x);
void List_Budget();
void Result();

int main() {
    double money;
    Budget(money);
    List_Budget();
    Result();
}

void Budget(double& x) {
    cout << "1주일 동안 사용할 예산을 입력하세요: ";
    cin >> x;
    cout << "1주일 동안 계획된 예산은 " << x << " 입니다" << endl;
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
void Result() {
    int no_expenditure = 0;
    double total_consumption = 0;
    double max_price = numeric_limits<double>::min(); // 최대값 초기화

    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << "요일 거래 내역:" << endl;

        // 거래 내역이 없는 경우 처리
        if (trade_data[i].empty()) {
            cout << "거래 내역이 없습니다." << endl;
            no_expenditure++;
        }
        else {
            for (const auto& transaction : trade_data[i]) {
                cout << "카테고리: " << transaction.category << ", 거래처: " << transaction.trade << ", 금액: " << transaction.price << endl;
                total_consumption += transaction.price;
                // 최대값 갱신
                if (transaction.price > max_price) {
                    max_price = transaction.price;
                }
            }
        }
    }

    cout << "무지출 일수는 " << no_expenditure << " 입니다" << endl;
    cout << "총 소비금액는 " << total_consumption << "입니다" << endl;
    cout << "최대 소비금액은 " << max_price << "입니다" << endl;
}
