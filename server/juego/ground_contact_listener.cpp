#include "./ground_contact_listener.h"

void GroundContactListener::BeginContact(b2Contact* contact) {
    Worm* worm = (Worm*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if (worm)
        worm->startGroundContact();

    worm = (Worm*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (worm)
        worm->startGroundContact();
}

void GroundContactListener::EndContact(b2Contact* contact) {
    Worm* worm = (Worm*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if (worm)
        worm->endGroundContact();
    
    worm = (Worm*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (worm)
        worm->endGroundContact();
}
