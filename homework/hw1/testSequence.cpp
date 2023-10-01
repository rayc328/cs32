#include "Sequence.h"
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

//#include "Sequence.h"
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

///////////////////
// 
// personal test cases for when "ItemType" is string 
//////////////////
//int main()
//{
//    Sequence bruh;
//    bruh.dump();
//    Sequence s;
//    s.insert(0, "a");
//    s.insert(1, "b");
//    s.insert(2, "e");
//    s.insert(3, "b");
//    s.insert(4, "c");
//   // s.dump();
//    
//    s.remove("b"); 
//
//   // s.dump();
//
//    Sequence k;
//    k.insert(0, "dosa");
//    k.insert(1, "pita");
//    k.insert(2, "");
//    k.insert(3, "matzo");
//    assert(k.find("") == 2);
//    k.remove("dosa");
//    assert(k.size() == 3 && k.find("pita") == 0 && k.find("") == 1 &&
//        k.find("matzo") == 2);
//
//    Sequence r;
//    assert(r.empty());
//    assert(r.find("laobing") == -1);
//    assert(r.insert("laobing") == 0);
//    assert(r.size() == 1 && r.find("laobing") == 0);
//
//    Sequence j;
//    j.insert(0, "dosa");
//    j.insert(1, "pita");
//    j.insert(2, "");
//    j.insert(3, "matzo");
//    assert(j.find("") == 2);
//    j.remove("dosa");
//    assert(j.size() == 3 && j.find("pita") == 0 && j.find("") == 1 &&
//        j.find("matzo") == 2);
//
//    Sequence s1;
//    s1.insert(0, "paratha");
//    s1.insert(0, "focaccia");
//    
//    s1.dump(); //original s1
//
//    Sequence s2;
//    s2.insert(0, "roti");
//    
//    s2.dump(); //original s2
//
//    s1.swap(s2);
//    s1.dump();
//    cout << endl; 
//    s2.dump();
//
//    assert(s1.size() == 1 && s1.find("roti") == 0 && s2.size() == 2 &&
//        s2.find("focaccia") == 0 && s2.find("paratha") == 1);
//
//    cerr << "passed all tests" << endl;
//}