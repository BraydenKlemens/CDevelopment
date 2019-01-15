
Brayden Klemens
1000487
October 15, 2018

Program in which linked lists are used to maintain the data structure for acar rental company. The program allows several types of transactions to be applied to the datastructure in order to keep the lists up-to-date.

PROGRAM 1:

make
./q1

Note:
- The program does not need any command line arguments, everything is handeled with user input after while the program is running
- The maximum length to enter for a plate number is 7 charcters
- Return dates follow yyyymmdd entered as an int
- Mileage should be entered as an int

NOTE** expect output for when input is invalid or doesnt exist in the list

SAMPLE OUTPUT:

- this will be printed at the start of the program and after each transaction

When the program starts, enter an integer transaction code to do one of the functions:

Enter a transaction code to perform the coresponsing function:
1. add a new car to the available for rent list,
2. add a returned car to the available-for-rent list,
3. add a returned car to the repair list,
4. transfer a car from the repair list to the available-for-rent list,
5. rent the first available car,
6. print all the lists,
7. quit.

OPTION 6, before any transactions you will see:

Available for rent list: 
Plate: AVZT434, Mileage: 10, ReturnDate: 0
Plate: AVZT435, Mileage: 20, ReturnDate: 0
Plate: AVZT436, Mileage: 30, ReturnDate: 0
Plate: AVZT437, Mileage: 40, ReturnDate: 0
Plate: AVZT438, Mileage: 50, ReturnDate: 0
Rented list: 
Plate: BRXT434, Mileage: 0, ReturnDate: 20180304
Plate: BRXT435, Mileage: 0, ReturnDate: 20180405
Plate: BRXT436, Mileage: 0, ReturnDate: 20180506
Plate: BRXT437, Mileage: 0, ReturnDate: 20180607
Plate: BRXT438, Mileage: 0, ReturnDate: 20180708
In-repair list: 
Plate: RLYX436, Mileage: 0, ReturnDate: 0
Plate: RLYX435, Mileage: 0, ReturnDate: 0
Plate: RLYX434, Mileage: 0, ReturnDate: 0
Plate: RLYX436, Mileage: 0, ReturnDate: 0
Plate: RLYX435, Mileage: 0, ReturnDate: 0

- this is the data read in from the text file
- each line underneath the heading represents a node in the list and its coressponding data

OPTION 1, enter input when prompted:

Enter a valid plate number: 
XXXX555
Enter a mileage: 
50
adding new car to available for rent list...

OPTION 2, 3 enter a plate number of an existing rented car:

Enter a valid plate number: 
BRXT434
Enter a mileage: 
50
Adding a returned car to the available-for-rent list...
Fee for rent: $40.00

OPTION 4 , enter plate Number of existing in-repair car: 

Enter a plate Number: 
RLYX436
Transfering a car from the repair list to the available-for-rent list...

OPTION 5:

Enter an expected return date yyyymmdd: 
20180203
renting the first available car...

OPTION 7:

- Quits program automatically

PROGRAM 2:

program that evaluates postfix expressions composed of single digits and binary operators of +, −, ,and /, for addition, subtraction, multiplication, and devision respectively.

- Takes commmand line argument 

EXAMPLE: 
make
./q2 12+12++
result = 6.00










