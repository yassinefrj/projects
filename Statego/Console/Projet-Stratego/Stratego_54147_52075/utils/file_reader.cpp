#include "file_reader.h"

namespace stratego {


FileReader::FileReader(){}

void FileReader::readFilePiece(Stratego& game){

    std::string red = "../Stratego_54147_52075/model/red.txt";
    std::string blue = "../Stratego_54147_52075/model/blue.txt";
    std::cout << "Voici le chemin du fichier config du joueur Bleu  : " <<std::endl << blue << std::endl;
    std::cout << "Voici le chemin du fichier config du joueur Rouge : " << std::endl <<red << std::endl;

    std::ifstream redFile (red );
    std::ifstream blueFile (blue);


    if(redFile.is_open() && blueFile.is_open() ){
        int countRed = 0;
        int countBlue = 0;
        std::string pieceRed;
        std::string pieceBlue;

        while (redFile >> pieceRed && blueFile >> pieceBlue) {
            redPieces_.push_back(pieceRed);
            countRed ++;
            bluePieces_.push_back(pieceBlue);
            countBlue ++;
        }
        if(countBlue < 40 || countBlue > 40 ){
            std::cout << "Error : need 40 pieces ! They are : "
                      << countBlue << std::endl
                      << "Please put exactly  40 pieces in the blue file config ! ";
            std::cout << std::endl;
            exit(1);

        }else if (countRed< 40 || countRed > 40) {
            std::cout << "Error : need 40 pieces ! They are : "
                      << countRed << std::endl
                      << "Please put exactly  40 pieces in the red file config ! ";
            std::cout << std::endl;
            exit(1);
        }

        redFile.close();
        blueFile.close();

    }


    int countD = 0;
    int countB = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int count5 = 0;
    int count6 = 0;
    int count7 = 0;
    int count8 = 0;
    int count9 = 0;
    int count10= 0;

    int countDB = 0;
    int countBB = 0;
    int count1B = 0;
    int count2B = 0;
    int count3B = 0;
    int count4B = 0;
    int count5B = 0;
    int count6B = 0;
    int count7B = 0;
    int count8B = 0;
    int count9B = 0;
    int count10B= 0;


    for (int row {6},column{0},cpt{0}; cpt < static_cast<int>(redPieces_.size()); column++,cpt ++ ) {

        if(row!=0 && row%10 == 0){
            row++;
            column=0;
        }

        if(redPieces_[cpt] == "10"){
            count10++;
            game.addPiece(Position(row,column),Piece(10,Color::RED,1));


        }else if(redPieces_[cpt] == "9"){
            count9++;
            game.addPiece(Position(row,column),Piece(9,Color::RED,1));


        }else if(redPieces_[cpt] == "8"){
            count8++;
            game.addPiece(Position(row,column),Piece(8,Color::RED,1));


        }else if(redPieces_[cpt] == "7"){
            count7++;
            game.addPiece(Position(row,column),Piece(7,Color::RED,1));


        }else if(redPieces_[cpt] == "6"){
            count6++;
            game.addPiece(Position(row,column),Piece(6,Color::RED,1));


        }else if(redPieces_[cpt] == "5"){
            count5++;
            game.addPiece(Position(row,column),Piece(5,Color::RED,1));


        }else if(redPieces_[cpt] == "4"){
            count4++;
            game.addPiece(Position(row,column),Piece(4,Color::RED,1));


        }else if(redPieces_[cpt] == "3"){
            count3++;
            game.addPiece(Position(row,column),Piece(3,Color::RED,1));


        }else if(redPieces_[cpt] == "2"){
            count2++;
            game.addPiece(Position(row,column),Piece(2,Color::RED));


        }else if(redPieces_[cpt] == "1"){
            count1++;
            game.addPiece(Position(row,column),Piece(1,Color::RED,1));


        }else if(redPieces_[cpt] == "D"){
            countD++;
            game.addPiece(Position(row,column),Piece(0,Color::RED,0));


        }else if(redPieces_[cpt] == "B"){
            countB++;
            game.addPiece(Position(row,column),Piece(11,Color::RED,0));


        }else {
            std::cout << "Error : the piece is not recognized : " << redPieces_[cpt] << std::endl
                      << "Please put exactly 40 correct pieces in the red file ! ";
            std::cout << std::endl;
            exit(1);
        }

    }

    for (int row {0},column{0},cpt{0}; cpt < static_cast<int>(bluePieces_.size()); column++,cpt ++ ) {

        if(row!=0 && row%10 == 0){
            row++;
            column=0;
        }

        if(bluePieces_[cpt] == "10"){
            count10B++;
            game.addPiece(Position(row,column),Piece(10,Color::BLUE,1));

        }else if(bluePieces_[cpt] == "9"){
            count9B++;
            game.addPiece(Position(row,column),Piece(9,Color::BLUE,1));

        }else if(bluePieces_[cpt] == "8"){
            count8B++;
            game.addPiece(Position(row,column),Piece(8,Color::BLUE,1));

        }else if(bluePieces_[cpt] == "7"){
            count7B++;
            game.addPiece(Position(row,column),Piece(7,Color::BLUE,1));


        }else if(bluePieces_[cpt] == "6"){
            count6B++;
            game.addPiece(Position(row,column),Piece(6,Color::BLUE,1));


        }else if(bluePieces_[cpt] == "5"){
            count5B++;
            game.addPiece(Position(row,column),Piece(5,Color::BLUE,1));


        }else if(bluePieces_[cpt] == "4"){
            count4B++;
            game.addPiece(Position(row,column),Piece(4,Color::BLUE,1));


        }else if(bluePieces_[cpt] == "3"){
            count3B++;
            game.addPiece(Position(row,column),Piece(3,Color::BLUE,1));


        }else if(bluePieces_[cpt] == "2"){
            count2B++;
            game.addPiece(Position(row,column),Piece(2,Color::BLUE));


        }else if(bluePieces_[cpt] == "1"){
            count1B++;
            game.addPiece(Position(row,column),Piece(1,Color::BLUE,1));


        }else if(bluePieces_[cpt] == "D"){
            countDB++;
            game.addPiece(Position(row,column),Piece(0,Color::BLUE,0));


        }else if(bluePieces_[cpt] == "B"){
            countBB++;
            game.addPiece(Position(row,column),Piece(11,Color::BLUE,0));


        }else {
            std::cout << "Error : the piece is not recognized : " << bluePieces_[cpt] << std::endl
                      << "Please put exactly 40 correct pieces in the blue file ! ";
            std::cout << std::endl;
            exit(1);
        }


    }

    if(count1B != 1 || count1 != 1 ||count2B !=  8 ||
            count2 != 8  ||count3B != 5 ||count3 != 5 ||
            count4B != 4 ||count4 != 4  ||count5B != 4 ||
            count5 != 4 ||count6B != 4 || count6 != 4 ||
            count7B != 3 || count7 != 3 || count8B != 2 ||
            count8 != 2 || count9B != 1 || count9 != 1 ||
            count10B != 1 || count10 != 1 || countBB != 6
            || countB != 6 ||  countDB != 1 || countD != 1 ){

        std::cout << "Error : miss the correct amount of pieces "  << std::endl
                  << "Please put exactly the correct amount of pieces : See the manual of the game ! ";
        std::cout << std::endl;

        exit(1);
    }

}


}
