// File: GameAssets.h

#ifndef GAMEASSETS_H
#define GAMEASSETS_H

#include <SFML/Graphics.hpp>

using namespace sf;

class GameAssets {
public:
    // Textures for tile colors
    Texture tileTextureYellow;
    Texture tileTextureCyan;
    Texture tileTextureRed;
    Texture tileTextureGreen;
    Texture tileTextureOrange;
    Texture tileTextureBlue;
    Texture tileTexturePurple;
    Texture backgroundTexture;
    Texture tileTextureEmpty;

    // Sprites for tile colors
    Sprite tileSpriteYellow;
    Sprite tileSpriteCyan;
    Sprite tileSpriteRed;
    Sprite tileSpriteGreen;
    Sprite tileSpriteOrange;
    Sprite tileSpriteBlue;
    Sprite tileSpritePurple;
    Sprite backgroundSprite;
    Sprite tileSpriteEmpty;

    FloatRect TileBounds;

    GameAssets() {
        // Load Textures
        tileTextureYellow.loadFromFile("TetrisAssets/TileYellow.png");
        tileTextureCyan.loadFromFile("TetrisAssets/TileCyan.png");
        tileTextureRed.loadFromFile("TetrisAssets/TileRed.png");
        tileTextureGreen.loadFromFile("TetrisAssets/TileGreen.png");
        tileTextureOrange.loadFromFile("TetrisAssets/TileOrange.png");
        tileTextureBlue.loadFromFile("TetrisAssets/TileBlue.png");
        tileTexturePurple.loadFromFile("TetrisAssets/TilePurple.png");
        backgroundTexture.loadFromFile("TetrisAssets/Background.png");
        tileTextureEmpty.loadFromFile("TetrisAssets/TileEmpty.png");

        // Assign Textures to Sprites
        tileSpriteYellow.setTexture(tileTextureYellow);
        tileSpriteCyan.setTexture(tileTextureCyan);
        tileSpriteRed.setTexture(tileTextureRed);
        tileSpriteGreen.setTexture(tileTextureGreen);
        tileSpriteOrange.setTexture(tileTextureOrange);
        tileSpriteBlue.setTexture(tileTextureBlue);
        tileSpritePurple.setTexture(tileTexturePurple);
        backgroundSprite.setTexture(backgroundTexture);
        tileSpriteEmpty.setTexture(tileTextureEmpty);

        float scale = 0.15f;  // Adjust the scale factor as needed
        tileSpriteYellow.setScale(scale, scale);
        tileSpriteCyan.setScale(scale, scale);
        tileSpriteRed.setScale(scale, scale);
        tileSpriteGreen.setScale(scale, scale);
        tileSpriteOrange.setScale(scale, scale);
        tileSpriteBlue.setScale(scale, scale);
        tileSpritePurple.setScale(scale, scale);
        tileSpriteEmpty.setScale(scale, scale);

        TileBounds = tileSpriteEmpty.getGlobalBounds();
    }
};

#endif // GAMEASSETS_H
