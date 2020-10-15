//
// Created by nitay on 30/12/18.
//

#include <fstream>
#include <iostream>
#include <map>
#include "Reader.h"
#include <vector>
#include <algorithm>
#include <sstream>
/**
 * The following is a name_space contains
 * string operations (such as split)
 */
namespace
    {
        /**
         *Split function
         * The following takes a string, a vector and another string
         * represents a group of delims, and fills that vector with
         * resulting split method.
         * @param str a given string std::string const reference
         * @param vec a given vector vector<std::string>
         * @param delims Seperators string //
         */
        void split(const std::string &str, std::vector<std::string> &vec,
                   const std::string &delims = " ")
        {
            std::size_t current, previous = 0;
            current = str.find_first_of(delims);
            while (current != std::string::npos)
            {
                vec.push_back(str.substr(previous, current - previous));
                previous = current + 1;
                current = str.find_first_of(delims, previous);
            }
            vec.push_back(str.substr(previous, current - previous));
        }
    }

/**
 * The following takes a file,
 * and returns a vector which describes the
 * common words  counter of this reader's common words
 * @param file_name
 * @return
 */

std::vector<int> Reader::readFile(std::string file_name)
{
    int vector_size = static_cast<int>(_frequent_words.size());
    std::vector<int> words_vec(static_cast<unsigned long>(vector_size));
    std::string none_words_characters = {'!', ',', ';', ':', ' ', '"', '\n', '\r'};
    std::ifstream txt_data;
    txt_data.open(file_name);
    if (!txt_data)
    {
        std::cerr << "****Error****\nEnter a valid txt file, " << file_name << " is not exist, returning\n";
        return words_vec;
    }
    std::string line;
    _current_line = 0;
    std::map<std::string, int> file_word_map;
    while (std::getline(txt_data, line))
    {
        _current_line += 1;
        std::vector<std::string> words;
        split(line, words, none_words_characters);
        for (std::string word:words)
        {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            std::set<std::string>::iterator it;
            it = _frequent_words.find(word);
            if (it != _frequent_words.end())
            {
                int index = static_cast<int>(std::distance(_frequent_words.begin(), it));
                words_vec[index]++;
            }
        }
    }
    return words_vec;
}


/**
 *The following is in charge of setting frequent words SET  accorrding
 * to the frequent words file given in the constructor
 * it reads the file with the hided assumption that it's
 * containing a  bunch of words seperated by a NEW LINE \n .
 */
void Reader::setFrequentWords()
{
    _current_line = 0;
    std::ifstream txt_data;
    txt_data.open(_frequent_word_file_name);
    if (!txt_data)
    {
        std::cerr << "****Error****\nEnter a Valid Frequent words file!\n" << "file " << _frequent_word_file_name
                  << " is Invalid! " <<
                  "returning\n";
        return;
    }
    std::string line;
    while (txt_data >> line)
    {
        _frequent_words.insert(line);
        _current_line += 1;
    }
}
