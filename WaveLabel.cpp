// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <sstream>
#include <vector>
#include "WaveLabel.hpp"

using namespace uzume::utau;

WaveLabel::WaveLabel(std::string filename, std::string name, double msLeftBlank, double msConsonant, double msRightBlank, double msPreUtterance, double msOverlap)
    : filename(std::move(filename)), name(std::move(name)), msLeftBlank(msLeftBlank), msConsonant(msConsonant), msRightBlank(msRightBlank), msPreUtterance(msPreUtterance), msOverlap(msOverlap) {
}

namespace {
    WaveLabel parse(const std::string &line) {
        std::string filename, name;
        double msLeftBlank = 0.0, msConsonant = 0.0, msRightBlank = 0.0, msPreUtterance = 0.0, msOverlap = 0.0;

        std::stringstream s1(line);
        std::string buf;
        std::vector<std::string> es;
        while(std::getline(s1, buf, ',')) {
            es.push_back(buf);
        }
        if(es.size() != 6) {
            return WaveLabel("", "", 0, 0, 0, 0, 0);
        }
        std::stringstream s2(es[0]);
        std::vector<std::string> ns;
        while(std::getline(s2, buf, '=')) {
            ns.push_back(buf);
        }
        if(ns.size() != 2) {
            return WaveLabel("", "", 0, 0, 0, 0, 0);
        }
        // FIXME: `atof` can not report errors while converting string into digits. `strtod` will be good here.
        return WaveLabel(
                ns[0],
                ns[1],
                std::atof(es[1].c_str()),
                std::atof(es[2].c_str()),
                std::atof(es[3].c_str()),
                std::atof(es[4].c_str()),
                std::atof(es[5].c_str()));
    }
}

std::vector<WaveLabel> WaveLabel::from(const std::string &text) {
    std::stringstream ss(text);
    std::string line;
    std::vector<WaveLabel> ret;
    while(std::getline(ss, line)) {
        ret.push_back(parse(line));
    }
    return ret;
}

std::string WaveLabel::to_string() const {
    return std::string("WaveLabel(")
        + filename + ","
        + name + ","
        + std::to_string(msLeftBlank) + ","
        + std::to_string(msConsonant) + ","
        + std::to_string(msRightBlank) + ","
        + std::to_string(msPreUtterance) + ","
        + std::to_string(msOverlap) + ")";
}
