#include <tr1/random>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace std::tr1;

int main()
{
    variate_generator<mt19937, normal_distribution<> > r(mt19937(time(NULL)), normal_distribution<>(0.0, 0.1));

    for (int i = 0; i < 100; i++)
        cout << r() << endl;
    return 0;
}
