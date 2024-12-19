20.7 P4: Hash Table
Overview
This project is about about building a hash table.

Reading Words
You will read words from a given file into your program. Each word consists strictly of the letters A-Z and a-z. Any whitespace, punctuation, digit, etc. will separate words. For example “this!is A&&Word.” would represent four words: this, is, a, and word (note that an empty word is not created from &&). Each word should be converted to lowercase so that only lowercase letters remain.

Inserting into the Hash Table
As you read the words, you should insert each word into a hash table. The word itself is the key value, and each entry in the hash table also needs to store a list of the line numbers where the word appears. When inserting a word that already appears in the hash table, simply add the current line number to the list for the word (there can be duplicate lines).

Counting Collisions
You will also count the number of collisions that occur while inserting words into the hash table. Every probe to a cell that contains a word other than the one being inserted or searched should count as an additional collision, so that inserting a word may have multiple collisions. Probes to empty cells or cells already containing the word do not count as collisions.

Results
Once you have read all of the words, you should output the total number of words read, the number of distinct words, and the total number of collisions that occurred in the hash table. Finally, you will read words from the query file and report the line numbers where the word occurs, and the number of collisions while searching for the word in the table.A

Requirements
Command-Line Arguments
There will be four or five command-line arguments to your program.
The name of the input file
The name of the query file
The size of the hash table
The collision resolution strategy
lp for linear probing
qp for quadratic probing
dh for double hashing
If the strategy is double hashing, the double hash function will be of the form h2(key) = a - (djb2(key) % a), and the integer parameter a will be the fifth command-line argument.
The a parameter for the dh function (only present if the collision resolution strategy is dh)

Hash Function
You must use the djb2 hash function provided in the starting template to turn a string into an unsigned long/uint64_t.
The uint64_t type is an unsigned 64-bit int (the int type is a signed 32-bit int). Be sure to store the return value of djb2 appropriately.
Mapping Function
Use h1(key) = djb2(key) % size to map the string key to an index in the table.
You can store the result of djb2(key) % size as an int, as the result of uint64_t % int will be an int for this project.
Examples where int size = 11;:
uint64_t a = djb2(key); int b = a % size; is good
int a = djb2(key) % size; is good
int a = djb2(key); is bad
dh Mapping Function
h2(key) = a - (djb2(key) % a)
Collision Resolution
Use the collision resolution strategies as defined in the lecture slides.
lp: (h1(key) + j) % size
qp: (h1(key) + j*j) % size
dh: (h1(key) + j*h2(key)) % size
Running Time
Your code must perform insert and find operations in the expected O(1) time.
If your HashTable operations or counting stats calculations are inefficient, then your code will easily timeout on the large test inputs.
You will want to test your code on large input files containing many paragraphs of text. Your code should run within 3 seconds or so for inputs containing 200,000 words with 20,000 unique words, so choose carefully where and how you count total and unique words.
You must define and use classes. One must be named HashTable.
You have the freedom to design the classes (their fields and methods) as you see fit.
You can use the vector and list classes.
Do not include libraries other than iostream, fstream, sstream, iomanip, string, cctype, cmath, vector, and list.
You must format your output as shown in the examples below.
Notes
You have to store the line numbers, so getline() could be useful.
You have to parse words from the line, so the string class could be useful for creating words.
Be sure to not insert "empty" words into the table.
Make sure your code inserts the last word in a line.
Make sure your code inserts a word when the line contains only one word.  
Examples
Example files downloadable below.

$ cat sample1.txt
Cryptography is both the practice and study of the techniques used
to communicate and/or store information or data privately and
securely, without being intercepted by third parties. This can include
processes such as encryption, hashing, and steganography. Until the
modern era, cryptography almost exclusively referred to encryption, but
now cryptography is a broad field with applications in many critical
areas of our lives.

$ cat q1.txt
cryptography
of
lives
hash

$ g++ -std=c++11 p4.cpp
$ ./a.out sample1.txt q1.txt 79 lp
The number of words found in the file was 64
The number of unique words found in the file was 52
The number of collisions was 30

cryptography appears on lines [1,5,6]
The search had 0 collisions

of appears on lines [1,7]
The search had 0 collisions

lives appears on lines [7]
The search had 1 collisions

hash appears on lines []
The search had 2 collisions
$ ./a.out sample1.txt q1.txt 79 qp
The number of words found in the file was 64
The number of unique words found in the file was 52
The number of collisions was 26

cryptography appears on lines [1,5,6]
The search had 0 collisions

of appears on lines [1,7]
The search had 0 collisions

lives appears on lines [7]
The search had 1 collisions

hash appears on lines []
The search had 5 collisions
$ ./a.out sample1.txt q1.txt 79 dh 43
The number of words found in the file was 64
The number of unique words found in the file was 52
The number of collisions was 21

cryptography appears on lines [1,5,6]
The search had 0 collisions

of appears on lines [1,7]
The search had 0 collisions

lives appears on lines [7]
The search had 2 collisions

hash appears on lines []
The search had 1 collisions
Debugging
Example mappings from $ ./a.out sample1.txt q1.txt 79 dh 43
cryptography
h1("cryptography") --> 53
h2("cryptography") --> 40
is
h1("is") --> 30
h2("is") --> 34
Note: these indices are not necessarily where the word is stored in the table, just the result of the mapping functions.
Below is the words stored at each index in the table of size 79:
0: 
1: 
2: referred
3: as
4: without
5: a
6: practice
7: such
8: privately
9: securely
10: 
11: include
12: modern
13: 
14: 
15: 
16: era
17: encryption
18: this
19: 
20: 
21: 
22: 
23: now
24: exclusively
25: in
26: 
27: but
28: broad
29: 
30: is
31: intercepted
32: 
33: 
34: and
35: 
36: store
37: 
38: parties
39: many
40: applications
41: our
42: by
43: 
44: with
45: study
46: 
47: areas
48: data
49: 
50: until
51: field
52: communicate
53: cryptography
54: steganography
55: can
56: lives
57: of
58: 
59: 
60: hashing
61: being
62: used
63: techniques
64: 
65: 
66: critical
67: the
68: 
69: or
70: both
71: 
72: 
73: to
74: information
75: almost
76: 
77: processes
78: third
