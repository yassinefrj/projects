#ifndef FILE_READER_H
#define FILE_READER_H
#include <string>
#include <fstream>
#include <vector>
#include "model/stratego.h"
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
};

}

#endif // FILE_READER_H
