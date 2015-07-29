# CIS 22C: Data Abstraction and Structures
This repository contains the team project assigned during De Anza College's CIS22C course for Winter 2015. The source code is entirely in C++, which the course was also based on.

The project itself demonstrates students' knowledge of some of the major data structures learned over the course. Depending on the project variation (all teams have some variation to required data structures to use as well as other general requirements), the range of data structures included are Linked Lists, Stacks, Queues, Binary Trees, BSTs, and Hash Tables.

Our team was assigned a variation that involved using a regular BST as well as a specialized Hash Table. This hash table is a separate-chaining type, meaning it resolves collisions using Linked Lists. The specialization of the hash table is in the type of linked lists it uses. We implemented them to be doubly-linked, self-adjusting lists. The doubly-linked functionality means that the nodes can be traversed both backwards and forwards. The self-adjusting functionality is the main feature of the specialization for this hash table implementation; it allows for the linked list to push nodes with higher access times towards the front of the list while nodes with lower access times are naturally pushed to the end of the list. This specialization increases the hash table's practical access time.

## Background (from project instructions)
As a team of two to five programmers, you will assist in the implementation of a data processing system. The application data are of your own design with the requirement that each record in the system must contain a **unique key** and at least **three** attributes (non-key fields). Each team will choose one out of three variations of the same project.

## Basic Requirements (from project instructions)
The system's data structures is to contain a hashed list array of at least 25 records read from a file. As the records are read, they are placed in dynamic memory. Application data must contain a unique primary key (it must be stored as a string) and at least three non-key fields. The key of each record and its memory location (address) are then inserted into a hashed array. Collisions will be resolved using open addressing, linked lists, or buckets. In addition to the hashed array, to provide sequential processing there is to be a binary search tree that contains the key for each record and its location in dynamic memory. The BST key does not necessarily need to be the same as the hashed list key; that is, it may be a secondary key. Choose any hashing function that is appropriate for your data.

Processing is to be menu driven with the following options:
- Add new data
- Delete Data
- Find and display one element using the primary key; if a secondary key is being used, allow a search by that key too
- List data in hash table sequence
- List data in key sequence (sorted)
- Print indented tree
- Write data to a file
- Efficiency report
- Quit

At the end of the program, the file is to be automatically written to a file. This is in addition to the menu write file option. The file names do not have to be the same as the input file name, but the file format must be the same as the input file format so that it can be read back into the program.

## Team Members:
- Wolfgang C. Strack - **lead**, Member 1
- Louis Christopher - Member 2
- Andrew Wang - Member 3
