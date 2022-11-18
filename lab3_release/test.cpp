#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(){
    string line;
    getline(cin, line);
    stringstream foo(line);
    string tempName;
    int tempSize2;
    foo >> tempName >> tempSize2;
    // if(foo.fail()){
    //     cout << "failed";
    // }
    cout << tempName << tempSize2;
}