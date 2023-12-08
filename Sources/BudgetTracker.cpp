#include"BudgetTracker.h"

//dayIndex�� �Է¹޾� ������ �ŷ�����,ī�װ�,�ŷ�ó,�ݾ��� ����� 
void BudgetTracker::DisplayTransactionDetails(int dayIndex) {
    cout << week[dayIndex] << "���� �ŷ� ����:" << endl;

    if (trade_data[dayIndex].empty()) {
        cout << "�ŷ� ������ �����ϴ�." << endl;
    }
    else {
        for (const auto& transaction : trade_data[dayIndex]) {
            cout << "ī�װ�: " << transaction.category
                << ", �ŷ�ó: " << transaction.trade
                << ", �ݾ�: " << transaction.price << endl;
        }
    }
}
//������ ������ ��� �Һ�ݾ� ���
double BudgetTracker::CalculateAverageConsumption() {
    double total_consumption = 0;

    for (int i = 0; i < WEEK_DAY; i++) {
        if (!trade_data[i].empty()) {
            for (const auto& transaction : trade_data[i]) {
                total_consumption += transaction.price;
            }
        }
    }

    return total_consumption / WEEK_DAY;
}

//ī�װ��� �Һ���� ���
vector<double> BudgetTracker::AnalyzeCategoryPercentage(double total_consumption) {
    vector<double> category_percentage(category.size(), 0.0);

    for (int i = 0; i < WEEK_DAY; i++) {
        for (const auto& transaction : trade_data[i]) {
            auto iter = find(category.begin(), category.end(), transaction.category);
            if (iter != category.end()) {
                int index = distance(category.begin(), iter);
                category_percentage[index] += transaction.price;
            }
        }
    }

    for (int i = 0; i < category.size(); i++) {
        category_percentage[i] = (category_percentage[i] / total_consumption) * 100;
    }

    return category_percentage;
}
//�������ϼ�,�ѼҺ�ݾ�,�ִ�Һ�ݾ��� ��½�Ŵ
double BudgetTracker::Result(const vector<string>& excluded_categories,
    double& average_consumption,
    vector<double>& category_percentage) {
    int no_expenditure = 0;
    string max_trade = "";
    double total_consumption = 0;
    double max_price = numeric_limits<double>::min();

    for (int i = 0; i < WEEK_DAY; i++) {
        if (find(excluded_categories.begin(), excluded_categories.end(), "ALL") != excluded_categories.end()) {
            continue;
        }

        DisplayTransactionDetails(i);

        if (trade_data[i].empty()) {
            no_expenditure++;
        }
        else {
            bool allCategoriesNoExpenditure = true;

            for (const auto& transaction : trade_data[i]) {
                if (find(excluded_categories.begin(), excluded_categories.end(),
                    transaction.category) != excluded_categories.end()) {
                    allCategoriesNoExpenditure = false;
                }

                total_consumption += transaction.price;
                if (transaction.price > max_price) {
                    max_price = transaction.price;
                    max_trade = transaction.trade;
                }
            }

            if (allCategoriesNoExpenditure) {
                no_expenditure++;
            }
        }
    }

    average_consumption = CalculateAverageConsumption();
    category_percentage = AnalyzeCategoryPercentage(total_consumption);

    cout << "������ �ϼ��� " << no_expenditure << " �Դϴ�" << endl;
    cout << "�� �Һ�ݾ״� " << total_consumption << "�� �Դϴ�" << endl;
    cout << "�ִ� �Һ�ݾ��� " << max_trade << " : " << max_price << "�� �Դϴ�" << endl;


    return total_consumption;
}
//����ڿ��� �Է��� ���θ� Ȯ����
void BudgetTracker::ListBudget() {
    for (int i = 0; i < WEEK_DAY; i++) {
        cout << week[i] << endl;
        cout << "�Է��Ұ� �����ø� O, �Է��Ұ� ������ X�̶�� �������� " << endl;
        string check1;
        cin >> check1;
        if (check1 == "x" or check1 == "X") {
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

            if (cin.fail()) {
                cout << "���ڸ� �Է��ϼ���." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

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

            cout << "�� �Է��Ͻðڽ��ϱ�? ('X'�� �Է��ϸ� �Է��� ����ǰ�, ���� ���� "
                "�Ѿ�ϴ�.): ";
            string check2;
            cin >> check2;
            if (check2 == "x" or check2 == "X") {
                break;
            }
        }

        // �ŷ� ���� ���� �� ���� �ɼ� �߰�
        cout << "���� �Ǵ� �����Ͻðڽ��ϱ�? ('M' or 'D', �Է��� �����Ϸ��� 'X'): ";
        string modifyOrDelete;
        cin >> modifyOrDelete;

        if (modifyOrDelete == "M" || modifyOrDelete == "m") {
            // ���� ���� �߰�
            // ����ڿ��� ������ �ŷ� ���� ������ �ް� �����մϴ�.
        }
        else if (modifyOrDelete == "D" || modifyOrDelete == "d") {
            // ���� ���� �߰�
            // ����ڿ��� ������ �ŷ� ���� ������ �ް� �����մϴ�.
        }
        else if (modifyOrDelete == "X" || modifyOrDelete == "x") {
            // �Է� ����
            break;
        }
    }
}



void BudgetTracker::RunBudgetTracker() {
    double week_budget;
    cout << "1���� ���� ����� ������ �Է��ϼ���: ";
    cin >> week_budget;
    cout << "1���� ���� ��ȹ�� ������ " << week_budget << "�� �Դϴ�" << endl;

    ListBudget();
    vector<string> excluded_categories;


    while (true) {
        int c;
        for (int i = 0; i < category.size(); i++) {
            cout << category[i] << " ";
        }
        cout << "������ ç�������� ������ ī�װ��� �����ϼ���. (������ ��ġ���� 0�� �Է��ϼ���): ";
        cin >> c;


        if (cin.fail()) {
            cout << "���ڸ� �Է��ϼ���." << endl;
            continue;
        }

        if (c == 0) {
            break;
        }

        if (c < 1 || c > category.size()) {
            cout << "�ùٸ� ī�װ��� �����ϼ���." << endl;
            continue;
        }

        excluded_categories.push_back(category[c - 1]);
    }


    double average_consumption = 0;
    vector<double> category_percentage;
    double total_consumption =
        Result(excluded_categories, average_consumption, category_percentage);

    if (week_budget > total_consumption) {
        cout << "���� ����!" << endl;
        cout << "-----------------------------" << endl;
        cout << week_budget - total_consumption << "���� ���ҽ��ϴ�" << endl;
    }
    else {
        cout << "���� �ʰ�!!" << endl;
        cout << "-----------------------------" << endl;
        cout << total_consumption - week_budget << "���� �ʰ��߽��ϴ�" << endl;
    }

    cout << "�� ��� �Һ�ݾ�: " << average_consumption << endl;

    cout << "ī�װ��� �Һ� �м�:" << endl;
    for (int i = 0; i < category.size(); i++) {
        cout << category[i] << ": " << category_percentage[i] << "%" << endl;
    }
}