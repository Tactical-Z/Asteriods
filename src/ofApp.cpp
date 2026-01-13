#include "ofApp.h"
#include "Entity.h" 
#include "GameConstants.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofNoFill();
	ofSetColor(255, 255, 255);
	mSceneEntities.push_back(new Ship());
	mSceneEntities[0]->AddComponent<PhysicsComponent>("PhysicsComponent");
	//mSceneEntities[0]->GetPhysicsComponent()->SetVelocity(glm::vec2(10,10));
	mSceneEntities[0]->GetComponent<PhysicsComponent>()->SetAngularVelocity(0.f);
	mSceneEntities[0]->AddComponent<CollisionComponent>("CollisionComponent");
	mSceneEntities[0]->SetRotation(-45);
	mSceneEntities[0]->SetPosition({100, 100});
	
	mSceneEntities.push_back(new Asteroid());
	mSceneEntities[1]->AddComponent<PhysicsComponent>("PhysicsComponent");
	mSceneEntities[1]->GetComponent<PhysicsComponent>()->SetVelocity(glm::vec2(10, 10));
	mSceneEntities[1]->GetComponent<PhysicsComponent>()->SetAngularVelocity(5.f);
	mSceneEntities[1]->AddComponent<CollisionComponent>("CollisionComponent");
	mSceneEntities[1]->SetScale(glm::vec2(10));
	mSceneEntities[1]->SetPosition(glm::vec2(250,250));
}

//--------------------------------------------------------------
void ofApp::update(){
	float dt = ofGetLastFrameTime();

	UpdateCommands();
	MaintainBounds();
	CheckCollisions();

	for (Entity* entity : mSceneEntities) {
		entity->UpdateEntityComponent(dt);
		entity->Update(dt);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	for (Entity* entity : mSceneEntities)
		entity->Draw();
}

//--------------------------------------------------------------
void ofApp::exit()
{
	shuttingDown = true;

	for (Entity* entity : mSceneEntities)
		delete entity;

	mSceneEntities.clear();
	mCommandMap.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (shuttingDown) return;

	if (key == 'w')
		mCommandMap['w'] = true;
	if (key == 'a')
		mCommandMap['a'] = true;
	if (key == 'd')
		mCommandMap['d'] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (shuttingDown) return;

	if (key == 'w')
		mCommandMap['w'] = false;
	if (key == 'a')
		mCommandMap['a'] = false;
	if (key == 'd')
		mCommandMap['d'] = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if (button == OF_MOUSE_BUTTON_LEFT) {
		Bullet* bullet = new Bullet();
		bullet->AddComponent<PhysicsComponent>("PhysicsComponent");
		bullet->GetComponent<PhysicsComponent>()->SetVelocity(GetPlayerShip()->GetForwardVector() * sPlayerBulletSpeed);
		bullet->AddComponent<CollisionComponent>("CollisionComponent");
		bullet->GetComponent<CollisionComponent>()->AddIgnoreEntity(GetPlayerShip());
		bullet->SetPosition(GetPlayerShip()->GetPosition());
		mSceneEntities.push_back(bullet);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

Ship* ofApp::GetPlayerShip()
{
	for (Entity* entity : mSceneEntities) {
		Ship* playerShip = dynamic_cast<Ship*>(entity);
		if (playerShip) {
			return playerShip;
		}
	}
	return nullptr;
}

void ofApp::UpdateCommands()
{
	Ship* playerShip = GetPlayerShip();
	if (playerShip) {
		if (mCommandMap['w']) {
			playerShip->GetComponent<PhysicsComponent>()->AddAcceleration(playerShip->GetTransformRef()->GetForwardVector() * sPlayerShipAcceleration);
			playerShip->SetIsAccelerating(true);
		}
		else {
			playerShip->SetIsAccelerating(false);
		}
		if (mCommandMap['a']) {
			playerShip->GetComponent<PhysicsComponent>()->AddAngularVelocity(sPlayerShipAngularAcceleration);
		}
		if (mCommandMap['d']) {
			playerShip->GetComponent<PhysicsComponent>()->AddAngularVelocity(-sPlayerShipAngularAcceleration);
		}
	}
}

void ofApp::MaintainBounds()
{
	for(Entity* entity : mSceneEntities)
	if (entity) {
		if (entity->GetPosition().x > ofGetWindowWidth() + 10) {
			entity->SetPosition(glm::vec2(-10, entity->GetPosition().y));
		}
		else if (entity->GetPosition().x < -10) {
			entity->SetPosition(glm::vec2(ofGetWindowWidth() + 10, entity->GetPosition().y));
		}
		else if (entity->GetPosition().y > ofGetWindowHeight() + 10) {
			entity->SetPosition(glm::vec2(entity->GetPosition().x, -10));
		}
		else if (entity->GetPosition().y < -10) {
			entity->SetPosition(glm::vec2(entity->GetPosition().x, ofGetWindowHeight() + 10));
		}
	}
}

void ofApp::CheckCollisions()
{
	
	for (int i = 0; i < mSceneEntities.size(); i++) {

		CollisionComponent* collisionCompA = mSceneEntities[i]->GetComponent<CollisionComponent>();

		for (int j = i + 1; j < mSceneEntities.size(); j++) {
			CollisionComponent* collisionCompB = mSceneEntities[j]->GetComponent<CollisionComponent>();

			// Check for early exit
			if ((!collisionCompA || !collisionCompB) ||
				(!collisionCompA->IsCollisionEnabled() || !collisionCompB->IsCollisionEnabled()) ||
				(collisionCompA->ContainsIgnoreEntity(collisionCompB->GetParent()) || collisionCompB->ContainsIgnoreEntity(collisionCompA->GetParent()))) {
				return;
			}

			if (CollisionComponent::IsIntersecting(collisionCompA, collisionCompB)) {

				// Collision Result
				// player collided into something
				if (collisionCompA->GetParent() == GetPlayerShip()) {
					std::cout << "player died" << std::endl;
					continue;
				}

				// Bullet collided into something (only bullet and asteroid left)
				std::cout << "destroy asteroid and bullet" << std::endl;
			}
		}
	}
}
