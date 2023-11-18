#include <iostream>
#include <string>
#include <vector>
#include <limits> // numeric_limits ���
using namespace std;
const int WEEK_DAY = 7;

struct Transaction {
    string category;
    string trade;
    double price;
};

string week[] = { "��", "ȭ", "��", "��", "��", "��", "��" };
vector<string> category = { "1.�ĺ�","2.ī��","3.��/����","4.��Ȱ","5.����","6.�̿�",
                   "7.����","8.�ְ�/���","9.�Ƿ�/�ǰ�","10.����","11.��ȭ/����",
                    "12.����/����","13.����/�н�","14.����/����" };

vector<Transaction> trade_data[WEEK_DAY];

void List_Budget();
double Result(const vector<string>& excluded_categories);

int main() {
    double week_budget;
    cout << "1���� ���� ����� ������ �Է��ϼ���: ";
    cin >> week_budget;
    cout << "1���� ���� ��ȹ�� ������ " << week_budget << " �Դϴ�" << endl;

    List_Budget();
    vector<string> excluded_categories;
    cout << "������ ç���� ���� ������ ī�װ��� �����ϼ���. (������ ��ġ���� 0�� �Է��ϼ���)" << endl;
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
            cout << "�ùٸ� ī�װ��� �����ϼ���." << endl;
            continue;
        }

        excluded_categories.push_back(category[c - 1]);
    }

    double total_consumption = Result(excluded_categories);
    if (week_budget > total_consumption) {
        cout << "���� ����!" << endl;
        cout << "-----------------------------" << endl;
        cout << week_budget - total_consumption << endl;
    }
    else {
        cout << "���� �ʰ�!!" << endl;
        cout << "-----------------------------" << endl;
        cout << total_consumption - week_budget << endl;
    }
}



// ������ ����� �Է¹���
void List_Budget() {
    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << endl;
        cout << "�Է��Ұ� �����ø� O, �Է��Ұ� ������ X�̶�� �������� " << endl;
        string check1;
        cin >> check1;
        if (check1 == "x" or check1 == "X") {
            // "����"�� �Է��ϸ� ���� ������ �Է��� �����ϰ� ���� ���Ϸ� �̵�
            continue;
        }

        while (true) {
            cout << "ī�װ��� �������ּ���" << endl;
            for (int i = 0; i < category.size(); i++) {
                cout << category[i] << " ";
            }
            cout << endl;

            int c;
            cin >> c;

            if (c < 1 || c > category.size()) {
                cout << "�ùٸ� ī�װ��� �����ϼ���." << endl;
                continue;
            }

            string selected_category = category[c - 1];
            cout << "�ŷ�ó�� �ݾ��� �Է��ϼ���: ";
            Transaction new_transaction;
            new_transaction.category = selected_category;
            cin >> new_transaction.trade >> new_transaction.price;
            trade_data[i].push_back(new_transaction);

            cout << "�� �Է��Ͻðڽ��ϱ�? ('X'�� �Է��ϸ� �Է��� ����ǰ�, ���� ���� �Ѿ�ϴ�.): ";
            string check2;
            cin >> check2;
            if (check2 == "x" or check2 == "X") {
                break;
            }
        }
    }
}

// ����� ��� ��Ÿ�� (������)
double Result(const vector<string>& excluded_categories) {
    int no_expenditure = 0;
    double total_consumption = 0;
    double percentage = 0;
    double max_price = numeric_limits<double>::min(); // �ִ밪 �ʱ�ȭ

    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << "���� �ŷ� ����:" << endl;

        // �ŷ� ������ ���� ��� ó��
        if (trade_data[i].empty()) {
            cout << "�ŷ� ������ �����ϴ�." << endl;
            no_expenditure++;
        }
        else {
            bool allCategoriesNoExpenditure = true; // ��� ī�װ��� ���������� ����

            for (const auto& transaction : trade_data[i]) {
                // Ư�� ī�װ��� ���ԵǾ� ������ �ش� ī�װ��� �������� �ƴ�
                if (find(excluded_categories.begin(), excluded_categories.end(), transaction.category) != excluded_categories.end()) {
                    allCategoriesNoExpenditure = false;
                }

                cout << "ī�װ�: " << transaction.category << ", �ŷ�ó: " << transaction.trade << ", �ݾ�: " << transaction.price << endl;
                total_consumption += transaction.price;
                // �ִ밪 ����
                if (transaction.price > max_price) {
                    max_price = transaction.price;
                }
            }

            // ��� ī�װ��� �������� ��쿡�� no_expenditure�� ������Ŵ
            if (allCategoriesNoExpenditure) {
                no_expenditure++;
            }
        }
    }
    percentage = max_price / total_consumption * 100;

    cout << "������ �ϼ��� " << no_expenditure << " �Դϴ�" << endl;
    cout << "�� �Һ�ݾ״� " << total_consumption << "�Դϴ�" << endl;
    cout << "�ִ� �Һ�ݾ��� " << max_price << "�Դϴ�" << endl;
    cout << percentage << " ��ü �ݾ׿��� �����ϴ� ���� �Դϴ�" << endl;
    return total_consumption;
}
