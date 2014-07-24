#include "Stats.h"
#include <fstream>

int main() {
	Stats test;
	ofstream logfile;
	logfile.open("log-file.txt", std::ios::out | std::ios::app);
	test.Allocate(10);
	test.Add_Stat(0,4);
	test.logCSV_FieldNames(logfile);
	test.logCSV(logfile);
	return 0;
}
