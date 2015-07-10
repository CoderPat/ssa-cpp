#include "script.hpp"
#include "subtitle.hpp"

#include "alignment/basic_score.hpp"
#include "alignment/hirschberg.hpp"

#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;
using namespace alignment;

// Taken from the aligners library
template <typename Type, int Match, int Mismatch, int Insertion, int Deletion>
struct simple_score : basic_score<Type> {
  simple_score() : basic_score<Type>(Match, Mismatch, Insertion, Deletion) {}
};

class dumb_line_matcher {
    hirschberg<string, simple_score<string, 10,-10,0,0>> aligner;

public:
  typedef shared_ptr<basic_line> align_type;
  typedef basic_score<align_type>::score_type score_type;

  score_type operator()(align_type l, align_type r) const {
    auto wordsl = words_of(l->line()),
         wordsr = words_of(r->line());

    auto ret = aligner(wordsl, wordsr, "UNALIGNED");
    return get<0>(ret);
  }

  score_type ins() const { return 0; }
  score_type del() const { return 0; }
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    clog << "Usage: " << argv[0] << " script subtitle" << endl;
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

  ifstream scriptFile(argv[1]);
  if (!scriptFile.is_open()) {
    clog << "Could not open script: " << strerror(errno) << std::endl;
    return 2;
  }

  script script;
  script.from_ims(scriptFile);

  cout << "--- Script ---" << endl;
  for_each(script.begin(), script.end(), [](auto e) { e->output_to(cout); });
  cout << endl;

  hirschberg<shared_ptr<basic_line>, dumb_line_matcher> aligner;
  auto gap_symbol = make_shared<basic_line>(0, "GAP");
  auto alignment = aligner(script, subtitle, gap_symbol);

  cout << "Score of alignment: " << get<0>(alignment) << endl;
  cout << "Pairs:" << endl;

  auto Z = get<1>(alignment), W = get<2>(alignment);
  assert(Z.size() == W.size() && "alignments are not of same size");

  for (size_t i = 0; i < Z.size(); ++i) {
    Z[i]->output_to(cout);
    W[i]->output_to(cout);
    cout << endl;
  }

  return 0;
}
