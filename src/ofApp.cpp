#include "ofApp.h"
#include "Entity.h" 
#include "GameConstants.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofNoFill();
	mSceneEntities.push_back(new Ship());
	mSceneEntities[0]->AddComponent<PhysicsComponent>("PhysicsComponent");
	//mSceneEntities[0]->GetPhysicsComponent()->SetVelocity(glm::vec2(10,10));
	mSceneEntities[0]->GetPhysicsComponent()->SetAngularVelocity(0.f);
	mSceneEntities[0]->GetTransformRef().SetRotation(-45);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	float dt = ofGetLastFrameTime();

	UpdateCommands();
	MaintainBounds();

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
			playerShip->GetPhysicsComponent()->AddAcceleration(playerShip->GetTransformRef().GetForwardVector() * sPlayerShipAcceleration);
			playerShip->SetIsAccelerating(true);
		}
		else {
			playerShip->SetIsAccelerating(false);
		}
		if (mCommandMap['a']) {
			playerShip->GetPhysicsComponent()->AddAngularVelocity(sPlayerShipAngularAcceleration);
		}
		if (mCommandMap['d']) {
			playerShip->GetPhysicsComponent()->AddAngularVelocity(-sPlayerShipAngularAcceleration);
		}
	}
}

void ofApp::MaintainBounds()
{
	Ship* playerShip = GetPlayerShip();
	if (playerShip) {
		if (playerShip->GetPosition().x > ofGetWindowWidth() + 10) {
			playerShip->SetPosition(glm::vec2(-10, playerShip->GetPosition().y));
		}
		else if (playerShip->GetPosition().x < -10) {
			playerShip->SetPosition(glm::vec2(ofGetWindowWidth() + 10, playerShip->GetPosition().y));
		}
		else if (playerShip->GetPosition().y > ofGetWindowHeight() + 10) {
			playerShip->SetPosition(glm::vec2(playerShip->GetPosition().x, -10));
		}
		else if (playerShip->GetPosition().y < -10) {
			playerShip->SetPosition(glm::vec2(playerShip->GetPosition().x, ofGetWindowHeight() + 10));
		}
	}
}
