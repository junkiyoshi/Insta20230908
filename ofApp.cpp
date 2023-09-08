#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
	ofSetLineWidth(3);

	auto ico_sphere = ofIcoSpherePrimitive(250, 4);
	this->base_mesh = ico_sphere.getMesh();
	this->draw_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh.clear();

	ofColor color;
	for (int i = 0; i < this->base_mesh.getNumVertices(); i++) {

		auto v = this->base_mesh.getVertex(i);
		color.setHsb(ofMap(i, 0, this->base_mesh.getNumVertices(), 150, 255), 255, 255);

		for (int j = 0; j < 15; j++) {
			
			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.006, ofGetFrameNum() * 0.0015 + j * 0.0015)), 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.006, ofGetFrameNum() * 0.0015 + j * 0.0015)), 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.006, ofGetFrameNum() * 0.0015 + j * 0.0015)), 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));
			auto vertex = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;

			this->draw_mesh.addVertex(vertex);
			this->draw_mesh.addColor(ofColor(color, ofMap(j, 0, 15, 0, 100)));

			if (j != 0) {

				this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 1);
				this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 2);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	ofSetColor(0);
	ofFill();
	ofDrawSphere(248);

	this->draw_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}