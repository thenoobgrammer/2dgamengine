#ifndef INC_2DGAMEENGINE_MOUSETRACKCOMPONENT_H
#define INC_2DGAMEENGINE_MOUSETRACKCOMPONENT_H

struct MouseTrackComponent {
  int mouseX;
  int mouseY;
  float mouseAngle;

  MouseTrackComponent(int mouseX = 0, int mouseY = 0, float mouseAngle = 0.0f) {
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->mouseAngle = mouseAngle;
  }
};

#endif
