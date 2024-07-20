//
// Created by max on 02.07.24.
//


#pragma once

#include <global.h>

#include <gamebase.h>
#include <recthelper.h>

#include "Player.h"
#include <Enemy.h>
#include <Card_Dagger.h>
#include <Card_Sword.h>
#include <Card_ForgeStrike.h>
#include <Ui_Bar.h>

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
    Texture * playerTexture          = nullptr;
    Texture * enemyTexture           = nullptr;
    Texture * playerFacingTexture    = nullptr;
    Texture * cardDaggerTexture      = nullptr;
    Texture * cardSwordTexture       = nullptr;
    Texture * cardForgeStrikeTexture = nullptr;
    Texture * uiBackgroundTexture    = nullptr;
    Texture * uiCardBaseTexture      = nullptr;
    Texture * uiCardWhiteSpinTexture = nullptr;
    Texture * uiBarWhiteRedTexture   = nullptr;
    Texture * uiBarYellowBlueTexture = nullptr;
    Texture * uiPilesTexture         = nullptr;
    Texture * uiDrawReadyIconTexture = nullptr;
    Texture * uiNumbersTexture       = nullptr;

    //Texture * blendedText            = nullptr;
    //Point     blendedTextSize   = { 0, 0 };

    //-----------------------------------------------

    std::vector<Enemy*> enemyVec;
    std::vector<Enemy*> enemyDeadVec;
    std::unordered_set<int> setForHitEnemyIDs;
    bool respawnToggle = true;

    Player *p;

    //current player size is 32x32. Spritesheet in 64x64.
    ///TODO give player a clip rect when taking damage is implemented
    Rect playerClipRect = {64,0,64,64};

    /**UI needs to be refactored badly. All of this stuff should be composed into classes. Noticed that too late.
    * Naming them uiSomething_ helped but this still hurts to look at.
    * uiCard and uiPile are background objects while numbers and icons are foreground.
     * Kommentare für UI sollen helfen den Überblick zu behalten bis ich das refactor.
    */

    //define UI background surface dimensions
    Rect guiRect = {0,SCREEN_HEIGHT-SCREEN_HEIGHT/3,SCREEN_WIDTH,SCREEN_HEIGHT/3};

    //store width and height of GUI card elements
    Point uiCard_Size = {128, 192};
    //clipper for the card spritesheet
    Rect uiCard_Clip = {0, 0, 64, 96};


    Rect uiCard_SlotLeftRect = {uiCard_Size.x * 3, (SCREEN_HEIGHT - uiCard_Size.y) - uiCard_Size.y / 2, uiCard_Size.x, uiCard_Size.y};
    Rect uiCard_SlotMiddleRect = {(uiCard_Size.x * 4) + uiCard_Size.x / 4, (SCREEN_HEIGHT - uiCard_Size.y) - uiCard_Size.y / 2, uiCard_Size.x, uiCard_Size.y};
    Rect uiCard_SlotRightRect = {(uiCard_Size.x * 5) + (uiCard_Size.x / 4) * 2, (SCREEN_HEIGHT - uiCard_Size.y) - uiCard_Size.y / 2, uiCard_Size.x, uiCard_Size.y};

    Point uiCard_IconSize = {uiCard_Size.x/2,uiCard_Size.y/2};
    Rect uiCard_IconLeftRect = {uiCard_SlotLeftRect.x+(uiCard_SlotLeftRect.w/2)-uiCard_IconSize.x/2,
                                uiCard_SlotLeftRect.y+(uiCard_SlotLeftRect.h/2)-uiCard_IconSize.y/2,
                                uiCard_IconSize.x,
                                uiCard_IconSize.y};

    Rect uiCard_IconMiddleRect ={uiCard_SlotMiddleRect.x+(uiCard_SlotMiddleRect.w/2)-uiCard_IconSize.x/2,
                                 uiCard_SlotMiddleRect.y+(uiCard_SlotMiddleRect.h/2)-uiCard_IconSize.y/2,
                                uiCard_IconSize.x,
                                uiCard_IconSize.y};

    Rect uiCard_IconRightRect = {uiCard_SlotRightRect.x+(uiCard_SlotRightRect.w/2)-uiCard_IconSize.x/2,
                                 uiCard_SlotRightRect.y+(uiCard_SlotRightRect.h/2)-uiCard_IconSize.y/2,
                                uiCard_IconSize.x,
                                uiCard_IconSize.y};


    //for ease of use. Fix this later
    Vector<Rect> uiCard_IconVector;


    //card piles render size
    Point uiPile_Size = {96, 144};
    //clipper for uiPilesTexture
    Rect uiPile_Clip = {0, 0, 64, 96};

    Rect uiPile_DeckRect = {uiPile_Size.x, (SCREEN_HEIGHT - uiPile_Size.y) - uiPile_Size.y / 2, uiPile_Size.x, uiPile_Size.y};
    Rect uiPile_DiscardRect = {uiPile_Size.x * 10, (SCREEN_HEIGHT - uiPile_Size.y) - uiPile_Size.y, uiPile_Size.x, uiPile_Size.y};
    Rect uiPile_BurnRect = {uiPile_Size.x * 11 + uiPile_Size.x / 2, (SCREEN_HEIGHT - uiPile_Size.y) - uiPile_Size.y, uiPile_Size.x, uiPile_Size.y};


    //UI BARS
    Point uiBar_Size = {200, 20};
    Ui_Bar uiBar_DrawBar = {uiBar_Size, 8, 14};
    Ui_Bar uiBar_OverheatBar = {uiBar_Size, 8, 12};

    //UI DRAW READY ICON

    Rect uiIcon_DrawReadyClip = {0,0,16,16};
    Rect uiIcon_1DrawReadyRect = {uiBar_DrawBar._backgroundRect.x + uiBar_DrawBar._backgroundRect.w + 16, uiBar_DrawBar._backgroundRect.y, 16, 16};
    Rect uiIcon_2DrawReadyRect = {uiIcon_1DrawReadyRect.x + uiIcon_1DrawReadyRect.w, uiIcon_1DrawReadyRect.y, uiIcon_1DrawReadyRect.w, uiIcon_1DrawReadyRect.h};
    Rect uiIcon_3DrawReadyRect = {uiIcon_2DrawReadyRect.x + uiIcon_2DrawReadyRect.w, uiIcon_2DrawReadyRect.y, uiIcon_2DrawReadyRect.w, uiIcon_2DrawReadyRect.h};

    //UI NUMBERS
    Point uiNumbers_Size = {64,64};
    Rect uiNumbers_Clip = {0,0,32,32};

    Rect uiNumbers_DeckCounterRect = {uiPile_DeckRect.x+uiPile_DeckRect.w/2- uiNumbers_Size.x/2,
                                      uiPile_DeckRect.y+(uiPile_DeckRect.h/2)- uiNumbers_Size.y/8,
                                      uiNumbers_Size.x,
                                      uiNumbers_Size.y};
    Rect uiNumbers_DiscardCounterRect = {uiPile_DiscardRect.x+uiPile_DiscardRect.w/2- uiNumbers_Size.x/2,
                                         uiPile_DiscardRect.y+(uiPile_DiscardRect.h/2)- uiNumbers_Size.y/8,
                                         uiNumbers_Size.x,
                                         uiNumbers_Size.y};
    Rect uiNumbers_AshesCounterRect = {uiPile_BurnRect.x+uiPile_BurnRect.w/2- uiNumbers_Size.x/2,
                                       uiPile_BurnRect.y+(uiPile_BurnRect.h/2)- uiNumbers_Size.y/8,
                                       uiNumbers_Size.x,
                                       uiNumbers_Size.y};




    //collision table + carries ID and debuff status into things as well
    //will later hold a debuff vector for multiple types (if i ever get to that)
    std::vector< Hitbox > colliderVec;


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
    void activeCardsLogic(const Vector<Card *>& cardVector, u32 frame);
    void renderActiveCardsInVector(const Vector<Card *> &cardVector);

    //helper function for SDL_RenderCopyEx
    void renderFromSpritesheet(int targetX,
                               int targetY,
                               int targetW,
                               int targetH,
                               SDL_Texture* t,
                               const SDL_Rect* clip = nullptr,
                               double angle = 0.0,
                               SDL_Point* center = nullptr,
                               SDL_RendererFlip flip = SDL_FLIP_NONE,
                               bool useClipSize = false
                                       );

    void renderFromSpritesheet(Rect values,
                               SDL_Texture* t,
                               SDL_Rect* clip = nullptr,
                               double angle = 0.0,
                               SDL_Point* center = nullptr,
                               SDL_RendererFlip flip = SDL_FLIP_NONE,
                               bool useClipSize = false);

    //helper for SDL_CreateTextureFromSurface. Also applys a color key:(r:0, g:0xFF,b:0xFF) if transparent pixels are ever needed
    Texture* loadFromFile(const std::string& path);

    //these are a good indicator for things that should be classes
    void setUICardClipOffset(int offset)noexcept{ uiCard_Clip.x = uiCard_Clip.w * offset;}
    void setUIPileClipOffset(int offset)noexcept{ uiPile_Clip.x = uiPile_Clip.w * offset;}
    void setUIIconDrawReadyClipOffset(int offset)noexcept{uiIcon_DrawReadyClip.x = uiIcon_DrawReadyClip.w * offset;}
    void setUINumbersClipOffset(int offset)noexcept{uiNumbers_Clip.x = uiNumbers_Clip.w* offset;}

    //helper to pack all cooldowns into one easy to find place
    void manageCooldowns(u32 frame);
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


//------------ left the old states in for testing

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
