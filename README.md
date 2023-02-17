# AlgorithmsAndDataStructures
 Projects from Algorithms And Data Structures course on IT in Gdansk University Of Technology.

EXPLENATIONS OF THE PROJECTS

Hash table:

    Count the number of occurences of each word in the text given in the input. Store these numbers in a hash table: the word should be interpreted as a key (type string), and the number of occurences as a value (type int). Use the method of collision resolving suggested by the teacher.

    You can use an array of fixed, constant size, but allocate it dynamically! The maximum number of elements in a test is 100000. Choose the appropriate size of the array (check lecture slides).

    Input
    The text (any number of words with only lower case letters, separated by spaces or new line characters). The words starting with character '?' and '-', and the word "q" should be interpreted as commands:
    '?': print the number of occurences of the given word on the screen,
    '-': remove the information about the given word from your hash table (from this point you should start counting the occurences of this word from 0),
    'q': exit.

    Output
    For every word starting with '?': print a line with the number of occurences (to this point) of this word in the text.

Heap:

    Implement a min heap for the following data:
    date in the following format: dd-mm-yyyy
    name one word
    The heap should act as a priority queue for the instances of the given structure. Initially, all instances should be stored in the heap with regard to the alphabetical order of names (i.e. the instance with the first name in alphabetical order should be on top). Your program should support the following operations:

    + n v1 ...vn
    add n individuals (format: <date> <name>) to the priority queue (heap). Initially, the first name in alphabetical order is on the top;
    - m
    remove m elements from the top of the heap and print their data on the screen (format: <date> <name> e.g. 19-04-2022 Alan);
    p
    print all elements of the heap in the order in which they are stored in an array;
    r
    rearrange the order of the queue such that the earliest date is on top. Repeats of this operation alternate between the two orders;
    q
    exit the program (and deallocate memory).
    Additional remarks: If both children are equal the child of the lesser index is swapped. It is sufficient to implement operations '+' and 'p' to pass tests 1 and 2. The next two tests include also operation '-'. The remaining tests use all operations. Test 0 is given below.

    Input
    A sequence of instructions in the format presented above. The last instruction is q.

    Output
    Result of instructions '-' and 'p'.

List:
    A basic object oriented implementation of a list data structure.

NMK Solver:
    An algorithm that output with player wins game of TicTacToe based on input game state and min max algorithm.

Partitions:
    A partition of n is a representation of this number as a sum of positive integers: n=n1+n2+...+nr such that n1≥n2≥...≥nr. The numbers n1,n2,...,nr are called parts.

    The partition 19=5+3+3+2+2+2+2 can be written as 53224, while 19=5+2+2+2+2+2+2+2 can be written as 527.
    Hence the upper indices are 124 and 107, thus 5+3+3+2+2+2+2 is larger than 5+2+2+2+2+2+2+2, 
    since 124 is larger than 107.

    Input
    In the first line: a number of the rest lines
    Then, separated by spaces: n and k

    Output
    Partitions separated by +. If there is no partition, then write nothing.