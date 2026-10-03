from datetime import datetime
from collections import defaultdict

expenses = []
budgets = {}
DATE_FMT = "%Y-%m-%d"


def read_date(prompt):
    while True:
        value = input(prompt).strip()
        try:
            datetime.strptime(value, DATE_FMT)
            return value
        except ValueError:
            print("Invalid date. Use YYYY-MM-DD.")


def read_amount(prompt):
    while True:
        try:
            value = float(input(prompt).strip())
            if value <= 0:
                raise ValueError
            return value
        except ValueError:
            print("Invalid amount. Enter a number greater than 0.")


def add_expense():
    print("\nADD EXPENSE")
    expense = {
        "date": read_date("Date (YYYY-MM-DD): "),
        "amount": read_amount("Amount: $"),
        "category": input("Category: ").strip().title() or "Other",
        "description": input("Description: ").strip() or "No description",
    }
    expenses.append(expense)
    print("Expense added successfully.")


def display_expenses(records):
    if not records:
        print("No matching expenses found.")
        return
    print(f"{'Date':<12}{'Category':<16}{'Amount':>10}  Description")
    print("-" * 62)
    for e in records:
        print(f"{e['date']:<12}{e['category']:<16}${e['amount']:>8.2f}  {e['description']}")


def view_expenses():
    print("\nALL EXPENSES")
    display_expenses(expenses)


def search_or_filter():
    print("\nSEARCH / FILTER")
    print("1. Description keyword\n2. Category\n3. Date range")
    choice = input("Select: ").strip()
    if choice == "1":
        word = input("Keyword: ").strip().lower()
        display_expenses([e for e in expenses if word in e["description"].lower()])
    elif choice == "2":
        cat = input("Category: ").strip().lower()
        display_expenses([e for e in expenses if e["category"].lower() == cat])
    elif choice == "3":
        start = read_date("Start date (YYYY-MM-DD): ")
        end = read_date("End date (YYYY-MM-DD): ")
        if start > end:
            start, end = end, start
            print("Dates were reversed, so SpendScope corrected the range.")
        display_expenses([e for e in expenses if start <= e["date"] <= end])
    else:
        print("Invalid filter option.")


def set_budget():
    category = input("Category: ").strip().title()
    budgets[category] = read_amount("Budget limit: $")
    print(f"Budget saved for {category}.")


def show_summary():
    print("\nSPENDING SUMMARY")
    if not expenses:
        print("No expenses available for summary.")
        return

    totals = defaultdict(float)
    overall = 0.0
    for e in expenses:
        overall += e["amount"]
        totals[e["category"]] += e["amount"]

    print(f"Overall total: ${overall:.2f}")
    for category in sorted(totals):
        spent = totals[category]
        print(f"{category}: ${spent:.2f}", end="")
        if category in budgets:
            limit = budgets[category]
            remaining = limit - spent
            ratio = spent / limit
            status = "OVER BUDGET" if remaining < 0 else ("CLOSE TO LIMIT" if ratio >= 0.80 else "WITHIN BUDGET")
            print(f" | Budget ${limit:.2f} | Remaining ${remaining:.2f} | {status}", end="")
        print()

    top = max(totals, key=totals.get)
    print(f"Highest-spending category: {top} (${totals[top]:.2f})")


def main():
    menu = """\nSPENDSCOPE MAIN MENU
1. Add Expense
2. View All Expenses
3. Search or Filter Expenses
4. Set Category Budget
5. View Spending Summary
6. Exit"""
    actions = {"1": add_expense, "2": view_expenses, "3": search_or_filter,
               "4": set_budget, "5": show_summary}
    while True:
        print(menu)
        choice = input("Choose an option: ").strip()
        if choice == "6":
            print("Thank you for using SpendScope.")
            break
        action = actions.get(choice)
        if action:
            action()
        else:
            print("Invalid menu choice. Please select 1-6.")


if __name__ == "__main__":
    main()
