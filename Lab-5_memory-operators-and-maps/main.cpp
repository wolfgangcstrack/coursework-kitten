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
	Falsegrind::startFalsegrind();            // start memory monitor application

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

	Falsegrind::closeFalsegrind();            // close memory monitor application

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
Creating new random pair<long, long> pointer that holds 25306 and 30683... Total number of dynamic memory allocations: 5. Total number of bytes allocated: 168
Creating new random pair<long, long> pointer that holds 9732 and 1348... Total number of dynamic memory allocations: 6. Total number of bytes allocated: 176
Creating new random pair<long, long> pointer that holds 22210 and 21825... Total number of dynamic memory allocations: 7. Total number of bytes allocated: 184
Creating new random pair<long, long> pointer that holds 23704 and 6533... Total number of dynamic memory allocations: 8. Total number of bytes allocated: 192
Creating new random pair<long, long> pointer that holds 30196 and 3514... Total number of dynamic memory allocations: 9. Total number of bytes allocated: 200
Creating new random pair<long, long> pointer that holds 26153 and 19031... Total number of dynamic memory allocations: 10. Total number of bytes allocated: 208
Creating new random pair<long, long> pointer that holds 18478 and 18231... Total number of dynamic memory allocations: 11. Total number of bytes allocated: 216
Creating new random pair<long, long> pointer that holds 21623 and 21459... Total number of dynamic memory allocations: 12. Total number of bytes allocated: 224
Creating new random pair<long, long> pointer that holds 6746 and 14917... Total number of dynamic memory allocations: 13. Total number of bytes allocated: 232
Creating new random pair<long, long> pointer that holds 29156 and 11145... Total number of dynamic memory allocations: 14. Total number of bytes allocated: 240
Creating new random pair<long, long> pointer that holds 20742 and 18064... Total number of dynamic memory allocations: 15. Total number of bytes allocated: 248
Creating new random pair<long, long> pointer that holds 18309 and 22818... Total number of dynamic memory allocations: 16. Total number of bytes allocated: 256
Creating new random pair<long, long> pointer that holds 16148 and 12454... Total number of dynamic memory allocations: 17. Total number of bytes allocated: 264
Creating new random pair<long, long> pointer that holds 18809 and 16964... Total number of dynamic memory allocations: 18. Total number of bytes allocated: 272
Creating new random pair<long, long> pointer that holds 21683 and 27902... Total number of dynamic memory allocations: 19. Total number of bytes allocated: 280
Creating new random pair<long, long> pointer that holds 7545 and 28086... Total number of dynamic memory allocations: 20. Total number of bytes allocated: 288
Creating new random pair<long, long> pointer that holds 14990 and 7225... Total number of dynamic memory allocations: 21. Total number of bytes allocated: 296
Creating new random pair<long, long> pointer that holds 12209 and 453... Total number of dynamic memory allocations: 22. Total number of bytes allocated: 304
Creating new random pair<long, long> pointer that holds 11587 and 7335... Total number of dynamic memory allocations: 23. Total number of bytes allocated: 312
Creating new random pair<long, long> pointer that holds 2510 and 486... Total number of dynamic memory allocations: 24. Total number of bytes allocated: 320
Creating new random pair<long, long> pointer that holds 11542 and 21773... Total number of dynamic memory allocations: 25. Total number of bytes allocated: 328
Creating new random pair<long, long> pointer that holds 8281 and 3996... Total number of dynamic memory allocations: 26. Total number of bytes allocated: 336
Creating new random pair<long, long> pointer that holds 21991 and 7334... Total number of dynamic memory allocations: 27. Total number of bytes allocated: 344
Creating new random pair<long, long> pointer that holds 2627 and 12956... Total number of dynamic memory allocations: 28. Total number of bytes allocated: 352
Creating new random pair<long, long> pointer that holds 29537 and 25703... Total number of dynamic memory allocations: 29. Total number of bytes allocated: 360
Creating new random pair<long, long> pointer that holds 22209 and 27696... Total number of dynamic memory allocations: 30. Total number of bytes allocated: 368
Creating new random pair<long, long> pointer that holds 9589 and 1415... Total number of dynamic memory allocations: 31. Total number of bytes allocated: 376
Creating new random pair<long, long> pointer that holds 30042 and 6617... Total number of dynamic memory allocations: 32. Total number of bytes allocated: 384
Creating new random pair<long, long> pointer that holds 10502 and 22847... Total number of dynamic memory allocations: 33. Total number of bytes allocated: 392
Creating new random pair<long, long> pointer that holds 25661 and 27448... Total number of dynamic memory allocations: 34. Total number of bytes allocated: 400
Creating new random pair<long, long> pointer that holds 6374 and 32207... Total number of dynamic memory allocations: 35. Total number of bytes allocated: 408
Creating new random pair<long, long> pointer that holds 6361 and 28462... Total number of dynamic memory allocations: 36. Total number of bytes allocated: 416

Creating new pair array... Total number of dynamic memory allocations: 38. Total number of bytes allocated: 556
Creating new random pair<long, long> pointer that holds 15106 and 27841... Total number of dynamic memory allocations: 39. Total number of bytes allocated: 564
Creating new random pair<long, long> pointer that holds 22184 and 31811... Total number of dynamic memory allocations: 40. Total number of bytes allocated: 572
Creating new random pair<long, long> pointer that holds 11737 and 18033... Total number of dynamic memory allocations: 41. Total number of bytes allocated: 580
Creating new random pair<long, long> pointer that holds 26699 and 30788... Total number of dynamic memory allocations: 42. Total number of bytes allocated: 588
Creating new random pair<long, long> pointer that holds 2611 and 30413... Total number of dynamic memory allocations: 43. Total number of bytes allocated: 596
Creating new random pair<long, long> pointer that holds 28380 and 17200... Total number of dynamic memory allocations: 44. Total number of bytes allocated: 604
Creating new random pair<long, long> pointer that holds 19727 and 5978... Total number of dynamic memory allocations: 45. Total number of bytes allocated: 612
Creating new random pair<long, long> pointer that holds 15232 and 18774... Total number of dynamic memory allocations: 46. Total number of bytes allocated: 620
Creating new random pair<long, long> pointer that holds 7645 and 12920... Total number of dynamic memory allocations: 47. Total number of bytes allocated: 628
Creating new random pair<long, long> pointer that holds 26427 and 183... Total number of dynamic memory allocations: 48. Total number of bytes allocated: 636
Creating new random pair<long, long> pointer that holds 17645 and 19430... Total number of dynamic memory allocations: 49. Total number of bytes allocated: 644
Creating new random pair<long, long> pointer that holds 7433 and 21937... Total number of dynamic memory allocations: 50. Total number of bytes allocated: 652
Creating new random pair<long, long> pointer that holds 26152 and 21128... Total number of dynamic memory allocations: 51. Total number of bytes allocated: 660
Creating new random pair<long, long> pointer that holds 18986 and 19167... Total number of dynamic memory allocations: 52. Total number of bytes allocated: 668
Creating new random pair<long, long> pointer that holds 21502 and 24424... Total number of dynamic memory allocations: 53. Total number of bytes allocated: 676
Creating new random pair<long, long> pointer that holds 10429 and 20539... Total number of dynamic memory allocations: 54. Total number of bytes allocated: 684
Creating new random pair<long, long> pointer that holds 3743 and 26108... Total number of dynamic memory allocations: 55. Total number of bytes allocated: 692
Creating new random pair<long, long> pointer that holds 22672 and 5509... Total number of dynamic memory allocations: 56. Total number of bytes allocated: 700
Creating new random pair<long, long> pointer that holds 17262 and 14759... Total number of dynamic memory allocations: 57. Total number of bytes allocated: 708
Creating new random pair<long, long> pointer that holds 31287 and 23529... Total number of dynamic memory allocations: 58. Total number of bytes allocated: 716
Creating new random pair<long, long> pointer that holds 24754 and 3201... Total number of dynamic memory allocations: 59. Total number of bytes allocated: 724
Creating new random pair<long, long> pointer that holds 91 and 2780... Total number of dynamic memory allocations: 60. Total number of bytes allocated: 732
Creating new random pair<long, long> pointer that holds 4495 and 19291... Total number of dynamic memory allocations: 61. Total number of bytes allocated: 740
Creating new random pair<long, long> pointer that holds 11093 and 3143... Total number of dynamic memory allocations: 62. Total number of bytes allocated: 748
Creating new random pair<long, long> pointer that holds 13878 and 31486... Total number of dynamic memory allocations: 63. Total number of bytes allocated: 756
Creating new random pair<long, long> pointer that holds 25339 and 13287... Total number of dynamic memory allocations: 64. Total number of bytes allocated: 764
Creating new random pair<long, long> pointer that holds 11352 and 31412... Total number of dynamic memory allocations: 65. Total number of bytes allocated: 772
Creating new random pair<long, long> pointer that holds 25274 and 13811... Total number of dynamic memory allocations: 66. Total number of bytes allocated: 780
Creating new random pair<long, long> pointer that holds 31712 and 20490... Total number of dynamic memory allocations: 67. Total number of bytes allocated: 788
Creating new random pair<long, long> pointer that holds 27622 and 28928... Total number of dynamic memory allocations: 68. Total number of bytes allocated: 796
Creating new random pair<long, long> pointer that holds 15329 and 24531... Total number of dynamic memory allocations: 69. Total number of bytes allocated: 804
Creating new random pair<long, long> pointer that holds 29261 and 3875... Total number of dynamic memory allocations: 70. Total number of bytes allocated: 812

Creating new pair array... Total number of dynamic memory allocations: 72. Total number of bytes allocated: 952
Creating new random pair<long, long> pointer that holds 17357 and 14448... Total number of dynamic memory allocations: 73. Total number of bytes allocated: 960
Creating new random pair<long, long> pointer that holds 30482 and 16981... Total number of dynamic memory allocations: 74. Total number of bytes allocated: 968
Creating new random pair<long, long> pointer that holds 31977 and 20815... Total number of dynamic memory allocations: 75. Total number of bytes allocated: 976
Creating new random pair<long, long> pointer that holds 1465 and 8219... Total number of dynamic memory allocations: 76. Total number of bytes allocated: 984
Creating new random pair<long, long> pointer that holds 26621 and 25522... Total number of dynamic memory allocations: 77. Total number of bytes allocated: 992
Creating new random pair<long, long> pointer that holds 1918 and 24678... Total number of dynamic memory allocations: 78. Total number of bytes allocated: 1000
Creating new random pair<long, long> pointer that holds 11088 and 16562... Total number of dynamic memory allocations: 79. Total number of bytes allocated: 1008
Creating new random pair<long, long> pointer that holds 24811 and 951... Total number of dynamic memory allocations: 80. Total number of bytes allocated: 1016
Creating new random pair<long, long> pointer that holds 15571 and 18563... Total number of dynamic memory allocations: 81. Total number of bytes allocated: 1024
Creating new random pair<long, long> pointer that holds 3497 and 9352... Total number of dynamic memory allocations: 82. Total number of bytes allocated: 1032
Creating new random pair<long, long> pointer that holds 31901 and 26361... Total number of dynamic memory allocations: 83. Total number of bytes allocated: 1040
Creating new random pair<long, long> pointer that holds 11927 and 30696... Total number of dynamic memory allocations: 84. Total number of bytes allocated: 1048
Creating new random pair<long, long> pointer that holds 21399 and 14667... Total number of dynamic memory allocations: 85. Total number of bytes allocated: 1056
Creating new random pair<long, long> pointer that holds 15897 and 16741... Total number of dynamic memory allocations: 86. Total number of bytes allocated: 1064
Creating new random pair<long, long> pointer that holds 10873 and 16664... Total number of dynamic memory allocations: 87. Total number of bytes allocated: 1072
Creating new random pair<long, long> pointer that holds 24243 and 15918... Total number of dynamic memory allocations: 88. Total number of bytes allocated: 1080
Creating new random pair<long, long> pointer that holds 19701 and 18599... Total number of dynamic memory allocations: 89. Total number of bytes allocated: 1088
Creating new random pair<long, long> pointer that holds 30678 and 19321... Total number of dynamic memory allocations: 90. Total number of bytes allocated: 1096
Creating new random pair<long, long> pointer that holds 3377 and 23667... Total number of dynamic memory allocations: 91. Total number of bytes allocated: 1104
Creating new random pair<long, long> pointer that holds 5369 and 19491... Total number of dynamic memory allocations: 92. Total number of bytes allocated: 1112
Creating new random pair<long, long> pointer that holds 15227 and 32231... Total number of dynamic memory allocations: 93. Total number of bytes allocated: 1120
Creating new random pair<long, long> pointer that holds 15084 and 4502... Total number of dynamic memory allocations: 94. Total number of bytes allocated: 1128
Creating new random pair<long, long> pointer that holds 17977 and 29542... Total number of dynamic memory allocations: 95. Total number of bytes allocated: 1136
Creating new random pair<long, long> pointer that holds 10089 and 19440... Total number of dynamic memory allocations: 96. Total number of bytes allocated: 1144
Creating new random pair<long, long> pointer that holds 5662 and 22926... Total number of dynamic memory allocations: 97. Total number of bytes allocated: 1152
Creating new random pair<long, long> pointer that holds 12013 and 17762... Total number of dynamic memory allocations: 98. Total number of bytes allocated: 1160
Creating new random pair<long, long> pointer that holds 31396 and 22974... Total number of dynamic memory allocations: 99. Total number of bytes allocated: 1168
Creating new random pair<long, long> pointer that holds 11461 and 27861... Total number of dynamic memory allocations: 100. Total number of bytes allocated: 1176
Creating new random pair<long, long> pointer that holds 15030 and 10709... Total number of dynamic memory allocations: 101. Total number of bytes allocated: 1184
Creating new random pair<long, long> pointer that holds 14700 and 29652... Total number of dynamic memory allocations: 102. Total number of bytes allocated: 1192
Creating new random pair<long, long> pointer that holds 7596 and 14653... Total number of dynamic memory allocations: 103. Total number of bytes allocated: 1200
Creating new random pair<long, long> pointer that holds 6932 and 934... Total number of dynamic memory allocations: 104. Total number of bytes allocated: 1208

Creating new pair array... Total number of dynamic memory allocations: 106. Total number of bytes allocated: 1348
Creating new random pair<long, long> pointer that holds 125 and 12073... Total number of dynamic memory allocations: 107. Total number of bytes allocated: 1356
Creating new random pair<long, long> pointer that holds 9347 and 19898... Total number of dynamic memory allocations: 108. Total number of bytes allocated: 1364
Creating new random pair<long, long> pointer that holds 19248 and 7706... Total number of dynamic memory allocations: 109. Total number of bytes allocated: 1372
Creating new random pair<long, long> pointer that holds 30240 and 31561... Total number of dynamic memory allocations: 110. Total number of bytes allocated: 1380
Creating new random pair<long, long> pointer that holds 23188 and 4264... Total number of dynamic memory allocations: 111. Total number of bytes allocated: 1388
Creating new random pair<long, long> pointer that holds 21838 and 16438... Total number of dynamic memory allocations: 112. Total number of bytes allocated: 1396
Creating new random pair<long, long> pointer that holds 12849 and 21375... Total number of dynamic memory allocations: 113. Total number of bytes allocated: 1404
Creating new random pair<long, long> pointer that holds 3576 and 5433... Total number of dynamic memory allocations: 114. Total number of bytes allocated: 1412
Creating new random pair<long, long> pointer that holds 2686 and 8360... Total number of dynamic memory allocations: 115. Total number of bytes allocated: 1420
Creating new random pair<long, long> pointer that holds 4717 and 23868... Total number of dynamic memory allocations: 116. Total number of bytes allocated: 1428
Creating new random pair<long, long> pointer that holds 3925 and 4106... Total number of dynamic memory allocations: 117. Total number of bytes allocated: 1436
Creating new random pair<long, long> pointer that holds 19823 and 31237... Total number of dynamic memory allocations: 118. Total number of bytes allocated: 1444
Creating new random pair<long, long> pointer that holds 25251 and 28976... Total number of dynamic memory allocations: 119. Total number of bytes allocated: 1452
Creating new random pair<long, long> pointer that holds 23174 and 5142... Total number of dynamic memory allocations: 120. Total number of bytes allocated: 1460
Creating new random pair<long, long> pointer that holds 14180 and 29260... Total number of dynamic memory allocations: 121. Total number of bytes allocated: 1468
Creating new random pair<long, long> pointer that holds 6299 and 6609... Total number of dynamic memory allocations: 122. Total number of bytes allocated: 1476
Creating new random pair<long, long> pointer that holds 6351 and 14460... Total number of dynamic memory allocations: 123. Total number of bytes allocated: 1484
Creating new random pair<long, long> pointer that holds 19137 and 14816... Total number of dynamic memory allocations: 124. Total number of bytes allocated: 1492
Creating new random pair<long, long> pointer that holds 12749 and 19789... Total number of dynamic memory allocations: 125. Total number of bytes allocated: 1500
Creating new random pair<long, long> pointer that holds 15190 and 23764... Total number of dynamic memory allocations: 126. Total number of bytes allocated: 1508
Creating new random pair<long, long> pointer that holds 10416 and 1406... Total number of dynamic memory allocations: 127. Total number of bytes allocated: 1516
Creating new random pair<long, long> pointer that holds 5451 and 25100... Total number of dynamic memory allocations: 128. Total number of bytes allocated: 1524
Creating new random pair<long, long> pointer that holds 25378 and 17670... Total number of dynamic memory allocations: 129. Total number of bytes allocated: 1532
Creating new random pair<long, long> pointer that holds 26560 and 9177... Total number of dynamic memory allocations: 130. Total number of bytes allocated: 1540
Creating new random pair<long, long> pointer that holds 18011 and 17495... Total number of dynamic memory allocations: 131. Total number of bytes allocated: 1548
Creating new random pair<long, long> pointer that holds 2004 and 1759... Total number of dynamic memory allocations: 132. Total number of bytes allocated: 1556
Creating new random pair<long, long> pointer that holds 18328 and 15077... Total number of dynamic memory allocations: 133. Total number of bytes allocated: 1564
Creating new random pair<long, long> pointer that holds 17595 and 6335... Total number of dynamic memory allocations: 134. Total number of bytes allocated: 1572
Creating new random pair<long, long> pointer that holds 24776 and 4834... Total number of dynamic memory allocations: 135. Total number of bytes allocated: 1580
Creating new random pair<long, long> pointer that holds 8721 and 499... Total number of dynamic memory allocations: 136. Total number of bytes allocated: 1588
Creating new random pair<long, long> pointer that holds 15752 and 2636... Total number of dynamic memory allocations: 137. Total number of bytes allocated: 1596
Creating new random pair<long, long> pointer that holds 3181 and 20217... Total number of dynamic memory allocations: 138. Total number of bytes allocated: 1604

Creating new pair array... Total number of dynamic memory allocations: 140. Total number of bytes allocated: 1744
Creating new random pair<long, long> pointer that holds 13393 and 25898... Total number of dynamic memory allocations: 141. Total number of bytes allocated: 1752
Creating new random pair<long, long> pointer that holds 15418 and 21683... Total number of dynamic memory allocations: 142. Total number of bytes allocated: 1760
Creating new random pair<long, long> pointer that holds 24560 and 5395... Total number of dynamic memory allocations: 143. Total number of bytes allocated: 1768
Creating new random pair<long, long> pointer that holds 15042 and 13326... Total number of dynamic memory allocations: 144. Total number of bytes allocated: 1776
Creating new random pair<long, long> pointer that holds 27959 and 31215... Total number of dynamic memory allocations: 145. Total number of bytes allocated: 1784
Creating new random pair<long, long> pointer that holds 15756 and 16610... Total number of dynamic memory allocations: 146. Total number of bytes allocated: 1792
Creating new random pair<long, long> pointer that holds 28915 and 8194... Total number of dynamic memory allocations: 147. Total number of bytes allocated: 1800
Creating new random pair<long, long> pointer that holds 19432 and 20505... Total number of dynamic memory allocations: 148. Total number of bytes allocated: 1808
Creating new random pair<long, long> pointer that holds 23070 and 7974... Total number of dynamic memory allocations: 149. Total number of bytes allocated: 1816
Creating new random pair<long, long> pointer that holds 25288 and 12564... Total number of dynamic memory allocations: 150. Total number of bytes allocated: 1824
Creating new random pair<long, long> pointer that holds 21589 and 32599... Total number of dynamic memory allocations: 151. Total number of bytes allocated: 1832
Creating new random pair<long, long> pointer that holds 2769 and 22090... Total number of dynamic memory allocations: 152. Total number of bytes allocated: 1840
Creating new random pair<long, long> pointer that holds 11916 and 18037... Total number of dynamic memory allocations: 153. Total number of bytes allocated: 1848
Creating new random pair<long, long> pointer that holds 5298 and 28978... Total number of dynamic memory allocations: 154. Total number of bytes allocated: 1856
Creating new random pair<long, long> pointer that holds 6656 and 4934... Total number of dynamic memory allocations: 155. Total number of bytes allocated: 1864
Creating new random pair<long, long> pointer that holds 28597 and 1380... Total number of dynamic memory allocations: 156. Total number of bytes allocated: 1872
Creating new random pair<long, long> pointer that holds 21869 and 27067... Total number of dynamic memory allocations: 157. Total number of bytes allocated: 1880
Creating new random pair<long, long> pointer that holds 20115 and 14075... Total number of dynamic memory allocations: 158. Total number of bytes allocated: 1888
Creating new random pair<long, long> pointer that holds 6273 and 5236... Total number of dynamic memory allocations: 159. Total number of bytes allocated: 1896
Creating new random pair<long, long> pointer that holds 3725 and 22589... Total number of dynamic memory allocations: 160. Total number of bytes allocated: 1904
Creating new random pair<long, long> pointer that holds 21393 and 16261... Total number of dynamic memory allocations: 161. Total number of bytes allocated: 1912
Creating new random pair<long, long> pointer that holds 5304 and 31358... Total number of dynamic memory allocations: 162. Total number of bytes allocated: 1920
Creating new random pair<long, long> pointer that holds 6028 and 12411... Total number of dynamic memory allocations: 163. Total number of bytes allocated: 1928
Creating new random pair<long, long> pointer that holds 5529 and 1601... Total number of dynamic memory allocations: 164. Total number of bytes allocated: 1936
Creating new random pair<long, long> pointer that holds 14893 and 16282... Total number of dynamic memory allocations: 165. Total number of bytes allocated: 1944
Creating new random pair<long, long> pointer that holds 31473 and 7841... Total number of dynamic memory allocations: 166. Total number of bytes allocated: 1952
Creating new random pair<long, long> pointer that holds 2676 and 30313... Total number of dynamic memory allocations: 167. Total number of bytes allocated: 1960
Creating new random pair<long, long> pointer that holds 23514 and 21487... Total number of dynamic memory allocations: 168. Total number of bytes allocated: 1968
Creating new random pair<long, long> pointer that holds 10582 and 30577... Total number of dynamic memory allocations: 169. Total number of bytes allocated: 1976
Creating new random pair<long, long> pointer that holds 15123 and 27037... Total number of dynamic memory allocations: 170. Total number of bytes allocated: 1984
Creating new random pair<long, long> pointer that holds 23220 and 4929... Total number of dynamic memory allocations: 171. Total number of bytes allocated: 1992
Creating new random pair<long, long> pointer that holds 32665 and 13146... Total number of dynamic memory allocations: 172. Total number of bytes allocated: 2000

Creating new pair array... Total number of dynamic memory allocations: 174. Total number of bytes allocated: 2140
Creating new random pair<long, long> pointer that holds 25226 and 11957... Total number of dynamic memory allocations: 175. Total number of bytes allocated: 2148
Creating new random pair<long, long> pointer that holds 23415 and 19839... Total number of dynamic memory allocations: 176. Total number of bytes allocated: 2156
Creating new random pair<long, long> pointer that holds 17001 and 24184... Total number of dynamic memory allocations: 177. Total number of bytes allocated: 2164
Creating new random pair<long, long> pointer that holds 5342 and 13482... Total number of dynamic memory allocations: 178. Total number of bytes allocated: 2172
Creating new random pair<long, long> pointer that holds 27431 and 23496... Total number of dynamic memory allocations: 179. Total number of bytes allocated: 2180
Creating new random pair<long, long> pointer that holds 25976 and 168... Total number of dynamic memory allocations: 180. Total number of bytes allocated: 2188
Creating new random pair<long, long> pointer that holds 14037 and 13945... Total number of dynamic memory allocations: 181. Total number of bytes allocated: 2196
Creating new random pair<long, long> pointer that holds 25594 and 18073... Total number of dynamic memory allocations: 182. Total number of bytes allocated: 2204
Creating new random pair<long, long> pointer that holds 16113 and 26685... Total number of dynamic memory allocations: 183. Total number of bytes allocated: 2212
Creating new random pair<long, long> pointer that holds 11257 and 26190... Total number of dynamic memory allocations: 184. Total number of bytes allocated: 2220
Creating new random pair<long, long> pointer that holds 25309 and 11554... Total number of dynamic memory allocations: 185. Total number of bytes allocated: 2228
Creating new random pair<long, long> pointer that holds 14334 and 18166... Total number of dynamic memory allocations: 186. Total number of bytes allocated: 2236
Creating new random pair<long, long> pointer that holds 4752 and 17756... Total number of dynamic memory allocations: 187. Total number of bytes allocated: 2244
Creating new random pair<long, long> pointer that holds 8668 and 18170... Total number of dynamic memory allocations: 188. Total number of bytes allocated: 2252
Creating new random pair<long, long> pointer that holds 12684 and 1093... Total number of dynamic memory allocations: 189. Total number of bytes allocated: 2260
Creating new random pair<long, long> pointer that holds 15681 and 25381... Total number of dynamic memory allocations: 190. Total number of bytes allocated: 2268
Creating new random pair<long, long> pointer that holds 9743 and 20642... Total number of dynamic memory allocations: 191. Total number of bytes allocated: 2276
Creating new random pair<long, long> pointer that holds 16524 and 22792... Total number of dynamic memory allocations: 192. Total number of bytes allocated: 2284
Creating new random pair<long, long> pointer that holds 26766 and 31272... Total number of dynamic memory allocations: 193. Total number of bytes allocated: 2292
Creating new random pair<long, long> pointer that holds 28638 and 18589... Total number of dynamic memory allocations: 194. Total number of bytes allocated: 2300
Creating new random pair<long, long> pointer that holds 10079 and 2111... Total number of dynamic memory allocations: 195. Total number of bytes allocated: 2308
Creating new random pair<long, long> pointer that holds 32372 and 6442... Total number of dynamic memory allocations: 196. Total number of bytes allocated: 2316
Creating new random pair<long, long> pointer that holds 21174 and 26117... Total number of dynamic memory allocations: 197. Total number of bytes allocated: 2324
Creating new random pair<long, long> pointer that holds 6708 and 9576... Total number of dynamic memory allocations: 198. Total number of bytes allocated: 2332
Creating new random pair<long, long> pointer that holds 9426 and 3990... Total number of dynamic memory allocations: 199. Total number of bytes allocated: 2340
Creating new random pair<long, long> pointer that holds 21893 and 29413... Total number of dynamic memory allocations: 200. Total number of bytes allocated: 2348
Creating new random pair<long, long> pointer that holds 31352 and 9355... Total number of dynamic memory allocations: 201. Total number of bytes allocated: 2356
Creating new random pair<long, long> pointer that holds 25444 and 30887... Total number of dynamic memory allocations: 202. Total number of bytes allocated: 2364
Creating new random pair<long, long> pointer that holds 4001 and 960... Total number of dynamic memory allocations: 203. Total number of bytes allocated: 2372
Creating new random pair<long, long> pointer that holds 22965 and 14610... Total number of dynamic memory allocations: 204. Total number of bytes allocated: 2380
Creating new random pair<long, long> pointer that holds 29808 and 21595... Total number of dynamic memory allocations: 205. Total number of bytes allocated: 2388
Creating new random pair<long, long> pointer that holds 28118 and 13068... Total number of dynamic memory allocations: 206. Total number of bytes allocated: 2396

Creating new pair array... Total number of dynamic memory allocations: 208. Total number of bytes allocated: 2536
Creating new random pair<long, long> pointer that holds 20070 and 8201... Total number of dynamic memory allocations: 209. Total number of bytes allocated: 2544
Creating new random pair<long, long> pointer that holds 24442 and 28254... Total number of dynamic memory allocations: 210. Total number of bytes allocated: 2552
Creating new random pair<long, long> pointer that holds 14809 and 25227... Total number of dynamic memory allocations: 211. Total number of bytes allocated: 2560
Creating new random pair<long, long> pointer that holds 1461 and 10077... Total number of dynamic memory allocations: 212. Total number of bytes allocated: 2568
Creating new random pair<long, long> pointer that holds 24482 and 12914... Total number of dynamic memory allocations: 213. Total number of bytes allocated: 2576
Creating new random pair<long, long> pointer that holds 12883 and 24011... Total number of dynamic memory allocations: 214. Total number of bytes allocated: 2584
Creating new random pair<long, long> pointer that holds 4887 and 26406... Total number of dynamic memory allocations: 215. Total number of bytes allocated: 2592
Creating new random pair<long, long> pointer that holds 24430 and 19192... Total number of dynamic memory allocations: 216. Total number of bytes allocated: 2600
Creating new random pair<long, long> pointer that holds 3129 and 24621... Total number of dynamic memory allocations: 217. Total number of bytes allocated: 2608
Creating new random pair<long, long> pointer that holds 23360 and 812... Total number of dynamic memory allocations: 218. Total number of bytes allocated: 2616
Creating new random pair<long, long> pointer that holds 4654 and 20906... Total number of dynamic memory allocations: 219. Total number of bytes allocated: 2624
Creating new random pair<long, long> pointer that holds 26165 and 17993... Total number of dynamic memory allocations: 220. Total number of bytes allocated: 2632
Creating new random pair<long, long> pointer that holds 10737 and 14884... Total number of dynamic memory allocations: 221. Total number of bytes allocated: 2640
Creating new random pair<long, long> pointer that holds 30532 and 17325... Total number of dynamic memory allocations: 222. Total number of bytes allocated: 2648
Creating new random pair<long, long> pointer that holds 7496 and 25993... Total number of dynamic memory allocations: 223. Total number of bytes allocated: 2656
Creating new random pair<long, long> pointer that holds 6784 and 21846... Total number of dynamic memory allocations: 224. Total number of bytes allocated: 2664
Creating new random pair<long, long> pointer that holds 28150 and 8563... Total number of dynamic memory allocations: 225. Total number of bytes allocated: 2672
Creating new random pair<long, long> pointer that holds 7658 and 30281... Total number of dynamic memory allocations: 226. Total number of bytes allocated: 2680
Creating new random pair<long, long> pointer that holds 2354 and 1705... Total number of dynamic memory allocations: 227. Total number of bytes allocated: 2688
Creating new random pair<long, long> pointer that holds 138 and 30772... Total number of dynamic memory allocations: 228. Total number of bytes allocated: 2696
Creating new random pair<long, long> pointer that holds 20313 and 31721... Total number of dynamic memory allocations: 229. Total number of bytes allocated: 2704
Creating new random pair<long, long> pointer that holds 22462 and 15442... Total number of dynamic memory allocations: 230. Total number of bytes allocated: 2712
Creating new random pair<long, long> pointer that holds 17376 and 21989... Total number of dynamic memory allocations: 231. Total number of bytes allocated: 2720
Creating new random pair<long, long> pointer that holds 7889 and 29583... Total number of dynamic memory allocations: 232. Total number of bytes allocated: 2728
Creating new random pair<long, long> pointer that holds 31116 and 14475... Total number of dynamic memory allocations: 233. Total number of bytes allocated: 2736
Creating new random pair<long, long> pointer that holds 9423 and 10733... Total number of dynamic memory allocations: 234. Total number of bytes allocated: 2744
Creating new random pair<long, long> pointer that holds 3813 and 7561... Total number of dynamic memory allocations: 235. Total number of bytes allocated: 2752
Creating new random pair<long, long> pointer that holds 3224 and 8486... Total number of dynamic memory allocations: 236. Total number of bytes allocated: 2760
Creating new random pair<long, long> pointer that holds 20200 and 9233... Total number of dynamic memory allocations: 237. Total number of bytes allocated: 2768
Creating new random pair<long, long> pointer that holds 4916 and 16019... Total number of dynamic memory allocations: 238. Total number of bytes allocated: 2776
Creating new random pair<long, long> pointer that holds 18940 and 3545... Total number of dynamic memory allocations: 239. Total number of bytes allocated: 2784
Creating new random pair<long, long> pointer that holds 4198 and 4172... Total number of dynamic memory allocations: 240. Total number of bytes allocated: 2792

Creating new pair array... Total number of dynamic memory allocations: 242. Total number of bytes allocated: 2932
Creating new random pair<long, long> pointer that holds 31527 and 3431... Total number of dynamic memory allocations: 243. Total number of bytes allocated: 2940
Creating new random pair<long, long> pointer that holds 25988 and 11665... Total number of dynamic memory allocations: 244. Total number of bytes allocated: 2948
Creating new random pair<long, long> pointer that holds 19842 and 18827... Total number of dynamic memory allocations: 245. Total number of bytes allocated: 2956
Creating new random pair<long, long> pointer that holds 20101 and 30312... Total number of dynamic memory allocations: 246. Total number of bytes allocated: 2964
Creating new random pair<long, long> pointer that holds 5610 and 14893... Total number of dynamic memory allocations: 247. Total number of bytes allocated: 2972
Creating new random pair<long, long> pointer that holds 18780 and 30344... Total number of dynamic memory allocations: 248. Total number of bytes allocated: 2980
Creating new random pair<long, long> pointer that holds 21753 and 16968... Total number of dynamic memory allocations: 249. Total number of bytes allocated: 2988
Creating new random pair<long, long> pointer that holds 1925 and 28534... Total number of dynamic memory allocations: 250. Total number of bytes allocated: 2996
Creating new random pair<long, long> pointer that holds 21812 and 11063... Total number of dynamic memory allocations: 251. Total number of bytes allocated: 3004
Creating new random pair<long, long> pointer that holds 7645 and 19950... Total number of dynamic memory allocations: 252. Total number of bytes allocated: 3012
Creating new random pair<long, long> pointer that holds 31110 and 25904... Total number of dynamic memory allocations: 253. Total number of bytes allocated: 3020
Creating new random pair<long, long> pointer that holds 26294 and 3716... Total number of dynamic memory allocations: 254. Total number of bytes allocated: 3028
Creating new random pair<long, long> pointer that holds 20462 and 12558... Total number of dynamic memory allocations: 255. Total number of bytes allocated: 3036
Creating new random pair<long, long> pointer that holds 18987 and 21899... Total number of dynamic memory allocations: 256. Total number of bytes allocated: 3044
Creating new random pair<long, long> pointer that holds 15476 and 5971... Total number of dynamic memory allocations: 257. Total number of bytes allocated: 3052
Creating new random pair<long, long> pointer that holds 24753 and 15926... Total number of dynamic memory allocations: 258. Total number of bytes allocated: 3060
Creating new random pair<long, long> pointer that holds 20577 and 20589... Total number of dynamic memory allocations: 259. Total number of bytes allocated: 3068
Creating new random pair<long, long> pointer that holds 9199 and 9469... Total number of dynamic memory allocations: 260. Total number of bytes allocated: 3076
Creating new random pair<long, long> pointer that holds 8623 and 568... Total number of dynamic memory allocations: 261. Total number of bytes allocated: 3084
Creating new random pair<long, long> pointer that holds 8656 and 28994... Total number of dynamic memory allocations: 262. Total number of bytes allocated: 3092
Creating new random pair<long, long> pointer that holds 14015 and 30405... Total number of dynamic memory allocations: 263. Total number of bytes allocated: 3100
Creating new random pair<long, long> pointer that holds 26070 and 8757... Total number of dynamic memory allocations: 264. Total number of bytes allocated: 3108
Creating new random pair<long, long> pointer that holds 23114 and 12378... Total number of dynamic memory allocations: 265. Total number of bytes allocated: 3116
Creating new random pair<long, long> pointer that holds 3249 and 8949... Total number of dynamic memory allocations: 266. Total number of bytes allocated: 3124
Creating new random pair<long, long> pointer that holds 27546 and 32441... Total number of dynamic memory allocations: 267. Total number of bytes allocated: 3132
Creating new random pair<long, long> pointer that holds 13840 and 10744... Total number of dynamic memory allocations: 268. Total number of bytes allocated: 3140
Creating new random pair<long, long> pointer that holds 32506 and 31141... Total number of dynamic memory allocations: 269. Total number of bytes allocated: 3148
Creating new random pair<long, long> pointer that holds 18615 and 10156... Total number of dynamic memory allocations: 270. Total number of bytes allocated: 3156
Creating new random pair<long, long> pointer that holds 25195 and 1187... Total number of dynamic memory allocations: 271. Total number of bytes allocated: 3164
Creating new random pair<long, long> pointer that holds 15569 and 2142... Total number of dynamic memory allocations: 272. Total number of bytes allocated: 3172
Creating new random pair<long, long> pointer that holds 23192 and 16382... Total number of dynamic memory allocations: 273. Total number of bytes allocated: 3180
Creating new random pair<long, long> pointer that holds 24712 and 19804... Total number of dynamic memory allocations: 274. Total number of bytes allocated: 3188





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