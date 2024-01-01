# Query Search Master

## Author : Abdullah

## Overview
**Query Search Master** is an advanced search engine designed to efficiently locate words within a corpus. Offering enhanced speed compared to traditional methods like Ctrl+F, this engine can swiftly pinpoint words even if they begin or end within the middle of a word in the corpus.

## Features
- Efficient word search within a corpus of 98 books.
- Capability to search words even if they span across the middle of other words.
- A comprehensive dictionary functionality that counts the occurrences of each word.

## Running the Code

###  Search Functionality
To execute the search functionality, follow these steps:
 Compile the code using the command:
   ```bash
   g++ search.cpp Node.cpp tester_search.cpp -o a.exe
```
  1. Run the compiled program
```bash
./a.exe
```
  2. Modify the word to be searched by adjusting the value at line 63 in `tester_search.cpp`.

### Dictionary functionality
To execute the search functionality, follow these steps:
 Compile the code using the command:
   ```bash
   g++ dict.cpp tester.cpp -o a.exe
```
Run the compiled program
```bash
./a.exe
```
This will initialize the dictionary by inserting all words from vol1 of the corpus and subsequently check their counts.
