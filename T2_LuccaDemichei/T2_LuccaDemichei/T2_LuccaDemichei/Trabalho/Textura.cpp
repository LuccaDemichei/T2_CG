// **********************************************************************
// PUCRS/Escola Politécnica
// COMPUTAÇÃO GRÁFICA
//
// Programa básico para criar aplicacoes 3D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include "gl\glut.h"
    static DWORD last_idle_time;
#else
    #include <sys/time.h>
    static struct timeval last_idle_time;
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif


#include "SOIL/SOIL.h"

#include "TextureClass.h"

#include "ListaDeCoresRGB.h"

#include "Ponto.h"

GLfloat AspectRatio, AngY=0;
GLuint TEX0, TEX1, TEX2, TEX3, TEX4, TEX5, TEX7, TEX8, TEX9, TEX10, TEX11, TEX12;
bool ComTextura = true;

Ponto CantoEsquerdo = Ponto (-20,-1,-10);

double alvoX = 0.0;
double alvoY = 0.0;
double alvoZ = 0.0;

double visaoX = 0.0;
double visaoY = 1.0;
double visaoZ = -10.0;

//Movimento do carro
double posCarX = 0.0;
double posCarZ = 0.0;
double anguloCarro = 0.0;

double velocidadeCarro = 0;

class Elemento{
public:
    int idPosicao;
};

#define TERRENO 0
#define CROSS 1
#define DL 2
#define DLR 3
#define DR 4
#define LR 5
#define UD 6
#define UDL 7
#define UDR 8
#define UL 9
#define ULR 10
#define UR 11

//Dimensıes da cidade
int tamX = 6;
int tamZ = 6;

int Cidade1[5][5] = {
{0,1,0,2,0},
{0,1,0,2,0},
{0,1,0,2,0},
{0,1,0,2,0},
{0,1,0,2,0},
};

int Cidade[30][30] = {
{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
{4,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	3,	3,	5,	5,	5,	5,	5,	5,	3,	5,	5,	5,	5,	5,	5,	5},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	2,	5,	5,	5,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	7,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{9,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	1,	1,	5,	5,	5,	5,	5,	5,	1,	5,	5,	5,	5,	5,	5,	5},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{9,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	1,	1,	5,	5,	5,	5,	5,	5,	1,	5,	5,	5,	5,	5,	5,	5},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	7,	7,	0,	0,	0,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0},
{12,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	11,	11,	5,	5,	5,	5,	5,	5,	11,	5,	5,	5,	5,	5,	5,	5}
};

// **********************************************************************
//  void initTexture(void)
//        Define a textura a ser usada
//
// **********************************************************************
void initTexture (void)
{
    TEX0 = LoadTexture ("None.png");
    TEX1 = LoadTexture ("Cross.png");
    TEX2 = LoadTexture ("DL.png");
    TEX3 = LoadTexture ("DLR.png");
    TEX4 = LoadTexture ("DR.png");
    TEX5 = LoadTexture ("LR.png");
    TEX7 = LoadTexture ("UD.png");
    TEX8 = LoadTexture ("UDL.png");
    TEX9 = LoadTexture ("UDR.png");
    TEX10 = LoadTexture ("UL.png");
    TEX11 = LoadTexture ("ULR.png");
    TEX12 = LoadTexture ("UR.png");
}

// **********************************************************************
//  void DefineLuz(void)
// **********************************************************************
void DefineLuz(void)
{
  // Define cores para um objeto dourado
  GLfloat LuzAmbiente[]   = {0.4, 0.4, 0.4 } ;
  GLfloat LuzDifusa[]   = {0.7, 0.7, 0.7};
  GLfloat LuzEspecular[] = {0.9f, 0.9f, 0.9 };
  GLfloat PosicaoLuz0[]  = {0.0f, 3.0f, 5.0f };  // Posição da Luz
  GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f};

   // ****************  Fonte de Luz 0

 glEnable ( GL_COLOR_MATERIAL );

   // Habilita o uso de iluminação
  glEnable(GL_LIGHTING);

  // Ativa o uso da luz ambiente
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
  // Define os parametros da luz número Zero
  glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
  glEnable(GL_LIGHT0);

  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentraçãoo do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado será o brilho. (Valores válidos: de 0 a 128)
  glMateriali(GL_FRONT,GL_SHININESS,51);

}


// **********************************************************************
//  void init(void)
//		Inicializa os par‚metros globais de OpenGL
//
// **********************************************************************
void init(void)
{
	glClearColor(0.0f, 0.6f, 1.0f, 1.0f);

	glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	glEnable(GL_DEPTH_TEST);
	//glEnable ( GL_CULL_FACE );
    glDisable ( GL_CULL_FACE );

    glEnable(GL_NORMALIZE);
    initTexture();

}
// **********************************************************************
//  void PosicUser()
// **********************************************************************
void PosicUser()
{
	// Set the clipping volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,AspectRatio,0.01,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(visaoX, visaoY, visaoZ,   // Posição do Observador
              alvoX, alvoY, alvoZ,     // Posição do Alvo
              0.0f,1.0f,0.0f);


}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	AspectRatio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    //cout << "Largura" << w << endl;

	PosicUser();

}
// **********************************************************************
//   void DesenhaCubo (GLuint nro_da_textura)
//
//
// **********************************************************************
void DesenhaCarro(){
    //Desenha carcaca
    glPushMatrix();
        glColor3f(0.0,0.0,1.0);
        glScalef(2.0, 0.5, 1.0);
        glutSolidCube(1);
        glVertex3f(-1.0,0.0,1.0);
        glVertex3f(1.0,0.0,1.0);
        glVertex3f(0.8,-0.0,1.0);
        glVertex3f(-0.8,-0.0,1.0);
    glPopMatrix();

    glScalef(0.8, 0.8, 0.8);

    glPushMatrix();
        glBegin(GL_QUADS);
        glutSolidCube(1);
        glVertex3f(-1.0,0.5,-1.0);
        glVertex3f(1.0,0.5,-1.0);
        glVertex3f(0.8,-0.5,-1.0);
        glVertex3f(-0.8,-0.5,-1.0);
        glEnd();
    glPopMatrix();

    //Roda 1
    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
        glTranslatef(-0.7,-0.7,-0.5);
        glutSolidTorus(0.1,0.3,10,10);
    glPopMatrix();
    //Roda 2
    glPushMatrix();
        glTranslatef(0.7,-0.7,-0.5);
        glutSolidTorus(0.1,0.3,10,10);
    glPopMatrix();
    //Roda 3
    glPushMatrix();
        glTranslatef(-0.7,-0.7,0.5);
        glutSolidTorus(0.1,0.3,10,10);
    glPopMatrix();
    //Roda 4
    glPushMatrix();
        glTranslatef(0.7,-0.7,0.5);
        glutSolidTorus(0.1,0.3,10,10);
    glPopMatrix();
}

void DesenhaCubo ()
{
    glBegin ( GL_QUADS );

    // Front Face
    glNormal3f(0,0,1);
    glTexCoord2f(0.5f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    glTexCoord2f(1.0f, 0.5f);
    glVertex3f( 1.0f,  1.0f,  1.0f);

    glTexCoord2f(0.5f, 0.5);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    // Back Face
    glNormal3f(0,0,-1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Top Face
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Bottom Face
    glNormal3f(0,-1,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    // Right face
    glNormal3f(1,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    // Left Face
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();

}
// **********************************************************************
// void DesenhaLadrilho(int idTextura)
// Desenha uma célula do piso.
// Eh possivel definir a cor da borda e do interior do piso
// O ladrilho tem largula 1, centro no (0,0,0) e está sobre o plano XZ
// **********************************************************************
void DesenhaQuadrado(int idTextura)
{

    glBegin ( GL_QUADS );
        glNormal3f(0,1,0);
        glVertex3f(-0.5f,  0.0f, -0.5f);
        glVertex3f(-0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f, -0.5f);
    glEnd();
}
// **********************************************************************
// void DesenhaLadrilho(int corBorda, int corDentro)
// Desenha uma célula do piso.
// Eh possivel definir a cor da borda e do interior do piso
// O ladrilho tem largula 1, centro no (0,0,0) e está sobre o plano XZ
// **********************************************************************
void DesenhaQuadrado(int corBorda, int corDentro)
{

    defineCor(corBorda); // desenha QUAD preenchido
    glBegin ( GL_QUADS );
        glNormal3f(0,1,0);
        glVertex3f(-0.5f,  0.0f, -0.5f);
        glVertex3f(-0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f, -0.5f);
    glEnd();

    defineCor(corDentro);
    glBegin ( GL_LINE_STRIP );
        glNormal3f(0,1,0);
        glVertex3f(-0.5f,  0.0f, -0.5f);
        glVertex3f(-0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f, -0.5f);
    glEnd();

}
// **********************************************************************
// void DesenhaLadrilho(int corBorda, int corDentro)
// Desenha uma célula do piso.
// Eh possivel definir a cor da borda e do interior do piso
// O ladrilho tem largula 1, centro no (0,0,0) e está sobre o plano XZ
// **********************************************************************
void DesenhaLadrilho(int corBorda, int corDentro)
{
    corDentro = Green;
    defineCor(corDentro);// desenha QUAD preenchido
    glBegin ( GL_QUADS );
        //glBindTexture (GL_TEXTURE_2D, TEX1);
        glNormal3f(0,1,0);
        glVertex3f(-0.5f,  0.0f, -0.5f);
        glVertex3f(-0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f, -0.5f);
    glEnd();

    //defineCor(corBorda);
    glColor3f(0,0,0);

    glBegin ( GL_LINE_STRIP );
        glNormal3f(0,1,0);
        glVertex3f(-0.5f,  0.0f, -0.5f);
        glVertex3f(-0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f, -0.5f);
    glEnd();
}

// **********************************************************************\
//
// **********************************************************************
void DesenhaLadrilho(int textura)
{
    defineCor(textura);
    glBegin ( GL_QUADS );
        glNormal3f(0,1,0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.5f,  0.0f, -0.5f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5f,  0.0f,  0.5f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 0.5f,  0.0f,  0.5f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 0.5f,  0.0f, -0.5f);
    glEnd();

    glColor3f(0,0,0);
    glBegin ( GL_LINE_STRIP );
        glNormal3f(0,1,0);
        glVertex3f(-0.5f,  0.0f, -0.5f);
        glVertex3f(-0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f,  0.5f);
        glVertex3f( 0.5f,  0.0f, -0.5f);
    glEnd();


}

void DesenhaPiso()
{
    //srand(100); // usa uma semente fixa para gerar sempre as mesma cores no piso
    glPushMatrix();
    glTranslated(CantoEsquerdo.x, CantoEsquerdo.y, CantoEsquerdo.z);
    for(int x=0; x<30; x++)
    {
        glPushMatrix();
        for(int z=0; z<30; z++)
        {
            int aux = 0;
            if(Cidade[z][x] == 0){
                    glBindTexture(GL_TEXTURE_2D, TEX0);
                    aux = TEX0;
                } else if(Cidade[z][x] == 1){
                    glBindTexture(GL_TEXTURE_2D, TEX1);
                    aux = TEX1;
                } else if(Cidade[z][x] == 2){
                    glBindTexture(GL_TEXTURE_2D, TEX2);
                    aux = TEX2;
                } else if(Cidade[z][x] == 3){
                    glBindTexture(GL_TEXTURE_2D, TEX3);
                    aux = TEX3;
                } else if(Cidade[z][x] == 4){
                    glBindTexture(GL_TEXTURE_2D, TEX4);
                    aux = TEX4;
                } else if(Cidade[z][x] == 5){
                    glBindTexture(GL_TEXTURE_2D, TEX5);
                    aux = TEX5;
                } else if(Cidade[z][x] == 12){
                    glBindTexture(GL_TEXTURE_2D, TEX12);
                    aux = TEX12;
                } else if(Cidade[z][x] == 7){
                    glBindTexture(GL_TEXTURE_2D, TEX7);
                    aux = TEX7;
                } else if(Cidade[z][x] == 8){
                    glBindTexture(GL_TEXTURE_2D, TEX8);
                    aux = TEX8;
                } else if(Cidade[z][x] == 9){
                    glBindTexture(GL_TEXTURE_2D, TEX9);
                    aux = TEX9;
                } else if(Cidade[z][x] == 10){
                    glBindTexture(GL_TEXTURE_2D, TEX10);
                    aux = TEX10;
                } else {
                    glBindTexture(GL_TEXTURE_2D, TEX11);
                    aux = TEX11;
                }
            DesenhaLadrilho(aux);
            glTranslated(0,0,1);
        }
        glPopMatrix();
        glTranslated(1, 0, 0);
    }
    glPopMatrix();
}
// **********************************************************************
//  void display( void )
//
//
// **********************************************************************
void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //DefineLuz();
	PosicUser();

	glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);

    if (ComTextura)
        glEnable(GL_TEXTURE_2D);
    else glDisable(GL_TEXTURE_2D);

    if (glIsEnabled(GL_TEXTURE_2D))
        glColor3f(1,1,1);
    else glColor3f(0.5, 0, 0);

    if (glIsEnabled(GL_TEXTURE_2D))
        glColor3f(1,1,1);
    else glColor3f(0.5f,0.0f,0.0f); // Vermelho

    glPushMatrix();
        DesenhaPiso();
    glPopMatrix();


	glPushMatrix();
        glTranslatef ( 5.0f, 0.0f, 3.0f );
        glRotatef(AngY,0,1,0);
        glBindTexture (GL_TEXTURE_2D, TEX3);
		DesenhaCubo();
	glPopMatrix();

    if (glIsEnabled(GL_TEXTURE_2D))
        glColor3f(1,1,1);
    else glColor3f(0.6156862745, 0.8980392157, 0.9803921569); // Azul claro

	glPushMatrix();
        glTranslatef ( -4.0f, 8.0f, 2.0f );
		glRotatef(AngY,0,1,0);
        glBindTexture (GL_TEXTURE_2D, TEX3);
		DesenhaCubo();
	glPopMatrix();

    glPushMatrix();
        glTranslatef(posCarX, 0.0, posCarZ);
        glRotatef(anguloCarro,0.0,1.0,0.0);
        DesenhaCarro();
    glPopMatrix();

	glutSwapBuffers();
}

// **********************************************************************
//  void animate ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void animate()
{
    // Anima cubos
    AngY++;

    // Redesenha
    glutPostRedisplay();
}

// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
    case 27:        // Termina o programa qdo
      exit ( 0 );   // a tecla ESC for pressionada
      break;
    case 't':
        ComTextura = !ComTextura;
        break;
    case 'i':
			visaoY += 2;
			break;
	case 'o':
			visaoY -= 2;
			break;
	case 'j':
			alvoZ -= 2;
			break;
	case 'k':
			alvoZ += 2;
			break;
	case 'l':
			alvoX -= 2;
			break;
	case 'h':
			alvoX += 2;
			break;
    case 'w':
			visaoZ++;
			alvoZ++;
			break;
    case 's':
			visaoZ--;
			alvoZ--;
			break;
    case 'a':
			visaoX++;
			alvoX++;
			break;
    case 'd':
			visaoX--;
			alvoX--;
			break;
    default:
            cout << key;
      break;
  }

  glutPostRedisplay();
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
    double velocidade = 0.2;

	switch ( a_keys )
	{
        case GLUT_KEY_DOWN:
            posCarZ -= velocidade;
            anguloCarro = 90;
            break;
        case GLUT_KEY_UP:
            posCarZ += velocidade;
            anguloCarro = 90;
            break;
        case GLUT_KEY_RIGHT:
            posCarX -= velocidade;
            anguloCarro = 0;
            break;
        case GLUT_KEY_LEFT:
            posCarX += velocidade;
            anguloCarro = 0;
            break;
		default:
			break;
    glutPostRedisplay();
	}
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main ( int argc, char** argv )
{

	glutInit            ( &argc, argv );
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
	glutInitWindowPosition (0,0);
	glutInitWindowSize  ( 700, 700 );
	glutCreateWindow    ( "Computacao Grafica - Exemplo com Textura 3D" );

	init ();
    //system("pwd");

	glutDisplayFunc ( display );
	glutReshapeFunc ( reshape );
	glutKeyboardFunc ( keyboard );
	glutSpecialFunc ( arrow_keys );
	glutIdleFunc ( animate );

	glutMainLoop ( );
	return 0;
}



