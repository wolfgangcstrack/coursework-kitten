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
		for (int j = 0; j < aBigNumber; j++)
		{
			long rlong1, rlong2;
			cout << "Creating new random pair<long, long> pointer that holds "
				<< (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG)
				<< "... ";
			newPair[j] = new pair<long, long>(rlong1, rlong2);          // uses operator new
			printStatistics();
		}
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
		for (int j = 0; j < aBigNumber; j++)
		{
			delete (*i)[j]; // uses operator delete
			cout << "Deleted a pair<long, long> pointer. ";
			printStatistics();
		}
		delete[] (*i);      // uses operator delete[]
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
Creating new random pair<long, long> pointer that holds 18030 and 1736... Total number of dynamic memory allocations: 5. Total number of bytes allocated: 168
Creating new random pair<long, long> pointer that holds 16097 and 29212... Total number of dynamic memory allocations: 6. Total number of bytes allocated: 176
Creating new random pair<long, long> pointer that holds 28964 and 31253... Total number of dynamic memory allocations: 7. Total number of bytes allocated: 184
Creating new random pair<long, long> pointer that holds 6665 and 10853... Total number of dynamic memory allocations: 8. Total number of bytes allocated: 192
Creating new random pair<long, long> pointer that holds 13149 and 21722... Total number of dynamic memory allocations: 9. Total number of bytes allocated: 200
Creating new random pair<long, long> pointer that holds 12151 and 9820... Total number of dynamic memory allocations: 10. Total number of bytes allocated: 208
Creating new random pair<long, long> pointer that holds 11792 and 1228... Total number of dynamic memory allocations: 11. Total number of bytes allocated: 216
Creating new random pair<long, long> pointer that holds 23797 and 1265... Total number of dynamic memory allocations: 12. Total number of bytes allocated: 224
Creating new random pair<long, long> pointer that holds 2914 and 225... Total number of dynamic memory allocations: 13. Total number of bytes allocated: 232
Creating new random pair<long, long> pointer that holds 27900 and 23167... Total number of dynamic memory allocations: 14. Total number of bytes allocated: 240
Creating new random pair<long, long> pointer that holds 12735 and 4861... Total number of dynamic memory allocations: 15. Total number of bytes allocated: 248
Creating new random pair<long, long> pointer that holds 620 and 26518... Total number of dynamic memory allocations: 16. Total number of bytes allocated: 256
Creating new random pair<long, long> pointer that holds 11562 and 25806... Total number of dynamic memory allocations: 17. Total number of bytes allocated: 264
Creating new random pair<long, long> pointer that holds 27775 and 11517... Total number of dynamic memory allocations: 18. Total number of bytes allocated: 272
Creating new random pair<long, long> pointer that holds 17105 and 21492... Total number of dynamic memory allocations: 19. Total number of bytes allocated: 280
Creating new random pair<long, long> pointer that holds 30464 and 247... Total number of dynamic memory allocations: 20. Total number of bytes allocated: 288
Creating new random pair<long, long> pointer that holds 25317 and 20838... Total number of dynamic memory allocations: 21. Total number of bytes allocated: 296
Creating new random pair<long, long> pointer that holds 2744 and 2502... Total number of dynamic memory allocations: 22. Total number of bytes allocated: 304
Creating new random pair<long, long> pointer that holds 27816 and 20497... Total number of dynamic memory allocations: 23. Total number of bytes allocated: 312
Creating new random pair<long, long> pointer that holds 12842 and 16750... Total number of dynamic memory allocations: 24. Total number of bytes allocated: 320
Creating new random pair<long, long> pointer that holds 30920 and 1730... Total number of dynamic memory allocations: 25. Total number of bytes allocated: 328
Creating new random pair<long, long> pointer that holds 22144 and 26299... Total number of dynamic memory allocations: 26. Total number of bytes allocated: 336
Creating new random pair<long, long> pointer that holds 7659 and 2373... Total number of dynamic memory allocations: 27. Total number of bytes allocated: 344
Creating new random pair<long, long> pointer that holds 18628 and 32645... Total number of dynamic memory allocations: 28. Total number of bytes allocated: 352
Creating new random pair<long, long> pointer that holds 25483 and 31951... Total number of dynamic memory allocations: 29. Total number of bytes allocated: 360
Creating new random pair<long, long> pointer that holds 27475 and 20531... Total number of dynamic memory allocations: 30. Total number of bytes allocated: 368
Creating new random pair<long, long> pointer that holds 22276 and 27545... Total number of dynamic memory allocations: 31. Total number of bytes allocated: 376
Creating new random pair<long, long> pointer that holds 3983 and 27774... Total number of dynamic memory allocations: 32. Total number of bytes allocated: 384
Creating new random pair<long, long> pointer that holds 30443 and 31694... Total number of dynamic memory allocations: 33. Total number of bytes allocated: 392
Creating new random pair<long, long> pointer that holds 23509 and 17784... Total number of dynamic memory allocations: 34. Total number of bytes allocated: 400
Creating new random pair<long, long> pointer that holds 26786 and 3495... Total number of dynamic memory allocations: 35. Total number of bytes allocated: 408
Creating new random pair<long, long> pointer that holds 19887 and 22732... Total number of dynamic memory allocations: 36. Total number of bytes allocated: 416

Creating new pair array... Total number of dynamic memory allocations: 38. Total number of bytes allocated: 556
Creating new random pair<long, long> pointer that holds 11305 and 1236... Total number of dynamic memory allocations: 39. Total number of bytes allocated: 564
Creating new random pair<long, long> pointer that holds 11338 and 25927... Total number of dynamic memory allocations: 40. Total number of bytes allocated: 572
Creating new random pair<long, long> pointer that holds 16951 and 16671... Total number of dynamic memory allocations: 41. Total number of bytes allocated: 580
Creating new random pair<long, long> pointer that holds 32554 and 18583... Total number of dynamic memory allocations: 42. Total number of bytes allocated: 588
Creating new random pair<long, long> pointer that holds 30858 and 2636... Total number of dynamic memory allocations: 43. Total number of bytes allocated: 596
Creating new random pair<long, long> pointer that holds 23836 and 27219... Total number of dynamic memory allocations: 44. Total number of bytes allocated: 604
Creating new random pair<long, long> pointer that holds 20603 and 29507... Total number of dynamic memory allocations: 45. Total number of bytes allocated: 612
Creating new random pair<long, long> pointer that holds 10092 and 22588... Total number of dynamic memory allocations: 46. Total number of bytes allocated: 620
Creating new random pair<long, long> pointer that holds 13269 and 30833... Total number of dynamic memory allocations: 47. Total number of bytes allocated: 628
Creating new random pair<long, long> pointer that holds 1369 and 30659... Total number of dynamic memory allocations: 48. Total number of bytes allocated: 636
Creating new random pair<long, long> pointer that holds 27623 and 23915... Total number of dynamic memory allocations: 49. Total number of bytes allocated: 644
Creating new random pair<long, long> pointer that holds 13254 and 28875... Total number of dynamic memory allocations: 50. Total number of bytes allocated: 652
Creating new random pair<long, long> pointer that holds 3800 and 3540... Total number of dynamic memory allocations: 51. Total number of bytes allocated: 660
Creating new random pair<long, long> pointer that holds 32050 and 13743... Total number of dynamic memory allocations: 52. Total number of bytes allocated: 668
Creating new random pair<long, long> pointer that holds 22331 and 1410... Total number of dynamic memory allocations: 53. Total number of bytes allocated: 676
Creating new random pair<long, long> pointer that holds 28138 and 19591... Total number of dynamic memory allocations: 54. Total number of bytes allocated: 684
Creating new random pair<long, long> pointer that holds 6627 and 988... Total number of dynamic memory allocations: 55. Total number of bytes allocated: 692
Creating new random pair<long, long> pointer that holds 6269 and 15783... Total number of dynamic memory allocations: 56. Total number of bytes allocated: 700
Creating new random pair<long, long> pointer that holds 19961 and 3718... Total number of dynamic memory allocations: 57. Total number of bytes allocated: 708
Creating new random pair<long, long> pointer that holds 32369 and 19305... Total number of dynamic memory allocations: 58. Total number of bytes allocated: 716
Creating new random pair<long, long> pointer that holds 23371 and 1857... Total number of dynamic memory allocations: 59. Total number of bytes allocated: 724
Creating new random pair<long, long> pointer that holds 28980 and 22317... Total number of dynamic memory allocations: 60. Total number of bytes allocated: 732
Creating new random pair<long, long> pointer that holds 8935 and 22796... Total number of dynamic memory allocations: 61. Total number of bytes allocated: 740
Creating new random pair<long, long> pointer that holds 32597 and 6045... Total number of dynamic memory allocations: 62. Total number of bytes allocated: 748
Creating new random pair<long, long> pointer that holds 30185 and 143... Total number of dynamic memory allocations: 63. Total number of bytes allocated: 756
Creating new random pair<long, long> pointer that holds 16884 and 1078... Total number of dynamic memory allocations: 64. Total number of bytes allocated: 764
Creating new random pair<long, long> pointer that holds 28305 and 29626... Total number of dynamic memory allocations: 65. Total number of bytes allocated: 772
Creating new random pair<long, long> pointer that holds 7800 and 6660... Total number of dynamic memory allocations: 66. Total number of bytes allocated: 780
Creating new random pair<long, long> pointer that holds 24473 and 11434... Total number of dynamic memory allocations: 67. Total number of bytes allocated: 788
Creating new random pair<long, long> pointer that holds 20608 and 23980... Total number of dynamic memory allocations: 68. Total number of bytes allocated: 796
Creating new random pair<long, long> pointer that holds 19909 and 23500... Total number of dynamic memory allocations: 69. Total number of bytes allocated: 804
Creating new random pair<long, long> pointer that holds 20507 and 16048... Total number of dynamic memory allocations: 70. Total number of bytes allocated: 812

Creating new pair array... Total number of dynamic memory allocations: 72. Total number of bytes allocated: 952
Creating new random pair<long, long> pointer that holds 10171 and 1348... Total number of dynamic memory allocations: 73. Total number of bytes allocated: 960
Creating new random pair<long, long> pointer that holds 26683 and 16367... Total number of dynamic memory allocations: 74. Total number of bytes allocated: 968
Creating new random pair<long, long> pointer that holds 12309 and 3472... Total number of dynamic memory allocations: 75. Total number of bytes allocated: 976
Creating new random pair<long, long> pointer that holds 4455 and 2411... Total number of dynamic memory allocations: 76. Total number of bytes allocated: 984
Creating new random pair<long, long> pointer that holds 19893 and 31080... Total number of dynamic memory allocations: 77. Total number of bytes allocated: 992
Creating new random pair<long, long> pointer that holds 25777 and 18255... Total number of dynamic memory allocations: 78. Total number of bytes allocated: 1000
Creating new random pair<long, long> pointer that holds 13912 and 25833... Total number of dynamic memory allocations: 79. Total number of bytes allocated: 1008
Creating new random pair<long, long> pointer that holds 15080 and 31281... Total number of dynamic memory allocations: 80. Total number of bytes allocated: 1016
Creating new random pair<long, long> pointer that holds 10094 and 30195... Total number of dynamic memory allocations: 81. Total number of bytes allocated: 1024
Creating new random pair<long, long> pointer that holds 19470 and 7316... Total number of dynamic memory allocations: 82. Total number of bytes allocated: 1032
Creating new random pair<long, long> pointer that holds 8490 and 19920... Total number of dynamic memory allocations: 83. Total number of bytes allocated: 1040
Creating new random pair<long, long> pointer that holds 25356 and 16817... Total number of dynamic memory allocations: 84. Total number of bytes allocated: 1048
Creating new random pair<long, long> pointer that holds 22485 and 15894... Total number of dynamic memory allocations: 85. Total number of bytes allocated: 1056
Creating new random pair<long, long> pointer that holds 31141 and 4471... Total number of dynamic memory allocations: 86. Total number of bytes allocated: 1064
Creating new random pair<long, long> pointer that holds 20327 and 17614... Total number of dynamic memory allocations: 87. Total number of bytes allocated: 1072
Creating new random pair<long, long> pointer that holds 20649 and 17872... Total number of dynamic memory allocations: 88. Total number of bytes allocated: 1080
Creating new random pair<long, long> pointer that holds 21848 and 5077... Total number of dynamic memory allocations: 89. Total number of bytes allocated: 1088
Creating new random pair<long, long> pointer that holds 22635 and 3366... Total number of dynamic memory allocations: 90. Total number of bytes allocated: 1096
Creating new random pair<long, long> pointer that holds 19636 and 10115... Total number of dynamic memory allocations: 91. Total number of bytes allocated: 1104
Creating new random pair<long, long> pointer that holds 32116 and 30246... Total number of dynamic memory allocations: 92. Total number of bytes allocated: 1112
Creating new random pair<long, long> pointer that holds 110 and 12427... Total number of dynamic memory allocations: 93. Total number of bytes allocated: 1120
Creating new random pair<long, long> pointer that holds 11641 and 18627... Total number of dynamic memory allocations: 94. Total number of bytes allocated: 1128
Creating new random pair<long, long> pointer that holds 28662 and 21794... Total number of dynamic memory allocations: 95. Total number of bytes allocated: 1136
Creating new random pair<long, long> pointer that holds 10379 and 28798... Total number of dynamic memory allocations: 96. Total number of bytes allocated: 1144
Creating new random pair<long, long> pointer that holds 18957 and 3428... Total number of dynamic memory allocations: 97. Total number of bytes allocated: 1152
Creating new random pair<long, long> pointer that holds 29326 and 23525... Total number of dynamic memory allocations: 98. Total number of bytes allocated: 1160
Creating new random pair<long, long> pointer that holds 2521 and 7923... Total number of dynamic memory allocations: 99. Total number of bytes allocated: 1168
Creating new random pair<long, long> pointer that holds 30956 and 30042... Total number of dynamic memory allocations: 100. Total number of bytes allocated: 1176
Creating new random pair<long, long> pointer that holds 27188 and 31713... Total number of dynamic memory allocations: 101. Total number of bytes allocated: 1184
Creating new random pair<long, long> pointer that holds 16523 and 6422... Total number of dynamic memory allocations: 102. Total number of bytes allocated: 1192
Creating new random pair<long, long> pointer that holds 9034 and 2256... Total number of dynamic memory allocations: 103. Total number of bytes allocated: 1200
Creating new random pair<long, long> pointer that holds 12284 and 11374... Total number of dynamic memory allocations: 104. Total number of bytes allocated: 1208

Creating new pair array... Total number of dynamic memory allocations: 106. Total number of bytes allocated: 1348
Creating new random pair<long, long> pointer that holds 9827 and 3671... Total number of dynamic memory allocations: 107. Total number of bytes allocated: 1356
Creating new random pair<long, long> pointer that holds 18933 and 14932... Total number of dynamic memory allocations: 108. Total number of bytes allocated: 1364
Creating new random pair<long, long> pointer that holds 19453 and 22952... Total number of dynamic memory allocations: 109. Total number of bytes allocated: 1372
Creating new random pair<long, long> pointer that holds 27649 and 14624... Total number of dynamic memory allocations: 110. Total number of bytes allocated: 1380
Creating new random pair<long, long> pointer that holds 10270 and 20592... Total number of dynamic memory allocations: 111. Total number of bytes allocated: 1388
Creating new random pair<long, long> pointer that holds 25974 and 23953... Total number of dynamic memory allocations: 112. Total number of bytes allocated: 1396
Creating new random pair<long, long> pointer that holds 30952 and 31743... Total number of dynamic memory allocations: 113. Total number of bytes allocated: 1404
Creating new random pair<long, long> pointer that holds 31399 and 7950... Total number of dynamic memory allocations: 114. Total number of bytes allocated: 1412
Creating new random pair<long, long> pointer that holds 25454 and 20393... Total number of dynamic memory allocations: 115. Total number of bytes allocated: 1420
Creating new random pair<long, long> pointer that holds 10332 and 20786... Total number of dynamic memory allocations: 116. Total number of bytes allocated: 1428
Creating new random pair<long, long> pointer that holds 29382 and 11884... Total number of dynamic memory allocations: 117. Total number of bytes allocated: 1436
Creating new random pair<long, long> pointer that holds 15231 and 30344... Total number of dynamic memory allocations: 118. Total number of bytes allocated: 1444
Creating new random pair<long, long> pointer that holds 3424 and 29651... Total number of dynamic memory allocations: 119. Total number of bytes allocated: 1452
Creating new random pair<long, long> pointer that holds 4376 and 12435... Total number of dynamic memory allocations: 120. Total number of bytes allocated: 1460
Creating new random pair<long, long> pointer that holds 21653 and 1049... Total number of dynamic memory allocations: 121. Total number of bytes allocated: 1468
Creating new random pair<long, long> pointer that holds 4732 and 28946... Total number of dynamic memory allocations: 122. Total number of bytes allocated: 1476
Creating new random pair<long, long> pointer that holds 8835 and 10130... Total number of dynamic memory allocations: 123. Total number of bytes allocated: 1484
Creating new random pair<long, long> pointer that holds 16832 and 20609... Total number of dynamic memory allocations: 124. Total number of bytes allocated: 1492
Creating new random pair<long, long> pointer that holds 6681 and 13639... Total number of dynamic memory allocations: 125. Total number of bytes allocated: 1500
Creating new random pair<long, long> pointer that holds 27252 and 11747... Total number of dynamic memory allocations: 126. Total number of bytes allocated: 1508
Creating new random pair<long, long> pointer that holds 32110 and 20704... Total number of dynamic memory allocations: 127. Total number of bytes allocated: 1516
Creating new random pair<long, long> pointer that holds 19086 and 31679... Total number of dynamic memory allocations: 128. Total number of bytes allocated: 1524
Creating new random pair<long, long> pointer that holds 15959 and 16328... Total number of dynamic memory allocations: 129. Total number of bytes allocated: 1532
Creating new random pair<long, long> pointer that holds 18341 and 24169... Total number of dynamic memory allocations: 130. Total number of bytes allocated: 1540
Creating new random pair<long, long> pointer that holds 32056 and 6539... Total number of dynamic memory allocations: 131. Total number of bytes allocated: 1548
Creating new random pair<long, long> pointer that holds 1120 and 32642... Total number of dynamic memory allocations: 132. Total number of bytes allocated: 1556
Creating new random pair<long, long> pointer that holds 27162 and 22403... Total number of dynamic memory allocations: 133. Total number of bytes allocated: 1564
Creating new random pair<long, long> pointer that holds 27181 and 15042... Total number of dynamic memory allocations: 134. Total number of bytes allocated: 1572
Creating new random pair<long, long> pointer that holds 15358 and 1971... Total number of dynamic memory allocations: 135. Total number of bytes allocated: 1580
Creating new random pair<long, long> pointer that holds 31542 and 2037... Total number of dynamic memory allocations: 136. Total number of bytes allocated: 1588
Creating new random pair<long, long> pointer that holds 12913 and 9971... Total number of dynamic memory allocations: 137. Total number of bytes allocated: 1596
Creating new random pair<long, long> pointer that holds 145 and 17988... Total number of dynamic memory allocations: 138. Total number of bytes allocated: 1604

Creating new pair array... Total number of dynamic memory allocations: 140. Total number of bytes allocated: 1744
Creating new random pair<long, long> pointer that holds 21857 and 26190... Total number of dynamic memory allocations: 141. Total number of bytes allocated: 1752
Creating new random pair<long, long> pointer that holds 26806 and 19638... Total number of dynamic memory allocations: 142. Total number of bytes allocated: 1760
Creating new random pair<long, long> pointer that holds 26415 and 24488... Total number of dynamic memory allocations: 143. Total number of bytes allocated: 1768
Creating new random pair<long, long> pointer that holds 27191 and 25591... Total number of dynamic memory allocations: 144. Total number of bytes allocated: 1776
Creating new random pair<long, long> pointer that holds 15621 and 32163... Total number of dynamic memory allocations: 145. Total number of bytes allocated: 1784
Creating new random pair<long, long> pointer that holds 16043 and 3415... Total number of dynamic memory allocations: 146. Total number of bytes allocated: 1792
Creating new random pair<long, long> pointer that holds 29034 and 6852... Total number of dynamic memory allocations: 147. Total number of bytes allocated: 1800
Creating new random pair<long, long> pointer that holds 2539 and 15125... Total number of dynamic memory allocations: 148. Total number of bytes allocated: 1808
Creating new random pair<long, long> pointer that holds 9492 and 7122... Total number of dynamic memory allocations: 149. Total number of bytes allocated: 1816
Creating new random pair<long, long> pointer that holds 16770 and 24030... Total number of dynamic memory allocations: 150. Total number of bytes allocated: 1824
Creating new random pair<long, long> pointer that holds 16893 and 2431... Total number of dynamic memory allocations: 151. Total number of bytes allocated: 1832
Creating new random pair<long, long> pointer that holds 10334 and 27537... Total number of dynamic memory allocations: 152. Total number of bytes allocated: 1840
Creating new random pair<long, long> pointer that holds 29881 and 27979... Total number of dynamic memory allocations: 153. Total number of bytes allocated: 1848
Creating new random pair<long, long> pointer that holds 13004 and 17221... Total number of dynamic memory allocations: 154. Total number of bytes allocated: 1856
Creating new random pair<long, long> pointer that holds 20486 and 30116... Total number of dynamic memory allocations: 155. Total number of bytes allocated: 1864
Creating new random pair<long, long> pointer that holds 26275 and 4749... Total number of dynamic memory allocations: 156. Total number of bytes allocated: 1872
Creating new random pair<long, long> pointer that holds 20133 and 9554... Total number of dynamic memory allocations: 157. Total number of bytes allocated: 1880
Creating new random pair<long, long> pointer that holds 3006 and 8187... Total number of dynamic memory allocations: 158. Total number of bytes allocated: 1888
Creating new random pair<long, long> pointer that holds 10088 and 4626... Total number of dynamic memory allocations: 159. Total number of bytes allocated: 1896
Creating new random pair<long, long> pointer that holds 16560 and 7906... Total number of dynamic memory allocations: 160. Total number of bytes allocated: 1904
Creating new random pair<long, long> pointer that holds 10125 and 30337... Total number of dynamic memory allocations: 161. Total number of bytes allocated: 1912
Creating new random pair<long, long> pointer that holds 18356 and 28768... Total number of dynamic memory allocations: 162. Total number of bytes allocated: 1920
Creating new random pair<long, long> pointer that holds 1866 and 6972... Total number of dynamic memory allocations: 163. Total number of bytes allocated: 1928
Creating new random pair<long, long> pointer that holds 8163 and 30108... Total number of dynamic memory allocations: 164. Total number of bytes allocated: 1936
Creating new random pair<long, long> pointer that holds 27817 and 23366... Total number of dynamic memory allocations: 165. Total number of bytes allocated: 1944
Creating new random pair<long, long> pointer that holds 16042 and 22349... Total number of dynamic memory allocations: 166. Total number of bytes allocated: 1952
Creating new random pair<long, long> pointer that holds 4246 and 18346... Total number of dynamic memory allocations: 167. Total number of bytes allocated: 1960
Creating new random pair<long, long> pointer that holds 32122 and 26236... Total number of dynamic memory allocations: 168. Total number of bytes allocated: 1968
Creating new random pair<long, long> pointer that holds 14902 and 11873... Total number of dynamic memory allocations: 169. Total number of bytes allocated: 1976
Creating new random pair<long, long> pointer that holds 4033 and 31370... Total number of dynamic memory allocations: 170. Total number of bytes allocated: 1984
Creating new random pair<long, long> pointer that holds 1147 and 2165... Total number of dynamic memory allocations: 171. Total number of bytes allocated: 1992
Creating new random pair<long, long> pointer that holds 5402 and 28788... Total number of dynamic memory allocations: 172. Total number of bytes allocated: 2000

Creating new pair array... Total number of dynamic memory allocations: 174. Total number of bytes allocated: 2140
Creating new random pair<long, long> pointer that holds 8694 and 4967... Total number of dynamic memory allocations: 175. Total number of bytes allocated: 2148
Creating new random pair<long, long> pointer that holds 7104 and 12118... Total number of dynamic memory allocations: 176. Total number of bytes allocated: 2156
Creating new random pair<long, long> pointer that holds 4844 and 6607... Total number of dynamic memory allocations: 177. Total number of bytes allocated: 2164
Creating new random pair<long, long> pointer that holds 10057 and 22062... Total number of dynamic memory allocations: 178. Total number of bytes allocated: 2172
Creating new random pair<long, long> pointer that holds 427 and 12098... Total number of dynamic memory allocations: 179. Total number of bytes allocated: 2180
Creating new random pair<long, long> pointer that holds 3985 and 30435... Total number of dynamic memory allocations: 180. Total number of bytes allocated: 2188
Creating new random pair<long, long> pointer that holds 14622 and 25464... Total number of dynamic memory allocations: 181. Total number of bytes allocated: 2196
Creating new random pair<long, long> pointer that holds 19444 and 646... Total number of dynamic memory allocations: 182. Total number of bytes allocated: 2204
Creating new random pair<long, long> pointer that holds 27040 and 12462... Total number of dynamic memory allocations: 183. Total number of bytes allocated: 2212
Creating new random pair<long, long> pointer that holds 32448 and 19159... Total number of dynamic memory allocations: 184. Total number of bytes allocated: 2220
Creating new random pair<long, long> pointer that holds 12302 and 10570... Total number of dynamic memory allocations: 185. Total number of bytes allocated: 2228
Creating new random pair<long, long> pointer that holds 21737 and 15627... Total number of dynamic memory allocations: 186. Total number of bytes allocated: 2236
Creating new random pair<long, long> pointer that holds 4896 and 10430... Total number of dynamic memory allocations: 187. Total number of bytes allocated: 2244
Creating new random pair<long, long> pointer that holds 3583 and 14796... Total number of dynamic memory allocations: 188. Total number of bytes allocated: 2252
Creating new random pair<long, long> pointer that holds 27385 and 2990... Total number of dynamic memory allocations: 189. Total number of bytes allocated: 2260
Creating new random pair<long, long> pointer that holds 16478 and 11906... Total number of dynamic memory allocations: 190. Total number of bytes allocated: 2268
Creating new random pair<long, long> pointer that holds 26364 and 13141... Total number of dynamic memory allocations: 191. Total number of bytes allocated: 2276
Creating new random pair<long, long> pointer that holds 11685 and 21457... Total number of dynamic memory allocations: 192. Total number of bytes allocated: 2284
Creating new random pair<long, long> pointer that holds 9698 and 22565... Total number of dynamic memory allocations: 193. Total number of bytes allocated: 2292
Creating new random pair<long, long> pointer that holds 15209 and 13666... Total number of dynamic memory allocations: 194. Total number of bytes allocated: 2300
Creating new random pair<long, long> pointer that holds 5129 and 28589... Total number of dynamic memory allocations: 195. Total number of bytes allocated: 2308
Creating new random pair<long, long> pointer that holds 25642 and 26343... Total number of dynamic memory allocations: 196. Total number of bytes allocated: 2316
Creating new random pair<long, long> pointer that holds 1039 and 10688... Total number of dynamic memory allocations: 197. Total number of bytes allocated: 2324
Creating new random pair<long, long> pointer that holds 13445 and 2649... Total number of dynamic memory allocations: 198. Total number of bytes allocated: 2332
Creating new random pair<long, long> pointer that holds 13728 and 18644... Total number of dynamic memory allocations: 199. Total number of bytes allocated: 2340
Creating new random pair<long, long> pointer that holds 10412 and 2948... Total number of dynamic memory allocations: 200. Total number of bytes allocated: 2348
Creating new random pair<long, long> pointer that holds 16012 and 22952... Total number of dynamic memory allocations: 201. Total number of bytes allocated: 2356
Creating new random pair<long, long> pointer that holds 32276 and 13510... Total number of dynamic memory allocations: 202. Total number of bytes allocated: 2364
Creating new random pair<long, long> pointer that holds 2589 and 3626... Total number of dynamic memory allocations: 203. Total number of bytes allocated: 2372
Creating new random pair<long, long> pointer that holds 19821 and 276... Total number of dynamic memory allocations: 204. Total number of bytes allocated: 2380
Creating new random pair<long, long> pointer that holds 25255 and 16279... Total number of dynamic memory allocations: 205. Total number of bytes allocated: 2388
Creating new random pair<long, long> pointer that holds 215 and 20285... Total number of dynamic memory allocations: 206. Total number of bytes allocated: 2396

Creating new pair array... Total number of dynamic memory allocations: 208. Total number of bytes allocated: 2536
Creating new random pair<long, long> pointer that holds 14688 and 23524... Total number of dynamic memory allocations: 209. Total number of bytes allocated: 2544
Creating new random pair<long, long> pointer that holds 31315 and 23155... Total number of dynamic memory allocations: 210. Total number of bytes allocated: 2552
Creating new random pair<long, long> pointer that holds 8306 and 16989... Total number of dynamic memory allocations: 211. Total number of bytes allocated: 2560
Creating new random pair<long, long> pointer that holds 32375 and 7175... Total number of dynamic memory allocations: 212. Total number of bytes allocated: 2568
Creating new random pair<long, long> pointer that holds 11087 and 21388... Total number of dynamic memory allocations: 213. Total number of bytes allocated: 2576
Creating new random pair<long, long> pointer that holds 14183 and 31348... Total number of dynamic memory allocations: 214. Total number of bytes allocated: 2584
Creating new random pair<long, long> pointer that holds 10565 and 14428... Total number of dynamic memory allocations: 215. Total number of bytes allocated: 2592
Creating new random pair<long, long> pointer that holds 25600 and 27039... Total number of dynamic memory allocations: 216. Total number of bytes allocated: 2600
Creating new random pair<long, long> pointer that holds 28242 and 9342... Total number of dynamic memory allocations: 217. Total number of bytes allocated: 2608
Creating new random pair<long, long> pointer that holds 1878 and 24669... Total number of dynamic memory allocations: 218. Total number of bytes allocated: 2616
Creating new random pair<long, long> pointer that holds 7737 and 6156... Total number of dynamic memory allocations: 219. Total number of bytes allocated: 2624
Creating new random pair<long, long> pointer that holds 11361 and 18230... Total number of dynamic memory allocations: 220. Total number of bytes allocated: 2632
Creating new random pair<long, long> pointer that holds 11733 and 25708... Total number of dynamic memory allocations: 221. Total number of bytes allocated: 2640
Creating new random pair<long, long> pointer that holds 4595 and 17513... Total number of dynamic memory allocations: 222. Total number of bytes allocated: 2648
Creating new random pair<long, long> pointer that holds 3758 and 30840... Total number of dynamic memory allocations: 223. Total number of bytes allocated: 2656
Creating new random pair<long, long> pointer that holds 21229 and 2351... Total number of dynamic memory allocations: 224. Total number of bytes allocated: 2664
Creating new random pair<long, long> pointer that holds 14538 and 14299... Total number of dynamic memory allocations: 225. Total number of bytes allocated: 2672
Creating new random pair<long, long> pointer that holds 24243 and 1092... Total number of dynamic memory allocations: 226. Total number of bytes allocated: 2680
Creating new random pair<long, long> pointer that holds 1734 and 25022... Total number of dynamic memory allocations: 227. Total number of bytes allocated: 2688
Creating new random pair<long, long> pointer that holds 21981 and 7588... Total number of dynamic memory allocations: 228. Total number of bytes allocated: 2696
Creating new random pair<long, long> pointer that holds 6181 and 19109... Total number of dynamic memory allocations: 229. Total number of bytes allocated: 2704
Creating new random pair<long, long> pointer that holds 7984 and 24466... Total number of dynamic memory allocations: 230. Total number of bytes allocated: 2712
Creating new random pair<long, long> pointer that holds 11751 and 28051... Total number of dynamic memory allocations: 231. Total number of bytes allocated: 2720
Creating new random pair<long, long> pointer that holds 18636 and 12511... Total number of dynamic memory allocations: 232. Total number of bytes allocated: 2728
Creating new random pair<long, long> pointer that holds 13661 and 6261... Total number of dynamic memory allocations: 233. Total number of bytes allocated: 2736
Creating new random pair<long, long> pointer that holds 2470 and 1129... Total number of dynamic memory allocations: 234. Total number of bytes allocated: 2744
Creating new random pair<long, long> pointer that holds 30013 and 14269... Total number of dynamic memory allocations: 235. Total number of bytes allocated: 2752
Creating new random pair<long, long> pointer that holds 30521 and 8674... Total number of dynamic memory allocations: 236. Total number of bytes allocated: 2760
Creating new random pair<long, long> pointer that holds 4338 and 1358... Total number of dynamic memory allocations: 237. Total number of bytes allocated: 2768
Creating new random pair<long, long> pointer that holds 17273 and 27603... Total number of dynamic memory allocations: 238. Total number of bytes allocated: 2776
Creating new random pair<long, long> pointer that holds 22069 and 7832... Total number of dynamic memory allocations: 239. Total number of bytes allocated: 2784
Creating new random pair<long, long> pointer that holds 5897 and 18144... Total number of dynamic memory allocations: 240. Total number of bytes allocated: 2792

Creating new pair array... Total number of dynamic memory allocations: 242. Total number of bytes allocated: 2932
Creating new random pair<long, long> pointer that holds 2273 and 17924... Total number of dynamic memory allocations: 243. Total number of bytes allocated: 2940
Creating new random pair<long, long> pointer that holds 23469 and 1613... Total number of dynamic memory allocations: 244. Total number of bytes allocated: 2948
Creating new random pair<long, long> pointer that holds 8451 and 21394... Total number of dynamic memory allocations: 245. Total number of bytes allocated: 2956
Creating new random pair<long, long> pointer that holds 2818 and 449... Total number of dynamic memory allocations: 246. Total number of bytes allocated: 2964
Creating new random pair<long, long> pointer that holds 12081 and 6336... Total number of dynamic memory allocations: 247. Total number of bytes allocated: 2972
Creating new random pair<long, long> pointer that holds 21869 and 14410... Total number of dynamic memory allocations: 248. Total number of bytes allocated: 2980
Creating new random pair<long, long> pointer that holds 23326 and 15279... Total number of dynamic memory allocations: 249. Total number of bytes allocated: 2988
Creating new random pair<long, long> pointer that holds 13649 and 9378... Total number of dynamic memory allocations: 250. Total number of bytes allocated: 2996
Creating new random pair<long, long> pointer that holds 12395 and 19841... Total number of dynamic memory allocations: 251. Total number of bytes allocated: 3004
Creating new random pair<long, long> pointer that holds 17029 and 9905... Total number of dynamic memory allocations: 252. Total number of bytes allocated: 3012
Creating new random pair<long, long> pointer that holds 11711 and 8197... Total number of dynamic memory allocations: 253. Total number of bytes allocated: 3020
Creating new random pair<long, long> pointer that holds 23045 and 9810... Total number of dynamic memory allocations: 254. Total number of bytes allocated: 3028
Creating new random pair<long, long> pointer that holds 18969 and 7830... Total number of dynamic memory allocations: 255. Total number of bytes allocated: 3036
Creating new random pair<long, long> pointer that holds 28135 and 21338... Total number of dynamic memory allocations: 256. Total number of bytes allocated: 3044
Creating new random pair<long, long> pointer that holds 25701 and 11840... Total number of dynamic memory allocations: 257. Total number of bytes allocated: 3052
Creating new random pair<long, long> pointer that holds 4497 and 9943... Total number of dynamic memory allocations: 258. Total number of bytes allocated: 3060
Creating new random pair<long, long> pointer that holds 20814 and 22821... Total number of dynamic memory allocations: 259. Total number of bytes allocated: 3068
Creating new random pair<long, long> pointer that holds 5674 and 2453... Total number of dynamic memory allocations: 260. Total number of bytes allocated: 3076
Creating new random pair<long, long> pointer that holds 31572 and 18719... Total number of dynamic memory allocations: 261. Total number of bytes allocated: 3084
Creating new random pair<long, long> pointer that holds 19278 and 17383... Total number of dynamic memory allocations: 262. Total number of bytes allocated: 3092
Creating new random pair<long, long> pointer that holds 18718 and 21927... Total number of dynamic memory allocations: 263. Total number of bytes allocated: 3100
Creating new random pair<long, long> pointer that holds 14342 and 6819... Total number of dynamic memory allocations: 264. Total number of bytes allocated: 3108
Creating new random pair<long, long> pointer that holds 15889 and 10486... Total number of dynamic memory allocations: 265. Total number of bytes allocated: 3116
Creating new random pair<long, long> pointer that holds 24567 and 15727... Total number of dynamic memory allocations: 266. Total number of bytes allocated: 3124
Creating new random pair<long, long> pointer that holds 2337 and 16489... Total number of dynamic memory allocations: 267. Total number of bytes allocated: 3132
Creating new random pair<long, long> pointer that holds 26841 and 27195... Total number of dynamic memory allocations: 268. Total number of bytes allocated: 3140
Creating new random pair<long, long> pointer that holds 30183 and 19498... Total number of dynamic memory allocations: 269. Total number of bytes allocated: 3148
Creating new random pair<long, long> pointer that holds 13355 and 27151... Total number of dynamic memory allocations: 270. Total number of bytes allocated: 3156
Creating new random pair<long, long> pointer that holds 29684 and 12813... Total number of dynamic memory allocations: 271. Total number of bytes allocated: 3164
Creating new random pair<long, long> pointer that holds 16677 and 19207... Total number of dynamic memory allocations: 272. Total number of bytes allocated: 3172
Creating new random pair<long, long> pointer that holds 10342 and 14264... Total number of dynamic memory allocations: 273. Total number of bytes allocated: 3180
Creating new random pair<long, long> pointer that holds 27375 and 31644... Total number of dynamic memory allocations: 274. Total number of bytes allocated: 3188





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