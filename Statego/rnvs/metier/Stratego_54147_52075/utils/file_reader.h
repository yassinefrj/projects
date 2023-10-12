#ifndef FILE_READER_H
#define FILE_READER_H
#include <string>
// #include <fstream>       // rnvs : include / déclaration anticipée
#include <vector>
//#include "model/stratego.h"   // rnvs : include / déclaration anticipée
#include "model/piece.h"        // rnvs : include / déclaration anticipée
namespace stratego
{

class Stratego;             // rnvs : include / déclaration anticipée

class FileReader
{

    std::vector<std::string> bluePieces_;
    std::vector<std::string> redPieces_;

    std::vector<Piece> listBluePiece_;
    std::vector<Piece> listRedPiece_;

  public :


    FileReader();

    void readFilePiece(Stratego & game);

    void readFilePiece();

    std::vector<std::string> getBluePieces() const;
    std::vector<std::string> getRedPieces() const;

    std::vector<Piece> getListBluePiece() const;
    std::vector<Piece> getListRedPiece() const;


};

}

#endif // FILE_READER_H
