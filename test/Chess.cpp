#include "Chess.h"

void Board::onStart()
{
    auto king = createGameObject("King");
    m_pieces.push_back(king);

    
}

void ChessScene::onStart()
{
    auto board = createGameObject("Board");
    board->addComponent(new Board());
}

ChessGame::ChessGame()
{
    m_scenes.push_back(std::make_shared<ChessScene>());
    changeScene("Chess Game");
}