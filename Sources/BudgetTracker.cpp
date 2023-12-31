#include"BudgetTracker.h"

//dayIndex를 입력받아 요일의 거래내역,카테고리,거래처,금액을 출력함 
void BudgetTracker::DisplayTransactionDetails(int dayIndex) {
    cout << week[dayIndex] << "요일 거래 내역:" << endl;

    if (trade_data[dayIndex].empty()) {
        cout << "거래 내역이 없습니다." << endl;
    }
    else {
        for (const auto& transaction : trade_data[dayIndex]) {
            cout << "카테고리: " << transaction.category
                << ", 거래처: " << transaction.trade
                << ", 금액: " << transaction.price << endl;
        }
    }
}
//일주일 동안의 평균 소비금액 계산
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

//카테고리별 소비비율 계산
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
//무지출일수,총소비금액,최대소비금액을 출력시킴
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

    cout << "무지출 일수는 " << no_expenditure << " 입니다" << endl;
    cout << "총 소비금액는 " << total_consumption << "원 입니다" << endl;
    cout << "최대 소비금액은 " << max_trade << " : " << max_price << "원 입니다" << endl;


    return total_consumption;
}
//사용자에게 입력을 여부를 확인함

void BudgetTracker::ListBudget() {
    for (int day = 0; day < WEEK_DAY; day++) {
        cout << week[day] << endl;
        cout << "입력할게 있으시면 O, 입력할게 없으면 X이라고 적으세요 " << endl;
        string check1;
        cin >> check1;
        if (check1 == "x" or check1 == "X") {
            continue;
        }
        ofstream outputFile{ "user_input.txt", ios::app };

        if (!outputFile.is_open()) {
            cout << "파일을 열 수 없습니다." << endl;
            return;
        }

        while (true) {
            cout << "카테고리를 선택해주세요" << endl;
            for (int j = 0; j < category.size(); j++) {
                cout << category[j] << " ";
            }
            cout << endl;
            try {
                int c;
                cout << "카테고리 번호를 입력하세요: ";
                cin >> c;

                if (cin.fail()) {
                    throw std::invalid_argument("숫자를 입력하세요.");
                }

                if (c < 1 || c > category.size()) {
                    throw std::out_of_range("올바른 카테고리를 선택하세요.");
                }

                string selected_category = category[c - 1];
                cout << "거래처와 금액을 입력하세요: ";
                Transaction new_transaction;
                new_transaction.category = selected_category;
                cin >> new_transaction.trade >> new_transaction.price;

                outputFile << week[day] << endl;
                outputFile << selected_category << " " << new_transaction.trade << " " << new_transaction.price << endl;

                // 입력 에러 처리
                if (cin.fail() || new_transaction.price < 0) {
                    throw std::invalid_argument("올바른 금액을 입력하세요.");
                }

                trade_data[day].push_back(new_transaction);

                cout << "더 입력하시겠습니까? ('X'를 입력하면 입력이 종료되고, 다음 날로 "
                    "넘어갑니다.): ";
                string check2;
                cin >> check2;
                if (check2 == "x" or check2 == "X") {
                    break;
                }
            }
            catch (const std::exception& e) {
                cout << "예외 발생: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        outputFile.close();


        // 거래 내역 수정 및 삭제 옵션 추가
        cout << "수정 또는 삭제하시겠습니까? ('M' or 'D', 입력을 종료하려면 'X'): ";
        string modifyOrDelete;
        cin >> modifyOrDelete;

        if (modifyOrDelete == "M" || modifyOrDelete == "m") {
            // 여기서는 일요일까지 모든 거래 내역 입력이 완료되었으므로
            // 모든 거래 내역에 대한 수정을 진행합니다.
            for (int index = 0; index < trade_data[day].size(); index++) {
                Transaction& selectedTransaction = trade_data[day][index];
                cout << "새로운 거래처와 금액을 입력하세요: ";
                cin >> selectedTransaction.trade >> selectedTransaction.price;

                // 에러 처리
                if (cin.fail() || selectedTransaction.price < 0) {
                    cout << "올바른 금액을 입력하세요." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    // 수정을 실패하더라도 계속 진행할지, 또는 중단할지 선택
                }
            }
        }
        else if (modifyOrDelete == "D" || modifyOrDelete == "d") {
            cout << "삭제할 거래 내역의 번호를 입력하세요: ";
            int deleteIndex;
            cin >> deleteIndex;

            // 입력이 유효한지 확인
            if (cin.fail() || deleteIndex < 1 || deleteIndex > trade_data[day].size()) {
                cout << "올바른 번호를 입력하세요." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                // 삭제 실패하더라도 계속 진행할지, 또는 중단할지 선택
            }
            else {
                // 선택한 거래 내역 삭제
                trade_data[day].erase(trade_data[day].begin() + deleteIndex - 1);
                cout << "거래 내역이 삭제되었습니다." << endl;
            }
        }
        else if (modifyOrDelete == "X" || modifyOrDelete == "x") {
            // 입력 종료
        }
    }
}


void BudgetTracker::RunBudgetTracker() {
    double week_budget;
    cout << "1주일 동안 사용할 예산을 입력하세요: ";
    cin >> week_budget;
    cout << "1주일 동안 계획된 예산은 " << week_budget << "원 입니다" << endl;

    ListBudget();
    vector<string> excluded_categories;
    excluded_categories.push_back("ALL");

    while (true) {
        int c;
        for (int i = 0; i < category.size(); i++) {
            cout << category[i] << " ";
        }
        cout << "무지출 챌린지에서 제외할 카테고리를 선택하세요. (선택을 마치려면 0을 입력하세요): ";
        cin >> c;


        if (cin.fail()) {
            cout << "숫자를 입력하세요." << endl;
            continue;
        }

        if (c == 0) {
            break;
        }

        if (c < 1 || c > category.size()) {
            cout << "올바른 카테고리를 선택하세요." << endl;
            continue;
        }

        excluded_categories.push_back(category[c - 1]);
    }


    double average_consumption = 0;
    vector<double> category_percentage;
    double total_consumption =
        Result(excluded_categories, average_consumption, category_percentage);

    if (week_budget > total_consumption) {
        cout << "남은 예산!" << endl;
        cout << "-----------------------------" << endl;
        cout << week_budget - total_consumption << "원이 남았습니다" << endl;
    }
    else {
        cout << "예산 초과!!" << endl;
        cout << "-----------------------------" << endl;
        cout << total_consumption - week_budget << "원을 초과했습니다" << endl;
    }

    cout << "일 평균 소비금액: " << average_consumption << endl;

    cout << "카테고리별 소비 분석:" << endl;
    for (int i = 0; i < category.size(); i++) {
        cout << category[i] << ": " << category_percentage[i] << "%" << endl;
    }
}


