/**
 * OpenGL Geometry viewer
 *
 * @file </viewer.cpp>
 * @author Prajankya Sonar - <prajankya@gmail.com>
 * @project OpenGL Geometry viewer
 * <https://github.com/prajankya/OpenGLModelViewer>
 *
 * MIT License
 * Copyright (c) 2020 Prajankya sonar
 *
 *
 * Adapted from https://www.cc.gatech.edu/~jarek/courses/openGL/viewer.htm
 *
 *
 *
 *
 * Left mouse    rotate;
 * Middle mouse  zoom;
 * Right mouse   menu;
 * ESC           quit
 */

#include <GL/glut.h>

/***************************************** Constants
 * *****************************************/
const int windowHeight = 400;
const int windowWidth = 400;

const GLfloat light0Position[] = {0, 1, 0, 1.0};
const float zNear = 1.0, zFar = 100.0;
const float aspect = windowWidth / windowHeight;

/******************************** Variables ********************************/

/* Viewer state */

float sphi = 90.0, stheta = 45.0;
float sdepth = 10;
float xcam = 0, ycam = 0;

long xsize, ysize;

int downX, downY;

bool leftButton = false, middleButton = false;

int i, j;

int mainMenu;

/******************************** Functions ********************************/

/**
 * @brief Context menu
 *
 * @param value : key stroke code
 */
void SetMainMenu(int value) {
  switch (value) {
    case 99:
      exit(0);
      break;
  }
}
/**
 * @brief Callback for any keyboard event
 *
 * @param ch
 * @param x
 * @param y
 */
void KeyboardCallback(unsigned char ch, int x, int y) {
  switch (ch) {
    case 27:
      exit(0);
      break;
  }
  glutPostRedisplay();
}

/**
 * @brief Callback on mouse event
 *
 * @param button
 * @param state
 * @param x
 * @param y
 */
void MouseCallback(int button, int state, int x, int y) {
  downX = x;
  downY = y;

  leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));

  middleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));

  glutPostRedisplay();
}

/******************************** Main ********************************/
int main(int argc, char **argv) {
  /*======== Initialize OpenGL ========*/
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow("OpenGL Geometry Viewer");

  glEnable(GL_DEPTH_TEST);

  glDepthFunc(GL_LEQUAL);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glPolygonOffset(1.0, 1.0);
  glDisable(GL_CULL_FACE);

  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_DIFFUSE);

  glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
  glEnable(GL_LIGHT0);
  // glutReshapeFunc(ReshapeCallback);
  // glutDisplayFunc(DisplayCallback);
  // glutKeyboardFunc(KeyboardCallback);
  // glutMouseFunc(MouseCallback);
  // glutMotionFunc(MotionCallback);

  /*======== Initialize Menu ========*/

  mainMenu = glutCreateMenu(SetMainMenu);
  glutAddMenuEntry("Exit", 99);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  /*======== Start Program loop ========*/
  glutMainLoop();

  return 0;
}
