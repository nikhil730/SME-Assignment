#pragma once
#include <SFML/Graphics.hpp>
#include "../Collision/ICollider.h"
#include "../../header/Powerup/PowerupConfig.h"
#include "../../header/Player/PlayerModel.h"
#include "../../header/Player/PlayerView.h"

namespace Player
{
    class PlayerView;
    class PlayerController : public Collision::ICollider
    {
    private:
        EventService* event_service;
        float elapsed_shield_duration;
        float elapsed_rapid_fire_duration;
        float elapsed_tripple_laser_duration;

        float elapsed_fire_duration;
        float elapsed_freez_duration;

        PlayerView* player_view;
        PlayerModel* player_model;

        void processPlayerInput();
        void moveLeft();
        void moveRight();

        bool processPowerupCollision(ICollider* other_collider);
        bool processEnemyCollision(ICollider* other_collider);
        void updateFreezDuration();
        void freezPlayer();
        void updatePowerupDuration();
       
        void disableShield();   
        void disableRapidFire();    
        void disableTrippleLaser();
        void fireSimpleBullet();
        void saveHighScore();

        void processBulletFire();
        void renderBullet(const SimpleBullet::Bullet& bullet) {
            // Implement the rendering logic here
        }

    public:
        PlayerController();
        ~PlayerController();

        void initialize();
        void update();
        void render();

        PlayerController(EventService* eventService);

        void reset();

        void decreasePlayerLive();
        inline void increaseScore(int val) { PlayerModel::player_score += val; }
        inline void decreaseScore(int val) { PlayerModel::player_score -= val; }
        inline void increaseEnemiesKilled(int val) { PlayerModel::enemies_killed += val; }
        inline void increaseBulletsFired(int val) { PlayerModel::bullets_fired += val; }
        
        void enableShield();
        void enableRapidFire();
        void enableTrippleLaser();
        void fireSimpleBullet();
        void simpleBullet();
        sf::Vector2f getPlayerPosition();
        PlayerState getPlayerState();

        const sf::Sprite& getColliderSprite() override;
        void onCollision(ICollider* other_collider) override;
    };
}
namespace SimpleBullet {
    // Define the SimpleBullet class or struct
    struct Bullet {
        sf::Vector2f position;
        float speed;
        bool isActive; // Flag to indicate if the bullet is active

        // Constructor
        Bullet(sf::Vector2f startPos, float bulletSpeed)
            : position(startPos), speed(bulletSpeed), isActive(true) {}

        // Update method to move the bullet
        void update(float deltaTime) {
            // Move the bullet vertically down
            position.y += speed * deltaTime;
        }

        // Method to check if the bullet is outside the screen boundaries
        bool isOutsideScreen(float screenHeight) const {
            return position.y > screenHeight;
        }
    };
}
