/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the main application for this lab.

NOTE: Sample execution results have been appended to the end of this file.
*/

#include "Falsegrind.h" // Dynamic memory monitor application
#include <iostream>     // For printing statistics
#include <cstdlib>      // For rand and srand
#include <ctime>        // For seeding RNG
#include <list>         // Used to demonstrate use of new/new[]/delete/delete[] 10+ times
using namespace std;

#define aNumber int(1 << 3)
#define aBigNumber int(1 << 5)
#define aReallyBigNumber long(1 << 20)
#define RANDOM_LONG rand() % aReallyBigNumber + 1

inline void printStatistics();
void useNewAtLeastTenTimes(list <pair<long, long>**> &reallyLongList);
void useDeleteAtLeastTenTimes(list <pair<long, long>**> &reallyLongList);

int main()
{
	Falsegrind::startFalsegrind(); // start memory monitor application

	cout << "Creating a new list pointer of type <pair<long, long>**>... ";
	list <pair<long, long>**> *reallyLongList = new list<pair<long, long>**>();
	printStatistics(); cout << endl;

	useNewAtLeastTenTimes(*reallyLongList);
	useDeleteAtLeastTenTimes(*reallyLongList);

	cout << "Deleting list pointer of type <pair<long, long>**>... ";
	delete reallyLongList;
	printStatistics(); cout << endl;

	cout << "Checking for memory leaks... "
		<< (Falsegrind::getTotalAllocationCount() == 0 ? "No leak!" : "Memory leak.")
		<< endl << endl;

	Falsegrind::closeFalsegrind(); // close memory monitor application

	return 0;
}

inline void printStatistics()
{
	cout << "Total number of dynamic memory allocations: " << Falsegrind::getTotalAllocationCount()
		<< ". Total number of bytes allocated: " << Falsegrind::getTotalBytesMapped() << endl;
}

/* This method involves an unnecessarily complicated setup that eventually
 results in the new operator being used (aNumber * aBigNumber) times (see
 macros defined above). Why is the setup unnescessarily complicated, one
 might ask? Because 10 lines of "int *foo = new int(7);" is boring! */
void useNewAtLeastTenTimes(list<pair<long, long>**> &reallyLongList)
{
	printStatistics();
	cout << "Now starting test method for use of overloaded new/new[] operators ten or more times.\n\n";

	srand(time(0)); // seed RNG for random pairs of longs

	cout << "Inserting " << aNumber << " pair arrays of " << aBigNumber << " random pair<long, long> pointers each.\n\n";
	for (int i = 0; i < aNumber; i++)
	{
		cout << "Creating new pair array... ";
		pair<long, long> **newPair = new pair<long, long>*[aBigNumber]; // uses operator new[]
		printStatistics();
		for (int j = 0; j < aBigNumber - 10; j++)
		{
			long rlong1, rlong2;
			cout << "Creating new random pair<long, long> pointer that holds "
				<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
				<< "... ";
			newPair[j] = new pair<long, long>(rlong1, rlong2); // uses operator new
			printStatistics();
		}

		long rlong1, rlong2;
		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 10] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();
		
		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 9] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 8] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 7] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 6] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 5] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 4] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 3] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 2] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		cout << "Creating new random pair<long, long> pointer that holds "
			<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
			<< "... ";
		newPair[aBigNumber - 1] = new pair<long, long>(rlong1, rlong2); // uses operator new
		printStatistics();

		reallyLongList.push_back(newPair);
		cout << endl;
	}

	cout << "\n\n\n\n";
}

/* See method description for useNewAtLeastTenTimes()
 but replace "new" with "delete". */
void useDeleteAtLeastTenTimes(list <pair<long, long>**> &reallyLongList)
{
	printStatistics();
	cout << "Now starting test method for use of overloaded delete/delete[] operators ten or more times.\n\n";

	cout << "Deleting " << aNumber << " pair arrays of " << aBigNumber << " random pair<long, long> pointers each.\n\n";
	for (auto i = reallyLongList.begin(); i != reallyLongList.end(); i++)
	{
		cout << "Deleting individual pair<long, long> pointers in pair array...\n";
		for (int j = 0; j < aBigNumber - 10; j++)
		{
			delete (*i)[j]; // uses operator delete
			cout << "Deleted a pair<long, long> pointer. ";
			printStatistics();
		}

		delete (*i)[aBigNumber - 10]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 9]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 8]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 7]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 6]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 5]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 4]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 3]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 2]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete (*i)[aBigNumber - 1]; // uses operator delete
		cout << "Deleted a pair<long, long> pointer. ";
		printStatistics();

		delete[] (*i); // uses operator delete[]
		cout << "Deleted a pair array from the list. ";
		printStatistics(); cout << endl;
	}

	cout << "\n\n\n\n";
}

/* EXECUTION RESULTS
Creating a new list pointer of type <pair<long, long>**>... Total number of dynamic memory allocations: 3. Total number of bytes allocated: 32

Total number of dynamic memory allocations: 3. Total number of bytes allocated: 32
Now starting test method for use of overloaded new/new[] operators ten or more times.

Inserting 8 pair arrays of 32 random pair<long, long> pointers each.

Creating new pair array... Total number of dynamic memory allocations: 4. Total number of bytes allocated: 160
Creating new random pair<long, long> pointer that holds 19234 and 15596... Total number of dynamic memory allocations: 5. Total number of bytes allocated: 168
Creating new random pair<long, long> pointer that holds 27572 and 20973... Total number of dynamic memory allocations: 6. Total number of bytes allocated: 176
Creating new random pair<long, long> pointer that holds 13595 and 3229... Total number of dynamic memory allocations: 7. Total number of bytes allocated: 184
Creating new random pair<long, long> pointer that holds 7926 and 22562... Total number of dynamic memory allocations: 8. Total number of bytes allocated: 192
Creating new random pair<long, long> pointer that holds 22794 and 27249... Total number of dynamic memory allocations: 9. Total number of bytes allocated: 200
Creating new random pair<long, long> pointer that holds 1713 and 18258... Total number of dynamic memory allocations: 10. Total number of bytes allocated: 208
Creating new random pair<long, long> pointer that holds 9881 and 16544... Total number of dynamic memory allocations: 11. Total number of bytes allocated: 216
Creating new random pair<long, long> pointer that holds 4480 and 1422... Total number of dynamic memory allocations: 12. Total number of bytes allocated: 224
Creating new random pair<long, long> pointer that holds 4052 and 8428... Total number of dynamic memory allocations: 13. Total number of bytes allocated: 232
Creating new random pair<long, long> pointer that holds 17766 and 1733... Total number of dynamic memory allocations: 14. Total number of bytes allocated: 240
Creating new random pair<long, long> pointer that holds 27530 and 5076... Total number of dynamic memory allocations: 15. Total number of bytes allocated: 248
Creating new random pair<long, long> pointer that holds 21849 and 13718... Total number of dynamic memory allocations: 16. Total number of bytes allocated: 256
Creating new random pair<long, long> pointer that holds 22262 and 26635... Total number of dynamic memory allocations: 17. Total number of bytes allocated: 264
Creating new random pair<long, long> pointer that holds 12289 and 24163... Total number of dynamic memory allocations: 18. Total number of bytes allocated: 272
Creating new random pair<long, long> pointer that holds 23198 and 5672... Total number of dynamic memory allocations: 19. Total number of bytes allocated: 280
Creating new random pair<long, long> pointer that holds 27581 and 20647... Total number of dynamic memory allocations: 20. Total number of bytes allocated: 288
Creating new random pair<long, long> pointer that holds 22140 and 3231... Total number of dynamic memory allocations: 21. Total number of bytes allocated: 296
Creating new random pair<long, long> pointer that holds 13287 and 10889... Total number of dynamic memory allocations: 22. Total number of bytes allocated: 304
Creating new random pair<long, long> pointer that holds 31068 and 30704... Total number of dynamic memory allocations: 23. Total number of bytes allocated: 312
Creating new random pair<long, long> pointer that holds 7001 and 689... Total number of dynamic memory allocations: 24. Total number of bytes allocated: 320
Creating new random pair<long, long> pointer that holds 18309 and 23326... Total number of dynamic memory allocations: 25. Total number of bytes allocated: 328
Creating new random pair<long, long> pointer that holds 30767 and 25690... Total number of dynamic memory allocations: 26. Total number of bytes allocated: 336
Creating new random pair<long, long> pointer that holds 29851 and 3171... Total number of dynamic memory allocations: 27. Total number of bytes allocated: 344
Creating new random pair<long, long> pointer that holds 11471 and 20904... Total number of dynamic memory allocations: 28. Total number of bytes allocated: 352
Creating new random pair<long, long> pointer that holds 5316 and 27170... Total number of dynamic memory allocations: 29. Total number of bytes allocated: 360
Creating new random pair<long, long> pointer that holds 551 and 16444... Total number of dynamic memory allocations: 30. Total number of bytes allocated: 368
Creating new random pair<long, long> pointer that holds 26890 and 23581... Total number of dynamic memory allocations: 31. Total number of bytes allocated: 376
Creating new random pair<long, long> pointer that holds 30518 and 17415... Total number of dynamic memory allocations: 32. Total number of bytes allocated: 384
Creating new random pair<long, long> pointer that holds 19201 and 29928... Total number of dynamic memory allocations: 33. Total number of bytes allocated: 392
Creating new random pair<long, long> pointer that holds 10702 and 23643... Total number of dynamic memory allocations: 34. Total number of bytes allocated: 400
Creating new random pair<long, long> pointer that holds 31657 and 18334... Total number of dynamic memory allocations: 35. Total number of bytes allocated: 408
Creating new random pair<long, long> pointer that holds 15512 and 5960... Total number of dynamic memory allocations: 36. Total number of bytes allocated: 416

Creating new pair array... Total number of dynamic memory allocations: 38. Total number of bytes allocated: 556
Creating new random pair<long, long> pointer that holds 22933 and 17874... Total number of dynamic memory allocations: 39. Total number of bytes allocated: 564
Creating new random pair<long, long> pointer that holds 24152 and 32549... Total number of dynamic memory allocations: 40. Total number of bytes allocated: 572
Creating new random pair<long, long> pointer that holds 16973 and 14792... Total number of dynamic memory allocations: 41. Total number of bytes allocated: 580
Creating new random pair<long, long> pointer that holds 22130 and 1645... Total number of dynamic memory allocations: 42. Total number of bytes allocated: 588
Creating new random pair<long, long> pointer that holds 8946 and 12517... Total number of dynamic memory allocations: 43. Total number of bytes allocated: 596
Creating new random pair<long, long> pointer that holds 15022 and 26061... Total number of dynamic memory allocations: 44. Total number of bytes allocated: 604
Creating new random pair<long, long> pointer that holds 31776 and 27237... Total number of dynamic memory allocations: 45. Total number of bytes allocated: 612
Creating new random pair<long, long> pointer that holds 12856 and 8314... Total number of dynamic memory allocations: 46. Total number of bytes allocated: 620
Creating new random pair<long, long> pointer that holds 23832 and 7756... Total number of dynamic memory allocations: 47. Total number of bytes allocated: 628
Creating new random pair<long, long> pointer that holds 27115 and 8904... Total number of dynamic memory allocations: 48. Total number of bytes allocated: 636
Creating new random pair<long, long> pointer that holds 6687 and 12447... Total number of dynamic memory allocations: 49. Total number of bytes allocated: 644
Creating new random pair<long, long> pointer that holds 7630 and 12025... Total number of dynamic memory allocations: 50. Total number of bytes allocated: 652
Creating new random pair<long, long> pointer that holds 16929 and 9427... Total number of dynamic memory allocations: 51. Total number of bytes allocated: 660
Creating new random pair<long, long> pointer that holds 23519 and 3154... Total number of dynamic memory allocations: 52. Total number of bytes allocated: 668
Creating new random pair<long, long> pointer that holds 6042 and 25990... Total number of dynamic memory allocations: 53. Total number of bytes allocated: 676
Creating new random pair<long, long> pointer that holds 25616 and 11381... Total number of dynamic memory allocations: 54. Total number of bytes allocated: 684
Creating new random pair<long, long> pointer that holds 4279 and 13421... Total number of dynamic memory allocations: 55. Total number of bytes allocated: 692
Creating new random pair<long, long> pointer that holds 18832 and 15082... Total number of dynamic memory allocations: 56. Total number of bytes allocated: 700
Creating new random pair<long, long> pointer that holds 8888 and 22158... Total number of dynamic memory allocations: 57. Total number of bytes allocated: 708
Creating new random pair<long, long> pointer that holds 14667 and 19199... Total number of dynamic memory allocations: 58. Total number of bytes allocated: 716
Creating new random pair<long, long> pointer that holds 23704 and 20655... Total number of dynamic memory allocations: 59. Total number of bytes allocated: 724
Creating new random pair<long, long> pointer that holds 2484 and 6098... Total number of dynamic memory allocations: 60. Total number of bytes allocated: 732
Creating new random pair<long, long> pointer that holds 5360 and 18446... Total number of dynamic memory allocations: 61. Total number of bytes allocated: 740
Creating new random pair<long, long> pointer that holds 30658 and 2732... Total number of dynamic memory allocations: 62. Total number of bytes allocated: 748
Creating new random pair<long, long> pointer that holds 12057 and 23378... Total number of dynamic memory allocations: 63. Total number of bytes allocated: 756
Creating new random pair<long, long> pointer that holds 13624 and 31632... Total number of dynamic memory allocations: 64. Total number of bytes allocated: 764
Creating new random pair<long, long> pointer that holds 15248 and 1986... Total number of dynamic memory allocations: 65. Total number of bytes allocated: 772
Creating new random pair<long, long> pointer that holds 11306 and 24596... Total number of dynamic memory allocations: 66. Total number of bytes allocated: 780
Creating new random pair<long, long> pointer that holds 30623 and 28341... Total number of dynamic memory allocations: 67. Total number of bytes allocated: 788
Creating new random pair<long, long> pointer that holds 7101 and 23664... Total number of dynamic memory allocations: 68. Total number of bytes allocated: 796
Creating new random pair<long, long> pointer that holds 28730 and 3913... Total number of dynamic memory allocations: 69. Total number of bytes allocated: 804
Creating new random pair<long, long> pointer that holds 29230 and 27349... Total number of dynamic memory allocations: 70. Total number of bytes allocated: 812

Creating new pair array... Total number of dynamic memory allocations: 72. Total number of bytes allocated: 952
Creating new random pair<long, long> pointer that holds 19496 and 18520... Total number of dynamic memory allocations: 73. Total number of bytes allocated: 960
Creating new random pair<long, long> pointer that holds 2070 and 3328... Total number of dynamic memory allocations: 74. Total number of bytes allocated: 968
Creating new random pair<long, long> pointer that holds 355 and 13992... Total number of dynamic memory allocations: 75. Total number of bytes allocated: 976
Creating new random pair<long, long> pointer that holds 8428 and 15374... Total number of dynamic memory allocations: 76. Total number of bytes allocated: 984
Creating new random pair<long, long> pointer that holds 31168 and 17250... Total number of dynamic memory allocations: 77. Total number of bytes allocated: 992
Creating new random pair<long, long> pointer that holds 21707 and 2706... Total number of dynamic memory allocations: 78. Total number of bytes allocated: 1000
Creating new random pair<long, long> pointer that holds 27346 and 30406... Total number of dynamic memory allocations: 79. Total number of bytes allocated: 1008
Creating new random pair<long, long> pointer that holds 18293 and 11493... Total number of dynamic memory allocations: 80. Total number of bytes allocated: 1016
Creating new random pair<long, long> pointer that holds 25868 and 25372... Total number of dynamic memory allocations: 81. Total number of bytes allocated: 1024
Creating new random pair<long, long> pointer that holds 20633 and 23485... Total number of dynamic memory allocations: 82. Total number of bytes allocated: 1032
Creating new random pair<long, long> pointer that holds 24103 and 15342... Total number of dynamic memory allocations: 83. Total number of bytes allocated: 1040
Creating new random pair<long, long> pointer that holds 31057 and 17665... Total number of dynamic memory allocations: 84. Total number of bytes allocated: 1048
Creating new random pair<long, long> pointer that holds 15043 and 28020... Total number of dynamic memory allocations: 85. Total number of bytes allocated: 1056
Creating new random pair<long, long> pointer that holds 29423 and 32476... Total number of dynamic memory allocations: 86. Total number of bytes allocated: 1064
Creating new random pair<long, long> pointer that holds 6993 and 18512... Total number of dynamic memory allocations: 87. Total number of bytes allocated: 1072
Creating new random pair<long, long> pointer that holds 27385 and 12561... Total number of dynamic memory allocations: 88. Total number of bytes allocated: 1080
Creating new random pair<long, long> pointer that holds 28720 and 5500... Total number of dynamic memory allocations: 89. Total number of bytes allocated: 1088
Creating new random pair<long, long> pointer that holds 24690 and 26766... Total number of dynamic memory allocations: 90. Total number of bytes allocated: 1096
Creating new random pair<long, long> pointer that holds 6422 and 9856... Total number of dynamic memory allocations: 91. Total number of bytes allocated: 1104
Creating new random pair<long, long> pointer that holds 24155 and 18755... Total number of dynamic memory allocations: 92. Total number of bytes allocated: 1112
Creating new random pair<long, long> pointer that holds 5042 and 13800... Total number of dynamic memory allocations: 93. Total number of bytes allocated: 1120
Creating new random pair<long, long> pointer that holds 16250 and 4660... Total number of dynamic memory allocations: 94. Total number of bytes allocated: 1128
Creating new random pair<long, long> pointer that holds 32144 and 11253... Total number of dynamic memory allocations: 95. Total number of bytes allocated: 1136
Creating new random pair<long, long> pointer that holds 24410 and 10189... Total number of dynamic memory allocations: 96. Total number of bytes allocated: 1144
Creating new random pair<long, long> pointer that holds 27964 and 7059... Total number of dynamic memory allocations: 97. Total number of bytes allocated: 1152
Creating new random pair<long, long> pointer that holds 23699 and 6262... Total number of dynamic memory allocations: 98. Total number of bytes allocated: 1160
Creating new random pair<long, long> pointer that holds 26282 and 2955... Total number of dynamic memory allocations: 99. Total number of bytes allocated: 1168
Creating new random pair<long, long> pointer that holds 20555 and 20328... Total number of dynamic memory allocations: 100. Total number of bytes allocated: 1176
Creating new random pair<long, long> pointer that holds 28373 and 24570... Total number of dynamic memory allocations: 101. Total number of bytes allocated: 1184
Creating new random pair<long, long> pointer that holds 7933 and 27071... Total number of dynamic memory allocations: 102. Total number of bytes allocated: 1192
Creating new random pair<long, long> pointer that holds 679 and 30722... Total number of dynamic memory allocations: 103. Total number of bytes allocated: 1200
Creating new random pair<long, long> pointer that holds 18042 and 25040... Total number of dynamic memory allocations: 104. Total number of bytes allocated: 1208

Creating new pair array... Total number of dynamic memory allocations: 106. Total number of bytes allocated: 1348
Creating new random pair<long, long> pointer that holds 29977 and 21439... Total number of dynamic memory allocations: 107. Total number of bytes allocated: 1356
Creating new random pair<long, long> pointer that holds 19757 and 1212... Total number of dynamic memory allocations: 108. Total number of bytes allocated: 1364
Creating new random pair<long, long> pointer that holds 30875 and 22140... Total number of dynamic memory allocations: 109. Total number of bytes allocated: 1372
Creating new random pair<long, long> pointer that holds 13986 and 26182... Total number of dynamic memory allocations: 110. Total number of bytes allocated: 1380
Creating new random pair<long, long> pointer that holds 22454 and 31015... Total number of dynamic memory allocations: 111. Total number of bytes allocated: 1388
Creating new random pair<long, long> pointer that holds 8522 and 18145... Total number of dynamic memory allocations: 112. Total number of bytes allocated: 1396
Creating new random pair<long, long> pointer that holds 8432 and 259... Total number of dynamic memory allocations: 113. Total number of bytes allocated: 1404
Creating new random pair<long, long> pointer that holds 29048 and 8205... Total number of dynamic memory allocations: 114. Total number of bytes allocated: 1412
Creating new random pair<long, long> pointer that holds 18928 and 3741... Total number of dynamic memory allocations: 115. Total number of bytes allocated: 1420
Creating new random pair<long, long> pointer that holds 11696 and 19172... Total number of dynamic memory allocations: 116. Total number of bytes allocated: 1428
Creating new random pair<long, long> pointer that holds 3554 and 6401... Total number of dynamic memory allocations: 117. Total number of bytes allocated: 1436
Creating new random pair<long, long> pointer that holds 28705 and 29936... Total number of dynamic memory allocations: 118. Total number of bytes allocated: 1444
Creating new random pair<long, long> pointer that holds 2845 and 10541... Total number of dynamic memory allocations: 119. Total number of bytes allocated: 1452
Creating new random pair<long, long> pointer that holds 4464 and 22336... Total number of dynamic memory allocations: 120. Total number of bytes allocated: 1460
Creating new random pair<long, long> pointer that holds 25603 and 27078... Total number of dynamic memory allocations: 121. Total number of bytes allocated: 1468
Creating new random pair<long, long> pointer that holds 28855 and 25531... Total number of dynamic memory allocations: 122. Total number of bytes allocated: 1476
Creating new random pair<long, long> pointer that holds 26409 and 24330... Total number of dynamic memory allocations: 123. Total number of bytes allocated: 1484
Creating new random pair<long, long> pointer that holds 31950 and 23732... Total number of dynamic memory allocations: 124. Total number of bytes allocated: 1492
Creating new random pair<long, long> pointer that holds 697 and 23302... Total number of dynamic memory allocations: 125. Total number of bytes allocated: 1500
Creating new random pair<long, long> pointer that holds 25289 and 2750... Total number of dynamic memory allocations: 126. Total number of bytes allocated: 1508
Creating new random pair<long, long> pointer that holds 1812 and 521... Total number of dynamic memory allocations: 127. Total number of bytes allocated: 1516
Creating new random pair<long, long> pointer that holds 1473 and 1217... Total number of dynamic memory allocations: 128. Total number of bytes allocated: 1524
Creating new random pair<long, long> pointer that holds 31931 and 29528... Total number of dynamic memory allocations: 129. Total number of bytes allocated: 1532
Creating new random pair<long, long> pointer that holds 9176 and 15949... Total number of dynamic memory allocations: 130. Total number of bytes allocated: 1540
Creating new random pair<long, long> pointer that holds 4463 and 27171... Total number of dynamic memory allocations: 131. Total number of bytes allocated: 1548
Creating new random pair<long, long> pointer that holds 19575 and 20527... Total number of dynamic memory allocations: 132. Total number of bytes allocated: 1556
Creating new random pair<long, long> pointer that holds 24727 and 27320... Total number of dynamic memory allocations: 133. Total number of bytes allocated: 1564
Creating new random pair<long, long> pointer that holds 3034 and 12098... Total number of dynamic memory allocations: 134. Total number of bytes allocated: 1572
Creating new random pair<long, long> pointer that holds 6883 and 20471... Total number of dynamic memory allocations: 135. Total number of bytes allocated: 1580
Creating new random pair<long, long> pointer that holds 28623 and 17800... Total number of dynamic memory allocations: 136. Total number of bytes allocated: 1588
Creating new random pair<long, long> pointer that holds 20783 and 19718... Total number of dynamic memory allocations: 137. Total number of bytes allocated: 1596
Creating new random pair<long, long> pointer that holds 18874 and 8569... Total number of dynamic memory allocations: 138. Total number of bytes allocated: 1604

Creating new pair array... Total number of dynamic memory allocations: 140. Total number of bytes allocated: 1744
Creating new random pair<long, long> pointer that holds 26282 and 14150... Total number of dynamic memory allocations: 141. Total number of bytes allocated: 1752
Creating new random pair<long, long> pointer that holds 20957 and 12187... Total number of dynamic memory allocations: 142. Total number of bytes allocated: 1760
Creating new random pair<long, long> pointer that holds 28215 and 11397... Total number of dynamic memory allocations: 143. Total number of bytes allocated: 1768
Creating new random pair<long, long> pointer that holds 4054 and 12883... Total number of dynamic memory allocations: 144. Total number of bytes allocated: 1776
Creating new random pair<long, long> pointer that holds 30483 and 26997... Total number of dynamic memory allocations: 145. Total number of bytes allocated: 1784
Creating new random pair<long, long> pointer that holds 11369 and 27643... Total number of dynamic memory allocations: 146. Total number of bytes allocated: 1792
Creating new random pair<long, long> pointer that holds 3256 and 25692... Total number of dynamic memory allocations: 147. Total number of bytes allocated: 1800
Creating new random pair<long, long> pointer that holds 4224 and 12084... Total number of dynamic memory allocations: 148. Total number of bytes allocated: 1808
Creating new random pair<long, long> pointer that holds 28162 and 14... Total number of dynamic memory allocations: 149. Total number of bytes allocated: 1816
Creating new random pair<long, long> pointer that holds 30064 and 18814... Total number of dynamic memory allocations: 150. Total number of bytes allocated: 1824
Creating new random pair<long, long> pointer that holds 16273 and 27417... Total number of dynamic memory allocations: 151. Total number of bytes allocated: 1832
Creating new random pair<long, long> pointer that holds 19070 and 31750... Total number of dynamic memory allocations: 152. Total number of bytes allocated: 1840
Creating new random pair<long, long> pointer that holds 15726 and 32575... Total number of dynamic memory allocations: 153. Total number of bytes allocated: 1848
Creating new random pair<long, long> pointer that holds 5026 and 30398... Total number of dynamic memory allocations: 154. Total number of bytes allocated: 1856
Creating new random pair<long, long> pointer that holds 12273 and 13609... Total number of dynamic memory allocations: 155. Total number of bytes allocated: 1864
Creating new random pair<long, long> pointer that holds 9611 and 2483... Total number of dynamic memory allocations: 156. Total number of bytes allocated: 1872
Creating new random pair<long, long> pointer that holds 10210 and 89... Total number of dynamic memory allocations: 157. Total number of bytes allocated: 1880
Creating new random pair<long, long> pointer that holds 25314 and 156... Total number of dynamic memory allocations: 158. Total number of bytes allocated: 1888
Creating new random pair<long, long> pointer that holds 17886 and 10081... Total number of dynamic memory allocations: 159. Total number of bytes allocated: 1896
Creating new random pair<long, long> pointer that holds 24275 and 23726... Total number of dynamic memory allocations: 160. Total number of bytes allocated: 1904
Creating new random pair<long, long> pointer that holds 4348 and 27730... Total number of dynamic memory allocations: 161. Total number of bytes allocated: 1912
Creating new random pair<long, long> pointer that holds 2250 and 24760... Total number of dynamic memory allocations: 162. Total number of bytes allocated: 1920
Creating new random pair<long, long> pointer that holds 8369 and 6520... Total number of dynamic memory allocations: 163. Total number of bytes allocated: 1928
Creating new random pair<long, long> pointer that holds 17786 and 9067... Total number of dynamic memory allocations: 164. Total number of bytes allocated: 1936
Creating new random pair<long, long> pointer that holds 7665 and 17988... Total number of dynamic memory allocations: 165. Total number of bytes allocated: 1944
Creating new random pair<long, long> pointer that holds 6436 and 7161... Total number of dynamic memory allocations: 166. Total number of bytes allocated: 1952
Creating new random pair<long, long> pointer that holds 24471 and 26762... Total number of dynamic memory allocations: 167. Total number of bytes allocated: 1960
Creating new random pair<long, long> pointer that holds 18198 and 23779... Total number of dynamic memory allocations: 168. Total number of bytes allocated: 1968
Creating new random pair<long, long> pointer that holds 9735 and 1517... Total number of dynamic memory allocations: 169. Total number of bytes allocated: 1976
Creating new random pair<long, long> pointer that holds 2674 and 28939... Total number of dynamic memory allocations: 170. Total number of bytes allocated: 1984
Creating new random pair<long, long> pointer that holds 14866 and 6551... Total number of dynamic memory allocations: 171. Total number of bytes allocated: 1992
Creating new random pair<long, long> pointer that holds 19504 and 3857... Total number of dynamic memory allocations: 172. Total number of bytes allocated: 2000

Creating new pair array... Total number of dynamic memory allocations: 174. Total number of bytes allocated: 2140
Creating new random pair<long, long> pointer that holds 29466 and 557... Total number of dynamic memory allocations: 175. Total number of bytes allocated: 2148
Creating new random pair<long, long> pointer that holds 31334 and 5852... Total number of dynamic memory allocations: 176. Total number of bytes allocated: 2156
Creating new random pair<long, long> pointer that holds 26742 and 3073... Total number of dynamic memory allocations: 177. Total number of bytes allocated: 2164
Creating new random pair<long, long> pointer that holds 25799 and 3447... Total number of dynamic memory allocations: 178. Total number of bytes allocated: 2172
Creating new random pair<long, long> pointer that holds 21015 and 27530... Total number of dynamic memory allocations: 179. Total number of bytes allocated: 2180
Creating new random pair<long, long> pointer that holds 17002 and 2847... Total number of dynamic memory allocations: 180. Total number of bytes allocated: 2188
Creating new random pair<long, long> pointer that holds 23660 and 15378... Total number of dynamic memory allocations: 181. Total number of bytes allocated: 2196
Creating new random pair<long, long> pointer that holds 17614 and 20378... Total number of dynamic memory allocations: 182. Total number of bytes allocated: 2204
Creating new random pair<long, long> pointer that holds 29572 and 22191... Total number of dynamic memory allocations: 183. Total number of bytes allocated: 2212
Creating new random pair<long, long> pointer that holds 23578 and 28874... Total number of dynamic memory allocations: 184. Total number of bytes allocated: 2220
Creating new random pair<long, long> pointer that holds 18803 and 5492... Total number of dynamic memory allocations: 185. Total number of bytes allocated: 2228
Creating new random pair<long, long> pointer that holds 4265 and 22401... Total number of dynamic memory allocations: 186. Total number of bytes allocated: 2236
Creating new random pair<long, long> pointer that holds 7158 and 22248... Total number of dynamic memory allocations: 187. Total number of bytes allocated: 2244
Creating new random pair<long, long> pointer that holds 5573 and 32407... Total number of dynamic memory allocations: 188. Total number of bytes allocated: 2252
Creating new random pair<long, long> pointer that holds 32090 and 21943... Total number of dynamic memory allocations: 189. Total number of bytes allocated: 2260
Creating new random pair<long, long> pointer that holds 31155 and 10298... Total number of dynamic memory allocations: 190. Total number of bytes allocated: 2268
Creating new random pair<long, long> pointer that holds 9369 and 10408... Total number of dynamic memory allocations: 191. Total number of bytes allocated: 2276
Creating new random pair<long, long> pointer that holds 5873 and 32134... Total number of dynamic memory allocations: 192. Total number of bytes allocated: 2284
Creating new random pair<long, long> pointer that holds 2247 and 32463... Total number of dynamic memory allocations: 193. Total number of bytes allocated: 2292
Creating new random pair<long, long> pointer that holds 10939 and 19541... Total number of dynamic memory allocations: 194. Total number of bytes allocated: 2300
Creating new random pair<long, long> pointer that holds 19372 and 27652... Total number of dynamic memory allocations: 195. Total number of bytes allocated: 2308
Creating new random pair<long, long> pointer that holds 13523 and 22361... Total number of dynamic memory allocations: 196. Total number of bytes allocated: 2316
Creating new random pair<long, long> pointer that holds 14259 and 22932... Total number of dynamic memory allocations: 197. Total number of bytes allocated: 2324
Creating new random pair<long, long> pointer that holds 1154 and 27752... Total number of dynamic memory allocations: 198. Total number of bytes allocated: 2332
Creating new random pair<long, long> pointer that holds 21763 and 28470... Total number of dynamic memory allocations: 199. Total number of bytes allocated: 2340
Creating new random pair<long, long> pointer that holds 5850 and 13590... Total number of dynamic memory allocations: 200. Total number of bytes allocated: 2348
Creating new random pair<long, long> pointer that holds 23019 and 2112... Total number of dynamic memory allocations: 201. Total number of bytes allocated: 2356
Creating new random pair<long, long> pointer that holds 10815 and 30089... Total number of dynamic memory allocations: 202. Total number of bytes allocated: 2364
Creating new random pair<long, long> pointer that holds 31363 and 2330... Total number of dynamic memory allocations: 203. Total number of bytes allocated: 2372
Creating new random pair<long, long> pointer that holds 11046 and 11657... Total number of dynamic memory allocations: 204. Total number of bytes allocated: 2380
Creating new random pair<long, long> pointer that holds 23440 and 10483... Total number of dynamic memory allocations: 205. Total number of bytes allocated: 2388
Creating new random pair<long, long> pointer that holds 24091 and 20439... Total number of dynamic memory allocations: 206. Total number of bytes allocated: 2396

Creating new pair array... Total number of dynamic memory allocations: 208. Total number of bytes allocated: 2536
Creating new random pair<long, long> pointer that holds 11433 and 948... Total number of dynamic memory allocations: 209. Total number of bytes allocated: 2544
Creating new random pair<long, long> pointer that holds 27401 and 960... Total number of dynamic memory allocations: 210. Total number of bytes allocated: 2552
Creating new random pair<long, long> pointer that holds 11672 and 2098... Total number of dynamic memory allocations: 211. Total number of bytes allocated: 2560
Creating new random pair<long, long> pointer that holds 11702 and 9457... Total number of dynamic memory allocations: 212. Total number of bytes allocated: 2568
Creating new random pair<long, long> pointer that holds 8963 and 5800... Total number of dynamic memory allocations: 213. Total number of bytes allocated: 2576
Creating new random pair<long, long> pointer that holds 28557 and 30093... Total number of dynamic memory allocations: 214. Total number of bytes allocated: 2584
Creating new random pair<long, long> pointer that holds 32332 and 25444... Total number of dynamic memory allocations: 215. Total number of bytes allocated: 2592
Creating new random pair<long, long> pointer that holds 28320 and 13949... Total number of dynamic memory allocations: 216. Total number of bytes allocated: 2600
Creating new random pair<long, long> pointer that holds 15541 and 29120... Total number of dynamic memory allocations: 217. Total number of bytes allocated: 2608
Creating new random pair<long, long> pointer that holds 21997 and 6664... Total number of dynamic memory allocations: 218. Total number of bytes allocated: 2616
Creating new random pair<long, long> pointer that holds 16840 and 15188... Total number of dynamic memory allocations: 219. Total number of bytes allocated: 2624
Creating new random pair<long, long> pointer that holds 2784 and 17571... Total number of dynamic memory allocations: 220. Total number of bytes allocated: 2632
Creating new random pair<long, long> pointer that holds 12534 and 22378... Total number of dynamic memory allocations: 221. Total number of bytes allocated: 2640
Creating new random pair<long, long> pointer that holds 29722 and 20490... Total number of dynamic memory allocations: 222. Total number of bytes allocated: 2648
Creating new random pair<long, long> pointer that holds 2686 and 14002... Total number of dynamic memory allocations: 223. Total number of bytes allocated: 2656
Creating new random pair<long, long> pointer that holds 7537 and 1167... Total number of dynamic memory allocations: 224. Total number of bytes allocated: 2664
Creating new random pair<long, long> pointer that holds 3984 and 18232... Total number of dynamic memory allocations: 225. Total number of bytes allocated: 2672
Creating new random pair<long, long> pointer that holds 23864 and 15538... Total number of dynamic memory allocations: 226. Total number of bytes allocated: 2680
Creating new random pair<long, long> pointer that holds 12722 and 5266... Total number of dynamic memory allocations: 227. Total number of bytes allocated: 2688
Creating new random pair<long, long> pointer that holds 24256 and 9971... Total number of dynamic memory allocations: 228. Total number of bytes allocated: 2696
Creating new random pair<long, long> pointer that holds 4452 and 14430... Total number of dynamic memory allocations: 229. Total number of bytes allocated: 2704
Creating new random pair<long, long> pointer that holds 13854 and 23012... Total number of dynamic memory allocations: 230. Total number of bytes allocated: 2712
Creating new random pair<long, long> pointer that holds 20479 and 12012... Total number of dynamic memory allocations: 231. Total number of bytes allocated: 2720
Creating new random pair<long, long> pointer that holds 24879 and 28290... Total number of dynamic memory allocations: 232. Total number of bytes allocated: 2728
Creating new random pair<long, long> pointer that holds 14563 and 25655... Total number of dynamic memory allocations: 233. Total number of bytes allocated: 2736
Creating new random pair<long, long> pointer that holds 23002 and 5317... Total number of dynamic memory allocations: 234. Total number of bytes allocated: 2744
Creating new random pair<long, long> pointer that holds 1489 and 3354... Total number of dynamic memory allocations: 235. Total number of bytes allocated: 2752
Creating new random pair<long, long> pointer that holds 7573 and 22134... Total number of dynamic memory allocations: 236. Total number of bytes allocated: 2760
Creating new random pair<long, long> pointer that holds 17046 and 8384... Total number of dynamic memory allocations: 237. Total number of bytes allocated: 2768
Creating new random pair<long, long> pointer that holds 20011 and 31809... Total number of dynamic memory allocations: 238. Total number of bytes allocated: 2776
Creating new random pair<long, long> pointer that holds 5098 and 1629... Total number of dynamic memory allocations: 239. Total number of bytes allocated: 2784
Creating new random pair<long, long> pointer that holds 20412 and 18699... Total number of dynamic memory allocations: 240. Total number of bytes allocated: 2792

Creating new pair array... Total number of dynamic memory allocations: 242. Total number of bytes allocated: 2932
Creating new random pair<long, long> pointer that holds 26007 and 19227... Total number of dynamic memory allocations: 243. Total number of bytes allocated: 2940
Creating new random pair<long, long> pointer that holds 2053 and 32646... Total number of dynamic memory allocations: 244. Total number of bytes allocated: 2948
Creating new random pair<long, long> pointer that holds 17374 and 29784... Total number of dynamic memory allocations: 245. Total number of bytes allocated: 2956
Creating new random pair<long, long> pointer that holds 8929 and 26114... Total number of dynamic memory allocations: 246. Total number of bytes allocated: 2964
Creating new random pair<long, long> pointer that holds 25622 and 16910... Total number of dynamic memory allocations: 247. Total number of bytes allocated: 2972
Creating new random pair<long, long> pointer that holds 16 and 15494... Total number of dynamic memory allocations: 248. Total number of bytes allocated: 2980
Creating new random pair<long, long> pointer that holds 8342 and 30098... Total number of dynamic memory allocations: 249. Total number of bytes allocated: 2988
Creating new random pair<long, long> pointer that holds 11832 and 22815... Total number of dynamic memory allocations: 250. Total number of bytes allocated: 2996
Creating new random pair<long, long> pointer that holds 27605 and 28802... Total number of dynamic memory allocations: 251. Total number of bytes allocated: 3004
Creating new random pair<long, long> pointer that holds 5929 and 24184... Total number of dynamic memory allocations: 252. Total number of bytes allocated: 3012
Creating new random pair<long, long> pointer that holds 32464 and 16376... Total number of dynamic memory allocations: 253. Total number of bytes allocated: 3020
Creating new random pair<long, long> pointer that holds 16741 and 16555... Total number of dynamic memory allocations: 254. Total number of bytes allocated: 3028
Creating new random pair<long, long> pointer that holds 18092 and 26628... Total number of dynamic memory allocations: 255. Total number of bytes allocated: 3036
Creating new random pair<long, long> pointer that holds 19168 and 3159... Total number of dynamic memory allocations: 256. Total number of bytes allocated: 3044
Creating new random pair<long, long> pointer that holds 21917 and 858... Total number of dynamic memory allocations: 257. Total number of bytes allocated: 3052
Creating new random pair<long, long> pointer that holds 260 and 9203... Total number of dynamic memory allocations: 258. Total number of bytes allocated: 3060
Creating new random pair<long, long> pointer that holds 23302 and 2887... Total number of dynamic memory allocations: 259. Total number of bytes allocated: 3068
Creating new random pair<long, long> pointer that holds 14840 and 26465... Total number of dynamic memory allocations: 260. Total number of bytes allocated: 3076
Creating new random pair<long, long> pointer that holds 26338 and 23530... Total number of dynamic memory allocations: 261. Total number of bytes allocated: 3084
Creating new random pair<long, long> pointer that holds 21282 and 31174... Total number of dynamic memory allocations: 262. Total number of bytes allocated: 3092
Creating new random pair<long, long> pointer that holds 31842 and 18592... Total number of dynamic memory allocations: 263. Total number of bytes allocated: 3100
Creating new random pair<long, long> pointer that holds 30955 and 6554... Total number of dynamic memory allocations: 264. Total number of bytes allocated: 3108
Creating new random pair<long, long> pointer that holds 14295 and 21696... Total number of dynamic memory allocations: 265. Total number of bytes allocated: 3116
Creating new random pair<long, long> pointer that holds 7106 and 16123... Total number of dynamic memory allocations: 266. Total number of bytes allocated: 3124
Creating new random pair<long, long> pointer that holds 3027 and 25737... Total number of dynamic memory allocations: 267. Total number of bytes allocated: 3132
Creating new random pair<long, long> pointer that holds 13923 and 29767... Total number of dynamic memory allocations: 268. Total number of bytes allocated: 3140
Creating new random pair<long, long> pointer that holds 22923 and 31320... Total number of dynamic memory allocations: 269. Total number of bytes allocated: 3148
Creating new random pair<long, long> pointer that holds 18777 and 7401... Total number of dynamic memory allocations: 270. Total number of bytes allocated: 3156
Creating new random pair<long, long> pointer that holds 26752 and 21534... Total number of dynamic memory allocations: 271. Total number of bytes allocated: 3164
Creating new random pair<long, long> pointer that holds 12225 and 7795... Total number of dynamic memory allocations: 272. Total number of bytes allocated: 3172
Creating new random pair<long, long> pointer that holds 351 and 32018... Total number of dynamic memory allocations: 273. Total number of bytes allocated: 3180
Creating new random pair<long, long> pointer that holds 12626 and 8174... Total number of dynamic memory allocations: 274. Total number of bytes allocated: 3188





Total number of dynamic memory allocations: 275. Total number of bytes allocated: 3200
Now starting test method for use of overloaded delete/delete[] operators ten or more times.

Deleting 8 pair arrays of 32 random pair<long, long> pointers each.

Deleting individual pair<long, long> pointers in pair array...
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 274. Total number of bytes allocated: 3192
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 273. Total number of bytes allocated: 3184
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 272. Total number of bytes allocated: 3176
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 271. Total number of bytes allocated: 3168
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 270. Total number of bytes allocated: 3160
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 269. Total number of bytes allocated: 3152
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 268. Total number of bytes allocated: 3144
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 267. Total number of bytes allocated: 3136
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 266. Total number of bytes allocated: 3128
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 265. Total number of bytes allocated: 3120
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 264. Total number of bytes allocated: 3112
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 263. Total number of bytes allocated: 3104
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 262. Total number of bytes allocated: 3096
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 261. Total number of bytes allocated: 3088
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 260. Total number of bytes allocated: 3080
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 259. Total number of bytes allocated: 3072
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 258. Total number of bytes allocated: 3064
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 257. Total number of bytes allocated: 3056
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 256. Total number of bytes allocated: 3048
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 255. Total number of bytes allocated: 3040
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 254. Total number of bytes allocated: 3032
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 253. Total number of bytes allocated: 3024
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 252. Total number of bytes allocated: 3016
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 251. Total number of bytes allocated: 3008
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 250. Total number of bytes allocated: 3000
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 249. Total number of bytes allocated: 2992
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 248. Total number of bytes allocated: 2984
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 247. Total number of bytes allocated: 2976
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 246. Total number of bytes allocated: 2968
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 245. Total number of bytes allocated: 2960
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 244. Total number of bytes allocated: 2952
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 243. Total number of bytes allocated: 2944
Deleted a pair array from the list. Total number of dynamic memory allocations: 242. Total number of bytes allocated: 2816

Deleting individual pair<long, long> pointers in pair array...
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 241. Total number of bytes allocated: 2808
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 240. Total number of bytes allocated: 2800
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 239. Total number of bytes allocated: 2792
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 238. Total number of bytes allocated: 2784
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 237. Total number of bytes allocated: 2776
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 236. Total number of bytes allocated: 2768
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 235. Total number of bytes allocated: 2760
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 234. Total number of bytes allocated: 2752
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 233. Total number of bytes allocated: 2744
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 232. Total number of bytes allocated: 2736
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 231. Total number of bytes allocated: 2728
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 230. Total number of bytes allocated: 2720
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 229. Total number of bytes allocated: 2712
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 228. Total number of bytes allocated: 2704
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 227. Total number of bytes allocated: 2696
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 226. Total number of bytes allocated: 2688
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 225. Total number of bytes allocated: 2680
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 224. Total number of bytes allocated: 2672
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 223. Total number of bytes allocated: 2664
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 222. Total number of bytes allocated: 2656
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 221. Total number of bytes allocated: 2648
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 220. Total number of bytes allocated: 2640
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 219. Total number of bytes allocated: 2632
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 218. Total number of bytes allocated: 2624
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 217. Total number of bytes allocated: 2616
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 216. Total number of bytes allocated: 2608
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 215. Total number of bytes allocated: 2600
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 214. Total number of bytes allocated: 2592
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 213. Total number of bytes allocated: 2584
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 212. Total number of bytes allocated: 2576
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 211. Total number of bytes allocated: 2568
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 210. Total number of bytes allocated: 2560
Deleted a pair array from the list. Total number of dynamic memory allocations: 209. Total number of bytes allocated: 2432

Deleting individual pair<long, long> pointers in pair array...
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 208. Total number of bytes allocated: 2424
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 207. Total number of bytes allocated: 2416
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 206. Total number of bytes allocated: 2408
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 205. Total number of bytes allocated: 2400
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 204. Total number of bytes allocated: 2392
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 203. Total number of bytes allocated: 2384
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 202. Total number of bytes allocated: 2376
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 201. Total number of bytes allocated: 2368
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 200. Total number of bytes allocated: 2360
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 199. Total number of bytes allocated: 2352
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 198. Total number of bytes allocated: 2344
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 197. Total number of bytes allocated: 2336
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 196. Total number of bytes allocated: 2328
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 195. Total number of bytes allocated: 2320
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 194. Total number of bytes allocated: 2312
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 193. Total number of bytes allocated: 2304
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 192. Total number of bytes allocated: 2296
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 191. Total number of bytes allocated: 2288
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 190. Total number of bytes allocated: 2280
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 189. Total number of bytes allocated: 2272
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 188. Total number of bytes allocated: 2264
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 187. Total number of bytes allocated: 2256
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 186. Total number of bytes allocated: 2248
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 185. Total number of bytes allocated: 2240
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 184. Total number of bytes allocated: 2232
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 183. Total number of bytes allocated: 2224
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 182. Total number of bytes allocated: 2216
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 181. Total number of bytes allocated: 2208
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 180. Total number of bytes allocated: 2200
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 179. Total number of bytes allocated: 2192
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 178. Total number of bytes allocated: 2184
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 177. Total number of bytes allocated: 2176
Deleted a pair array from the list. Total number of dynamic memory allocations: 176. Total number of bytes allocated: 2048

Deleting individual pair<long, long> pointers in pair array...
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 175. Total number of bytes allocated: 2040
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 174. Total number of bytes allocated: 2032
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 173. Total number of bytes allocated: 2024
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 172. Total number of bytes allocated: 2016
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 171. Total number of bytes allocated: 2008
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 170. Total number of bytes allocated: 2000
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 169. Total number of bytes allocated: 1992
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 168. Total number of bytes allocated: 1984
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 167. Total number of bytes allocated: 1976
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 166. Total number of bytes allocated: 1968
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 165. Total number of bytes allocated: 1960
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 164. Total number of bytes allocated: 1952
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 163. Total number of bytes allocated: 1944
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 162. Total number of bytes allocated: 1936
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 161. Total number of bytes allocated: 1928
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 160. Total number of bytes allocated: 1920
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 159. Total number of bytes allocated: 1912
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 158. Total number of bytes allocated: 1904
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 157. Total number of bytes allocated: 1896
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 156. Total number of bytes allocated: 1888
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 155. Total number of bytes allocated: 1880
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 154. Total number of bytes allocated: 1872
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 153. Total number of bytes allocated: 1864
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 152. Total number of bytes allocated: 1856
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 151. Total number of bytes allocated: 1848
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 150. Total number of bytes allocated: 1840
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 149. Total number of bytes allocated: 1832
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 148. Total number of bytes allocated: 1824
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 147. Total number of bytes allocated: 1816
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 146. Total number of bytes allocated: 1808
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 145. Total number of bytes allocated: 1800
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 144. Total number of bytes allocated: 1792
Deleted a pair array from the list. Total number of dynamic memory allocations: 143. Total number of bytes allocated: 1664

Deleting individual pair<long, long> pointers in pair array...
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 142. Total number of bytes allocated: 1656
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 141. Total number of bytes allocated: 1648
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 140. Total number of bytes allocated: 1640
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 139. Total number of bytes allocated: 1632
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 138. Total number of bytes allocated: 1624
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 137. Total number of bytes allocated: 1616
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 136. Total number of bytes allocated: 1608
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 135. Total number of bytes allocated: 1600
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 134. Total number of bytes allocated: 1592
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 133. Total number of bytes allocated: 1584
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 132. Total number of bytes allocated: 1576
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 131. Total number of bytes allocated: 1568
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 130. Total number of bytes allocated: 1560
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 129. Total number of bytes allocated: 1552
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 128. Total number of bytes allocated: 1544
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 127. Total number of bytes allocated: 1536
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 126. Total number of bytes allocated: 1528
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 125. Total number of bytes allocated: 1520
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 124. Total number of bytes allocated: 1512
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 123. Total number of bytes allocated: 1504
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 122. Total number of bytes allocated: 1496
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 121. Total number of bytes allocated: 1488
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 120. Total number of bytes allocated: 1480
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 119. Total number of bytes allocated: 1472
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 118. Total number of bytes allocated: 1464
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 117. Total number of bytes allocated: 1456
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 116. Total number of bytes allocated: 1448
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 115. Total number of bytes allocated: 1440
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 114. Total number of bytes allocated: 1432
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 113. Total number of bytes allocated: 1424
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 112. Total number of bytes allocated: 1416
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 111. Total number of bytes allocated: 1408
Deleted a pair array from the list. Total number of dynamic memory allocations: 110. Total number of bytes allocated: 1280

Deleting individual pair<long, long> pointers in pair array...
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 109. Total number of bytes allocated: 1272
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 108. Total number of bytes allocated: 1264
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 107. Total number of bytes allocated: 1256
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 106. Total number of bytes allocated: 1248
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 105. Total number of bytes allocated: 1240
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 104. Total number of bytes allocated: 1232
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 103. Total number of bytes allocated: 1224
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 102. Total number of bytes allocated: 1216
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 101. Total number of bytes allocated: 1208
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 100. Total number of bytes allocated: 1200
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 99. Total number of bytes allocated: 1192
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 98. Total number of bytes allocated: 1184
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 97. Total number of bytes allocated: 1176
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 96. Total number of bytes allocated: 1168
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 95. Total number of bytes allocated: 1160
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 94. Total number of bytes allocated: 1152
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 93. Total number of bytes allocated: 1144
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 92. Total number of bytes allocated: 1136
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 91. Total number of bytes allocated: 1128
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 90. Total number of bytes allocated: 1120
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 89. Total number of bytes allocated: 1112
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 88. Total number of bytes allocated: 1104
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 87. Total number of bytes allocated: 1096
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 86. Total number of bytes allocated: 1088
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 85. Total number of bytes allocated: 1080
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 84. Total number of bytes allocated: 1072
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 83. Total number of bytes allocated: 1064
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 82. Total number of bytes allocated: 1056
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 81. Total number of bytes allocated: 1048
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 80. Total number of bytes allocated: 1040
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 79. Total number of bytes allocated: 1032
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 78. Total number of bytes allocated: 1024
Deleted a pair array from the list. Total number of dynamic memory allocations: 77. Total number of bytes allocated: 896

Deleting individual pair<long, long> pointers in pair array...
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 76. Total number of bytes allocated: 888
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 75. Total number of bytes allocated: 880
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 74. Total number of bytes allocated: 872
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 73. Total number of bytes allocated: 864
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 72. Total number of bytes allocated: 856
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 71. Total number of bytes allocated: 848
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 70. Total number of bytes allocated: 840
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 69. Total number of bytes allocated: 832
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 68. Total number of bytes allocated: 824
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 67. Total number of bytes allocated: 816
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 66. Total number of bytes allocated: 808
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 65. Total number of bytes allocated: 800
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 64. Total number of bytes allocated: 792
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 63. Total number of bytes allocated: 784
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 62. Total number of bytes allocated: 776
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 61. Total number of bytes allocated: 768
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 60. Total number of bytes allocated: 760
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 59. Total number of bytes allocated: 752
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 58. Total number of bytes allocated: 744
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 57. Total number of bytes allocated: 736
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 56. Total number of bytes allocated: 728
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 55. Total number of bytes allocated: 720
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 54. Total number of bytes allocated: 712
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 53. Total number of bytes allocated: 704
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 52. Total number of bytes allocated: 696
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 51. Total number of bytes allocated: 688
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 50. Total number of bytes allocated: 680
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 49. Total number of bytes allocated: 672
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 48. Total number of bytes allocated: 664
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 47. Total number of bytes allocated: 656
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 46. Total number of bytes allocated: 648
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 45. Total number of bytes allocated: 640
Deleted a pair array from the list. Total number of dynamic memory allocations: 44. Total number of bytes allocated: 512

Deleting individual pair<long, long> pointers in pair array...
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 43. Total number of bytes allocated: 504
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 42. Total number of bytes allocated: 496
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 41. Total number of bytes allocated: 488
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 40. Total number of bytes allocated: 480
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 39. Total number of bytes allocated: 472
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 38. Total number of bytes allocated: 464
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 37. Total number of bytes allocated: 456
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 36. Total number of bytes allocated: 448
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 35. Total number of bytes allocated: 440
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 34. Total number of bytes allocated: 432
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 33. Total number of bytes allocated: 424
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 32. Total number of bytes allocated: 416
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 31. Total number of bytes allocated: 408
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 30. Total number of bytes allocated: 400
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 29. Total number of bytes allocated: 392
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 28. Total number of bytes allocated: 384
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 27. Total number of bytes allocated: 376
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 26. Total number of bytes allocated: 368
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 25. Total number of bytes allocated: 360
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 24. Total number of bytes allocated: 352
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 23. Total number of bytes allocated: 344
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 22. Total number of bytes allocated: 336
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 21. Total number of bytes allocated: 328
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 20. Total number of bytes allocated: 320
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 19. Total number of bytes allocated: 312
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 18. Total number of bytes allocated: 304
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 17. Total number of bytes allocated: 296
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 16. Total number of bytes allocated: 288
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 15. Total number of bytes allocated: 280
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 14. Total number of bytes allocated: 272
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 13. Total number of bytes allocated: 264
Deleted a pair<long, long> pointer. Total number of dynamic memory allocations: 12. Total number of bytes allocated: 256
Deleted a pair array from the list. Total number of dynamic memory allocations: 11. Total number of bytes allocated: 128





Deleting list pointer of type <pair<long, long>**>... Total number of dynamic memory allocations: 0. Total number of bytes allocated: 0

Checking for memory leaks... No leak!

Press any key to continue . . .
*/