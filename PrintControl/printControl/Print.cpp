#include "PrintControl.h"
#include <iostream>
using namespace std;
int main(int argc,char **argv) {
	if (argc < 2) {
		cout << "please enter file path" << endl;
		return 0;
	}
	PrintControl newPrint(argv[1], 1);
	if (argc >= 3) {
		int i = atoi(argv[2]);
		newPrint.setNumber(i);
	}
	newPrint.print_file();
}