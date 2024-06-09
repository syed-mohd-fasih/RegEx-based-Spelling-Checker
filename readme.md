# RegEx-Based Spelling Checker

## Project Overview

This project is a RegEx-Based Spelling Checker developed for a Theory of Computation course. The system is implemented in C++ and uses regular expressions to check the spelling of words. It includes a batch check option that allows for checking multiple files at once. The dictionary is stored in a text file and can be easily updated.

## Table of Contents

1. [Introduction](#introduction)
2. [Setup and Requirements](#setup-and-requirements)
3. [Code Structure](#code-structure)
4. [Implementation Details](#implementation-details)
5. [Running the Code](#running-the-code)
6. [Example Usage](#example-usage)
7. [Conclusion](#conclusion)

## Introduction

The RegEx-Based Spelling Checker uses regular expressions to verify the spelling of words against a predefined dictionary. It supports both single word checks and batch checks, making it versatile for different use cases. The project demonstrates the application of regular expressions in a practical context and provides a simple yet effective tool for spelling verification.

## Setup and Requirements

### Prerequisites

- C++ compiler (e.g., GCC)
- Basic knowledge of C++ and regular expressions

### Installation

1. Ensure a C++ compiler is installed on your system. You can install GCC on Unix-based systems using:
    ```sh
    sudo apt-get install g++
    ```

2. Clone this repository to your local machine:
    ```sh
    git clone https://github.com/your-repo/regex-spelling-checker.git
    cd regex-spelling-checker
    ```

## Code Structure

The project directory is structured as follows:

```
regex-spelling-checker/
│
├── src/
│   └── main.cpp
│
├── dictionary/
│   └── dictionary.txt
│
├── batch_input/
│   └── <file_name>.txt
│
├── batch_result/
│   └── batch_result.txt
│
├── README.md
```

### Files Description

- **src/main.cpp**: The main source file containing the implementation of the spelling checker.
- **dictionary/dictionary.txt**: The dictionary file containing the list of valid words.
- **batch_input/**: Directory containing file for batch spell checking.
- **batch_result/**: Directory where the results of batch spell checking are saved.

## Implementation Details

### Regular Expressions

The spelling checker uses regular expressions to match words against the entries in the dictionary. This approach allows for flexible and efficient checking of word spelling.

### Features

- **Single Word Check**: Check the spelling of a single word by comparing it against the dictionary.
- **Batch Check**: Check the spelling of words in multiple files and save the results in a specified output file.

## Running the Code

1. Compile the code using the provided Makefile:
    ```sh
    g++ main.cpp -o regex_spelling_checker
    ```

2. Run the executable:
    ```sh
    ./regex_spelling_checker
    ```

## Example Usage

1. The program will prompt for input options:
    - Check single word
    - Batch check

2. For single word check, input the word when prompted.

3. For batch check, ensure the input file is placed in the `batch_input` directory. The results will be saved in the `batch_result` directory.

## Conclusion

The RegEx-Based Spelling Checker demonstrates the practical application of regular expressions in a C++ project. This project serves as an example of using theoretical concepts from the Theory of Computation course in real-world applications.