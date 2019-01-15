Brayden Klemens
1000487
11/05/2018
Assignment 3

C program that takes as input a fully parenthesized, arithmetic expressionof binary operators +,−, , /, and converts the expression into a binary expression tree.

QUESTION 1:

- Takes input from the command line
- Arithmetic expression command line input should be fully parenthesized with “\(left operator right\)” with back slashes before parenthesis.
- User option is an integer from 1 - 7, if not ann option you will be prompted to choose again

TO COMPILE:

Note - can be any expression this is an example expression

make
./q1 \(\(\(1.56+4.26\)*\(x1-2.23\)\)/x2\)

TO RECOMPILE:
make clean
make

SAMPLE OUTPUT:

- Upon program start up:
- if you don’t choose a number you will be prompted to re-choose
- re printed after completing a case.

1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit

CASE 1: 

- each node that is an operator is printed with its left and right nodes for visualization.
-variables display only 1 decimal point as per the assignment description.

Parent: /, Left: *, Right: x2: 0.0
Parent: *, Left: +, Right: -
Parent: +, Left: 1.56, Right: 4.26
Parent: -, Left: x1: 0.0, Right: 2.23

CASE 2:

-pre order has spaces to help distinguish between floating values
/ * + 1.56 4.26 - x1 2.23 x2

CASE 3:

(((1.56+4.26)*(x1-2.23))/x2)

CASE 4:

-post order has spaces to help distinguish between floating values
1.56 4.26 + x1 2.23 - * x2 /

CASE 5:

-If entered a variable that doesn’t exist, nothing in the tree changes.
-New value can be any floating decimal number
-prompted to enter the variable to change then the new value:

Enter the variable to change: x1
Enter the new value: 2.5

CASE 6:

- displays the result value
- if a divide by zero, the calculation is set to 0 and this is printed:
Divide by zero not possible! (return 0) (exit)
result = 0.00

CASE 7:
-exit program with exit(0)

QUESTION 2:

reads 200 2-digit integers from text file “f.dat” and stores theintegers in an array of 20 rows and 10 columns. The program treats each row of the array asan object, with the sum of the first three integers being the key, and the other seven integersbeing the information content. The program then creates a heap with a node containing anobject. Applies the parental node downheap algorithm in the array representation. The program finally displays the heap as a20 × 10 array, a row for an object.

- Takes a file name as the first command line argument 
-use f.dat as an example

TO COMPILE:
make
./q2 f.dat

OUTPUT:

-Displays the heap created by the DownHeap algorithm:
- from sample f.dat

25 12 17 82 52 53 5 3 68 64 
16 14 27 99 29 99 79 45 59 19 
25 41 11 88 15 39 88 69 31 49 
50 9 6 44 59 87 32 36 36 46 
12 0 68 68 49 68 74 32 9 30 
43 27 20 59 4 84 10 42 43 2 
44 27 68 96 70 98 85 13 25 47 
3 37 97 53 36 54 69 68 38 43 
9 83 22 90 74 56 64 75 67 55 
49 17 44 32 33 54 60 33 51 87 
99 37 50 93 57 6 29 91 92 39 
81 14 42 21 9 69 5 30 20 91 
96 89 75 0 63 24 54 20 20 24 
3 60 76 23 14 81 82 0 38 4 
83 82 43 11 21 4 8 97 93 14 
51 90 37 86 42 44 48 64 41 1 
88 56 59 88 39 30 44 59 49 72 
41 62 82 46 69 42 74 68 79 28 
41 82 53 40 29 84 24 61 87 20 
81 30 16 65 40 39 44 49 32 60


