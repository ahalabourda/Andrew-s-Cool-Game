#pragma once
class Poolable
{

public:

	// TODO: figure out how to reconcile this. Enemy's Activate() takes no params because it finds its own position, but Bullet's Activate() requires position/rotation params. so the signatures don't match
	// do i make it so the Enemy Activate() requires a position and rotation? but what if want to pool some other object that doesn't require those things?
	// do i remove the params from Bullet's Activate(), and then make Bullet find its own direction/rotation? which would require it knowing about the player... or at least inputs?
	//virtual void Activate() = 0;
	virtual void Deactivate() = 0;

private:

};