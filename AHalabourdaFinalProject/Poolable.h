#pragma once
class Poolable
{

public:

	// TODO: figure out how to reconcile this. Enemy's Activate() takes no params because it finds its own position, but Bullet's Activate() requires position/rotation params. so the signatures don't match
	// do i make it so the Enemy Activate() requires a position and rotation? but what if want to pool some other object that doesn't require those things?
	// do i remove the params from Bullet's Activate(), and then make Bullet find its own direction/rotation? which would require it knowing about the player... or at least inputs?
	
	// UPDATE: it is the day before i'm done with this project and i'm realizing now that i should have explored TPacks here perhaps. i think that would have allowed me to have Tick() and Activate() methods in a parent class while allowing the child classes to have different parameters. alas i'm starting with a new team tomorrow morning so i don't think i'm going to have time to investigate that.
	// as it stands this parent class is pretty low value. lol
	
	//virtual void Activate() = 0;
	virtual void Deactivate() = 0;

private:

};