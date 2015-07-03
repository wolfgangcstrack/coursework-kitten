# CIS29: Advanced C++ - All Labs
This repository contains all the labs assigned during De Anza College's CIS29 course for Spring 2015. All labs were
created using Visual Studio Express 2013 for Windows Desktop. Each lab should contain its own README.md but the
following descriptions are summaries of what each lab is about:

## <a href="./Lab-0">Lab 0</a>
For this lab, we were given three different assignment descriptions and were asked to choose one. The lab itself
was meant to test our prior knowledge of C++ at the beginning of the quarter. Of the three, I chose the last variant
of the lab, which involved designing a Date class that could have arithmetic operations performed on it.

I.E.:

```
01/01/2015 + 1D = 01/02/2015<br/>
01/01/2015 + 1M = 02/01/2015<br/>
01/01/2015 + 1Y = 01/01/2016<br/>
```

## <a href="./Lab-1">Lab 1</a>
This lab involved designing a program that could decrypt Morse Code.

The use of C++ bitsets and vectors in this lab was required.

## <a href="./Lab-2">Lab 2</a>
This lab involved designing an XML parser that uses the C++ regex functionality. Since a fully-functional, dynamic
XML parser would take too much time, the basic design of this parser involves creating a class for holding specific
XML nodes that need to be parsed. Knowledge of the data being parsed is required.

For example:

If you have the following XML node `<example>`:

```
<example>
  <x>1000\</x>
  <y>2000\</y>
</example>
```

Then the class `Example`, which extends `XmlNode`, is built for the XML parser to use.
Basic example:
```
class Example : public XmlNode
{
private:
  int x, y;
public:
  Example();
  int getX();
  int getY();
  void setX(int newX);
  void setY(int newY);
  
  // used by the XML parser
  void readData(const std::string &data) = 0; // pure virtual method inherited from XmlNode (in my design anyway)
};
```

## <a href="./Lab-3">Lab 3</a>
This lab involved using Lab 2's XML parser to parse `<command>` nodes given in a data file. These commands are then
'executed' by the `Robot` class. We are required to use threading to allow for multiple robots to carry out their
respective commands asynchronously.

Again, the use of C++ threading in this lab was required.

## <a href="./Lab-4">Lab 4</a>
This lab involved designing a graph class where vertices of the graph are represented in coordinates. The coordinates
used to test our coordinate graph class must be parsed using the XML parser we built in our previous lab. Also, we were
required to pick one of three algorithms that produces a minimal spanning tree from a graph and were tasked with
implementing that algorithm into our designed graph class.

Also, the use of lambda expressions and class inheritance in this lab was required.

## <a href="./Lab-5">Lab 5</a>
This lab required for us to design a dynamic-memory-monitoring program. In other words, this program keeps track of dynamic
memory allocated in a program and has the ability to report how many times `new/delete` was used and how many bytes have
been dynamically allocated and/or are leaking.

The use of operator overloading for the `new, new[], delete, and delete[]` operators as well as the use of the STL `map`
class in this lab was required.

## <a href="./Lab-6">Lab 6</a>
This lab involved parsing an XML file that contains `Patient` data, storing it in a container, and then parsing a file
that contains `Barcode`s, retrieving `Patient`s from the aforementioned container with the corresponding `Barcode`.

The main point of this lab was to use, as much as possible, all the topics we had learned in the class thus far. For
example, the `Barcode`s involved binary, which required the use of `bitset`s, we could parse the `Patient` data ideally
by using the XML parser we had built from the previous lab, the use of threading could speed up the program (see next
paragraph for description on why speed mattered), we *could* use the memory-monitoring program built in the previous lab
to check if our program had memory leaks, and we should try to use as many of the STL classes/algorithms as needed.

An added challenge to designing this program was to have the entire program run as quickly as possible, using a timer
for checking the speed. It was announced that the student with the fastest overall program would receive special recognition.

## <a href="./Final-Lab"> Final Lab: *Design Your Own Lab*</a>
For this course's final, we were given the choice to either take an in-class final or complete a take-home final. I chose
to complete the take-home final, which involved designing a lab for this course, CIS29, that could be used for future
quarters. The take-home final did involve first getting permission from our professor of our lab design by presenting to him a
quick proposal of what our lab design will be about.

Once approved, we were to not only fully design the lab, but also implement a sample solution to the lab we designed.
