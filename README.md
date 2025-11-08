# Reverse Polish Notation Converter

This project implements a **Reverse Polish Notation (RPN)** converter in C++, which reads infix mathematical expressions from a file and converts them into postfix (RPN) form using the **Shunting Yard Algorithm**. It prints detailed step-by-step output showing token processing, stack operations, and the final postfix expression.

---

## 🧩 Project Structure

```
.
├── main.cpp
├── polishReverseForm.cpp
├── polishReverseForm.h
├── stackCustom.cpp
├── stackCustom.h
├── expressions.txt
└── README.md
```

### File Descriptions

| File | Description |
|------|--------------|
| **main.cpp** | Entry point of the program. Creates an instance of `polishReverseForm` and runs it. |
| **polishReverseForm.h / .cpp** | Core logic for parsing expressions, tokenizing, validating, and converting to Reverse Polish form. |
| **stackCustom.h / .cpp** | A template-based stack implementation used by the converter. |
| **expressions.txt** | Sample input file containing expressions to convert. |

---

## How It Works

1. The program prompts for an **input filename** (e.g., `expressions.txt`).
2. It reads each line from the file as a separate infix expression.
3. Each expression is validated and split into tokens.
4. The program applies operator precedence and associativity rules to produce a postfix (RPN) expression.
5. It prints a **table of operations** for each token showing:
   - Token being processed  
   - Action taken (push, pop, etc.)  
   - Stack contents  
   - Current output  

---

## Example

### Input (`expressions.txt`)
```
a+b
(a+b)*c
add(1,b,c,g)+ww=12
```

### Console Output (simplified)
```
Please type name of input file: expressions.txt

Input expression: (a+b)*c

Token               Action              Stack               Output

a                   Push to output                           a
+                   Push to stack        +                   a
b                   Push to output       +                   a b
)                   Pop from stack                           a b +
*                   Push to stack        *                   a b +
c                   Push to output       *                   a b + c

Output: a b + c *
```

---

## 🧮 Supported Features

- Basic arithmetic operators: `+`, `-`, `*`, `/`, `=`
- Parentheses `(` `)`
- Function calls such as `add(x,y)` or `pow(a,b)`
- Variable and numeric tokens
- Expression validation (detects invalid sequences like `++` or operators at ends)

---

## 🧠 Implementation Details

- Operator precedence and associativity are managed via `std::map` objects.
- Functions are detected as identifiers followed by parentheses (e.g., `func()`).
- A custom stack (`stackCustom<T>`) template is used for internal operations.
- Output is displayed in a structured table for clarity.

---

## 🖥️ Compilation and Execution

### Using g++

```bash
g++ -std=c++17 main.cpp polishReverseForm.cpp stackCustom.cpp -o rpn_converter
```

### Run the program

```bash
./rpn_converter
```

When prompted, type:
```
expressions.txt
```

---

## 🧾 Sample Input File

`expressions.txt` is provided and includes examples like:
```
a+b
xy+y=b
(a+b)*c
a+pow(x,y)
add(1,b,c,g)+ww=12
```

---

## 🧑‍💻 Author Notes

This program is an educational implementation of expression parsing and conversion, ideal for learning:
- Stack-based algorithms
- Tokenization and parsing in C++
- Operator precedence handling
