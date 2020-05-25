// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <fstream>
#include <utility>
#include "Voicebank.hpp"

#ifdef __WIN32__
#include <windows.h>
#include <iostream>

#else
#include <sys/types.h>
#include <dirent.h>
#endif

using namespace uzume::utau;

namespace uzume { namespace utau {
    const char *CharacterFilename = u8"character.txt";
    const char *LabelsFilename = u8"oto.ini";
    const char *AffixesFilename = u8"prefix.map";
} }

namespace {
    const char *Separator =
    #ifdef __WIN32__
            "\\"
    #else
            "/"
    #endif
            ;
}

std::string uzume::utau::DefaultFileReader(const char *filepath) {
    std::ifstream ifs(filepath);
    if(ifs.fail()) {
        return std::string();
    }
    return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}

std::vector<std::string> uzume::utau::DefaultDirectoryEnumerator(const char *filepath) {
    std::vector<std::string> ret;
#ifdef __WIN32__
    std::string path = std::string(filepath).append("\\*");
    WIN32_FIND_DATA data;
    HANDLE hFind;
    if((hFind = FindFirstFile(path.c_str(), &data)) != INVALID_HANDLE_VALUE) {
        do {
            if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                ret.emplace_back(data.cFileName);
            }
        } while(FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }
#else
    DIR* dirp = opendir(filepath);
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        ret.emplace_back(dp->d_name);
    }
    closedir(dirp);
#endif
    return ret;
}

Voicebank::Voicebank(Character character, Affixes affixes, std::unordered_map<std::string, std::vector<WaveLabel> > labels)
    : character(std::move(character)), affixes(std::move(affixes)), labels(std::move(labels)){
}

Voicebank Voicebank::from(
        const char *filepath,
        const std::function<std::string (const char *)>& read,
        const std::function<std::vector<std::string> (const char *)>& enumerate) {
    std::string characterPath = std::string(filepath).append(Separator).append(CharacterFilename);

    std::string affixesPath = std::string(filepath).append(Separator).append(AffixesFilename);

    std::vector<std::string> dirs = enumerate(filepath);
    std::unordered_map<std::string, std::vector<WaveLabel> > labels;
    for(const auto &dir: dirs) {
        if(dir.find_first_not_of("..") == 0) { continue; } // Do not read a parental directory.
        auto path(std::string(filepath).append(Separator).append(dir).append(Separator).append(LabelsFilename));
        labels.insert(std::pair<std::string, std::vector<WaveLabel> >(dir, WaveLabel::from(read(path.c_str()))));
    }
    return Voicebank(
            Character::from(read(characterPath.c_str())),
            Affix::from(read(affixesPath.c_str())),
            labels);
}

namespace {
    std::string enumerate(const Affixes &affixes) {
        std::string result("[");
        for(const auto &p: affixes) {
            result += "(" + p.first + ":" + p.second.to_string() +"),";
        }
        result += "]";
        return result;
    }

    std::string enumerate(const std::unordered_map<std::string, std::vector<WaveLabel> > &labels) {
        std::string result("[");
        for(const auto &p: labels) {
            result += "(dir=" + p.first + ":";
            for(const auto &l: p.second) {
                result += l.to_string() + ",";
            }
            result += ")\n";
        }
        result += "]";
        return result;
    }
}

std::string Voicebank::to_string() const {
    return std::string("Voicebank(")
        + enumerate(labels) + ","
        + character.to_string() + ","
        + enumerate(affixes) + ")";
}
