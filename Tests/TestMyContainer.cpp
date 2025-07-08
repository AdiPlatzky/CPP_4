//12adi45@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../MyContainer.hpp"
#include <string>
using namespace Container;

TEST_CASE("בדיקות בסיס - הוספה וגודל") {
    MyContainer<int> c;
    CHECK(c.size() == 0);
    c.addElement(4);
    c.addElement(2);
    c.addElement(7);
    c.addElement(2);
    CHECK(c.size() == 4);

    MyContainer<std::string> cs;
    cs.addElement("hi");
    cs.addElement("bye");
    CHECK(cs.size() == 2);
}

TEST_CASE("בדיקת מחיקה") {
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(1);
    c.addElement(2);
    c.addElement(1);
    CHECK(c.size() == 4);
    c.removeElement(1); // מוחק את כל ה-1
    CHECK(c.size() == 1);
    CHECK_THROWS_AS(c.removeElement(1), std::runtime_error); // לא נשאר 1

    MyContainer<std::string> cs;
    cs.addElement("yo");
    cs.addElement("yo");
    cs.removeElement("yo");
    CHECK(cs.size() == 0);
    CHECK_THROWS(cs.removeElement("yo"));
}

TEST_CASE("Order Iterator - שלמים") {
    MyContainer<int> c;
    std::vector<int> v = {5, 3, 9, -2, 7};
    for (int x : v) c.addElement(x);

    size_t i = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it, ++i) {
        CHECK(*it == v[i]);
    }
}

TEST_CASE("Order Iterator - מחרוזות") {
    MyContainer<std::string> cs;
    std::vector<std::string> v = {"a", "b", "c"};
    for (const auto& s : v) cs.addElement(s);

    size_t i = 0;
    for (auto it = cs.begin_order(); it != cs.end_order(); ++it, ++i) {
        CHECK(*it == v[i]);
    }
}

TEST_CASE("AscendingOrder Iterator - int") {
    MyContainer<int> c;
    std::vector<int> input = {4, 2, 7, 3};
    for (int x : input) c.addElement(x);

    std::vector<int> expected = {2, 3, 4, 7};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("AscendingOrder Iterator - double") {
    MyContainer<double> c;
    c.addElement(2.2);
    c.addElement(1.1);
    c.addElement(3.3);
    std::vector<double> expected = {1.1, 2.2, 3.3};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it, ++i) {
        CHECK(doctest::Approx(*it) == expected[i]);
    }
}

TEST_CASE("DescendingOrder Iterator") {
    MyContainer<int> c;
    std::vector<int> input = {8, 1, 3, 9};
    for (int x : input) c.addElement(x);

    std::vector<int> expected = {9, 8, 3, 1};
    size_t i = 0;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("SideCrossOrder Iterator") {
    MyContainer<int> c;
    std::vector<int> input = {7, 15, 6, 1, 2};
    for (int x : input) c.addElement(x);
    std::vector<int> expected = {1, 15, 2, 7, 6};
    size_t i = 0;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("ReverseOrder Iterator") {
    MyContainer<int> c;
    std::vector<int> input = {5, 6, 7, 8};
    for (int x : input) c.addElement(x);

    std::vector<int> expected = {8, 7, 6, 5};
    size_t i = 0;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}



TEST_CASE("Template support - string") {
    MyContainer<std::string> c;
    c.addElement("banana");
    c.addElement("apple");
    c.addElement("pear");

    std::vector<std::string> expectedAsc = {"apple", "banana", "pear"};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it, ++i) {
        CHECK(*it == expectedAsc[i]);
    }

    std::vector<std::string> expectedDesc = {"pear", "banana", "apple"};
    i = 0;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it, ++i) {
        CHECK(*it == expectedDesc[i]);
    }
}

TEST_CASE("בדיקות עומק - קונטיינר ענק") {
    MyContainer<int> c;
    for (int i = 0; i < 1000; ++i) c.addElement(i);
    CHECK(c.size() == 1000);

    int sum = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        sum += *it;
    }
    CHECK(sum == 499500); // סכום של 0..999
}


TEST_CASE("מחיקת איבר בקונטיינר ריק זורקת שגיאה") {
    MyContainer<int> c;
    CHECK_THROWS_AS(c.removeElement(5), std::runtime_error);
}

TEST_CASE("הוספה-מחיקה-הוספה, איטרטורים אחרי מחיקות") {
    MyContainer<int> c;
    for (int i=1; i<=5; ++i) c.addElement(i);
    c.removeElement(3);
    CHECK(c.size() == 4);
    c.addElement(7);

    std::vector<int> expected = {1,2,4,5,7};
    size_t i=0;
    for (auto it=c.begin_order(); it!=c.end_order(); ++it, ++i)
        CHECK(*it == expected[i]);
}

TEST_CASE("הוספת אותו איבר הרבה פעמים, מחיקה מוחקת הכל") {
    MyContainer<int> c;
    c.addElement(9);
    c.addElement(9);
    c.addElement(9);
    c.addElement(1);
    CHECK(c.size() == 4);
    c.removeElement(9);
    CHECK(c.size() == 1);
    for (auto it=c.begin_order(); it!=c.end_order(); ++it)
        CHECK(*it == 1);
}

TEST_CASE("לולאה מקוננת על שני איטרטורים במקביל - סדרים שונים") {
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(3);
    c.addElement(5);
    std::vector<int> asc = {3,5,7};
    std::vector<int> desc = {7,5,3};
    auto it_asc = c.begin_ascending_order();
    auto it_desc = c.begin_descending_order();
    for (int i=0; i<3; ++i, ++it_asc, ++it_desc) {
        CHECK(*it_asc == asc[i]);
        CHECK(*it_desc == desc[i]);
    }
}

TEST_CASE("בדיקה על טיפוסים שונים - double") {
    MyContainer<double> c;
    c.addElement(1.5);
    c.addElement(3.5);
    c.addElement(2.5);
    std::vector<double> asc = {1.5, 2.5, 3.5};
    int i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it, ++i) {
        CHECK(doctest::Approx(*it) == asc[i]);
    }
}

TEST_CASE("בדיקה על טיפוסים שונים - string") {
    MyContainer<std::string> c;
    c.addElement("ccc");
    c.addElement("bbb");
    c.addElement("aaa");
    std::vector<std::string> asc = {"aaa", "bbb", "ccc"};
    int i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it, ++i) {
        CHECK(*it == asc[i]);
    }
}

TEST_CASE("SideCrossOrder - עם איבר בודד ועם שניים") {
    MyContainer<int> c1;
    c1.addElement(4);
    for (auto it=c1.begin_side_cross_order(); it!=c1.end_side_cross_order(); ++it)
        CHECK(*it == 4);

    MyContainer<int> c2;
    c2.addElement(1);
    c2.addElement(9);
    std::vector<int> expected = {1,9};
    int i=0;
    for (auto it=c2.begin_side_cross_order(); it!=c2.end_side_cross_order(); ++it,++i)
        CHECK(*it == expected[i]);
}


TEST_CASE("בדיקה: שינוי תוכן אחרי יצירת איטרטור - האם משפיע?") {
    MyContainer<int> c;
    c.addElement(2); c.addElement(3); c.addElement(4);
    auto it = c.begin_ascending_order();
    c.addElement(5);
    // האיטרטור אמור לעבוד רק על המצב בזמן שנוצר! אין קשר למה שעשינו אחרי.
    std::vector<int> expected = {2,3,4};
    int i=0;
    for (; it!=c.begin_ascending_order(); ++it,++i)
        CHECK(*it == expected[i]);
}

TEST_CASE("כל האיטרטורים פועלים נכון על סדרות גדולות") {
    MyContainer<int> c;
    for (int i=0; i<20; ++i) c.addElement(20-i); // 20..1
    // ascending: 1..20
    int val=1;
    for (auto it=c.begin_ascending_order(); it!=c.end_ascending_order(); ++it,++val)
        CHECK(*it == val);
    // descending: 20..1
    val=20;
    for (auto it=c.begin_descending_order(); it!=c.end_descending_order(); ++it,--val)
        CHECK(*it == val);
}


