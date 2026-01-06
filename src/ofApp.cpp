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
	for (Entity* entity : mSceneEntities)
		delete entity;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	Ship* playerShip = GetPlayerShip();
	if (playerShip) {
		switch (key)
		{
		case 'w':
			playerShip->GetPhysicsComponent()->AddAcceleration(playerShip->GetTransformRef().GetForwardVector() * sPlayerShipAcceleration);
			break;
		case 'a':
			playerShip->GetPhysicsComponent()->AddAngularVelocity(sPlayerShipAngularAcceleration);
			break;
		case 'd':
			playerShip->GetPhysicsComponent()->AddAngularVelocity(-sPlayerShipAngularAcceleration);
			break;
		defaut:
			break;
		}
	}
	

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

Ship* GetPlayerShip()
{
	for (Entity* entity : mSceneEntities) {
		Ship* playerShip = dynamic_cast<Ship*>(entity);
		if (playerShip) {
			return playerShip;
		}
	}
	return nullptr;
}
