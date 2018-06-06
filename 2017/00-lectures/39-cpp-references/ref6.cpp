#include <iostream>

using namespace std;

template<typename ... T> class MyTuple;

template<typename F, typename ... L>
class MyTuple<F, L...> : public MyTuple<L...>
{
public:
    F f;
    using value_type = F;
    MyTuple() {}
};

template<>
class MyTuple<>
{
public:
    MyTuple() {}
};

template <int N, MyTuple<typename F, typename L...>>
typename T::value_type get(const T &v)
{
    if constexpr(N == 0) {
        return v.f;
    } else {
        get<N - 1, MyTuple<L...> >(v);
    }
}

int main()
{
    MyTuple<> mt0;
    MyTuple<int, double, int> mt;

    cout << sizeof(mt) << endl;
    cout << get<0>(mt) << endl;
}
