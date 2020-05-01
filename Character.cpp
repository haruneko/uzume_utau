// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <utility>
#include <vector>
#include <sstream>
#include "Character.hpp"

using namespace uzume::utau;

Character::Character(std::string name, std::string imagePath, std::string sampleWavePath, std::string author, std::string webURLPath)
    : name(std::move(name)), imagePath(std::move(imagePath)), sampleWavePath(std::move(sampleWavePath)), author(std::move(author)), webURLPath(std::move(webURLPath)) {
}

Character Character::from(const std::string &text) {
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string buf;
    while(std::getline(ss, buf)) {
        lines.push_back(buf);
    }
    std::string name, imagePath, sampleWavePath, author, webURLPath;
    for(const std::string &line: lines) {
        std::stringstream s(line);
        std::vector<std::string> es;
        while(std::getline(s, buf, '=')) {
            es.push_back(buf);
        }
        if(es.size() != 2) {
            continue;
        }
        if(es[0] == "name") {
            name = es[1];
        } else if(es[0] == "image") {
            imagePath = es[1];
        } else if(es[0] == "sample") {
            sampleWavePath = es[1];
        } else if(es[0] == "author") {
            author = es[1];
        } else if(es[0] == "web") {
            webURLPath = es[1];
        }
    }
    return Character(name, imagePath, sampleWavePath, author, webURLPath);
}

std::string Character::to_string() const {
    return std::string("Character(")
        + name + ","
        + imagePath + ","
        + sampleWavePath + ","
        + author + ","
        + webURLPath + ")";
}
