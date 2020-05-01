// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef UZUME_UTAU_VOICEBANK_HPP
#define UZUME_UTAU_VOICEBANK_HPP

#include <vector>
#include "Affix.hpp"
#include "Character.hpp"
#include "WaveLabel.hpp"

namespace uzume { namespace utau {

extern const char *CharacterFilename;
extern const char *LabelsFilename;
extern const char *AffixesFilename;

std::string DefaultFileReader(const char *filepath);
std::vector<std::string> DefaultDirectoryEnumerator(const char *filepath);

/**
 * Voicebank represents a single UTAU voicebank.
 */
class Voicebank final {
public:
    Voicebank() = delete;
    Voicebank(Character character, Affixes affixes, std::unordered_map<std::string, std::vector<WaveLabel> > labels);

    /**
     * Voicebank#from generates Voicebank in a single directory.
     * @param filepath to a UTAU voicebank.
     * @param read specifies a way to read files. (For debug or testing)
     * @param enumerate specifies a way to enumerate a list of directories in a specified directory. (For debug or testing)
     */
    static Voicebank from(
            const char* filepath,
            const std::function<std::string(const char*)>& read = DefaultFileReader,
            const std::function<std::vector<std::string>(const char*)>& enumerate = DefaultDirectoryEnumerator);

    std::string to_string() const;

    const Character character;
    const Affixes affixes;
    const std::unordered_map<std::string, std::vector<WaveLabel> > labels;
};

} }

#endif //UZUME_UTAU_VOICEBANK_HPP
