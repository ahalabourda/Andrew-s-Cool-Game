#include "Enemy.h"
#include "SoundManager.h"

Texture2D Enemy::mSprite;

void Enemy::InitializeSprite() {
	mSprite = LoadTexture("art/asteroid.png");
}

void Enemy::Tick(const Vector2 & pTarget)
{
	
	float deltaX = pTarget.x - mPosition.x;
	float deltaY = pTarget.y - mPosition.y;

	float distance = sqrtf((deltaX) * (deltaX) + (deltaY) * (deltaY));

	// we are more than 1 tick of movement away from the target. move normally
	if (distance > msSpeed) {

		float ratio = msSpeed / distance;

		mPosition.x += ratio * deltaX;
		mPosition.y += ratio * deltaY;

	}
	else {
		// we are less than 1 tick of movement away from the target! just teleport there
		mPosition.x = pTarget.x;
		mPosition.y = pTarget.y;
	}

	mRect.x = mPosition.x - mSprite.width * mTextureScale / 2.0f;
	mRect.y = mPosition.y - mSprite.height * mTextureScale / 2.0f;

	mRect.width = mSprite.width * mTextureScale;
	mRect.height = mSprite.height * mTextureScale;

	mTextureScale = GetAgeInMilliseconds() * .00005f;

}

void Enemy::Draw() const
{
	DrawTexturePro(	mSprite,
					Rectangle{ 0.0f, 0.0f, static_cast<float>(mSprite.width), static_cast<float>(mSprite.height) },
					Rectangle{ mPosition.x, mPosition.y, (mSprite.width) * mTextureScale, (mSprite.height) * mTextureScale },
					Vector2{ mSprite.width * mTextureScale / 2.0f, mSprite.height * mTextureScale / 2.0f },
					mBaseRotation + GetAgeInMilliseconds() * mRotationSpeed,
					GetActualColour());
}

void Enemy::Activate()
{

	mHealthCurrent = mHealthMax;
	mTimerBegin = std::chrono::steady_clock::now();
	PlaceRandomly();
	mIsActive = true;
	mBaseRotation = static_cast<float>(rand() % 360);

}

void Enemy::Deactivate()
{
	mIsActive = false;
	mTextureScale = 1.0f;
}

// separating this out so that we can reset enemies between rounds without all of them making a death sound
void Enemy::Die() {
	SoundManager::TriggerSound(SoundManager::SoundKey::AsteroidDeath);
	Deactivate();
}

void Enemy::PlaceRandomly()
{
	
	int side = rand() % 4;

	switch (side) {
		case 0: // left of screen
			mPosition.x = -10.0f;
			mPosition.y = static_cast<float>(rand() % GetScreenHeight());
			break;
		case 1: // right of screen
			mPosition.x = GetScreenWidth() + 10.0f;
			mPosition.y = static_cast<float>(rand() % GetScreenHeight());
			break;
		case 2: // above screen
			mPosition.x = static_cast<float>(rand() % GetScreenWidth());
			mPosition.y = -10.0f;
			break;
		case 3: // below screen
			mPosition.x = static_cast<float>(rand() % GetScreenWidth());
			mPosition.y = GetScreenHeight() + 10.0f;
			break;
	}

}

int Enemy::GetAgeInMilliseconds() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mTimerBegin).count();
}

bool Enemy::IsCollidingWithPlayer(const Vector2& pPlayerPosition)
{
	if (CheckCollisionPointCircle(pPlayerPosition, mPosition, mSprite.height * mTextureScale / 2.0f)) {
		return true;
	}
	else {
		return false;
	}
}

bool Enemy::TakeDamage(float pDamage)
{

	SoundManager::TriggerSound(SoundManager::SoundKey::Impact);

	mHealthCurrent -= pDamage;
	if (mHealthCurrent <= 0.0f) {
		Die();
		return true;
	}
	else{
		return false;
	}

}
