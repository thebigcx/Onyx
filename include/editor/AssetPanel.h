#pragma once

#include <string>

namespace Onyx
{

class AssetPanel
{
public:
    static void setupAssets();

    static void drawAssetPanel();

private:
    static inline std::string m_assetView = "Texture View";
};

}