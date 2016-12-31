#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class read{
	private:			
		ifstream infile;
	public:
		read(string fileName){infile.open(fileName.c_str(), ios::binary | ios::in | ios::out);}
		~read(){infile.close();}
};

int main(){
	string fileName = "./test/FileCreator/SourceTEST.cpp";
	read r(fileName);

return 0;
}
