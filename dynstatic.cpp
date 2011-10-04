#include <iostream>
#include <type_traits>


// a bunch of base classes we want to mixin (kinda)
struct a
{
    void fa() const { std::cout << "fa" <<std::endl; }
};

struct b
{
    void fb() const { std::cout << "fb" <<std::endl; }
};

struct c
{
    void fc() const { std::cout << "fc" <<std::endl; }
};

struct d
{
    void fd() const { std::cout << "fd" <<std::endl; }
};


// the composer
struct with
{
    // rules
    a  operator()(        )       { return a(); }

    b  operator()(a, b    )       { return b(); }

    c  operator()(a, c&&  ) const { return c(); }

    a  operator()(a, c&   ) const { return a(); }

    d& operator()(b const&)       { static d s = d(); return s; }

    // do not require to be default constructible
    // this is where std::declval comes in handy. see below
    with() = delete;
};


// declare a host class
template<typename...>
struct host;

template<>
struct host<>
{ };

// which inherits from whatever the rules say
template<typename F, typename... Args, typename... Rest>
struct host<F(Args...), Rest...>
    : std::decay<decltype(std::declval<F>()(std::declval<Args>()...))>::type
    , host<Rest...>
{ };


int main()
{
    // you decide. with reports

    host<with()> h1; // inherits from result type of with::operator()()
    h1.fa();

    host<with(b)> h2; // with::operator()(b)
    h2.fd();

    host<with(a, b), with const(a, c)> h3; // etc.
    h3.fb();
    h3.fc();

    host<with const(a, c&&), with(b&&), with(a, c&)> h4;
    h4.fc();
    h4.fd();
    h4.fa();
}
