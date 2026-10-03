# Residency-Project---Team-12
# SpendScope

> **Deliverable 2 — Python and C++ Core Functionality Implementation**

SpendScope is a command-line expense tracker implemented in both **Python** and **C++**. It supports expense entry, searching, filtering, budget tracking, category summaries, and input validation.

## Project Files

| File | Purpose |
| --- | --- |
| `spendscope.py` | Complete Python implementation |
| `main.cpp` | Complete C++ implementation |
| `SpendScope_Deliverable_2_Report.docx` | Submission-ready project report |
| `sample_input.txt` | Test data for both implementations |
| `test_results.txt` | Compilation and functional test results |

## Features

- [x] Add an expense
- [x] View all expenses
- [x] Search expenses by description
- [x] Filter expenses by category
- [x] Filter expenses by date range
- [x] Set budgets for individual categories
- [x] View overall and category totals
- [x] Display budget status
- [x] Identify the highest-spending category
- [x] Validate dates, amounts, and menu selections

## Python Setup

### Requirements

- Python 3.x
- No third-party packages required

### Run the Program

```bash
python spendscope.py
```

### Check the Python Syntax

```bash
python -m py_compile spendscope.py
```

### Run the Automated Sample Test

```bash
python spendscope.py < sample_input.txt
```

## C++ Setup

### Requirements

- A compiler with C++17 support, such as `g++`

### Compile the Program

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o spendscope_cpp
```

### Run on Linux or macOS

```bash
./spendscope_cpp
```

### Run on Windows

```powershell
.\spendscope_cpp.exe
```

### Run the Automated Sample Test

#### Linux or macOS

```bash
./spendscope_cpp < sample_input.txt
```

#### Windows PowerShell

```powershell
Get-Content sample_input.txt | .\spendscope_cpp.exe
```

## Expected Sample Results

| Measurement | Expected Result |
| --- | ---: |
| Overall total | **$115.50** |
| Food total | **$25.50** |
| Travel total | **$90.00** |
| Food budget remaining | **$74.50** |
| Highest-spending category | **Travel ($90.00)** |

## Verification

After running either implementation with `sample_input.txt`, compare the program output with the expected values above. Detailed compilation and functional test results are available in `test_results.txt`.