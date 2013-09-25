#include <stdio.h>
#include <math.h>

#include "world.h"
#include "shared.h"
#include "shader_program.h"

#define MOUSE_OVERFLOW 300

int screen_width, screen_height,	
    mouse_x, mouse_y;

bool f_key_up, f_key_down,
	 f_key_left, f_key_right,
	 f_key_lower, f_key_higher,
     f_key_w, f_key_s,
     f_key_a, f_key_d;

float speed=1;
float pauseSpeed=0;

World *world;


void key_down(int c, int x, int y) {
	switch (c) {
		case GLUT_KEY_LEFT:
			f_key_left = true;
			break;
		case GLUT_KEY_RIGHT:
			f_key_right = true;
			break;
		case GLUT_KEY_UP:
			f_key_up = true;
			break;
		case GLUT_KEY_DOWN:
			f_key_down = true;
			break;
		case GLUT_KEY_PAGE_UP:
			f_key_higher = true;
			break;
		case GLUT_KEY_PAGE_DOWN:
			f_key_lower = true;
			break;
	}
}

void keyDown(unsigned char c, int x, int y) {
  switch (c) {
    case 'w':
      f_key_w = true;
      break;
    case 's':
      f_key_s = true;
      break;
    case 'a':
      f_key_a = true;
      break;
    case 'd':
      f_key_d = true;
      break;
    case 'p':
      if(speed>0) {
	pauseSpeed=speed;
	speed=0;
      }
      else
	speed=pauseSpeed;
      break;
    case '>':
      if(speed<4)
	speed+=0.1;
      break;
    case '<':
      if(speed>0.1)
	speed-=0.1;
      else
	speed=0;
      break;
    case 'q':
      glutLeaveMainLoop();
      break;
  }
}

void key_up(int c, int x, int y) {
	switch (c) {
		case GLUT_KEY_LEFT:
			f_key_left = false;
			break;
		case GLUT_KEY_RIGHT:
			f_key_right = false;
			break;
		case GLUT_KEY_UP:
			f_key_up = false;
			break;
		case GLUT_KEY_DOWN:
			f_key_down = false;
			break;
		case GLUT_KEY_PAGE_UP:
			f_key_higher = false;
			break;
		case GLUT_KEY_PAGE_DOWN:
			f_key_lower = false;
			break;

	}
}

void keyUp(unsigned char c, int x, int y) {
    switch (c) {
        case 'w':
            f_key_w = false;
            break;
        case 's':
            f_key_s = false;
            break;
        case 'a':
            f_key_a = false;
            break;
        case 'd':
            f_key_d = false;
            break;
    }
}

void mouse_motion(int x, int y) {
	int dx = x - mouse_x, 
  dy = y - mouse_y;
	
	if ((abs(dx) < MOUSE_OVERFLOW) && (abs(dy) < MOUSE_OVERFLOW)) {
		world->mouse_motion(dx, dy);
	}

	if (x <= 10 ||
    	x >= screen_width - 10 ||
    	y <= 10 ||
    	y >= screen_height - 10
	) {
		mouse_x = screen_width / 2;
		mouse_y = screen_height / 2;
		glutWarpPointer(mouse_x, mouse_y);
	} else {
		mouse_x = x;
		mouse_y = y;
	}
}

void display_frame() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	world->draw();
	glutSwapBuffers();
}

void next_frame() {
	world->next_frame(speed,
		(direct_t)(BACK * f_key_left + FRONT * f_key_right),
		(direct_t)(BACK * f_key_down + FRONT * f_key_up),
		(direct_t)(BACK * f_key_lower + FRONT * f_key_higher),
		(direct_t)(BACK * f_key_s    + FRONT * f_key_w),
		(direct_t)(BACK * f_key_a + FRONT * f_key_d)
	);
	glutPostRedisplay();
}

void gl_init(int *argc, char **argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	screen_width = glutGet(GLUT_SCREEN_WIDTH);
	screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	
	glutInitWindowSize(screen_width, screen_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pendulum");
	glutFullScreen();
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutSetCursor(GLUT_CURSOR_NONE);
	
	glewInit();
	
	glutDisplayFunc(display_frame);
	glutIdleFunc(next_frame);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	glutSpecialUpFunc(key_up);
	glutSpecialFunc(key_down);
	glutPassiveMotionFunc(mouse_motion);
	glutMotionFunc(mouse_motion);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
  
  glActiveTexture(GL_TEXTURE0);
}

int main(int argc, char **argv) {
  cout<<"Main"<<endl;
	gl_init(&argc, argv);
  cout<<"Main after gl_init"<<endl;
  
  ShaderProgram* shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
  shaderProgram->use();

  world = new World(shaderProgram,NULL);
  cout<<"Main after world"<<endl;
  if(!world->load("config.ini", screen_width, screen_height)) {
    fprintf(stderr, "Error loading world. Spierdalaj\n");
    return -1;
  }
  cout<<"Main after world->load"<<endl;
	
	glutMainLoop();

  delete world;
  delete shaderProgram;
	return 0;
}
