#ifndef SCRIPT_HPP__
#define SCRIPT_HPP__

#include "basic_line.hpp"
#include "dialogue_line.hpp"
#include "utils.hpp"
#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class script {
public:
  using content_type = std::vector<std::shared_ptr<basic_line>>;

  content_type::const_iterator begin() const;
  content_type::const_iterator end() const;

public:
  template <typename InputStream>
  void from_ims(InputStream &in);

private:
  content_type script_;
};

template <typename InputStream>
void script::from_ims(InputStream &in) {
  using namespace std;

  vector<block_type> blocks {read_blocks(in)};

  script_.clear(); // XXX: should we really clear the script?

  for (const auto &rawblock : blocks) {
    assert(!rawblock.empty() && "read_blocks creates empty blocks");

    // Group by indentation
    auto groups = group(rawblock.cbegin(), rawblock.cend(), [](auto &l, auto &r) {
      // FIXME: whitespace definition. Also, use std::find_if_not + isspace
      size_t il = l.line().find_first_not_of(" \t");
      size_t ir = r.line().find_first_not_of(" \t");

      assert(il != l.line().npos && "read_blocks adds empty lines");
      assert(ir != r.line().npos && "read_blocks adds empty lines");

      return ir == il;
    });

    assert(!groups.empty() && "group creates empty groups");

    // Narrative or directive
    if (groups.size() == 1) {
      // Single line
      if (groups.front().size() == 1) {
        auto &line = groups.front().front().line();

        if (is_all_upper(line)) {
          // TODO: Location/timeline directive
        } else {
          // TODO: Narrative
        }
      } else {
        // TODO: Narrative
      }
    } else {
      assert(!groups.front().empty() && "group creates empty subgroups");

      // Dialogue
      if (is_all_upper(groups.front().front().line())) {
        auto character = trim(groups.front().front().line());

        for (auto it = ++rawblock.begin(), et = rawblock.end(); it != et; ++it) {
          assert(!it->line().empty() && "empty line!");

          // Dialogue lines are indented
          if (!isspace(it->line()[0])) break;

          script_.push_back(make_shared<dialogue_line>(it->lineno(), it->line(), character));
        }
      }
    }
  }
}

#endif // SCRIPT_HPP__
