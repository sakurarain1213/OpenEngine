#include "Contact.h"

void OpenEngine::ContactManifold::UpdateContacts()
{
}

void OpenEngine::ContactManifold::AddContact(ContactPoint point)
{
	if (contactPointCount >= 4)
	{
		return;
	}

	contactPointCount += 1;
	contactPoints[contactPointCount] = point;
}
