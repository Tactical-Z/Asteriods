#include "ofApp.h"
#include "Entity.h" 

//--------------------------------------------------------------
void ofApp::setup(){
	ofNoFill();
	mSceneEntities.push_back(new Ship());

}

//--------------------------------------------------------------
void ofApp::update(){
	float _dt = 1.f;
	for (Entity* entity : mSceneEntities)
		entity->Update(_dt);
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
