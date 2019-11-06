#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(2);

	this->mesh.setMode(OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	auto radius = 100;
	auto span = 240;
	int deg_start = ofGetFrameNum() % 360;

	for (auto deg = deg_start; deg < deg_start + 360; deg += 10) {

		this->mesh.addVertex(glm::vec3(span, 0, 0) + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
		this->mesh.addVertex(glm::vec3(0, -span, 0) + glm::vec3(radius * cos((deg + 90) * DEG_TO_RAD), radius * sin((deg + 90) * DEG_TO_RAD), 0));
		this->mesh.addVertex(glm::vec3(-span, 0, 0) + glm::vec3(radius * cos((deg + 180) * DEG_TO_RAD), radius * sin((deg + 180) * DEG_TO_RAD), 0));
		this->mesh.addVertex(glm::vec3(0, span, 0) + glm::vec3(radius * cos((deg + 270) * DEG_TO_RAD), radius * sin((deg + 270) * DEG_TO_RAD), 0));

		ofColor color;

		for (auto i = 0; i < 4; i++) {
		
			color.setHsb(ofMap((deg + (360 - deg_start) + i * 180) % 360, 0, 360, 0, 255), 200, 255);
			this->mesh.addColor(color);
		}

		auto index = this->mesh.getVertices().size() - 4;

		this->mesh.addIndex(index);
		this->mesh.addIndex(index + 1);
		
		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 2);

		this->mesh.addIndex(index + 2);
		this->mesh.addIndex(index + 3);

		this->mesh.addIndex(index + 3);
		this->mesh.addIndex(index + 0);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	this->mesh.draw();
	for (int i = 0; i < this->mesh.getVertices().size(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawCircle(this->mesh.getVertex(i), 4);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}