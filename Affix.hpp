// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef UZUME_UTAU_AFFIX_HPP
#define UZUME_UTAU_AFFIX_HPP

#include <string>
#include <unordered_map>

namespace uzume { namespace utau {
class Affix;
typedef std::unordered_map<std::string, Affix> Affixes;

/**
 * Affix represents a single line in `preset.map` of a UTAU voicebank.
 */
class Affix final {
public:
    Affix() = delete;
    Affix(std::string prefix, std::string suffix);

    const std::string prefix;
    const std::string suffix;

    /**
     * Affix#from generates a list of affix from text in `prefix.map`.
     */
    static Affixes from(std::string text);

    std::string to_string() const;
};

} }

#endif //UZUME_UTAU_AFFIX_HPP
