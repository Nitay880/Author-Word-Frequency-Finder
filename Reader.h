#include <utility>

#include <utility>

#include <utility>

//
// Created by nitay on 30/12/18.
//

#ifndef EX2_READER_H
#define EX2_READER_H


#include <string>
#include <set>
#include <vector>

/**
 * The following represents a READER -
 * which takes a file and reades it,
 * according to the rules of the ex.
 * it's pre - loaded with frequent words file,
 * when initiated,
 * it is determine each and every file it reads
 * through the eyes of the FREQUENT WORDS SET.
 */
class Reader
{
    // Frequent_words file
    std::string _frequent_word_file_name;
    // Frequent_words set
    std::set<std::string> _frequent_words = {};
    //lines counter
    int _current_line;
public:

    /**
     * Constructor with a
     * frequent words file name
     * @param file_name  file's path and name i.e ' /folder/name .type'
     */

    explicit Reader(std::string file_name)
    {
        _frequent_word_file_name = std::move(file_name);
        _current_line = 0;
    }

    /**
     * The following returns
     * used words vector according
     * to the frequent words set
     * @param file_name file's path and name i.e ' /folder/name .type'
     * @return Vector<int>
     */
    std::vector<int> readFile(std::string file_name);

    /**
     *  The following reads the frequent
     *  words file that was given in the constructor
     *  and intializes _frequent words set.
     *  @return None
     */
    void setFrequentWords();
};


#endif //EX2_READER_H
