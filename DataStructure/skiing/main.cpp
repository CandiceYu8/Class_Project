#include <iostream>
#include "skiing.h"

using namespace std;

int main()
{
    skiing ski1;
    ski1.SearchMaxLength();
    ski1.PrintLength();
    int result = ski1.ReturnMaxLength();
    cout << result << endl;
    return 0;
}
