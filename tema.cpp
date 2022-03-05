#include "lab_m1/tema/tema.h"

#include <vector>
#include <iostream>
#include <cmath>

#include "components/simple_scene.h"

#include "lab_m1/tema/transform2D.h"
#include "lab_m1/tema/object2D.h"
#include "lab_m1/tema/tema_vis2D.h"


using namespace std;
using namespace m1;
float xleftSquare;
float xrightSquare;
float yUpSquare;
float yDownSquare;


float resX;
float resY;

float smallCircle1CenterX;
float smallCircle1CenterY;

float smallCircle2CenterX;
float smallCircle2CenterY;

float bigCircleCenterX;
float bigCircleCenterY;

float bigCircleRadius;
float smallCirclesRadius;


float translateEnemyX;
float translateEnemyY;
float counterTimerEnemies;
float enemyAngle;

int liveCheck;
bool liveCounter;
float lengthLifeX;
float translateLifeY;
float scaleX;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */
float centerX;
float centerY;
float oldX;
float oldY;
float projectileCircleRadius;

bool checkerRight;
bool checkerLeft;
bool checkerUp;
bool checkerDown;
float score;
float cameraX;
float cameraY;
tema::tema()
{
}


tema::~tema()
{
}


void tema::Init()
{
    cameraX = 0;
    cameraY = 0;
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    characterAngle = 0;

    smallCirclesRadius = 15;
    projectileCircleRadius = 7;
    bigCircleRadius = 100;
    resX = 0;
    enemyAngle = 0;
    scaleX = 1;
    score = 0;

    liveCheck = 5;
    liveCounter = false;

    oldX = resolution.x ;
    oldY = resolution.y ;
    smallCircle1CenterX = resolution.x / 2 + 70;
    smallCircle1CenterY = resolution.y / 2 + 65;
    smallCircle2CenterX = resolution.x / 2  + 70;
    smallCircle2CenterY = resolution.y / 2 - 65;
    bigCircleCenterX = centerX = resolution.x / 2 ;
    bigCircleCenterY = centerY =  resolution.y / 2;
    counterTimerEnemies = 20;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;
    translateProjectileX = 0;
    translateProjectileY = 0;
    translateEnemyX = 0;
    translateEnemyY = 0;
    lengthLifeX = 100;
    translateLifeY = 0;

    //timpul care trb sa astepte pentru a trage
    time = 0.5;


    projectileAngle = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    checkerRight = false;
    checkerLeft = false;
    checkerUp = false;
    checkerDown = false;

    glLineWidth(10);
    Mesh* square1 = object2D::CreateSquare("square1", glm::vec3(0,0, 0), 600, glm::vec3(1, 1, 1), false);
    AddMeshToList(square1);
    map.length = 600;


    //Mesh* square2 = object2D::CreateSquare("square2", glm::vec3(resolution.x / 2 + 300, resolution.y / 2 + 300, 0), 100, glm::vec3(1, 0, 1), false);
    //AddMeshToList(square2);


    Mesh* obstacle1 = object2D::CreateDrept("obstacle1", glm::vec3(resolution.x / 2 + 150, resolution.y / 2 + 100, -1), 150, 50, glm::vec3(1, 0, 1), true);
    AddMeshToList(obstacle1);
    obstacles.push_back(Obstacle(150, 50, resolution.x / 2 + 150, resolution.y / 2 + 100));


    Mesh* obstacle2 = object2D::CreateDrept("obstacle2", glm::vec3(resolution.x / 2, resolution.y / 2 - 200, -1), 50, 50, glm::vec3(1, 0, 1), true);
    AddMeshToList(obstacle2);
    obstacles.push_back(Obstacle(50, 50, resolution.x / 2 , resolution.y / 2 - 200));


    Mesh* obstacle3 = object2D::CreateDrept("obstacle3", glm::vec3(resolution.x / 2 - 300, resolution.y / 2 + 190, -1), 210, 110, glm::vec3(1, 0, 1), true);
    AddMeshToList(obstacle3);
    obstacles.push_back(Obstacle(210 ,110, resolution.x / 2 - 300 , resolution.y / 2 + 190 ));


    //generateObstacles();


    //for (int i = 0; i < obstacles.size(); i++) {
    //    Mesh* obstacle = object2D::CreateDrept("obstacle", glm::vec3(resolution.x / 2, resolution.y / 2, 0), obstacles[i].length ,obstacles[i].width, glm::vec3(1, 1, 0), true);
    //    AddMeshToList(obstacle);
    //}  



    Mesh* bigCircle = object2D::CreateCircle("bigCircle", bigCircleRadius, CYAN, CYAN);
    AddMeshToList(bigCircle);

    Mesh* bigCircleBlack = object2D::CreateCircle("bigCircleBlack", bigCircleRadius + 5, glm::vec3(0.5, 0.5, 0.5), glm::vec3(1, 1, 1));
    AddMeshToList(bigCircleBlack);

    Mesh* smallCircle1 = object2D::CreateCircle("smallCircle1", smallCirclesRadius, CYAN, CYAN);
    AddMeshToList(smallCircle1);

    Mesh* smallCircle1Black = object2D::CreateCircle("smallCircle1Black", smallCirclesRadius + 5, glm::vec3(0.5,0.5,0.5), glm::vec3(1, 1, 1));
    AddMeshToList(smallCircle1Black);

    Mesh* smallCircle2 = object2D::CreateCircle("smallCircle2", smallCirclesRadius, CYAN, CYAN);
    AddMeshToList(smallCircle2);

    
    //mesh pentru proiectile
    Mesh* projectile = object2D::CreateCircle("projectile", projectileCircleRadius, CYAN, CYAN);
    AddMeshToList(projectile);

    //mesh pentru inamici




    Mesh* bodyEnemy = object2D::CreateSquare("bodyEnemy", glm::vec3(0, 0, 1 ), 50, RED, true);
    AddMeshToList(bodyEnemy);

   /* Mesh* bodyEnemyBlack = object2D::CreateSquare("bodyEnemyBlack", glm::vec3(0, 0, 0), 52, glm::vec3(0,1,0), false);
    AddMeshToList(bodyEnemyBlack);*/

    Mesh* eyeEnemy = object2D::CreateSquare("eyeEnemy", glm::vec3(0, 0, 1), 10, GREEN, true);
    AddMeshToList(eyeEnemy);
 /*   Mesh* eyeEnemyBlack = object2D::CreateSquare("eyeEnemyBlack", glm::vec3(0, 0, 0), 17, glm::vec3(0,1,0), false);
    AddMeshToList(eyeEnemyBlack);*/


    Mesh* liveSquareFillFalse = object2D::CreateDrept("liveSquareFillFalse", glm::vec3(0,0, -1), lengthLifeX, 20, RED, false);
    AddMeshToList(liveSquareFillFalse);

    Mesh* liveSquareFillTrue = object2D::CreateDrept("liveSquareFillTrue", glm::vec3(0, 0, -1), lengthLifeX, 20, RED, true);
    AddMeshToList(liveSquareFillTrue);
        

}


void tema::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}




//--------------------




void tema::drawMap() {
    //creearea hartii
    glm::ivec2 resolution = window->GetResolution();

    //glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);


    modelMatrix = glm::mat3(1);
    //if (resX == oldX && resY == oldY) {
        modelMatrix = transform2D::Translate(resX / 2 - 300, resY / 2 - 300);
        modelMatrix *= transform2D::Translate(map.translateX, map.translateY);
        //xleftSquare = resX / 2 - 600;
        //xrightSquare = resX / 2;
        //yUpSquare = resY / 2;
        //yDownSquare = resY / 2 - 600;
        map.xCenter = resolution.x / 2;
        map.yCenter = resolution.y / 2;
        bigCircleCenterX = map.xCenter;
        bigCircleCenterY = map.yCenter;
   // }

    //else {
    //    modelMatrix = transform2D::Translate(resolution.x / / 2 - oldX / 4 - 300, resY / 2 - oldY / 4 - 275);
    //    modelMatrix *= transform2D::Translate(map.translateX, map.translateY);
    //}


    /* *transform2D::Scale(m_viewport[2], m_viewport[2]);*/
    glLineWidth(10);

    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    //modelMatrix = glm::mat3(1);
  //  RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);



}

void tema::drawProjectiles(float projAngle) {
    glm::ivec2 resolution = window->GetResolution();


    Projectile a(projAngle, translateProjectileX, translateProjectileY);;
    projectiles.push_back(a);

}



void tema::drawObstacles() {

    glm::ivec2 resolution = window->GetResolution();


        //modelMatrix = transform2D::Translate(obstacles[i].length   , obstacles[i].width);
        //modelMatrix *= transform2D::Scale(-0.75f  , -1.0f);
        modelMatrix = glm::mat3(1);
        //if (obstacles[0].xLower < map.xCenter - map.length / 2 + map.translateX)
        //    modelMatrix *= transform2D::Scale(0.5, 1);
        RenderMesh2D(meshes["obstacle1"], shaders["VertexColor"], modelMatrix);   
      
        modelMatrix = glm::mat3(1);
        //if (obstacles[1].xLower > map.xCenter - map.length / 2 + map.translateX)
        //    modelMatrix *= transform2D::Scale(0.5, 1);

        RenderMesh2D(meshes["obstacle2"], shaders["VertexColor"], modelMatrix);   
        
        modelMatrix = glm::mat3(1);
        //modelMatrix *= transform2D::Translate(resolution.x / 2 - 300, resolution.y / 2 + 190);
        //if (obstacles[2].xLower < map.xCenter - map.length / 2 + map.translateX)
        //    modelMatrix *= transform2D::Scale(translateX / 100, 1);
        RenderMesh2D(meshes["obstacle3"], shaders["VertexColor"], modelMatrix);
}


void tema::createEnemies(int numberOfEnemies, float deltaTimeSeconds) {

    for (int i = 0; i < numberOfEnemies; i++) {
        translateEnemyX = rand() % (int)(resX ) + 1;
        translateEnemyY = rand() % (int)(resX ) + 1;

        Enemy enemy(translateEnemyX, translateEnemyY, 0);
        enemies.push_back(enemy);

    }

}




void tema::drawCircles() {

    glm::ivec2 resolution = window->GetResolution();


    //creearea caracterului
    modelMatrix = glm::mat3(1);

  //  if(resX == oldX && resY == oldY)
        modelMatrix = transform2D::Translate(smallCircle1CenterX + translateX, smallCircle1CenterY + translateY);
    //else 
    //    modelMatrix = transform2D::Translate(resX / 2 - oldX / 4 + translateX + 70, resY / 2 - oldY / 4 + translateY + 65);


    modelMatrix *= transform2D::Translate(-70, -65) *
                                            transform2D::Rotate(characterAngle) * transform2D::Translate(70, 65);

    RenderMesh2D(meshes["smallCircle1"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["smallCircle1Black"], shaders["VertexColor"], modelMatrix);

 



    modelMatrix = glm::mat3(1);

    //if(resX == oldX && resY == oldY)
        modelMatrix = transform2D::Translate(smallCircle2CenterX + translateX, smallCircle2CenterY + translateY);
    //else
    //    modelMatrix = transform2D::Translate(resX / 2 - oldX / 4 + translateX + 70, resY / 2 - oldY / 4 + translateY - 65);


    modelMatrix *= transform2D::Translate(-70, +65) *
        transform2D::Rotate(characterAngle) * transform2D::Translate(70, -65);

    RenderMesh2D(meshes["smallCircle2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["smallCircle1Black"], shaders["VertexColor"], modelMatrix);



    modelMatrix = glm::mat3(1);

  //  if (resX == oldX && resY == oldY){
        modelMatrix = transform2D::Translate(bigCircleCenterX + translateX, bigCircleCenterY + translateY);
        centerX += translateX;
        centerY += translateY;
   // }
    //else {
    //    modelMatrix = transform2D::Translate(resX / 2 - oldX / 4 + translateX, resY / 2 - oldY / 4 + translateY);
    //    centerX = centerX - oldX / 4 + translateX;
    //    centerY = centerY - oldY / 4 + translateY;
    //}

    centerX += translateX;
    centerY += translateY;


    modelMatrix *= transform2D::Rotate(characterAngle) ;

    RenderMesh2D(meshes["bigCircle"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["bigCircleBlack"], shaders["VertexColor"], modelMatrix);


 



}
void tema::computeCharacterAngle() {
    glm::ivec2 resolution = window->GetResolution();
    glm::ivec2 cursorPos = window->GetCursorPosition();
    float mouseX = cursorPos.x;
    float mouseY = resolution.y - cursorPos.y;

    characterAngle = atan2f(mouseY - resolution.y / 2  , mouseX - resolution.x / 2);
}

void tema::computeProjectileAngle() {
    glm::ivec2 resolution = window->GetResolution();
    glm::ivec2 cursorPos = window->GetCursorPosition();
    float mouseX = cursorPos.x;
    float mouseY = resolution.y - cursorPos.y;

    projectileAngle = atan2f(mouseY - resolution.y / 2, mouseX - resolution.x / 2 );
}


void tema::computerEnemyAngle(Enemy enemy) {
    glm::ivec2 resolution = window->GetResolution();

    glm::ivec2 cursorPos = window->GetCursorPosition();
    float circleX = bigCircleCenterX + translateX;
    float circleY = bigCircleCenterY + translateY;

    enemyAngle = atan2f(circleY - (enemy.bottomY + enemy.length /2 + enemy.translateToObjY), circleX - (enemy.bottomX + enemy.length / 2 + enemy.translateToObjX));

}

//coliziune proiectile

//BAD
//void tema::checkProjectileEnemyCollision() {
//        for (int i = 0; i < projectiles.size(); i++) {
//
//            for (int j = 0; j < enemies.size(); j++) {
//                float projX = bigCircleCenterX + translateX + projectiles[i].translateX ;
//                float projY = bigCircleCenterY + translateY + projectiles[i].translateY ;
//
//                float enemX = enemies[j].bottomX + enemies[j].translateToObjX;
//                float enemY = enemies[j].bottomY +  enemies[j].translateToObjY ;
//
//                float distance = sqrt((projX - enemX) * (projX - enemX) + (projY - enemY) * (projY - enemY));
//                if (enemies[j].length  / 2>= distance && !enemies[j].isDead) {
//                    enemies[j].isDead = true;
//                    projectiles[i].checkAlive = true;
//
//                }
//        }
//    }
//
//}

void tema::shootPrjectile(float deltaTimeSeconds) {
    for (int i = 0; i < projectiles.size(); i++) {
        projectiles[i].translateX += cos(projectiles[i].angle) * deltaTimeSeconds * 600;
        projectiles[i].translateY += sin(projectiles[i].angle) * deltaTimeSeconds * 600;

        modelMatrix = glm::mat3(1);
        modelMatrix = transform2D::Translate(bigCircleCenterX, bigCircleCenterY);
        modelMatrix *= transform2D::Translate(projectiles[i].translateX, projectiles[i].translateY);


        RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
    }
}

void tema::checkProjectileMapCollision(float deltaTimeSeconds) {

    for (int i = 0; i < projectiles.size(); i++) {
        if (bigCircleCenterX + projectiles[i].translateX < resX / 2 - 290 + map.translateX|| bigCircleCenterY + projectiles[i].translateY < resY / 2 - 290 + map.translateY ||
            bigCircleCenterX + projectiles[i].translateX > resX / 2 + 290 + map.translateX || bigCircleCenterY + projectiles[i].translateY  > resY / 2 + 290 + map.translateY) {
            projectiles[i].checkAlive = true;
        }
    }
}

void tema::checkProjectileObstacleCollision(float deltaTimeSeconds) {
    for (int i = 0; i < projectiles.size(); i++) {
        for (int j = 0; j < obstacles.size(); j++) {
            if (bigCircleCenterX + projectiles[i].translateX > obstacles[j].xLower && bigCircleCenterX + projectiles[i].translateX < obstacles[j].xLower + obstacles[j].length
                && bigCircleCenterY + projectiles[i].translateY > obstacles[j].yLower && bigCircleCenterY + projectiles[i].translateY < obstacles[j].yLower + obstacles[j].width) {
                projectiles[i].checkAlive = true;
            }
        }
    }
}

void tema::checkCharEnemyCollision(float centerCircleX, float centerCircleY, float radiusCircle, Enemy& enemy) // AABB - Circle collision
{
   ////  get center point circle first 
    glm::vec2 center(
        centerCircleX + translateX,
        centerCircleY + translateY);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(enemy.length , enemy.length );
    glm::vec2 aabb_center(
        enemy.bottomX + enemy.translateToObjX,
        enemy.bottomY + enemy.translateToObjY 
    );
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, glm::vec2(0, 0), aabb_half_extents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    if (glm::length(difference) < radiusCircle) {
        enemy.isDead = true;
        liveCheck--;
        liveCounter = true;
        scaleX -= 0.2;
    }

    //float dx = (centerCircleX + translateX+ radiusCircle) - (enemy.bottomX + enemy.translateToObjX +  enemy.length/2 );
    //float dy = (centerCircleY + translateY + radiusCircle) - (enemy.bottomY + enemy.translateToObjY + enemy.length /2) ;
    //float distance = sqrt(dx * dx + dy * dy);
    //if (distance < radiusCircle + enemy.length) {
    //    // collision detected!
    //    enemy.isDead = true;;
    //}

 
}

void tema::checkCharEnemiesCollisions() {
    for (int i = 0; i < enemies.size(); i++) {
        checkCharEnemyCollision(bigCircleCenterX, bigCircleCenterY, bigCircleRadius, enemies[i]);
    }

}




//credite link-ul coliziuni din tema
void tema::checkCollisionCharObj(float centerCircleX, float centerCircleY, float radiusCircle , Obstacle& obstacle) // AABB - Circle collision
{
    glm::vec2 center(
        centerCircleX + translateX,
        centerCircleY + translateY);
    glm::vec2 aabb_half_extents(obstacle.length , obstacle.width);
    glm::vec2 aabb_center(
        obstacle.xLower,
        obstacle.yLower 
    );
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, glm::vec2(0,0), aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;
    if ((closest.y > center.y) && glm::length(difference) < radiusCircle)
        checkerUp = true;
    if ((closest.y < center.y) && glm::length(difference) < radiusCircle) 
        checkerDown = true;
    if ((closest.x > center.x) && glm::length(difference) < radiusCircle) 
        checkerRight = true;
    if ((closest.x < center.x) && glm::length(difference) < radiusCircle)
        checkerLeft = true;
}

//credite link-ul coliziuni din tema

void tema::checkCollisionProjEnemy(Projectile& projectile, Enemy& enemy) // AABB - Circle collision
{
    glm::vec2 centerProj(
        bigCircleCenterX + projectile.translateX,
        bigCircleCenterY + projectile.translateY);
    glm::vec2 aabb_half_extents(enemy.length, enemy.length);
    glm::vec2 aabb_center(
        enemy.bottomX + enemy.translateToObjX,
        enemy.bottomY + enemy.translateToObjY
    );
    glm::vec2 difference = centerProj - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, glm::vec2(0, 0), aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - centerProj;
    if (glm::length(difference) < projectile.radius) {
        projectile.checkAlive = true;
        enemy.isDead = true;
    }
}




void tema::checkCharacterObstacleCollisionDown() {
    for (int i = 0; i < obstacles.size(); i++){
        checkCollisionCharObj(bigCircleCenterX, bigCircleCenterY, 100, obstacles[i]);
    }
}

void tema::checkCharacterProjEnemy() {
    for (int j = 0; j < projectiles.size(); j++) {
        for (int i = 0; i < enemies.size(); i++) {
            checkCollisionProjEnemy(projectiles[j], enemies[i]);
            }

                
        }
    }

void tema::generateLifeBar() {
    if (scaleX > 0) {
        modelMatrix = glm::mat3(1);
        glLineWidth(1);
        glm::ivec2 resolution = window->GetResolution();

        modelMatrix *= transform2D::Translate(resolution.x - 110 + translateX, resolution.y - 30 +translateY);
        modelMatrix *= transform2D::Scale(scaleX, 1);
    }
      RenderMesh2D(meshes["liveSquareFillTrue"], shaders["VertexColor"], modelMatrix);

}
 
void tema::enemiesMovement(float deltaTimeSeconds) {
    for (int i = 0; i < enemies.size(); i++) {
        computerEnemyAngle(enemies[i]);
        enemies[i].enemyAngle = enemyAngle;

        enemies[i].translateToObjX += cos(enemies[i].enemyAngle) * deltaTimeSeconds * enemies[i].speed;
        enemies[i].translateToObjY += sin(enemies[i].enemyAngle) * deltaTimeSeconds * enemies[i].speed;

        modelMatrix = glm::mat3(1);
        modelMatrix = transform2D::Translate(enemies[i].bottomX + 4 * enemies[i].eyeLength, enemies[i].bottomY + enemies[i].eyeLength);

        modelMatrix *= transform2D::Translate(enemies[i].translateToObjX, enemies[i].translateToObjY);

        modelMatrix *= transform2D::Translate(enemies[i].length / 2 - 4 * enemies[i].eyeLength, enemies[i].length / 2 - enemies[i].eyeLength);
        modelMatrix *= transform2D::Rotate(enemies[i].enemyAngle);
        modelMatrix *= transform2D::Translate(-enemies[i].length / 2 + 4 * enemies[i].eyeLength, -enemies[i].length / 2 + enemies[i].eyeLength);

        //translatie ochi catre caracter
        RenderMesh2D(meshes["eyeEnemy"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemies[i].bottomX + 4 * enemies[i].eyeLength, enemies[i].bottomY + 30);

        modelMatrix *= transform2D::Translate(enemies[i].translateToObjX, enemies[i].translateToObjY);


        modelMatrix *= transform2D::Translate(enemies[i].length / 2 - 4 * enemies[i].eyeLength, enemies[i].length / 2 - 3 * enemies[i].eyeLength);
        modelMatrix *= transform2D::Rotate(enemies[i].enemyAngle);
        modelMatrix *= transform2D::Translate(-enemies[i].length / 2 + 4 * enemies[i].eyeLength, -enemies[i].length / 2 + 3 * enemies[i].eyeLength);


        RenderMesh2D(meshes["eyeEnemy"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemies[i].bottomX, enemies[i].bottomY);

        modelMatrix *= transform2D::Translate(enemies[i].translateToObjX, enemies[i].translateToObjY);


        modelMatrix *= transform2D::Translate(25, 25);
        modelMatrix *= transform2D::Rotate(enemies[i].enemyAngle);
        modelMatrix *= transform2D::Translate(-25, -25);




        RenderMesh2D(meshes["bodyEnemy"], shaders["VertexColor"], modelMatrix);

        checkCharEnemyCollision(bigCircleCenterX, bigCircleCenterY, bigCircleRadius, enemies[i]);
        generateLifeBar();


    }
}


void tema::Update(float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();
    checkerUp = false;
    checkerDown = false;
    checkerLeft = false;
    checkerRight = false;

    resX = resolution.x;
    resY = resolution.y;


    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(cameraX, cameraY, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();

    if (liveCheck > 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(resolution.x - 110, resolution.y - 30);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        glLineWidth(1);
        RenderMesh2D(meshes["liveSquareFillFalse"], shaders["VertexColor"], modelMatrix);

        drawCircles();
        drawMap();
        drawObstacles();
        shootPrjectile(deltaTimeSeconds);

        if (counterTimerEnemies >= 5) {
            createEnemies(5, deltaTimeSeconds);
            counterTimerEnemies = 0;
            cout << "SCOR : " << score << "\n";

        }

        enemiesMovement(deltaTimeSeconds);

        checkProjectileMapCollision(deltaTimeSeconds);
        checkCharacterProjEnemy();
        checkProjectileObstacleCollision(deltaTimeSeconds);
        checkCharacterObstacleCollisionDown();


        //delete projectiles with alive 0
        for (int i = 0; i < projectiles.size(); i++) {
            if (projectiles[i].checkAlive == true) {
                projectiles.erase(projectiles.begin() + i);
                i--;

            }
        }

        //delete enemies with alive 0
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].isDead == true) {
                enemies.erase(enemies.begin() + i);
                i--;
                //se castiga 0.5 puncte pe fiecare inamic omorat
                score += 0.5;
            }
        }

    }
    else {
    glClearColor(0.2f, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    obstacles.clear();
    enemies.clear();
    projectiles.clear();

    }

    time += deltaTimeSeconds;
    counterTimerEnemies += deltaTimeSeconds;

}


void tema::FrameEnd()
{
}

void tema::OnInputUpdate(float deltaTime, int mods)
{
    glm::ivec2 resolution = window->GetResolution();


    if (window->KeyHold(GLFW_KEY_W))
        if (checkerUp == false && map.translateY + map.yCenter < resolution.y) {
            //if (CheckCollision(bigCircleCenterX + translateX, bigCircleCenterY + translateY, 100, obstacles[0]) == false) 
                translateY += deltaTime * 100;
                translateProjectileY += deltaTime * 100;
                map.translateY += deltaTime * 100;
                cameraY += deltaTime * 100;      
        }
    
    if (window->KeyHold(GLFW_KEY_S) && map.yCenter + map.translateY  > 0)
        if ( checkerDown == false ) {
             translateY -= deltaTime * 100;
             translateProjectileY -= deltaTime * 100;
             map.translateY -= deltaTime * 100;
             cameraY -= deltaTime * 100;
         }
    

    if (window->KeyHold(GLFW_KEY_D)) 
        if (checkerRight == false && map.translateX + map.xCenter < resolution.x) {
            translateX += deltaTime * 100;
            translateProjectileX += deltaTime * 100;
            map.translateX += deltaTime * 100;
            cameraX += deltaTime * 100;
        }
    
     if (window->KeyHold(GLFW_KEY_A )) 
         if (checkerLeft == false && map.translateX + map.xCenter > 0) {
             translateX -= deltaTime * 100;
            translateProjectileX -= deltaTime * 100;
            map.translateX -= deltaTime * 100;
            cameraX -= deltaTime * 100;
         }

    computeCharacterAngle();

}


void tema::OnKeyPress(int key, int mods)
{
   // Add key press event


}


void tema::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void tema::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (time > 0.5) {
            computeProjectileAngle();
            drawProjectiles(projectileAngle);
            time = 0;
        }
       

    }

}

       
   
void tema::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

}


void tema::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema::OnWindowResize(int width, int height)
{
    glm::ivec2 resolution = window->GetResolution();
    bigCircleCenterX = resolution.x / 2;
    bigCircleCenterY = resolution.y / 2;
    smallCircle1CenterX = resolution.x / 2 + 70;
    smallCircle1CenterY = resolution.y / 2 + 65;
    smallCircle2CenterX = resolution.x / 2 + 70;
    smallCircle2CenterY = resolution.y / 2 - 65;
    map.xCenter = bigCircleCenterX - map.translateX;
    map.yCenter = bigCircleCenterY - map.translateY;
}
