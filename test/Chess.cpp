#include "Chess.h"

void Board::onStart()
{
    auto king = createGameObject("King");
    m_pieces.push_back(king);
}

ChessGame::ChessGame()
{
    auto scene = std::make_shared<Onyx::Scene>("Chess");
    m_scenes.push_back(scene);
    m_currentScene = scene;

    auto board = scene->createGameObject("Board");
    board->addComponent(new Board());
}