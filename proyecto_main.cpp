//Semestre 2019 - 2
//************************************************************//
//************************************************************//
//************** Alumno: *********************************//
//*************         	******//
//*************	  ALMAGUER RIOJA CARLOS ISRAEL			******//
//*************	  	******//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include <ctime>
#include "cmodel/CModel.h"
//Solo para Visual Studio 2015 y en adelante
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito




CTexture textSilla;
CTexture textPizarron;
CFiguras pata1Mesa;
CFiguras pata2Mesa;
CFiguras pata3Mesa;
CFiguras pata4Mesa;
CFiguras asientoSilla;
CFiguras respaldoSilla1;
CFiguras respaldoSilla2;
CFiguras respaldoSilla3;
CFiguras respaldoSilla4;
CFiguras pizarron;

CTexture madera, windows, tecla, negro;
float  posXrat=90  , posZrat = 110;
float  rot_rat = 0;
float xc = -450, xy = 25, xz = 150;
int ry = 0, rz = 0;
float posXhel = -150, posYhel = 20, posZhel = -20;
float rot_helicoptero = 0;
float moveSkyI = 0;
float moveSkyF = 0;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;
#define PI 3.14159265
clock_t startTime;
clock_t prevTime;

/////////////////
CTexture arbol1,puerta,puertaSalon, muro1, techo1, pisointerior1, techoexterior, muro2, ventana1,marco,ladrillo, pisoexterior1,arbol2,pino2;
CFiguras edificio;

///////////////////
int giro = 0;
int altura = 300;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//NEW// Keyframes
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;

#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	float movBrazoDer;
	float movBrazoDerInc;

	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=5;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
//int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 16.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture text2;

CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01

CTexture tree;
CTexture metal;

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito

//Figuras de 3D Studio

CModel helicoptero;
CModel lampara;
CModel banca;
//Animación del coche
float angRot = 0.0;
float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;
float rotTires = 0.0;
bool g_fanimacion = false;
bool g_avanza = false;
bool baja= true;
bool sube = false;
bool recta1 = false;
bool subida1 = false;



///////////////////////////////////////////////////////////////////

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	movBrazoDer = KeyFrame[0].movBrazoDer;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	KeyFrame[playIndex].movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;

}

void arbol_alpha()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable( GL_ALPHA_TEST );
		glAlphaFunc( GL_GREATER, 0.1 );
		glBindTexture(GL_TEXTURE_2D, tree.GLindex);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
				
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
		glDisable( GL_ALPHA_TEST );
		glEnable(GL_LIGHTING);
				
	glPopMatrix();
}

void pino2_alpha()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, pino2.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}
void arbol1_alpha()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, arbol1.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}
void arbol2_alpha()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, arbol2.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}
void arbol_blend()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);     // Turn Blending On
		//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, tree.GLindex);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();	
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();	
	glPopMatrix();

	glPushMatrix();
		glRotatef(-45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();				
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();		
	glPopMatrix();
	glDisable(GL_BLEND);        // Turn Blending Off
	//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
	glEnable(GL_LIGHTING);
}

/*
GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
*/
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	//glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
    //glColor4f(1.0f, 1.0f, 1.0f, 0.5); 
    /////////////////////////////////////////////////////////////////

	muro2.LoadTGA("texturas_edificio/paredblocks2.tga");
	muro2.BuildGLTexture();
	muro2.ReleaseImage();

	madera.LoadBMP("texturas_edificio/madera.bmp");//textura de mesas
	madera.BuildGLTexture();
	madera.ReleaseImage();

	windows.LoadBMP("texturas_edificio/windows.bmp");//textura de compus
	windows.BuildGLTexture();
	windows.ReleaseImage();

	negro.LoadBMP("texturas_edificio/negro.bmp");//textura de compus
	negro.BuildGLTexture();
	negro.ReleaseImage();
	
	textPizarron.LoadBMP("texturas_edificio/pizarron.bmp");
	textPizarron.BuildGLTexture();
	textPizarron.ReleaseImage();

    text1.LoadTGA("archivos_gus/skybox.tga");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	tree.LoadTGA("Texturas/Tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();


	pino2.LoadTGA("archivos_gus/pino2.tga");
	pino2.BuildGLTexture();
	pino2.ReleaseImage();

	arbol2.LoadTGA("archivos_gus/arbol2.tga");
	arbol2.BuildGLTexture();
	arbol2.ReleaseImage();

	arbol1.LoadTGA("archivos_gus/arbol1.tga");
	arbol1.BuildGLTexture();
	arbol1.ReleaseImage();

	pisoexterior1.LoadTGA("texturas_edificio/pisoexterior1.tga");
	pisoexterior1.BuildGLTexture();
	pisoexterior1.ReleaseImage();

	text1.LoadTGA("archivos_gus/skybox.tga");
	text1.BuildGLTexture();
	text1.ReleaseImage();


	text5.LoadTGA("grass_seamless.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();


	metal.LoadTGA("texturas/metal2.tga");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	helicoptero._3dsLoad("helicopter/md500.3ds");
	helicoptero.LoadTextureImages();
	helicoptero.GLIniTextures();
	helicoptero.ReleaseTextureImages();

	banca._3dsLoad("Banca/Cgtuts_Wood_Bench_3DS.3ds");
	

	//objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);-57.22,26.70,-188.71
	objCamera.Position_Camera(95.67, 83.70, 179.03, -115.08, 100.80, 99.74,0.00, 1.00, 0.00);
	//NEW Crear una lista de dibujo
	//ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	/*for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
		KeyFrame[i].giroBrazo =0;
		KeyFrame[i].giroBrazoInc = 0;

	}*/

	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = -3.5;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].giroMonito = 0;
	KeyFrame[0].movBrazoDer = 0;

	KeyFrame[1].posX = 20;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = -3.5;
	KeyFrame[1].rotRodIzq = 60;
	KeyFrame[1].giroMonito = -90.0;
	KeyFrame[1].movBrazoDer = 40;

	KeyFrame[2].posX = 20;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = 4.0;
	KeyFrame[2].rotRodIzq = -20.0;
	KeyFrame[2].giroMonito = 0;
	KeyFrame[2].movBrazoDer = 0;

	KeyFrame[3].posX = 20;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = 4.0;
	KeyFrame[3].rotRodIzq = 40.0;
	KeyFrame[3].giroMonito = 45;
	KeyFrame[3].movBrazoDer = 90;

	KeyFrame[4].posX = 20;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = 4.0;
	KeyFrame[4].rotRodIzq = -40.0;
	KeyFrame[4].giroMonito = -45;
	KeyFrame[4].movBrazoDer = -90;
	//NEW//////////////////NEW//////////////////NEW//////////////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	
	glPushMatrix();

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,240,0);
				fig1.skybox(1200, 500, 1200,text1.GLindex,moveSkyI,moveSkyF);
				glEnable(GL_LIGHTING);
			glPopMatrix();




			glPushMatrix();

				glLineWidth(7.0);
				glDisable(GL_LIGHTING);
				glBegin(GL_LINES); //Ejes de Referencia
				
					glTranslatef(0, 60, 15);
					glColor3f(1.0, 0.0, 0.0);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(1150.0, 0.0, 0.0);// rojo X
					glColor3f(0.0, 1.0, 0.0);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 1150.0, 0.0);// verde y
					glColor3f(0.0, 0.0, 1.0);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 0.0, 1150.0); // azul Z
					glColor3f(1.0, 1.0, 1.0);
				glEnd();
				glEnable(GL_LIGHTING);

				glPopMatrix();

			
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			glPushMatrix(); //Pasto
			glTranslatef(0.0, 0.0, -4.0);
			glScalef(1200, 0.1, 1200);
			glDisable(GL_LIGHTING);
			fig4.prisma3(text5.GLindex, text5.GLindex,16);
			glEnable(GL_LIGHTING);
			glPopMatrix();
		

          
///////////////////////////////////////construccion juego giratorio
            glDisable(GL_LIGHTING);

              glPushMatrix();
			  glTranslatef(220, 5, -230);
			  fig3.cilindro(130, 10, 20, muro2.GLindex);//cilindro base
			  glPopMatrix();
			  glPushMatrix();
			  glTranslatef(220, 15, -230);
			  fig3.cilindro(110, 10, 20, muro2.GLindex);//cilindro base1
			  glPopMatrix();
			  glPushMatrix();
			  glTranslatef(220, 25, -230);
			  fig3.cilindro(90, 10, 20, muro2.GLindex);//cilindro base2
			  glPopMatrix();
			  glPushMatrix();
			  glTranslatef(220, 35, -230);
			  fig3.cilindro(70, 10, 20, muro2.GLindex);//cilindro base3
			  glPopMatrix();
			  glPushMatrix();
			  glTranslatef(220, 45, -230);
			  fig3.cilindro(50, 10, 20, muro2.GLindex);//cilindro base4
			  glPopMatrix();
			  glPushMatrix();
			  glTranslatef(220, 50, -230);
			  fig3.cilindro(5, 300, 20, textPizarron.GLindex);//cilindro hasta
			  glPopMatrix();
			  glPushMatrix();
			  glTranslatef(220, 360, -230);
			  fig3.esfera(15, 10, 10, negro.GLindex);//esfera copa
			  glPopMatrix();
	glPushMatrix();
		glTranslatef(220, altura, -230);
	    glRotatef(giro, 0, 1, 0);
	    fig3.cilindro(25, 10, 20, negro.GLindex);//cilindro base brazos
			      glPushMatrix();
				  glTranslatef(0, 5, 73.5);
			      fig3.prisma(2, 10, 115, 0);//brazo1
				  glTranslatef(0, 0, 50);
				  fig3.prisma(20, 35, 20, madera.GLindex);//cuerpo avion1
				     glPushMatrix();
				       glTranslatef(20, 0, 0);
				       glColor3f(0, 0, 0);
				       fig3.prisma(16, 5, 16, 0);//punta avion1
				       glTranslatef(3.75, 0, 0);
				       glColor3f(1, 1, 1);
				       fig3.prisma(8, 2.5, 8, 0);//punta1 avion1
				       glTranslatef(1.875, 0, 0);
				       glColor3f(1, 1, 1);
				       fig3.prisma(4, 1.25, 25, negro.GLindex);//helice 1 
				       fig3.prisma(25, 1.25, 4,negro.GLindex);//helice 2
					 glPopMatrix();
				  glTranslatef(-22.5, 0, 0);
				  fig3.prisma(15, 10, 10, madera.GLindex);//cola avion
				  glTranslatef(-3.5, 11.5, 0 );
				  fig3.prisma(8, 8, 2, negro.GLindex);//punta cola
				  glPopMatrix();
				  
				  glPushMatrix();
				  glTranslatef(73.5, 5, 0);
				  fig3.prisma(2, 115, 10, 0);//brazo2
				  glRotatef(90, 0, 1, 0);
				  glTranslatef(0, 0, 50);
				  fig3.prisma(20, 35, 20, metal.GLindex);//cuerpo avion2
				      glPushMatrix();
				          glTranslatef(20, 0, 0);
				          glColor3f(0, 0, 0);
				          fig3.prisma(16, 5, 16, 0);//punta avion2
				          glTranslatef(3.75, 0, 0);
				          glColor3f(1, 1, 1);
				          fig3.prisma(8, 2.5, 8, 0);//punta1 avion2
				          glTranslatef(1.875, 0, 0);
				          glColor3f(1, 1, 1);
				          fig3.prisma(4, 1.25, 25, negro.GLindex);//helice 1 
				          fig3.prisma(25, 1.25, 4, negro.GLindex);//helice 2
				      glPopMatrix();
				  glTranslatef(-22.5, 0, 0);
				  fig3.prisma(15, 10, 10, metal.GLindex);//cola avion
				  glTranslatef(-3.5, 11.5, 0);
				  fig3.prisma(8, 8, 2, negro.GLindex);//punta cola
				  glPopMatrix();

				  glPushMatrix();
				  glTranslatef(0, 5, -73.5);
				  fig3.prisma(2, 10, 115, 0);//brazo3
				  glRotatef(180, 0, 1, 0);
				  glTranslatef(0, 0, 50);
				  fig3.prisma(20, 35, 20, madera.GLindex);//cuerpo avion3
				      glPushMatrix();
				         glTranslatef(20, 0, 0);
				         glColor3f(0, 0, 0);
				         fig3.prisma(16, 5, 16, 0);//punta avion3
				         glTranslatef(3.75, 0, 0);
				         glColor3f(1, 1, 1);
				         fig3.prisma(8, 2.5, 8, 0);//punta1 avion3
				         glTranslatef(1.875, 0, 0);
				         glColor3f(1, 1, 1);
				         fig3.prisma(4, 1.25, 25, negro.GLindex);//helice 1 
				         fig3.prisma(25, 1.25, 4, negro.GLindex);//helice 2
				      glPopMatrix();
				  glTranslatef(-22.5, 0, 0);
				  fig3.prisma(15, 10, 10, madera.GLindex);//cola avion
				  glTranslatef(-3.5, 11.5, 0);
				  fig3.prisma(8, 8, 2, negro.GLindex);//punta cola
                  glPopMatrix();
				 
				  glPushMatrix();
				  glTranslatef(-73.5, 5, 0);
				  fig3.prisma(2, 115, 10, 0);//brazo4
				  glRotatef(270, 0, 1, 0);
				  glTranslatef(0, 0, 50);
				  fig3.prisma(20, 35, 20, metal.GLindex);//cuerpo avion4
				      glPushMatrix();
				          glTranslatef(20, 0, 0);
				          glColor3f(0, 0, 0);
				          fig3.prisma(16, 5, 16, 0);//punta avion4
				          glTranslatef(3.75, 0, 0);
				          glColor3f(1, 1, 1);
				          fig3.prisma(8, 2.5, 8, 0);//punta1 avion4
				          glTranslatef(1.875, 0, 0);
				          glColor3f(1, 1, 1);
				          fig3.prisma(4, 1.25, 25, negro.GLindex);//helice 1 
				          fig3.prisma(25, 1.25, 4, negro.GLindex);//helice 2
				      glPopMatrix();
				  glTranslatef(-22.5, 0, 0);
				  fig3.prisma(15, 10, 10, metal.GLindex);//cola avion
				  glTranslatef(-3.5, 11.5, 0);
				  fig3.prisma(8, 8, 2, negro.GLindex);//punta cola
				  glPopMatrix();

		glPopMatrix();

		///////////////////////Construccion Montana Rusa

glPushMatrix();
		glTranslatef(-450, 2.5, 150);           //////recta inicio
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		
		glRotatef(45, 0, 0, 1);                   ////primer subida
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);

		glRotatef(-45, 0, 0, 1);                  ///primera parte de arriba
		glTranslatef(20, 7, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);

		glRotatef(-25, 0, 1, 0);                   ///curva1 parte alta
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-25, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-25, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-15, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);

		glRotatef(-25, 0, 1, 0);                   ///curva2 parte alta
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-25, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-25, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-15, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);

		glRotatef(-45, 0, 0, 1);                   ///bajada1 
		glTranslatef(20, 7, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);

		glRotatef(45, 0, 0, 1);                 ///recta 2
		glTranslatef(20, -12, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);

		glRotatef(-25, 0, 1, 0);                   ///curva3 parte baja
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-25, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-25, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-15, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);

		glRotatef(-25, 0, 1, 0);                   ///curva4 parte baja
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-25, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-25, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);
		glRotatef(-15, 0, 1, 0);
		glTranslatef(20, 0, 0);
		fig3.prisma(5, 10, 30, madera.GLindex);

glPopMatrix();

glPushMatrix();

          glTranslatef(xc, xy, xz);          /////carro
		  glRotatef(ry, 0, 1, 0);
		  glRotatef(rz, 0, 0, 1);
          fig3.prisma(30, 40, 28,windows.GLindex);
               glPushMatrix();
                     glTranslatef(25, 0, 0);
                     fig3.prisma(15, 10, 15, windows.GLindex);                 ///punta carro
	           glPopMatrix();
			  
			   glPushMatrix();
			         glTranslatef(15, -15, -15);
			         glRotatef(90, 1, 0, 0);
			         fig3.cilindro(5, 1, 20, textPizarron.GLindex); ///llanta 1
			   glPopMatrix();

			   glPushMatrix();
			         glTranslatef(-15, -15, -15);
			         glRotatef(90, 1, 0, 0);
			         fig3.cilindro(5, 1, 20, textPizarron.GLindex); ///llanta 2
			   glPopMatrix();

			   glPushMatrix();
			         glTranslatef(-15, -15, 15);
			        glRotatef(90, 1, 0, 0);
			        fig3.cilindro(5, 1, 20, textPizarron.GLindex); ///llanta 3
			   glPopMatrix();

			   glPushMatrix();
			        glTranslatef(15, -15, 15);
			        glRotatef(90, 1, 0, 0);
			        fig3.cilindro(5, 1, 20, textPizarron.GLindex); ///llanta 4
			   glPopMatrix();

			   
glPopMatrix();






			/////////Camino de la Feria
			
         
          glPushMatrix();
				glPushMatrix();
					glTranslatef(0,0,0);
					glPushMatrix();
						glScalef(920,3,80);
						edificio.prisma3(pisoexterior1.GLindex, pisoexterior1.GLindex,5);//franja de en medio
					glPopMatrix();
					glTranslatef(500,0,0);
					glPushMatrix();
						glScalef(80,3,1000);
						edificio.prisma3(pisoexterior1.GLindex, pisoexterior1.GLindex,5);//parte derecha
					glPopMatrix();
					
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0, 0, -460);
				glScalef(920, 3, 80);
				edificio.prisma3(pisoexterior1.GLindex, pisoexterior1.GLindex, 5);//parte trasera
				glPopMatrix();


				glPushMatrix();
				glTranslatef(-500, 0, -230);
				glScalef(80, 3, 540);
			    edificio.prisma3(pisoexterior1.GLindex, pisoexterior1.GLindex, 5);//parte izquierda
				glPopMatrix();
			glPopMatrix();

			//////Arboles

			glPushMatrix();
			for (int i = 0; i < 1000; i+=80)
			{

				glPushMatrix();
				glTranslatef(570, 0, 500-i);
				glScalef(3, 8, 3);
				arbol2_alpha();                 ///arboles barda derecha
				glPopMatrix();
			}

			glPopMatrix();

			glPushMatrix();
			for (int i = 0; i < 1080; i += 80)
			{

				glPushMatrix();
				glTranslatef(570-i, 0, -530);
				glScalef(3, 8, 3);
				arbol2_alpha();                ///arboles barda trasera
				glPopMatrix();
			}

			glPopMatrix();

			glPushMatrix();
			for (int i = 0; i < 1080; i += 80)
			{

				glPushMatrix();
				glTranslatef(-570, 0, -530+i);
				glScalef(3, 8, 3);
				arbol2_alpha();                ///arboles barda izquierda
				glPopMatrix();
			}

			glPopMatrix();

			glPushMatrix();
			for (int i = 0; i < 470; i += 80)
			{

				glPushMatrix();
				glTranslatef(420, 0, 500 - i);
				glScalef(3, 8, 3);
				arbol2_alpha();                ///arboles barda entrada izquierda
				glPopMatrix();
			}

			glPopMatrix();



			glPushMatrix();
				glTranslatef(202.94, 0, 114.59);
				glScalef(3, 8, 3);
				pino2_alpha();
			glPopMatrix();


			glPushMatrix();
				glTranslatef(349.66, 0, -374.74);
				glScalef(3, 8, 3);
				arbol1_alpha();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-458.27, 0, -346.71);
				glScalef(3, 8, 3);
				arbol_alpha();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-204.69,0, -90.72);
				glScalef(3, 8, 3);
				pino2_alpha();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(154.83, 0, 399.27);
				glScalef(3, 8, 3);
				arbol2_alpha();
			glPopMatrix();

			
			glEnable(GL_LIGHTING);
			

			
			glDisable(GL_LIGHTING);
			glPushMatrix(); //Casa M0delo 3ds
				

			glTranslatef(0, 10, 0);
			glColor3f(0, 0, 0);

			glScalef(40, 40, 40);
			
			banca.GLrender(NULL, _SHADED, 1);
			glColor3f(1, 1, 1);
			glPopMatrix();

			glEnable(GL_LIGHTING);



		

			
			glPushMatrix(); //Casa M0delo 3ds
				
			   glTranslatef(posXhel, posYhel , posZhel);
				glRotatef(rot_helicoptero,0,1,0);
				glScalef(10, 10, 10);
				helicoptero.GLrender(NULL, _SHADED, 1);
			glPopMatrix();



			glPushMatrix();
				glTranslatef(-300, 0, 250);
				glScalef(3,8,3);
				arbol_alpha();
			glPopMatrix();

			glColor3f(1.0,1.0,1.0);

		glPopMatrix(); 

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Proyecto final");
			//pintaTexto(-11,10.5,-14,(void *)font,"Listas de Dibujo");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{

	clock_t currTime = clock();
	//double timeSincePrevFrame = double(currTime - prevTime)/CLOCKS_PER_SEC;
	double elapsedTime = 64*double(currTime - startTime) / CLOCKS_PER_SEC;
	fig3.text_izq-= 0.01;
	fig3.text_der-= 0.01;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;
	


	if (true)
	{
		
		if (baja)
		{
			altura -= 2;
			if (altura < 70)
			{
				sube = true;
				baja = false;
			}
		}
		if (sube)
		{
			altura += 2;
			if (altura > 300)
			{
				sube = false;
				baja = true;
			}
		}

	}

	if (true)
	{

		if (recta1) 
		{
			xc += 2;
			if (xc > -190)
			{
				recta1 = false;
				subida1 = true;
			}

		}

		if (subida1)
		{
			
		}




	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	dwCurrentTime = timeGetTime();//GetTickCount();
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 30)
	{
		//letras que se recorren a la derecha
		moveSkyI -= 0.000015;
		moveSkyF -= 0.000015;

	}


	if (true)
	{

		rot_helicoptero = fmod((elapsedTime * 2), 360);
		posXhel = -250 + cos(elapsedTime * PI / 180.0) * 50;
		posYhel = 250 + cos(elapsedTime * PI / 180.0) * 20 + sin(elapsedTime * PI / 180.0) * 20;
		posZhel = -250 + sin(elapsedTime * PI / 180.0) * 50;
		
	}
		
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 30)
	{
		giro = (giro + 5) % 360;
		

		dwLastUpdateTime = dwCurrentTime;
	}

	glutPostRedisplay();
	

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 3000.0);//170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		/*
		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
			*/
		case 'q':   //mostrar posicion de la camara
		case 'Q':
			//printf("pos: %.2f,%.2f,%.2f \n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
			printf("pos: %.2f,%.2f,%.2f,%.2f,%.2f,%.2f \n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z, objCamera.mView.x, objCamera.mView.y, objCamera.mView.z);
			//printf("lookupdown %.2f \n", g_lookupdown);
			//printf("view: %.2f,%.2f,%.2f \n", objCamera.mView.x, objCamera.mView.y, objCamera.mView.z);
			//printf("up: %.2f,%.2f,%.2f \n", objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
			break;
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.001 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.001));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.001));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+ 0.001);
			break;

		case 'O':		//  
		case 'o':
				g_fanimacion^= true; //Activamos/desactivamos la animacíon
				
			break;

		case 'i':		//  
		case 'I':
				 //Activamos/desactivamos la animacíon
				g_fanimacion = false;
			break;

		case 'k':		//
		case 'K':
			if (FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':
		case 'L':
			if (play == false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
			{
				play = false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			//printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			//printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			//printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			//printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			//printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			//printf("%f \n", rotRodIzq);
			break;

		case 'p':						
			giroMonito++;
			//printf("%f \n", giroMonito);
			break;

		case 'P':						
			giroMonito--;
			//printf("%f \n", giroMonito);
			break;
		case ' ':
			recta1 = true;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera((CAMERASPEED + 0.5));
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-(CAMERASPEED + 0.5));
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex >1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}


void menu(int id)
{

}

int main ( int argc, char** argv )   // Main Function
{
	int submenu;
	char soundfile[] = "01 Intro.wav";
	PlaySound((LPCSTR)soundfile, NULL, SND_FILENAME | SND_ASYNC);
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (1200, 900);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  startTime = glutGet(GLUT_ELAPSED_TIME);
  prevTime = startTime;


  submenu = glutCreateMenu(menuKeyFrame);
  glutAddMenuEntry("Guardar KeyFrame", 0);
  glutAddMenuEntry("Reproducir Animacion", 1);
  glutCreateMenu(menu);
  glutAddSubMenu("Animacion Monito", submenu);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop        ( );          // 

  return 0;
}
