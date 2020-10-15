//
// Created by nitay on 30/12/18.
//

#include <iostream>
#include <map>
#include <cmath>
#include "Reader.h"

/**
 * The following contains vectors operations
 * set - of functions.
 */
namespace vectors_operations
    {
        /**
         * get_vectors_norm
         * @param vec Given vector reference
         * @return  doube vector's norm
         */
        double getVectorNorm(std::vector<int> &vec)
        {
            double norm = 0;
            for (int i : vec)
            {
                norm += i * i;
            }
            norm = std::sqrt(norm);
            return norm;
        }

        /**
         * get_author_signature
         * @param unknown unknown author vector .
         * @param other - another vector same size as unknown vector.
         * @return  GAMMA - angle between unknown and other vector.
         */
        double getAuthorSignature(std::vector<int> &unknown, std::vector<int> &other)
        {
            double scalar_mult = 0;
            for (int i = 0; i < unknown.size(); i++)
            {
                scalar_mult += unknown[i] * other[i];
            }
            double unknown_norm = vectors_operations::getVectorNorm(unknown);
            double other_norm = vectors_operations::getVectorNorm(other);
            double cos_angle = scalar_mult;
            double denominator = (other_norm * unknown_norm);
            if (denominator == 0)
            {
                return 0;
            }
            return cos_angle / denominator;
        }
    }

/**
 * The following is the main function
 * @param argc  num of args + name of .o
 * @param argv  array of char* (arguments)
 * @return  None (only prints)
 */
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cout
                << "Please enter at least The following:\n"
                   "1.frequent_word.txt\n2.unknown_author.txt\n3.Additional knownAuthor.txt\n";
        return 0;
    }
    std::string freq = argv[1];
    std::string unknown = argv[2];
    Reader my_reader = Reader(freq);
    my_reader.setFrequentWords();
    std::vector<int> unknown_vector = my_reader.readFile(unknown);
    std::map<std::string, std::vector<int>> known_authors_vectors;
    double max = 0;
    std::string best_match;
    for (int i = 3; i < argc; i++)
    {
        std::vector<int> result_vector = my_reader.readFile(argv[i]);
        double cos_res = vectors_operations::getAuthorSignature(unknown_vector, result_vector);
        if (cos_res > max)
        {
            max = cos_res;
            best_match = argv[i];
        }
        std::cout << argv[i] << " " << cos_res << std::endl;
    }
    std::cout << "Best matching author is " << best_match << " " << max << std::endl;
}
