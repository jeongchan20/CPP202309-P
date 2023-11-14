#include <iostream>
#include <string>
using namespace std;

const int WEEK_DAY = 7;
string week[] = { "월", "화", "수", "목", "금", "토", "일" };
double trade_price[WEEK_DAY][1000];
string trade_list[WEEK_DAY][1000];

void Budget(double& x);
void List_Budget();

int main() {
    double money;
    Budget(money);
    List_Budget();
}

void Budget(double& x) {
    cout << "1주일 동안 사용할 예산을 입력하세요: ";
    cin >> x;
    cout << "1주일 동안 계획된 예산은 " << x << " 입니다" << endl;
}

void List_Budget() {
    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << endl;
        cout << "거래처와 지출내용을 입력하세요! 입력할게 없으면 없음이라고 적으세요 " << endl;
        string check;
        cin >> check;
        if (check == "없음") {
            // "없음"을 입력하면 루프를 빠져나갑니다.
            continue;
        }

        int j = 0;
        while (true) {
            cout << "거래처와 금액을 입력하세요: ";
            cin >> trade_list[i][j] >> trade_price[i][j];
            j++; // 새로운 거래 내역을 입력받을 때마다 j를 증가시킴

            cout << "더 입력하시겠습니까? ('완료'를 입력하면 입력이 종료되고, 다음 날로 넘어갑니다.): ";
            cin >> check;
            if (check == "완료") {
                break;
            }
        }
    }

    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << "요일 거래 내역:" << endl;

        // 거래 내역이 없는 경우 처리
        if (trade_list[i][0].empty()) {
            cout << "거래 내역이 없습니다." << endl;
        }
        else {
            for (int j = 0; j < 1000; j++) {
                if (trade_list[i][j].empty()) break;
                cout << "거래처: " << trade_list[i][j] << ", 금액: " << trade_price[i][j] << endl;
            }
        }
    }
}
