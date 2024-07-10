//
// Created by max on 02.07.24.
//


#pragma once

#include <global.h>

#include <gamebase.h>
#include <recthelper.h>
#include "Player.h"
#include <Enemy.h>

class ExampleGame;
class IntroState;
class PlasmaState;
class SortState;
class CameraState;
class ShooterState;
class MortalFlawState;

class ExampleGame final : public Game
{
public:
    ExampleGame();

    bool HandleEvent( const Event event ) override;
};

//My Game State
class MortalFlawState : public GameState
{

protected:

    //surfaces
    Surface * backgroundSurface = nullptr;

    Font    * font              = nullptr;
    Music   * music             = nullptr;
    Chunk   * sound             = nullptr;

    //textures
    Texture * playerTexture     = nullptr;
    Texture * enemyTexture      = nullptr;
    Texture * blendedText       = nullptr;


    Point     blendedTextSize   = { 0, 0 };

    //testing single enemy
    Enemy *enemyInstance;
    //multiple enemies
    std::vector<Enemy*> enemyVec;


    Player *p;
    //standard player size is 32x32
    Rect playerClipRect = {64,0,64,64};
    //collision table
    std::vector< SDL_Rect > colliderVec;


    static constexpr const Color white { 255, 255, 255, 255 };
    static constexpr const Color black { 0, 0, 0, 255 };


public:
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;

    //new functions


    void renderFromSpritesheet(int targetX,int targetY,int targetW,int targetH,SDL_Texture* t, const SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderFromSpritesheet(Rect values,SDL_Texture* t, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    Texture* loadFromFile(const std::string& path);
};


class IntroState : public GameState
{
protected:
    Font    * font              = nullptr;
    Texture * image             = nullptr;
    Music   * music             = nullptr;
    Chunk   * sound             = nullptr;
    Texture * blendedText       = nullptr;
    Point     blendedTextSize   = { 0, 0 };

    static constexpr const Color white { 255, 255, 255, 255 };
    static constexpr const Color black { 0, 0, 0, 255 };

    static constexpr const Array<Point,8> shadowOffsets = {
            /*
            Point { -1, -1 },
            Point { +1, -1 },
            Point { -1, +1 },
            Point { +1, +1 },
            Point { +0, +2 },
            Point { +2, +0 },
            Point { +0, -2 },
            Point { -2, +0 },
            */
            1_up   + 1_left,
            1_up   + 1_right,
            1_down + 1_left,
            1_down + 1_right,
            2_right,
            2_left,
            2_up,
            2_down,
    };

public:
    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;
};

class PlasmaState final : public IntroState
{
    Surface * plasmaSrf;
    Texture * plasmaTex;

    int brightness = 160;

    static constexpr const int Scale = 8;

public:
    // ctor
    using IntroState::IntroState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;
};

class SortState : public GameState
{
protected:
    struct Ball { float x,y,z,w; };

    Texture * image = nullptr;
    Vector<Ball> balls;
    bool isOrdered = false;
    bool isTransparent = false;
    bool isDarkened = false;

public:
    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;
};

class CameraState : public GameState
{
protected:
    Texture * bg[4] = { nullptr };
    Point bgSize[4];
    const FPoint bgStart[4] = {
            { 0,    -330 },
            { -350, -330 },
            { -450, -900 },
            { -800, -1500 },
    };
    const FPoint bgFactor[4] = {
            { 0.2f, 0.3f },
            { 0.4f, 0.45f },
            { 0.8f, 0.8f },
            { 1.2f, 1.2f },
    };
    bool bgIsVisible[4] = {
            true,
            true,
            true,
            true,
    };
    FPoint mouseOffset = { 0, 0 };
    FPoint mouseOffsetEased = { 0, 0 };

    bool isInverted = false;
    bool isEased = true;
    bool isFlux = true;
    FPoint cam { .x = 0, .y = 0 };

public:
    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;

    FPoint CalcFluxCam(const u32 totalMSec) const;
    void RenderLayer(const Point winSize, const FPoint camPos, const int index) const;
};

class ShooterState : public CameraState
{
protected:
    float progress = 0;
    u32 shootCooldown = 0;

    Chunk   * sound         = nullptr;
    Texture * projectile[4] = { nullptr };

    Vector<FPoint> enemyProjectiles;
    Vector<FPoint>::iterator enemyProjReuse;
    int     numDeadEnemyProj = 0;

    Vector<FPoint> myProjectiles;
    Vector<FPoint>::iterator myProjReuse;
    int     numDeadMyProj = 0;

    Vector<FRect> enemies = {
            { 1100, 280, 160, 160 },
            { 1200, 500, 80, 80 },
            { 1100, 680, 80, 80 },
    };

    FRect   player    = { 200, 530, 200, 100 };
    FPoint  sat[5]    = { { 0, 0 } };
    int     satCount  = 5;
    static constexpr const int satRadius = 25;

public:
    // ctor
    using CameraState::CameraState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;

    [[nodiscard]]
    bool IsProjectileAlive( const Vector<FPoint>::iterator & it ) const;
    void SpawnProjectile( const FPoint pos );
    void SpawnMyProjectile( const FPoint pos );
    void RetireProjectile( const Vector<FPoint>::iterator & it );
    void RetireMyProjectile( const Vector<FPoint>::iterator & it );
};
