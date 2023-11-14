#include <iostream>
#include <string>
using namespace std;

const int WEEK_DAY = 7;
string week[] = { "��", "ȭ", "��", "��", "��", "��", "��" };
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
    cout << "1���� ���� ����� ������ �Է��ϼ���: ";
    cin >> x;
    cout << "1���� ���� ��ȹ�� ������ " << x << " �Դϴ�" << endl;
}

void List_Budget() {
    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << endl;
        cout << "�ŷ�ó�� ���⳻���� �Է��ϼ���! �Է��Ұ� ������ �����̶�� �������� " << endl;
        string check;
        cin >> check;
        if (check == "����") {
            // "����"�� �Է��ϸ� ������ ���������ϴ�.
            continue;
        }

        int j = 0;
        while (true) {
            cout << "�ŷ�ó�� �ݾ��� �Է��ϼ���: ";
            cin >> trade_list[i][j] >> trade_price[i][j];
            j++; // ���ο� �ŷ� ������ �Է¹��� ������ j�� ������Ŵ

            cout << "�� �Է��Ͻðڽ��ϱ�? ('�Ϸ�'�� �Է��ϸ� �Է��� ����ǰ�, ���� ���� �Ѿ�ϴ�.): ";
            cin >> check;
            if (check == "�Ϸ�") {
                break;
            }
        }
    }

    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << "���� �ŷ� ����:" << endl;

        // �ŷ� ������ ���� ��� ó��
        if (trade_list[i][0].empty()) {
            cout << "�ŷ� ������ �����ϴ�." << endl;
        }
        else {
            for (int j = 0; j < 1000; j++) {
                if (trade_list[i][j].empty()) break;
                cout << "�ŷ�ó: " << trade_list[i][j] << ", �ݾ�: " << trade_price[i][j] << endl;
            }
        }
    }
}
