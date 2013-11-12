#pragma once

#include "Maths\Vector.h"

namespace Rendering
{

	enum EntityId
	{
		INVALID_ID = -1,
	};

	enum SectorPosition
	{
		DEFENSE = 1,
		DEFENSE_MIDFIELD = 2,
		MIDFIELD = 3,
		MIDFIELD_OFFENSE = 4,
		OFFENSE = 5
	};

	enum SidePosition
	{
		LEFT = 1,
		LEFT_CENTER = 2, // when on the edge between left and center sector
		CENTER = 3,
		CENTER_RIGHT = 4,  // when on the edge between center and right sector
		RIGHT = 5
	};

class Entity
{
public:
	Entity(void);
	~Entity(void);

public:
	/* Clears out all the internal member variables.
	 * The benefit of clearing variables in a separate function is that
	 * it allows you to clear the class variables at any time.
	 */
	void Clear();

    /* 
	 * At times, you won't want to "activate" your class the moment it is created.
	 * This often happens for wrapper classes that are themselves members of another class.
	 * Lastly, there is an efficiency issue. Divorcing the object's actual creation point
	 * from the constructor allows you to dynamically create an object once,
	 * but repeatedly call the Create() and Destroy() members to reuse the same object's memory.
	 * Dynamically allocating memory is expensive, so when possible, it is best to avoid doing so.
	 */
	bool Create();

	/*
	 * This is the "step" function or the function that gets called once every frame.
	 * Depending on the class, you might want to implement the Update() function with a bool return value
	 * for checking run-time errors in the step function.
	 */
	void Update();

	/*
	 * Since we want both the convenience of automatic cleanup and the flexibility of "destroy and recreate on demand",
	 * we need to make sure that Destroy() function can be called multiple times safely or without the Create() function having been called.
	 * Be sure to call Clear() function at the end of your destroy function in order to reset all the object variables back to their initial states.
	 */
	void Destroy();


	//void Render(const Renderer& renderer);
protected:
	int m_id;

	/*
	 * collision detector = structure of polyhedrons where each one has smaller volume, but is also more complex.
	 * This should be done following the assumption that if some entity does not collide with polyhedron[0]
	 * it does not collide with any polyhedrons[i>0] (thus enities do not collide with each other).
	 * For ghosts polyhedron[0] = NULL which means it does not collide with anything.
	 */

	Maths::Point3Df position;
};
} /* end namespace Rendering */