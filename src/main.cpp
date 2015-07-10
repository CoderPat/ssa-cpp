#include "subtitle.hpp"

#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    clog << "Usage: " << argv[0] << " script subtitle destination" << endl;
    return 1;
  }

  ifstream subtitleFile(argv[2]);
  if (!subtitleFile.is_open()) {
    clog << "Could not open subtitle: " << strerror(errno) << endl;
    return 1;
  }

  subtitle subtitle;
  subtitle.from_srt(subtitleFile);

  cout << "--- Subtitle ---" << endl;
  for_each(subtitle.begin(), subtitle.end(), [](auto e) { e->output_to(cout); });
  cout << endl;

  return 0;
}
