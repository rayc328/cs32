#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

//#include "newSequence.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Sequence s;
//    s.insert(0, "lavash");
//    s.insert(0, "tortilla");
//    assert(s.size() == 2);
//    ItemType x = "injera";
//    assert(s.get(0, x) && x == "tortilla");
//    assert(s.get(1, x) && x == "lavash");
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}

//#include "newSequence.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
////int main()
////{
////    Sequence a(1000);   // a can hold at most 1000 items
////    Sequence b(5); // b can hold at most 5 items
////    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
////    ItemType v = 89;
////
////    // No failures inserting 5 items into b
////    for (int k = 0; k < 5; k++)
////        assert(b.insert(v) != -1);
////
////    // Failure if we try to insert a sixth item into b
////    assert(b.insert(v) == -1);
////    assert(b.insert(5, v) == -1);
////
////    // When two Sequences' contents are swapped, their capacities are
////    // swapped as well:
////    /*a.swap(b);
////    assert(a.insert(v) == -1 && b.insert(v) != -1);*/
////
////    cerr << "passed all tests" << endl;
////}
//
//int main()
//{
//   // Sequence bruh;
//   //// bruh.dump();
//   //  Sequence s;
//   //  s.insert(0, "a");
//   //  s.insert(1, "b");
//   //  s.insert(2, "e");
//   //  s.insert(3, "b");
//   //  s.insert(4, "c");
//   // // s.dump();
//   //  
//   //  s.remove("b"); 
//
//   // // s.dump();
//
//   //  Sequence k;
//   //  k.insert(0, "dosa");
//   //  k.insert(1, "pita");
//   //  k.insert(2, "");
//   //  k.insert(3, "matzo");
//   //  assert(k.find("") == 2);
//   //  k.remove("dosa");
//   //  assert(k.size() == 3 && k.find("pita") == 0 && k.find("") == 1 &&
//   //      k.find("matzo") == 2);
//
//   //  Sequence r;
//   //  assert(r.empty());
//   //  assert(r.find("laobing") == -1);
//   //  assert(r.insert("laobing") == 0);
//   //  assert(r.size() == 1 && r.find("laobing") == 0);
//
//   //  Sequence j;
//   //  j.insert(0, "dosa");
//   //  j.insert(1, "pita");
//   //  j.insert(2, "");
//   //  j.insert(3, "matzo");
//   //  assert(j.find("") == 2);
//   //  j.remove("dosa");
//   //  assert(j.size() == 3 && j.find("pita") == 0 && j.find("") == 1 &&
//   //      j.find("matzo") == 2);
//
//    // swap test
//     Sequence s1(2);
//     s1.insert(0, "paratha");
//     s1.insert(0, "focaccia");
//     
//    s1.dump(); //original s1
//
//     Sequence s2(1);
//     s2.insert(0, "roti");
//     
//     s2.dump(); //original s2
//
//     s1.swap(s2);
//   
//     s1.dump(); //original s2
//     s2.dump(); //original s1
//
//     assert(s1.size() == 1 && s1.find("roti") == 0 && s2.size() == 2 &&
//         s2.find("focaccia") == 0 && s2.find("paratha") == 1);
//
//  /*   cout << endl;
//     cout << "size of s1 " << s1.size() << endl;
//     cout << "s1 insert return " << s1.insert("bruh") << endl;
//     cout << "s2 insert return "<< s2.insert("ok") << endl;*/
//     s1.dump();
//     s2.dump();
//
//    cerr << "passed all tests" << endl;
//}