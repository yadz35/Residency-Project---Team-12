# Residency-Project---Team-12
SPENDSCOPE - DELIVERABLE 2
Python and C++ Core Functionality Implementation

FILES
1. spendscope.py - Complete Python implementation
2. main.cpp - Complete C++ implementation
3. SpendScope_Deliverable_2_Report.docx - Submission-ready report
4. sample_input.txt - Test data for both programs
5. test_results.txt - Compilation and functional test results

PYTHON REQUIREMENTS
- Python 3.x
- No third-party packages are required

RUN PYTHON
python spendscope.py

CHECK PYTHON SYNTAX
python -m py_compile spendscope.py

C++ REQUIREMENTS
- A compiler with C++17 support, such as g++

COMPILE C++
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o spendscope_cpp

RUN C++ ON LINUX OR MACOS
./spendscope_cpp

RUN C++ ON WINDOWS
spendscope_cpp.exe

AUTOMATED SAMPLE TEST - PYTHON
python spendscope.py < sample_input.txt

AUTOMATED SAMPLE TEST - C++
./spendscope_cpp < sample_input.txt

CORE FEATURES
- Add an expense
- View all expenses
- Search by description
- Filter by category
- Filter by date range
- Set category budgets
- View overall and category totals
- Show budget status
- Identify the highest-spending category
- Validate dates, amounts, and menu selections

EXPECTED SAMPLE RESULTS
- Overall total: $115.50
- Food total: $25.50
- Travel total: $90.00
- Food budget remaining: $74.50
- Highest-spending category: Travel ($90.00)