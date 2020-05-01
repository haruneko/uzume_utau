// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef UZUME_UTAU_WAVE_LABEL_HPP
#define UZUME_UTAU_WAVE_LABEL_HPP

#include <string>

namespace uzume { namespace utau {

/**
 * WaveLabel represents a single line in `oto.ini` of a UTAU voicebank.
 */
class WaveLabel final {
public:
    WaveLabel() = delete;
    WaveLabel(std::string filename, std::string name, double msLeftBlank, double msConsonant, double msRightBlank, double msPreUtterance, double msOverlap);

    /**
     * WaveLabel#from generates a list of WaveLabel from text in `oto.ini`.
     */
    static std::vector<WaveLabel> from(const std::string &text);

    std::string to_string() const;

    const std::string filename;
    const std::string name;
    const double msLeftBlank;
    const double msConsonant;
    const double msRightBlank;
    const double msPreUtterance;
    const double msOverlap;
};

} }

#endif //UZUME_UTAU_WAVE_LABEL_HPP
