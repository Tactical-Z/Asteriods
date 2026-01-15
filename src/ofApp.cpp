#include "ofApp.h"
#include "Entity.h" 
#include "GameConstants.h"

//--------------------------------------------------------------
void ofApp::setup() {
	mGameState = GameState::LOADING;
	mScore = 0.f;
	ofNoFill();
	ofSetColor(255,255,255);
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
	mGameState = GameState::MAIN_MENU;
}

//--------------------------------------------------------------
void ofApp::update(){
	float dt = ofGetLastFrameTime();

	switch (mGameState) {
	case GameState::MAIN_MENU:
		
		break;

	case GameState::PLAYING:
		mScore += ofGetLastFrameTime();
		UpdateCommands();
		MaintainBounds();
		CheckCollisions();
		for (Entity* entity : mSceneEntities) {
			entity->UpdateEntityComponent(dt);
			entity->Update(dt);
		}
		break;

	case GameState::PAUSE_MENU:
		// paused logic
		break;

	case GameState::GAME_OVER:
		// game over logic
		break;
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	float centreX = ofGetWidth() / 2;
	float centreY = ofGetHeight() / 2;
	float upOffset = 100;


	int minutes = (int)(mScore / 60);
	float seconds = mScore - (60 * minutes);
	switch (mGameState) {
	case GameState::MAIN_MENU:
		ofDrawBitmapString("Asteroids", centreX - 50, centreY - upOffset);
		
		ofDrawBitmapString("Goal; Survive as long as you can", centreX - 140, centreY - upOffset + 50);
		
		ofDrawBitmapString("Press 'W', 'A' or 'D' to move", centreX - 130, centreY - upOffset + 100);
		ofDrawBitmapString("Press 'Left click' to shoot", centreX - 120, centreY - upOffset + 120);
		ofDrawBitmapString("Press 'Space' to boost", centreX - 100, centreY - upOffset + 140);
		ofDrawBitmapString("Press 'Enter' to start", centreX - 100, centreY - upOffset + 160);
		ofDrawBitmapString("Press 'Tab' to pause", centreX - 90, centreY - upOffset + 180);
		ofDrawBitmapString("Press 'Esc' to quit", centreX - 85, centreY - upOffset + 200);
		ofDrawBitmapString("Good Luck", centreX - 50, centreY - upOffset + 220);
		break;

	case GameState::PLAYING:
		ofDrawBitmapString("Time survived: " + ofToString(minutes) + " m, " + ofToString(seconds, 1) + " s", centreX - 100, 0 + 50);

		for (Entity* entity : mSceneEntities)
			entity->Draw(mGameState);
		break;

	case GameState::PAUSE_MENU:

		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Game Paused", centreX - 50, centreY - upOffset);
		ofDrawBitmapString("Pres 'Tab' to unpause", centreX - 90, centreY - upOffset + 50);
		ofDrawBitmapString("Time survived: " + ofToString(minutes) + " m, " + ofToString(seconds, 1) + " s", centreX - 100, 0 + 50);

		ofSetColor(255/2, 255/2, 255/2);
		for (Entity* entity : mSceneEntities)
			entity->Draw(mGameState);
		break;

	case GameState::GAME_OVER:
		ofDrawBitmapString("Game Over", centreX - 50, centreY - upOffset);

		ofDrawBitmapString("Your survived for " + ofToString(minutes) + " minute(s) and " + ofToString(seconds, 1) + " second(s)", centreX - 180, centreY - upOffset + 50);

		ofDrawBitmapString("Press 'Enter' to go back to main menu", centreX - 160, centreY - upOffset + 100);
		break;
	}

}

//--------------------------------------------------------------
void ofApp::exit()
{
	shuttingDown = true;
	ofResetElapsedTimeCounter();
	for (Entity* entity : mSceneEntities)
		delete entity;

	mSceneEntities.clear();
	mCommandMap.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (shuttingDown) return;

	if (mGameState == GameState::MAIN_MENU && key == OF_KEY_RETURN)
		mGameState = GameState::PLAYING;

	if (mGameState == GameState::PAUSE_MENU && !mWaitOnPauseRelease && key == OF_KEY_TAB) {
		mGameState = GameState::PLAYING;
		mWaitOnPauseRelease = true;
	}
	
	if (mGameState == GameState::PLAYING && !mWaitOnPauseRelease && key == OF_KEY_TAB) {
		mGameState = GameState::PAUSE_MENU;
		mWaitOnPauseRelease = true;
	}

	if (mGameState == GameState::GAME_OVER && key == OF_KEY_RETURN) {
		exit();
		shuttingDown = false;
		setup();
	}
		
	if (mGameState == GameState::PLAYING && key == 'w')
		mCommandMap['w'] = true;
	if (mGameState == GameState::PLAYING && key == 'a')
		mCommandMap['a'] = true;
	if (mGameState == GameState::PLAYING && key == 'd')
		mCommandMap['d'] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (shuttingDown) return;

	if ((mGameState == GameState::PLAYING || mGameState == GameState::PAUSE_MENU) && key == OF_KEY_TAB)
		mWaitOnPauseRelease = false;

	if (mGameState == GameState::PLAYING && key == 'w')
		mCommandMap['w'] = false;
	if (mGameState == GameState::PLAYING && key == 'a')
		mCommandMap['a'] = false;
	if (mGameState == GameState::PLAYING && key == 'd')
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

	if (mGameState == GameState::PLAYING && button == OF_MOUSE_BUTTON_LEFT) {
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
					SetState(GameState::GAME_OVER);
					continue;
				}

				// Bullet collided into something (only bullet and asteroid left)
				//std::cout << "destroy asteroid and bullet" << std::endl;
			}
		}
	}
}

void ofApp::SetState(GameState _newState)
{
	mGameState = _newState;
}
