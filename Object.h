#pragma once

#include <stdio.h>

#include "Rigidbody.h"

class Object
{
public:
	Rigidbody rigidbody;

	Object();

	void makeRigidbody();
};

