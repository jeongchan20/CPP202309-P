#include <iostream>;
#include <string>;
using namespace std;
void Budget(double x);
void List_Budget();

const int WEEK_DAY = 7;
string week[] = {"월", "화", "수", "목", "금", "토", "일"};
double trade_price[WEEK_DAY][1000];
string trade_list[WEEK_DAY][1000];

int main() {
  double money;
  cin >> money;
  Budget(money);
  List_Budget();
}

void Budget(double x) { cout << "1주일동안 계획된 예산은 " << x << " 입니다"; }

void List_Budget() {
  for (int i = 0; i < WEEK_DAY; i++) {
    cout << "거래처와 지출내용을 입력하세요! 다 작성시 0 입력!" << endl;
    cout << week[i] << endl;
    int j = 0;
    while (true) {
      cin >> trade_list[i][j] >> trade_price[i][j];
      string check;
      cin >> check;
      if (check == "완료") {
        break;
      } 
      else
      j++;
    }
    
  }
  
 for (int i = 0; i < WEEK_DAY; i++) {
    cout << week[i] << "요일 거래 내역:" << endl;
    for (int j = 0; j < 1000; j++) {
      if (trade_list[i][j].empty()) break;
      cout << "거래처: " << trade_list[i][j] << ", 금액: " << trade_price[i][j]
           << endl;
    }
  }
}