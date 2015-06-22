#ifndef SCRIPT_HPP__
#define SCRIPT_HPP__

#include "utils.hpp"
#include <memory>

class script {
public:
  template <typename InputStream>
  static std::unique_ptr<script> from_ims(InputStream &in);

private:

};


template <typename InputStream>
std::unique_ptr<script> script::from_ims(InputStream &in) {
  std::vector<block_type> blocks {read_blocks(in)};

  for (const auto &rawblock : blocks) {
    assert(!rawblock.empty() && "read_blocks creates empty blocks");

    // Group by indentation
    auto groups = group(rawblock.cbegin(), rawblock.cend(), [](auto &l, auto &r) {
      // FIXME: whitespace definition
      size_t il = l.line().find_first_not_of(" \t");
      size_t ir = r.line().find_first_not_of(" \t");

      assert(il != l.npos && "read_blocks adds empty lines");
      assert(ir != r.npos && "read_blocks adds empty lines");

      return ir == il;
    });

    assert(!groups.empty() && "group creates empty groups");

    // Narrative or directive
    if (groups.size() == 1) {
      static auto iscaps = [](auto c) {
        return ispunct(c) || isspace(c) || isupper(c);
      };

      // Single line
      if (groups.front().size() == 1) {
        auto &line = groups.front().front();

        if (std::all_of(line.cbegin(), line.cend(), iscaps)) {
          // Location/timeline directive
        }
      }
    }
  }

  return std::make_unique<script>();
}

#endif // SCRIPT_HPP__
