#pragma once

#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>
#include <onyx/scene/Script.h>

class Board : public Onyx::Script
{
public:
    void onStart() override;

    void onUpdate(float dt) override {}

private:
    std::vector<Onyx::WeakPtr<Onyx::GameObject>> m_pieces;
};

class ChessScene : public Onyx::Scene
{
public:
    ChessScene()
        : Onyx::Scene("Chess Game") {}

    void onStart() override;

private:
};

class ChessGame : public Onyx::Game
{
public:
    ChessGame();
};