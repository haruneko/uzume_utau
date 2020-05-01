// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <sstream>
#include <vector>

#include "Affix.hpp"

using namespace uzume::utau;

Affix::Affix(std::string prefix, std::string suffix)
    : prefix(std::move(prefix)), suffix(std::move(suffix)) {
}

Affixes Affix::from(std::string text) {
    Affixes ret;
    std::stringstream ss(text);
    std::string line;
    while(std::getline(ss, line)) {
        std::vector<std::string> es;
        std::stringstream s(line);
        std::string buf;
        while(std::getline(s, buf, '\t')) {
            es.push_back(buf);
        }
        if(es.size() != 3) {
            continue;
        }
        ret.insert(std::pair<std::string, Affix>(es[0], Affix(es[1], es[2])));
    }
    return ret;
}

std::string Affix::to_string() const {
    return std::string("Affix(") + prefix + "," + suffix + ")";
}
