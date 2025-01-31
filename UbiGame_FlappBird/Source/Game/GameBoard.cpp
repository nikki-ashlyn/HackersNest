#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/Util/CameraManager.h"
#include "Game/GameEntities/PlayerEntity.h"
#include "Game/GameEntities/ObstacleEntity.h"
#include "Game/GameEntities/CollectibleEntity.h"
#include "Game/GameEntities/HealthBar.h"



using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_backGround(nullptr)
	, m_lastObstacleSpawnTimer(0.f)
	, m_isGameOver(false)
{
	m_player = new PlayerEntity();
	
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(100.f, 50.f));	
	m_player->SetSize(sf::Vector2f(100.f, 150.f));
	
	CreateBackGround();
	//Debug
	for (int a = 0; a < 3; ++a)
	{
		//SpawnNewRandomObstacles();
	}
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{	
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		if (m_lastObstacleSpawnTimer <= 0.f)
		{
			SpawnNewRandomObstacles();
		}

		//CreateHealthBar();
		UpdateObstacles(dt);
		UpdateBackGround();
		UpdatePlayerDying();
	}		
}


void GameBoard::UpdateObstacles(float dt)
{
	static float obstacleSpeed = 100.f;
	
	for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
	{
		GameEngine::Entity* obstacle = (*it);
		sf::Vector2f currPos = obstacle->GetPos();
		currPos.x -= obstacleSpeed * dt;
		obstacle->SetPos(currPos);
		//If we are to remove ourselves
		if (currPos.x < -50.f)
		{
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
			it = m_obstacles.erase(it);
		}
		else
		{
			it++;
		}
	}
}


void GameBoard::UpdatePlayerDying()
{	
	bool noGameOver = GameEngine::CameraManager::IsFollowCameraEnabled();

	if (noGameOver)
		return;
	float time = GameEngine::GameEngineMain::GetGameTime();
	static float xToPlayerDie = 0.f;
	if (time > 30)
	{
		CreateGameOver();
		m_isGameOver = true;
	}
}


void GameBoard::SpawnNewRandomObstacles()
{
	//float time = GameEngine::GameEngineMain::GetGameTime();

	static float minNextSpawnTime = 3.5f;
	static float maxNextSpawnTime = 3.5f;

	static float minObstacleXPos = 800.f;
	static float maxObstacleXPos = 800.f;
	static float minObstacleYPos = 50.f;
	static float maxObstacleYPos = 450.f;
	
	static float minObstacleHeight = 150.f;
	static float maxObstacleHeight = 170.f;
	static float minObstacleWidth = 30.f;
	static float maxObstacleWidth = 40.f;

	static float minCollectibleYPos = 50.f;
	static float maxCollectibleYPos = 450.f;

	
	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(RandomFloatRange(minObstacleWidth, maxObstacleWidth), RandomFloatRange(minObstacleHeight, maxObstacleHeight));

	sf::Vector2f collectPos = sf::Vector2f(1000, RandomFloatRange(minCollectibleYPos, maxCollectibleYPos));
	SpawnNewObstacle(pos, size);
	SpawnNewCollectible(collectPos, size);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}

void GameBoard::SpawnNewRandomTiledObstacles()
{
	static int minObstacleCount = 2;
	static int maxObstacleCount = 7;

	static float minNextSpawnTime = 0.5f;
	static float maxNextSpawnTime = 0.5f;

	static float minObstacleXPos = 350.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 200.f;
	static float maxObstacleYPos = 500.f;


	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));	
	sf::Vector2f size = sf::Vector2f(75.f, 75.f);

	int obstacleCount = (int)RandomFloatRange((float)minObstacleCount, (float)maxObstacleCount);
	for (int a = 0; a < obstacleCount; ++a)
	{
		SpawnNewObstacle(pos, size);
		pos.y += size.y;
	}

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	ObstacleEntity* obstacle = new ObstacleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(75.f, 75.f));
	
	m_obstacles.push_back(obstacle);
}

void GameBoard::SpawnNewCollectible(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	CollectibleEntity* obstacle = new CollectibleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(100.f, 100.f));

	m_obstacles.push_back(obstacle);
}

void GameBoard::CreateHealthBar()
{
	sf::Vector2f barPosition = sf::Vector2f(30.f, 30.f);
	HealthBar* obstacle = new HealthBar();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(barPosition);
	obstacle->SetSize(sf::Vector2f(350, 30));

	m_obstacles.push_back(obstacle);
}


void GameBoard::CreateBackGround()
{
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = bgEntity->AddComponent<GameEngine::SpriteRenderComponent>();
	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(0);
	bgEntity->SetPos(sf::Vector2f(250.f, 325.f));
	bgEntity->SetSize(sf::Vector2f(500.f, 650.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
}

void GameBoard::CreateGameOver()
{
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = bgEntity->AddComponent<GameEngine::SpriteRenderComponent>();
	render->SetTexture(GameEngine::eTexture::GameOver);
	render->SetZLevel(5);
	bgEntity->SetPos(sf::Vector2f(250.f, 325.f));
	bgEntity->SetSize(sf::Vector2f(500.f, 650.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
}


void GameBoard::UpdateBackGround()
{
	if (!m_backGround || !m_player)
		return;

	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	m_backGround->SetPos(m_player->GetPos());
}