// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef UZUME_UTAU_CHARACTER_HPP
#define UZUME_UTAU_CHARACTER_HPP
#include <string>
#include <functional>

namespace uzume { namespace utau {

/**
 * Character represents a meta info in `character.txt` of a UTAU voicebank.
 */
class Character final {
public:
    Character() = delete;
    Character(std::string name, std::string imagePath, std::string sampleWavePath, std::string author, std::string webURLPath);

    /**
     * Character#from generates Character from text in `character.txt`.
     */
    static Character from(const std::string &text);

    std::string to_string() const;

    const std::string name;
    const std::string imagePath;
    const std::string sampleWavePath;
    const std::string author;
    const std::string webURLPath;
};

} }

#endif //UZUME_UTAU_CHARACTER_HPP
