#include <fstream>

int main() {
  std::ofstream outfile;

  outfile.open("/Users/andreas/untitled/yourfile.txt", std::ios_base::app);//std::ios_base::app
  outfile << "your data i here";
  outfile.close();
  return 0;
}
