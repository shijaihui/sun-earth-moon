#include "glut.h"
#include <cmath>
#include <windows.h>

static float year = 0;
static float month = 0;
static float day = 0;
static float angle = 30;

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);//太空环境色
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	GLfloat light0_ambient[]  = {1, 1, 1, 1};
	GLfloat light0_diffuse[]  = {1, 1, 1, 1};
	GLfloat light0_position[] = {0, 0, 0, 1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
	glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
}

void zhouqi()
{
	day+=angle;
	glutPostRedisplay();
}

void display(void)
{	
    year=day/365;
    month=day/30;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	//太阳材质
    GLfloat s_ambient[] = {1.0,0.0,0.0,1};
	GLfloat s_emission[] = {1,0.1,0,0};
	//地球材质
	GLfloat e_ambient[] = {0.0,0.0,0.0,1};
	GLfloat e_emission[] = {0.0,0.4,1,0};
	//月亮材质
	GLfloat m_ambient[] = {0.5,0.5,1.0,1};
	GLfloat m_emission[] = {0.8,0.8,0.8};
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);

	
	//光照
	GLfloat light0_position[] = {0.0,3.0,10.0,0.0};
	GLfloat light0_diffuse[] = {0.7f, 0.7f, 0.7f, 0.5f}; 
	GLfloat light0_specular[] = {0.5f, 0.5f, 0.5f, 0.2f};
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glEnable(GL_LIGHT0);
   	glDepthFunc(GL_LESS);

    glPushMatrix();	
		glRotatef (year, 0.0, 2.0, 0.0);//太阳自转
		glMaterialfv(GL_FRONT, GL_AMBIENT, s_ambient);//添加材质
		glMaterialfv(GL_FRONT, GL_EMISSION, s_emission);
		glRotatef (60, -1, 0, 0);
		glutSolidSphere(1.5, 40, 40);//画一个太阳
		glPopMatrix();
    
		glPushMatrix();
			glRotatef (year, 0.0, 2.0, 0.0);//地球公转
			glPushMatrix();
			glTranslatef (3.0, 0.0, 0.0);
			glRotatef (month, 0.0, 1.0, 0.0);//地球自转 
			glMaterialfv(GL_FRONT, GL_AMBIENT, e_ambient);//添加材质
			glMaterialfv(GL_FRONT, GL_EMISSION, e_emission);
			glRotatef (60, -1, 0, 0);
			glutSolidSphere(0.5, 40, 40);//画一个地球	
		glPopMatrix();

		glPushMatrix();
			glTranslatef (3.0, 0.0, 0.0);
			glRotatef (60, -1, 1, 0);
			glRotatef (month, 0, 3.0, 0);//月球公转
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);//添加材质
			glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
			glTranslatef (0.6, 0.0, 0.0);
			glRotatef (60, -1, 0, 0);
			glutSolidSphere(0.08, 20, 20);//画一个月球
		glPopMatrix();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	//视口大小
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	//透视投影	
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//视点
	gluLookAt (0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 5.0, -5.0);	
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("太阳系");
    init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(zhouqi);
	glutMainLoop();
	return 0;
}