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

/****************************** DRAW FUNCTION ******************************/

void draw() {
  /**
   * TODO: Insert geometry draw commands here
   *
   */

#define MAX_TRIANGLES (10)

  struct Point {
    float x[3];
    float n[3];
  };

  struct Triangle {
    Point v[3];
  };

  Triangle triangleList[MAX_TRIANGLES];

  int triangleCount = 2;

  /* coordinates */

  triangleList[0].v[0].x[0] = 0;
  triangleList[0].v[0].x[1] = 0;
  triangleList[0].v[0].x[2] = 0;

  triangleList[0].v[1].x[0] = 0;
  triangleList[0].v[1].x[1] = 1;
  triangleList[0].v[1].x[2] = 0;

  triangleList[0].v[2].x[0] = 1;
  triangleList[0].v[2].x[1] = 0;
  triangleList[0].v[2].x[2] = 0;

  triangleList[1].v[0].x[0] = 0;
  triangleList[1].v[0].x[1] = 0;
  triangleList[1].v[0].x[2] = 0;

  triangleList[1].v[1].x[0] = 0;
  triangleList[1].v[1].x[1] = 0;
  triangleList[1].v[1].x[2] = 1;

  triangleList[1].v[2].x[0] = 0;
  triangleList[1].v[2].x[1] = 1;
  triangleList[1].v[2].x[2] = 0;

  /* normals */

  triangleList[0].v[0].n[0] = 0.7;
  triangleList[0].v[0].n[1] = 0;
  triangleList[0].v[0].n[2] = 0.7;

  triangleList[0].v[1].n[0] = 0.7;
  triangleList[0].v[1].n[1] = 0;
  triangleList[0].v[1].n[2] = 0.7;

  triangleList[0].v[2].n[0] = 0;
  triangleList[0].v[2].n[1] = 0;
  triangleList[0].v[2].n[2] = 1;

  triangleList[1].v[0].n[0] = 0.7;
  triangleList[1].v[0].n[1] = 0;
  triangleList[1].v[0].n[2] = 0.7;

  triangleList[1].v[1].n[0] = 1;
  triangleList[1].v[1].n[1] = 0;
  triangleList[1].v[1].n[2] = 0;

  triangleList[1].v[2].n[0] = 0.7;
  triangleList[1].v[2].n[1] = 0;
  triangleList[1].v[2].n[2] = 0.7;

  int i;

  glColor3f(0.8f, 0.2f, 0.8f);

  glBegin(GL_TRIANGLES);

  for (i = 0; i < triangleCount; ++i) {
    glNormal3fv(triangleList[i].v[0].n);

    glVertex3fv(triangleList[i].v[0].x);

    glNormal3fv(triangleList[i].v[1].n);

    glVertex3fv(triangleList[i].v[1].x);

    glNormal3fv(triangleList[i].v[2].n);

    glVertex3fv(triangleList[i].v[2].x);
  }

  glEnd();
}

/******************************** Constants ********************************/
const long windowHeight = 400;
const long windowWidth = 400;

const GLfloat light0Position[] = {0, 1, 0, 1.0};
const float zNear = 1.0, zFar = 100.0;

/******************************** Variables ********************************/

/* Viewer state */

float sphi = 90.0, stheta = 45.0;
float sdepth = 10;

float aspect = windowWidth / windowHeight;

int downX, downY;

bool leftButton = false, middleButton = false;

/******************************** Functions ********************************/

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

/* ========================================= */
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

/* ========================================= */
/**
 * @brief Callback for Window resize
 *
 * @param width
 * @param height
 */
void ReshapeCallback(int width, int height) {
  aspect = (float)width / (float)height;

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutPostRedisplay();
}

/* ========================================= */
/**
 * @brief Callback for motion change
 *
 * @param x
 * @param y
 */
void MotionCallback(int x, int y) {
  if (leftButton) {
    sphi += (float)(x - downX) / 4.0;
    stheta += (float)(downY - y) / 4.0;
  }  // rotate

  if (middleButton) {
    sdepth += (float)(downY - y) / 10.0;
  }  // scale

  downX = x;
  downY = y;

  glutPostRedisplay();
}

/* ========================================= */
/**
 * @brief Callback to display
 *
 */
void DisplayCallback(void) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(64.0, aspect, zNear, zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -sdepth);
  glRotatef(-stheta, 1.0, 0.0, 0.0);
  glRotatef(sphi, 0.0, 0.0, 1.0);

  /* Call draw function */
  draw();

  glutSwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

  /*======== Register Callbacks ========*/

  glutReshapeFunc(ReshapeCallback);
  glutDisplayFunc(DisplayCallback);
  glutKeyboardFunc(KeyboardCallback);
  glutMouseFunc(MouseCallback);
  glutMotionFunc(MotionCallback);

  /*======== Start Program loop ========*/
  glutMainLoop();

  return 0;
}
