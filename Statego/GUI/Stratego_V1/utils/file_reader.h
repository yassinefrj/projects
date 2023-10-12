#ifndef FILE_READER_H
#define FILE_READER_H
#include "model/stratego.h"
#include <string>
#include <fstream>
#include <vector>
namespace stratego {

class FileReader{

    std::vector<std::string> bluePieces_;
    std::vector<std::string> redPieces_;

public :

    /*!
     * \brief Create a empty file reader
     */
    FileReader();
    /*!
     * \brief Read the red and blue files, then fill the board
     * \param game the game to fill
     */
    void readFilePiece(Stratego& game);
    void readFilePiece(Stratego& game, std::string blue, std::string red);
};

}

#endif // FILE_READER_H
