#include <iostream>
using namespace std;

bool test (int tamBloco) {
	return (tamBloco == 4);
}

int main() {


int tamBloco;
cin >> tamBloco;

if (test(tamBloco) == true) {
    cout << "true" << endl;
} else {
    cout << "false" << endl;
}

return 0;
}