#include <iostream>;
#include <string>;
using namespace std;
void Budget(double x);
void List_Budget();

const int WEEK_DAY = 7;
string week[] = {"��", "ȭ", "��", "��", "��", "��", "��"};
double trade_price[WEEK_DAY][1000];
string trade_list[WEEK_DAY][1000];

int main() {
  double money;
  cin >> money;
  Budget(money);
  List_Budget();
}

void Budget(double x) { cout << "1���ϵ��� ��ȹ�� ������ " << x << " �Դϴ�"; }

void List_Budget() {
  for (int i = 0; i < WEEK_DAY; i++) {
    cout << "�ŷ�ó�� ���⳻���� �Է��ϼ���! �� �ۼ��� 0 �Է�!" << endl;
    cout << week[i] << endl;
    int j = 0;
    while (true) {
      cin >> trade_list[i][j] >> trade_price[i][j];
      string check;
      cin >> check;
      if (check == "�Ϸ�") {
        break;
      } 
      else
      j++;
    }
    
  }
  
 for (int i = 0; i < WEEK_DAY; i++) {
    cout << week[i] << "���� �ŷ� ����:" << endl;
    for (int j = 0; j < 1000; j++) {
      if (trade_list[i][j].empty()) break;
      cout << "�ŷ�ó: " << trade_list[i][j] << ", �ݾ�: " << trade_price[i][j]
           << endl;
    }
  }
}