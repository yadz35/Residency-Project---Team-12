#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <cctype>

using namespace std;

struct Expense {
    string date;
    double amount;
    string category;
    string description;
};

vector<Expense> expenses;
map<string, double> budgets;

string lowerText(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return static_cast<char>(tolower(c)); });
    return s;
}

string titleText(string s) {
    if (s.empty()) return "Other";
    s = lowerText(s);
    s[0] = static_cast<char>(toupper(static_cast<unsigned char>(s[0])));
    return s;
}

bool validDate(const string& value) {
    if (value.size() != 10 || value[4] != '-' || value[7] != '-') return false;
    for (size_t i = 0; i < value.size(); ++i)
        if (i != 4 && i != 7 && !isdigit(static_cast<unsigned char>(value[i]))) return false;
    int y = stoi(value.substr(0,4)), m = stoi(value.substr(5,2)), d = stoi(value.substr(8,2));
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    if (leap) days[1] = 29;
    return d <= days[m-1];
}

string readDate(const string& prompt) {
    string value;
    while (true) {
        cout << prompt; getline(cin, value);
        if (validDate(value)) return value;
        cout << "Invalid date. Use YYYY-MM-DD.\n";
    }
}

double readAmount(const string& prompt) {
    string line; double value; char extra;
    while (true) {
        cout << prompt; getline(cin, line);
        stringstream ss(line);
        if ((ss >> value) && value > 0 && !(ss >> extra)) return value;
        cout << "Invalid amount. Enter a number greater than 0.\n";
    }
}

void displayExpenses(const vector<Expense>& records) {
    if (records.empty()) { cout << "No matching expenses found.\n"; return; }
    cout << left << setw(12) << "Date" << setw(16) << "Category" << right << setw(10) << "Amount" << "  Description\n";
    cout << string(62, '-') << "\n";
    for (const auto& e : records)
        cout << left << setw(12) << e.date << setw(16) << e.category << right << "$" << setw(8) << fixed << setprecision(2) << e.amount << "  " << e.description << "\n";
}

void addExpense() {
    Expense e;
    cout << "\nADD EXPENSE\n";
    e.date = readDate("Date (YYYY-MM-DD): ");
    e.amount = readAmount("Amount: $");
    cout << "Category: "; getline(cin, e.category); e.category = titleText(e.category);
    cout << "Description: "; getline(cin, e.description); if (e.description.empty()) e.description = "No description";
    expenses.push_back(e);
    cout << "Expense added successfully.\n";
}

void viewExpenses() { cout << "\nALL EXPENSES\n"; displayExpenses(expenses); }

void searchOrFilter() {
    string choice, text, start, end;
    vector<Expense> matches;
    cout << "\nSEARCH / FILTER\n1. Description keyword\n2. Category\n3. Date range\nSelect: ";
    getline(cin, choice);
    if (choice == "1") {
        cout << "Keyword: "; getline(cin, text); text = lowerText(text);
        copy_if(expenses.begin(), expenses.end(), back_inserter(matches), [&](const Expense& e){ return lowerText(e.description).find(text) != string::npos; });
    } else if (choice == "2") {
        cout << "Category: "; getline(cin, text); text = lowerText(text);
        copy_if(expenses.begin(), expenses.end(), back_inserter(matches), [&](const Expense& e){ return lowerText(e.category) == text; });
    } else if (choice == "3") {
        start = readDate("Start date (YYYY-MM-DD): "); end = readDate("End date (YYYY-MM-DD): ");
        if (start > end) { swap(start, end); cout << "Dates were reversed, so SpendScope corrected the range.\n"; }
        copy_if(expenses.begin(), expenses.end(), back_inserter(matches), [&](const Expense& e){ return e.date >= start && e.date <= end; });
    } else { cout << "Invalid filter option.\n"; return; }
    displayExpenses(matches);
}

void setBudget() {
    string category; cout << "Category: "; getline(cin, category); category = titleText(category);
    budgets[category] = readAmount("Budget limit: $");
    cout << "Budget saved for " << category << ".\n";
}

void showSummary() {
    if (expenses.empty()) { cout << "No expenses available for summary.\n"; return; }
    map<string,double> totals; double overall = 0;
    for (const auto& e : expenses) { overall += e.amount; totals[e.category] += e.amount; }
    cout << "\nSPENDING SUMMARY\nOverall total: $" << fixed << setprecision(2) << overall << "\n";
    string top; double topAmount = -1;
    for (const auto& [category, spent] : totals) {
        cout << category << ": $" << spent;
        auto it = budgets.find(category);
        if (it != budgets.end()) {
            double limit = it->second, remaining = limit - spent, ratio = spent / limit;
            string status = remaining < 0 ? "OVER BUDGET" : (ratio >= .80 ? "CLOSE TO LIMIT" : "WITHIN BUDGET");
            cout << " | Budget $" << limit << " | Remaining $" << remaining << " | " << status;
        }
        cout << "\n";
        if (spent > topAmount) { topAmount = spent; top = category; }
    }
    cout << "Highest-spending category: " << top << " ($" << topAmount << ")\n";
}

int main() {
    string choice;
    while (true) {
        cout << "\nSPENDSCOPE MAIN MENU\n1. Add Expense\n2. View All Expenses\n3. Search or Filter Expenses\n4. Set Category Budget\n5. View Spending Summary\n6. Exit\nChoose an option: ";
        getline(cin, choice);
        if (choice == "1") addExpense();
        else if (choice == "2") viewExpenses();
        else if (choice == "3") searchOrFilter();
        else if (choice == "4") setBudget();
        else if (choice == "5") showSummary();
        else if (choice == "6") { cout << "Thank you for using SpendScope.\n"; break; }
        else cout << "Invalid menu choice. Please select 1-6.\n";
    }
}
