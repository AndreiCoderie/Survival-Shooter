#pragma once

#include "components/simple_scene.h"

#define RED		glm::vec3(1.f, 0.f, 0.f)
#define GREEN		glm::vec3(0, 1, 0)
#define CYAN		glm::vec3(0,1,1)




namespace m1
{
    class Circle {
    public:
        glm::vec3 color;
        float translateX;
        float translateY;
        float startX;
        float startY;
        float radius;


        Circle(glm::vec3 color, float startX, float startY, float radius) {
            this->color = color;
            this->startX = startX;
            this->startY = startY;
            this->radius = radius;
            translateX = 0;
            translateY = 0;

        }

        ~Circle() {}
    };


    class Map {
    public:
        float length;
        float xCenter = 0 ;
        float yCenter = 0;
        float translateX = 0;
        float translateY = 0;


        Map() {
        }

        Map(float length) {
            this->length = length;
            this->xCenter = 0;
            this->yCenter = 0;
        }

        ~Map() {}
    };

    class Obstacle {
    public:
        float length;
        float width;
        float xLower;
        float yLower;


        Obstacle(float length, float width, float xLower, float yLower) {
            this->length = length;
            this->width = width;
            this->xLower = xLower;
            this->yLower = yLower;
        }

        ~Obstacle() {}
    };


    class Projectile {
    public:
        float angle;
        float translateX;
        float translateY;
        float speed;
        float radius;
        bool checkAlive = false;
        float scale = 1;


        Projectile(float angle,float transX, float transY) {
            this->angle = angle;
            this->translateX = transX;
            this->translateY = transY;
           // this->lastTranslate = lastTranslate;
            this->speed = 1;
            this->radius = 7;
        }

        ~Projectile() {}
    };

    class Enemy {
    public:
        float bottomX;
        float bottomY;
        float speed;
        float length;
        float isDead = false;
        float eyeLength;
        float enemyAngle;
        float translateToObjX;
        float translateToObjY;

        Enemy(float bottomX,float bottomY,  float enemyAngle) {
            this->bottomX = bottomX;
            this->bottomY = bottomY;
            this->length = 50;
            this->eyeLength = 10;
            this->speed = (int) rand() % 100 + 20;
            this->enemyAngle = enemyAngle;
            this->translateToObjX = 0;
            this->translateToObjY = 0;

        }

        ~Enemy() {}
    };




    class tema : public gfxc::SimpleScene
    {
     public:
         tema();
        ~tema();


        void updateTranslatesX(float translateX);

        void updateTranslatesY(float translateY);

        void Init() override;

     private:
        void FrameStart() override;
        void drawEnemies(Enemy enemy);
        void drawMap();
        void drawProjectiles(float angle);
        void generateObstacles();
        void drawObstacles();
        void createEnemies(int number, float seconds);
        void drawCircles();
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void computeCharacterAngle();

        void computeProjectileAngle();

        void computerEnemyAngle(Enemy enemy);

        void checkProjectileEnemyCollision();

        void shootPrjectile(float seconds);

        void checkProjectileMapCollision(float deltaSec);

        void checkProjectileObstacleCollision(float deltaTimeSeconds);

        void checkCharEnemyCollision(float x, float y, float radius, Enemy& obstacle);

        void checkCharEnemiesCollisions();


        void checkCharacterObstacleCollisionDown();
        void checkCharacterProjEnemy();
        void generateLifeBar();
        void enemiesMovement(float seconds);
        void checkCollisionCharObj(float x, float y, float radius, Obstacle& obstacle);
        void checkCollisionProjEnemy(Projectile& projectile, Enemy& obstacle);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
  
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float translateProjectileX, translateProjectileY;
        float scaleX, scaleY;
        float time;
        float projectileAngle;





        // TODO(student): If you need any other class variables, define them here.

        float characterAngle;

        std::vector<Circle> circles;
        std::vector<Obstacle> obstacles;
        std::vector<Projectile> projectiles;
        std::vector<Enemy> enemies;
        Map map;


    };
}   // namespace m1
