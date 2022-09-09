#include <iostream>
#include <iomanip>
#include <utility>
#include <iterator>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>

template <typename T1, typename T2>
std::ostream& operator << (std::ostream& strm, const std::pair<T1, T2>& p)
{
    return strm << "[" << p.first << ", " << p.second << "]";
}

template <typename T>
void printHashTableState (const T& cont)
{
    // basic layout data:
    std::cout << "size: " << cont.size() << "\n";
    std::cout << "buckets: " << cont.bucket_count() << "\n";
    std::cout << "load factor: " << cont.load_factor() << "\n";
    std::cout << "max load factor: " << cont.max_load_factor() << "\n";

    // elements per bucket:
    std::cout << "data: " << "\n";
    for (auto idx=0; idx != cont.bucket_count(); ++idx) {
        std::cout << " b[" << std::setw(2) << idx << "]: ";
        for (auto pos=cont.begin(idx); pos != cont.end(idx); ++pos) {
            std::cout << *pos << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void test_unordered_set()
{
    // create and initialize an unordered set
    std::unordered_set<int> intset = { 1,2,3,5,7,11,13,17,19 };
    printHashTableState(intset);

    // insert some additional values (might cause rehashing)
    intset.insert({-7,17,33,4});
    printHashTableState(intset);
}

void test_unordered_map()
{
    // create and initialize an unordered multimap as dictionary
    std::unordered_multimap<std::string, std::string> dict = {
        {"day","Tag"},
        {"strange","fremd"},
        {"car","Auto"},
        {"smart","elegant"},
        {"trait","Merkmal"},
        {"strange","seltsam"}
    };
    printHashTableState(dict);

    // insert some additional values (might cause rehashing)
    dict.insert({
        {"smart","raffiniert"},
        {"smart","klug"},
        {"clever","raffiniert"}
    });
    printHashTableState(dict);

    // modify maximum load factor (might cause rehashing)
    dict.max_load_factor(0.7);
    printHashTableState(dict);
}

void test_hash()
{
    std::unordered_map<int, int> m {{1,2}, {3,5}};
    std::cout << m.size() << std::endl;
    for_each(m.begin(), m.end(),
             [](decltype(m)::value_type& p)
             {
                std::cout << p.first << " " << p.second << std::endl;
             });
}

int main()
{
    test_unordered_set();
//    test_unordered_map();
//    test_hash();

    return 0;
}
