#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    float ratio = (float) (ofGetWidth()/ofGetHeight());
    
    shaderFilter.setUniform1f("ratio", ratio);
    shaderFilter.setUniform1f("randomNumber", 0);
    shaderFilter.load("shader.frag");
    shaderFilter.allocate(ofGetWidth(), ofGetHeight());
    file.open(ofToDataPath("qrandom.bin"),ofFile::ReadWrite, false);
    ofBuffer buff = file.readToBuffer();
    quantumData = buff.getData();
    shaderFilter.setUniform1f("randomNumber1", (int) quantumData[1]);
    shaderFilter.setUniform1f("randomNumber2", (int) quantumData[2]);
    shaderFilter.setUniform1f("randomNumber3", (int) quantumData[3]);
    shaderFilter.setUniform1f("randomNumber4", (int) quantumData[4]);
    shaderFilter.setUniform1f("randomNumber5", (int) quantumData[5]);
    
    camWidth = 640;
    camHeight = 480;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);


    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    shaderFilter.render();
    shaderFilter.draw(0,0);

      ofPixelsRef pixelsRef = vidGrabber.getPixels();

      float sum = 0;
      float total = camWidth/7 * camHeight/9;
      for (int i = 0; i < camWidth; i+= 7){
          for (int j = 0; j < camHeight; j+= 9){

              float lightness = pixelsRef.getColor(i,j).getLightness();
              sum = sum + lightness;

          }
      }
      float brightness = sum/total;

    shaderFilter.setUniform1f("brightness", brightness);
      std::cout << brightness << "\n";
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
    shaderFilter.allocate(w,h);
    float ratio = (float) (w/h);
    shaderFilter.setUniform1f("ratio", ratio);

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
