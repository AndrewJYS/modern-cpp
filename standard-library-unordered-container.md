# unordered containers  

## 概述  

Unordered sets and maps allow no duplicates, whereas unordered multisets and multimaps do.  

To use an unordered set or multiset, you must include the header file \<unordered_set\>. To use an unordered map or multimap, you must include the header file \<unordered_map\>.  

For each element to store, which is a key/value pair, **the hash function maps the value of the key to a bucket (slot) in the hash table**. Each bucket manages a singly linked list containing all the elements for which the hash function yields the same value.  

Assuming that the hashing strategy is well chosen and well implemented, you can guarantee amortized **constant time for insertions, deletions, and element search** (“amortized” because the occasional rehashing happens that occurs can be a large operation with a linear complexity).  

Because the iterators are guaranteed only to be forward iterators, reverse iterators, including rbegin(), rend(), crbegin(), and crend(), are not supported, and you can’t use algorithms that require bidirectional iterators, or at least this is not portable.  

## 基本操作  

### 创建，复制和销毁  

|Operation |Effect|
:-:|:-:
|Unord c |Default constructor; creates an empty unordered container without any elements|
|Unord c(bnum) |Creates an empty unordered container that internally uses **at least bnum buckets**|
|Unord c(bnum,hf) |Creates an empty unordered container that internally uses at least bnum buckets and **hf as hash function**|
|Unord c(bnum,hf,cmp) |Creates an empty unordered container that internally uses at least bnum buckets, hf as hash function, and **cmp as predicate to identify equal values**|
|Unord c(c2) |**Copy** constructor; creates a copy of another unordered container of the same type (all elements are copied)|
|Unord c = c2 |**Copy** constructor; creates a copy of another unordered container of the same type (all elements are copied)|
|Unord c(rv) |**Move** constructor; creates an unordered container, taking the contents of the rvalue rv (since C++11)|
|Unord c = rv |**Move** constructor; creates an unordered container, taking the contents of the rvalue rv (since C++11)|
|Unord c(beg,end) |Creates an unordered container initialized by the elements of the range [beg,end)|
|Unord c(beg,end,bnum) |Creates an unordered container initialized by the elements of the range [beg,end) that internally uses at least bnum buckets|
|Unord c(beg,end,bnum,hf) |Creates an unordered container initialized by the  elements of the range [beg,end) that internally uses at least bnum buckets and hf as hash function|
|Unord c(beg,end,bnum,hf,cmp) |Creates an unordered container initialized by the elements of the range [beg,end) that internally uses at least bnum buckets, hf as hash function, and cmp as predicate to identify equal values|
|Unord c(initlist) |Creates an unordered unordered container initialized by the elements of the **initializer list** initlist|
|Unord c = initlist |Creates an unordered unordered container initialized bythe elements of the **initializer list** initlist|
|c.~Unord()| Destroys all elements and frees the memory|

```cpp
std::unordered_map<int, int> m {{1,2}, {3,5}};
std::cout << m.size() << std::endl;
for_each(m.begin(), m.end(), 
            [](decltype(m)::value_type& p)
            { 
            std::cout << p.first << " " << p.second << std::endl; 
            });
```

### 非更易型操作  

|Operation| Effect|
:-:|:-:
|c.empty()| Returns whether the container is empty (equivalent to size()==0 but might be faster)|
|c.size() |Returns the current number of elements|
|c.max_size() |Returns the maximum number of elements possible|
|c1 == c2 |Returns whether c1 is equal to c2|
|c1 != c2 |Returns whether c1 is not equal to c2 (equivalent to !(c1==c2))|

### 特殊的查找操作  

|Operation |Effect|
:-:|:-:
|c.count(val)| Returns the number of elements with value val|
|c.find(val) |Returns the position of the first element with value val (or end() if none found)|
|c.equal_range(val) |Returns a range with all elements with a value equal to val (i.e., the first and last positions, where val would get inserted)|

### 赋值  

|Operation |Effect|
:-:|:-:
|c = c2 |Assigns all elements of c2 to c|
|c = rv |Move assigns all elements of the rvalue rv to c (since C++11)|
|c = initlist |Assigns all elements of the initializer list initlist to c (since C++11)|
|c1.swap(c2) |Swaps the data of c1 and c2|
|swap(c1,c2) |Swaps the data of c1 and c2|

For these operations, **both containers must have the same type**. In particular, **the type of the hash functions and the equivalence criteria must be the same, although the functions themselves may be different**.  

### 迭代器相关函数  

|Operation |Effect|
:-:|:-:
|c.begin() |Returns a forward iterator for the first element|
|c.end() |Returns a forward iterator for the position after the last element|
|**c.cbegin()** |Returns a constant forward iterator for the first element (since C++11)|
|**c.cend()** |Returns a constant forward iterator for the position after the last element (since C++11)|
|c.rbegin() |Returns a reverse iterator for the first element of a reverse iteration|
|c.rend() |Returns a reverse iterator for the position after the last element of a reverse iteration|
|**c.crbegin()** |Returns a constant reverse iterator for the first element of a reverse iteration (since C++11)|
|**c.crend()** |Returns a constant reverse iterator for the position after the last element of a reverse iteration (since C++11)|

**For unordered (multi)sets, all elements are considered constant** from an iterator’s point of view. **For unordered (multi)maps, the key of all elements is considered to be constant**. For this reason, you **can’t call any modifying algorithm** on the elements. For example, you can’t call the remove() algorithm, because it “removes” by overwriting “removed” elements with the following elements. To remove elements in unordered sets and multisets, you **can use only member functions provided by the container**.  

If you use algorithms and lambdas to operate on the elements of a map, you explicitly have to declare the element type:  

```cpp
std::unordered_map<std::string,int> coll;
...
// add 10 to the value of each element:
std::for_each (coll.begin(), coll.end(),
                [] (pair<const std::string,int>& elem) {
                elem.second += 10;
                });
```

Instead of using the following:  

```cpp
pair<const std::string,int>
```

you could also use  

```cpp
unordered_map<std::string,int>::value_type
```

or  

```cpp
decltype(coll)::value_type
```

### 安插和移除元素  

|Operation| Effect|
:-:|:-:
|c.insert(val) |Inserts a copy of val and returns the position of the new element and, for unordered containers, whether it succeeded|
|c.insert(pos,val) |Inserts a copy of val and returns the position of the new element (pos is used as a hint pointing to where the insert should start the search)|
|c.insert(beg,end) |Inserts a copy of all elements of the range [beg,end) (returns nothing)|
|c.insert(initlist) |Inserts a copy of all elements in the initializer list initlist (returns nothing; since C++11)|
|c.emplace(args...) |Inserts a copy of an element initialized with args and returns the position of the new element and, for unordered containers, whether it succeeded (since C++11)|
|c.emplace_hint(pos,args...) |Inserts a copy of an element initialized with args and returns the position of the new element (pos is used as a hint pointing to where the insert should start the search)|
|c.erase(val)| Removes all elements equal to val and returns the number of removed elements|
|c.erase(pos)| Removes the element at iterator position pos and returns the following position (returned nothing before C++11)|
|c.erase(beg,end) |Removes all elements of the range [beg,end) and returns the following position (returned nothing before C++11)|
|c.clear() |Removes all elements (empties the container)|

Rehashing happens when, because of an insertion, the number of resulting elements is equal to or exceeds the bucket count times the maximum load factor.  

### bucket接口  

It is possible to access the individual buckets with a specific bucket interface to expose the internal state of the whole hash table.  

|Operation| Effect|
:-:|:-:
|c.bucket_count()| Returns the current number of buckets|
|c.bucket(val)| Returns the index of the bucket in which val would/could be found|
|c.bucket_size(buckidx)| Returns the number of elements in the bucket with index buckidx|
|c.begin(buckidx)| Returns a forward iterator for the first element of the bucket with index buckidx|
|c.end(buckidx) |Returns a forward iterator for the position after the last element of the bucket with index buckidx|
|c.cbegin(buckidx) |Returns a constant forward iterator for the first element of the bucket with index buckidx|
|c.cend(buckidx) |Returns a constant forward iterator for the position after the last element of the bucket with index buckidx|

```cpp
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
```

test_unordered_set()的输出如下：  

```md
size: 9
buckets: 11
load factor: 0.818182
max load factor: 1
data:
 b[ 0]: 11
 b[ 1]: 1
 b[ 2]: 13 2
 b[ 3]: 3
 b[ 4]:
 b[ 5]: 5
 b[ 6]: 17
 b[ 7]: 7
 b[ 8]: 19
 b[ 9]:
 b[10]:

size: 12
buckets: 23
load factor: 0.521739
max load factor: 1
data:
 b[ 0]:
 b[ 1]: 1
 b[ 2]: 2
 b[ 3]: 3
 b[ 4]: 4
 b[ 5]: -7 5
 b[ 6]:
 b[ 7]: 7
 b[ 8]:
 b[ 9]:
 b[10]: 33
 b[11]: 11
 b[12]:
 b[13]: 13
 b[14]:
 b[15]:
 b[16]:
 b[17]: 17
 b[18]:
 b[19]: 19
 b[20]:
 b[21]:
 b[22]:
```

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 7.9  
