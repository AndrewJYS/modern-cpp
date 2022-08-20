# pair  

## 基本操作  

|Operation|Effect|examples|
:-:|:-:|:-:
| pair<T1,T2> p | Default constructor; creates a pair of values of types T1 and T2, initialized with their default constructors | std::pair<int, int> i_pair1; |
|pair<T1,T2> p(val1,val2) | Creates a pair of values of types T1 and T2, initialized with val1 and val2 | std::pair<int, int> i_pair2(2, 3); |
| pair<T1,T2> p(rv1,rv2) | Creates a pair of values of types T1 and T2, move initialized with rv1 and rv2 | std::string a = "hello"; </br> std::string b = "world"; </br> std::pair<std::string, std::string> s_pair1(std::move(a), std::move(b)); |
|