#pragma once

#include "ofMain.h"
#include "GameConstants.h"
#include "Entity.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
private:
	GameState mGameState;
	bool mWaitOnPauseRelease = false;
	std::vector<class Entity*> mSceneEntities;
	std::unordered_map<int, bool> mCommandMap;
	bool shuttingDown = false;
	float mScore = 0.f;

	Ship* GetPlayerShip();
	void UpdateCommands();
	void MaintainBounds();
	void CheckCollisions();
	void SetState(GameState _newState);
};