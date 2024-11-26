#include "WordCount.h"
#include "tddFuncs.h"
#include <sstream>

int main() {
    WordCount wc;
    wc.addAllWords("bob bobby st---study   b   b   b   aaaaa alice alice bobby                                  a");
    std::ostringstream out1;
    wc.dumpWordsSortedByWord(out1);
    std::string expected1 = "a,1\naaaaa,1\nalice,2\nb,3\nbob,1\nbobby,2\nststudy,1\n";
    assertEquals(expected1, out1.str(), "", __LINE__);

    wc = WordCount();
    wc.addAllWords("bob alice bob ali23ce  alice bobby     bobby    bobby");
    std::ostringstream out2;
    wc.dumpWordsSortedByOccurence(out2);
    std::string expected2 = "bob,2\nalice,3\nbobby,3\n";
    assertEquals(expected2, out2.str(), "", __LINE__);

    wc = WordCount();
    wc.addAllWords("");
    std::ostringstream out3;
    wc.dumpWordsSortedByWord(out3);
    std::string expected3 = "";
    assertEquals(expected3, out3.str(), "", __LINE__);

    wc = WordCount();
    wc.addAllWords("hello2           hel111lo he3234llo2      23 2");
    std::ostringstream out4;
    wc.dumpWordsSortedByWord(out4);
    std::string expected4 = "hello,3\n";
    assertEquals(expected4, out4.str(), "", __LINE__);

    wc = WordCount();
    wc.addAllWords("    22 333 Hello hello HEL33LO wor333ld    ");
    std::ostringstream out5;
    wc.dumpWordsSortedByWord(out5);
    std::string expected5 = "hello,3\nworld,1\n";
    assertEquals(expected5, out5.str(), "", __LINE__);

    wc = WordCount();
    wc.addAllWords("hello, world! hello.");
    std::ostringstream out6;
    wc.dumpWordsSortedByWord(out6);
    std::string expected6 = "hello,2\nworld,1\n";
    assertEquals(expected6, out6.str(), "", __LINE__);

    wc = WordCount();
    wc.addAllWords("000 456 000 789");
    std::ostringstream out7;
    wc.dumpWordsSortedByWord(out7);
    std::string expected7 = "";
    assertEquals(expected7, out7.str(), "", __LINE__);

    wc = WordCount();
    wc.addAllWords("  hello   world\nhello\n\nworld");
    std::ostringstream out8;
    wc.dumpWordsSortedByWord(out8);
    std::string expected8 = "hello,2\nworld,2\n";
    assertEquals(expected8, out8.str(), "", __LINE__);
    return 0; 
}
