#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  ifstream input_file("../4th_contest/CaesarEncrypt/input.txt");
  ofstream output_file("../4th_contest/CaesarEncrypt/output.txt");
  string s;
  input_file >> s;
  for (char& c : s)
    c = 'a' + (c + 3 - 'a') % 26;
  output_file << s;
  return 0;
}