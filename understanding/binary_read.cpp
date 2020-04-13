#include <fstream>
#include <iostream>
#include <string> 

using namespace std;

void print_first_bytes(char *arr, int size){
  for(int i=0; i<size; i++){
    printf("%02hhx ", arr[i]);
  }
  cout << endl;
}

int main()
{
    streampos size;

    // pointer to memory
    char * memblock;

    // ate flag -> pointer in the end to determine size
    ifstream file ("test.txt", ios::in|ios::ate);

    if (file.is_open())
    {
        size = file.tellg();

        // allocate memory for file
        memblock = new char [size];

        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();

        cout << "The entire file content is in memory" << endl;
        cout << "File size: " << to_string(size) << "B" << endl;

    }
    else cout << "Unable to open file";

    print_first_bytes(memblock, 10);

    delete[] memblock;

    return 0;
}