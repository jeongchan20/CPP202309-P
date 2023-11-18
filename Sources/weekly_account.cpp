#include <algorithm>
#include <iostream>
#include <limits>  // numeric_limits 사용
#include <string>
#include <vector>
using namespace std;

const int WEEK_DAY = 7;

struct Transaction {
  string category;
  string trade;
  double price;
};

string week[] = {"월", "화", "수", "목", "금", "토", "일"};
vector<string> category = {
    "1.식비",       "2.카페",       "3.술/유흥",    "4.생활",      "5.쇼핑",
    "6.미용",       "7.교통",       "8.주거/통신",  "9.의료/건강", "10.금융",
    "11.문화/여가", "12.여행/숙박", "13.교육/학습", "14.경조/선물"};

vector<Transaction> trade_data[WEEK_DAY];
void DisplayTransactionDetails(int dayIndex);
double CalculateAverageConsumption();
vector<double> AnalyzeCategoryPercentage(double total_consumption);
double Result(const vector<string>& excluded_categories,
              double& average_consumption, vector<double>& category_percentage);
void List_Budget();

int main() {
  double week_budget;
  cout << "1주일 동안 사용할 예산을 입력하세요: ";
  cin >> week_budget;
  cout << "1주일 동안 계획된 예산은 " << week_budget << "원 입니다" << endl;

  List_Budget();
  vector<string> excluded_categories;
  cout << "무지출 챌린지 에서 제외할 카테고리를 선택하세요. (선택을 마치려면 "
          "0을 입력하세요)"
       << endl;
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

  double average_consumption = 0;
  vector<double> category_percentage;
  double total_consumption =
      Result(excluded_categories, average_consumption, category_percentage);

  if (week_budget > total_consumption) {
    cout << "남은 예산!" << endl;
    cout << "-----------------------------" << endl;
    cout << week_budget - total_consumption << "원이 남았습니다" << endl;
  } else {
    cout << "예산 초과!!" << endl;
    cout << "-----------------------------" << endl;
    cout << total_consumption - week_budget << "원을 초과했습니다" << endl;
  }

  cout << "일 평균 소비금액: " << average_consumption << endl;

  cout << "카테고리별 소비 분석:" << endl;
  for (int i = 0; i < category.size(); i++) {
    cout << category[i] << ": " << category_percentage[i] << "%" << endl;
  }

  return 0;
}

void DisplayTransactionDetails(int dayIndex) {
  cout << week[dayIndex] << "요일 거래 내역:" << endl;

  // 거래 내역이 없는 경우 처리
  if (trade_data[dayIndex].empty()) {
    cout << "거래 내역이 없습니다." << endl;
  } else {
    for (const auto& transaction : trade_data[dayIndex]) {
      cout << "카테고리: " << transaction.category
           << ", 거래처: " << transaction.trade
           << ", 금액: " << transaction.price << endl;
    }
  }
}

double CalculateAverageConsumption() {
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

vector<double> AnalyzeCategoryPercentage(double total_consumption) {
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

double Result(const vector<string>& excluded_categories,
              double& average_consumption,
              vector<double>& category_percentage) {
  int no_expenditure = 0;
  double total_consumption = 0;
  double max_price = numeric_limits<double>::min();  // 최대값 초기화

  for (int i = 0; i < WEEK_DAY; i++) {
    DisplayTransactionDetails(i);

    // 거래 내역이 없는 경우 처리
    if (trade_data[i].empty()) {
      no_expenditure++;
    } else {
      bool allCategoriesNoExpenditure = true;

      for (const auto& transaction : trade_data[i]) {
        if (find(excluded_categories.begin(), excluded_categories.end(),
                 transaction.category) != excluded_categories.end()) {
          allCategoriesNoExpenditure = false;
        }

        total_consumption += transaction.price;
        if (transaction.price > max_price) {
          max_price = transaction.price;
        }
      }

      if (allCategoriesNoExpenditure) {
        no_expenditure++;
      }
    }
  }

  // 평균 소비 비교
  average_consumption = CalculateAverageConsumption();

  // 카테고리별 소비 분석
  category_percentage = AnalyzeCategoryPercentage(total_consumption);

  cout << "무지출 일수는 " << no_expenditure << " 입니다" << endl;
  cout << "총 소비금액는 " << total_consumption << "원 입니다" << endl;
  cout << "최대 소비금액은 " << max_price << "원 입니다" << endl;
  return total_consumption;
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

      cout << "더 입력하시겠습니까? ('X'를 입력하면 입력이 종료되고, 다음 날로 "
              "넘어갑니다.): ";
      string check2;
      cin >> check2;
      if (check2 == "x" or check2 == "X") {
        break;
      }
    }
  }
}
