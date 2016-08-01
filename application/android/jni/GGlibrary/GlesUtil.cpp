///
//  Includes
//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include "GlobalFun.h"
#include "GlesUtil.h"

GLuint		gProObject;
ESMatrix 	gOrthographic;
ESMatrix 	gMatrix;

GLint	gShaderPosition;
GLint	gShaderTexCoord;
GLint 	gShaderImgTexture;
GLint	gvpMatrix;

//GLint 	gColorFlag;
GLint 	gColorLoc;

GLuint	gTextureTmp;
GLuint	gMainTexture;
GLuint	gFrameBuffer;
GLuint	gBufferData;
int 	gWidthd2;
int		gHeightd2;
EGLConfig config;
EGLSurface gSurface;
EGLDisplay gDisplay;
EGLContext gContext;
EGLContext gShareContext;
ANativeWindow *gANativeWindow = NULL;
bool windowViewInitGL_success=false;
bool first=true;
int firstWidth=0;
int firstHeight=0;
int bwMode=10;
#define PI 3.1415926535897932384626433832795f
#define ES_PI  (3.14159265f)
static ANativeWindow *GLwindow ;
static EGLDisplay GLdisplay;

ANativeWindow *GetWindow(){
	LOGE("Got GLwindow %p", GLwindow);
	return GLwindow;
}

EGLDisplay GetDisplay()
{
	LOGE("Got EGLDisplay %p", GLdisplay);
	return GLdisplay;
}

void SetWindow(ANativeWindow *window,EGLDisplay display){
	GLwindow=window;
	GLdisplay=display;
}

void esScale(ESMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz)
{
    result->m[0][0] *= sx;
    result->m[0][1] *= sx;
    result->m[0][2] *= sx;
    result->m[0][3] *= sx;

    result->m[1][0] *= sy;
    result->m[1][1] *= sy;
    result->m[1][2] *= sy;
    result->m[1][3] *= sy;

    result->m[2][0] *= sz;
    result->m[2][1] *= sz;
    result->m[2][2] *= sz;
    result->m[2][3] *= sz;
}

void esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz)
{
    result->m[3][0] += (result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz);
    result->m[3][1] += (result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz);
    result->m[3][2] += (result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz);
    result->m[3][3] += (result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz);
}

void esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
   GLfloat sinAngle, cosAngle;
   GLfloat mag = sqrtf(x * x + y * y + z * z);

   sinAngle = sinf ( angle * PI / 180.0f );
   cosAngle = cosf ( angle * PI / 180.0f );
   if ( mag > 0.0f )
   {
      GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
      GLfloat oneMinusCos;
      ESMatrix rotMat;

      x /= mag;
      y /= mag;
      z /= mag;

      xx = x * x;
      yy = y * y;
      zz = z * z;
      xy = x * y;
      yz = y * z;
      zx = z * x;
      xs = x * sinAngle;
      ys = y * sinAngle;
      zs = z * sinAngle;
      oneMinusCos = 1.0f - cosAngle;

      rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
      rotMat.m[0][1] = (oneMinusCos * xy) - zs;
      rotMat.m[0][2] = (oneMinusCos * zx) + ys;
      rotMat.m[0][3] = 0.0F;

      rotMat.m[1][0] = (oneMinusCos * xy) + zs;
      rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
      rotMat.m[1][2] = (oneMinusCos * yz) - xs;
      rotMat.m[1][3] = 0.0F;

      rotMat.m[2][0] = (oneMinusCos * zx) - ys;
      rotMat.m[2][1] = (oneMinusCos * yz) + xs;
      rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
      rotMat.m[2][3] = 0.0F;

      rotMat.m[3][0] = 0.0F;
      rotMat.m[3][1] = 0.0F;
      rotMat.m[3][2] = 0.0F;
      rotMat.m[3][3] = 1.0F;

      esMatrixMultiply( result, &rotMat, result );
   }
}

void esFrustum(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;
    ESMatrix    frust;

    if ( (nearZ <= 0.0f) || (farZ <= 0.0f) ||
         (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f) )
         return;

    frust.m[0][0] = 2.0f * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

    frust.m[1][1] = 2.0f * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

    frust.m[2][0] = (right + left) / deltaX;
    frust.m[2][1] = (top + bottom) / deltaY;
    frust.m[2][2] = -(nearZ + farZ) / deltaZ;
    frust.m[2][3] = -1.0f;

    frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

    esMatrixMultiply(result, &frust, result);
}


void esPerspective(ESMatrix *result, float fovy, float aspect, float nearZ, float farZ)
{
   GLfloat frustumW, frustumH;

   frustumH = tanf( fovy / 360.0f * PI ) * nearZ;
   frustumW = frustumH * aspect;

   esFrustum( result, -frustumW, frustumW, -frustumH, frustumH, nearZ, farZ );
}

void esOrtho(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;
    ESMatrix    ortho;

    if ( (deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f) )
        return;

    esMatrixLoadIdentity(&ortho);
    ortho.m[0][0] = 2.0f / deltaX;
    ortho.m[3][0] = -(right + left) / deltaX;
    ortho.m[1][1] = 2.0f / deltaY;
    ortho.m[3][1] = -(top + bottom) / deltaY;
    ortho.m[2][2] = -2.0f / deltaZ;
    ortho.m[3][2] = -(nearZ + farZ) / deltaZ;

    esMatrixMultiply(result, &ortho, result);
}


void esMatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB)
{
    ESMatrix    tmp;
    int         i;

	for (i=0; i<4; i++)
	{
		tmp.m[i][0] =	(srcA->m[i][0] * srcB->m[0][0]) +
						(srcA->m[i][1] * srcB->m[1][0]) +
						(srcA->m[i][2] * srcB->m[2][0]) +
						(srcA->m[i][3] * srcB->m[3][0]) ;

		tmp.m[i][1] =	(srcA->m[i][0] * srcB->m[0][1]) +
						(srcA->m[i][1] * srcB->m[1][1]) +
						(srcA->m[i][2] * srcB->m[2][1]) +
						(srcA->m[i][3] * srcB->m[3][1]) ;

		tmp.m[i][2] =	(srcA->m[i][0] * srcB->m[0][2]) +
						(srcA->m[i][1] * srcB->m[1][2]) +
						(srcA->m[i][2] * srcB->m[2][2]) +
						(srcA->m[i][3] * srcB->m[3][2]) ;

		tmp.m[i][3] =	(srcA->m[i][0] * srcB->m[0][3]) +
						(srcA->m[i][1] * srcB->m[1][3]) +
						(srcA->m[i][2] * srcB->m[2][3]) +
						(srcA->m[i][3] * srcB->m[3][3]) ;
	}
    memcpy(result, &tmp, sizeof(ESMatrix));
}


void esMatrixLoadIdentity(ESMatrix *result)
{
    memset(result, 0x0, sizeof(ESMatrix));
    result->m[0][0] = 1.0f;
    result->m[1][1] = 1.0f;
    result->m[2][2] = 1.0f;
    result->m[3][3] = 1.0f;
}


GLuint esLoadShader ( GLenum type,  const char *shaderSrc )
{
   GLuint shader;
   GLint compiled;

   // Create the shader object
   shader = glCreateShader ( type );

   if ( shader == 0 )
   	return 0;

   // Load the shader source
   glShaderSource ( shader, 1, &shaderSrc, NULL );

   // Compile the shader
   glCompileShader ( shader );

   // Check the compile status
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled )
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

      if ( infoLen > 1 )
      {
         char* infoLog = (char *)malloc (sizeof(char) * infoLen );

         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );

         free ( infoLog );
      }

      glDeleteShader ( shader );
      return 0;
   }

   return shader;

}


//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
GLuint esLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc )
{
   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObject;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = esLoadShader ( GL_VERTEX_SHADER, vertShaderSrc );
   if ( vertexShader == 0 )
      return 0;

   fragmentShader = esLoadShader ( GL_FRAGMENT_SHADER, fragShaderSrc );
   if ( fragmentShader == 0 )
   {
      glDeleteShader( vertexShader );
      return 0;
   }

   // Create the program object
   programObject = glCreateProgram ( );

   if ( programObject == 0 )
      return 0;

   glAttachShader ( programObject, vertexShader );
   glAttachShader ( programObject, fragmentShader );

   // Link the program
   glLinkProgram ( programObject );

   // Check the link status
   glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

   if ( !linked )
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );

      if ( infoLen > 1 )
      {
         char* infoLog = (char *)malloc (sizeof(char) * infoLen );
         glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
         free ( infoLog );
      }

      glDeleteProgram ( programObject );
      return 0;
   }

   // Free up no longer needed shader resources
   glDeleteShader ( vertexShader );
   glDeleteShader ( fragmentShader );

   return programObject;
}

/////////////////////////////////////////////////////////////////

GLint CreateGlesEnv( )
{
	static char vShaderStr[] =
		"uniform mat4 u_TransMatrix;					\n"
		"attribute vec4 a_position;   					\n"
		"attribute vec2 a_texCoord;   					\n"
		"varying vec2 v_texCoord;    	 				\n"
		"void main()                  					\n"
		"{                            					\n"
		"   gl_Position = u_TransMatrix * a_position; 	\n"
		"   v_texCoord = a_texCoord;  					\n"
		"}                            					\n";

	static char fShaderStr[] =
	  "precision mediump float;                            		\n"
	  "varying vec2 v_texCoord;    	 							\n"
	  "uniform sampler2D s_ImgTexture;                     		\n"
	  //"uniform int specColorFlag; 						   		\n"
	  "uniform vec4 specColor; 							   		\n"
	  "void main()                                         		\n"
	  "{                                                   		\n"
	  "	   gl_FragColor = texture2D( s_ImgTexture, v_texCoord );\n"
	  //" if (specColorFlag == 0) 								\n"
	  //" {gl_FragColor = texture2D( s_ImgTexture, v_texCoord );} \n"
	  //" else {gl_FragColor = specColor;} 						\n"
	  "}                                                   		\n";

	//esOrtho(&gOrthographic, -100, 100, -100, 100, 5.0f, -5.0f );


	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = esLoadShader ( GL_VERTEX_SHADER, vShaderStr );
	if ( vertexShader == 0 )
	  return 0;

	fragmentShader = esLoadShader ( GL_FRAGMENT_SHADER, fShaderStr );
	if ( fragmentShader == 0 )
	{
	  glDeleteShader( vertexShader );
	  return 0;
	}

	gProObject = glCreateProgram ( );

	glAttachShader ( gProObject, vertexShader );
	glAttachShader ( gProObject, fragmentShader );

	// Link the program
	glLinkProgram ( gProObject );

	// Check the link status
	glGetProgramiv ( gProObject, GL_LINK_STATUS, &linked );

	if ( !linked )
	{
	  GLint infoLen = 0;

	  glGetProgramiv ( gProObject, GL_INFO_LOG_LENGTH, &infoLen );

	  if ( infoLen > 1 )
	  {
		 char* infoLog = (char *)malloc (sizeof(char) * infoLen );

		 glGetProgramInfoLog ( gProObject, infoLen, NULL, infoLog );
		 free ( infoLog );
	  }

	  glDeleteProgram ( gProObject );
	  return 0;
	}

	// Free up no longer needed shader resources
	glDeleteShader ( vertexShader );
	glDeleteShader ( fragmentShader );

	gShaderPosition = glGetAttribLocation ( gProObject, "a_position" );
	gShaderTexCoord = glGetAttribLocation ( gProObject, "a_texCoord" );

	gvpMatrix 	     = glGetUniformLocation( gProObject, "u_TransMatrix" );
	gShaderImgTexture = glGetUniformLocation ( gProObject, "s_ImgTexture" );

	//gColorFlag		= glGetUniformLocation( gProObject, "specColorFlag" );
	gColorLoc		= glGetUniformLocation( gProObject, "specColor" );

    //glEnable (GL_BLEND);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);

	glGenTextures(1, &gMainTexture );
	//glGenTextures(1, &gTextureTmp);

//	glGenBuffers(1, &gBufferData );

	//GlesBindOffScreen();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, gMainTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			gWidth,
			gHeight,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			NULL );

	return gProObject;
}

void GlesBindOffScreen()
{
	glGenFramebuffers(1, &gFrameBuffer);
	glBindTexture(GL_TEXTURE_2D, gMainTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gWidth, gHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gMainTexture, 0);
	return;
}

void GlesEnvChanged(  int width, int height )
{
	gWidthd2 = width / 2;
	gHeightd2 = height / 2;

	esMatrixLoadIdentity( &gOrthographic );
	//esOrtho(&gOrthographic, 0, mWidth, -mHeight, 0, 5.0f, -5.0f );
	esOrtho(&gOrthographic, -gWidthd2, gWidthd2, -gHeightd2, gHeightd2, 5.0f, -5.0f );

	ESMatrix modelview;
	esMatrixLoadIdentity( &gMatrix );
	esMatrixLoadIdentity( &modelview );
	esMatrixMultiply( &gMatrix, &modelview, &gOrthographic );

	glViewport(0, 0, width, height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, gMainTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			NULL );
	return;
}

void LoadImgDataTextuer( GLuint textureID, int width, int height, unsigned char * data )
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(GL_TEXTURE_2D,
			0,
			0,
			0,
			width,
			height,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data );//

	return;
}

void GlesPaintTexture( GLuint textureID, int dl, int dt, int dr, int db,
		GLfloat sl, GLfloat st, GLfloat sr, GLfloat sb )
{
	// left  = rt.left - gwidht / 2
	// top  = gheight/2 - rt.top
	ESMatrix matrixTrans;
	ESMatrix modelview;
	esMatrixLoadIdentity( &modelview );

	//esTranslate( &modelview, -fx, fy, 0.0 );
	esMatrixMultiply( &matrixTrans, &modelview, &gOrthographic );

	GLfloat posl = dl - gWidthd2;
	GLfloat posr = dr - gWidthd2;
	GLfloat post = gHeightd2 - dt;
	GLfloat posb = gHeightd2 - db;

	GLfloat ul = sl / (GLfloat)gWidth;
	GLfloat ur = sr / (GLfloat)gWidth;
	GLfloat vt = st / (GLfloat)gHeight;
	GLfloat vb = sb / (GLfloat)gHeight;

	GLfloat vVertices[] =
	{
		// x,	y,		z,		u,		v
		 posl, post, 0.0f, 	ul, vt,		// TexCoord 0
		 posl, posb, 0.0f,	ul, vb,		// TexCoord 1
		 posr, posb, 0.0f,	ur, vb,  	// TexCoord 2
		 posr, post, 0.0f,	ur, vt		// TexCoord 3
	};

	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	// Use the program object
	glUseProgram ( gProObject );

	// Load the vertex position
	glVertexAttribPointer ( gShaderPosition, 3, GL_FLOAT,
						   GL_FALSE, 5 * sizeof(GLfloat), vVertices );
	glEnableVertexAttribArray ( gShaderPosition );

	// Load the texture coordinate
	glVertexAttribPointer ( gShaderTexCoord, 2, GL_FLOAT,
						   GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );
	glEnableVertexAttribArray ( gShaderTexCoord );

	//glUniform1i ( gColorFlag, 0 );
	// Bind the base map
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, gMainTexture );

	glUniformMatrix4fv( gvpMatrix, 1, GL_FALSE, (GLfloat *)&matrixTrans );

	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );

}

void LoadImgDataTex( int width, int height, unsigned char * data )
{
	glBindTexture(GL_TEXTURE_2D, gMainTexture);
	glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data );
	return;
}

void SetDrawOffScreen(bool bOffScreen )
{
	if ( bOffScreen )
	{
		glBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void GlesPaint( )
{
	ESMatrix matrixTrans;
	ESMatrix modelview;
	esMatrixLoadIdentity( &modelview );

	//esTranslate( &modelview, -fx, fy, 0.0 );
	esMatrixMultiply( &matrixTrans, &modelview, &gOrthographic );

	GLfloat vVertices[] =
	{
		 -gWidthd2, gHeightd2, 	0.0f, 	0.0f, 0.0f,		// TexCoord 0
		 -gWidthd2, -gHeightd2 , 0.0f,	0.0f, 1.0f,		// TexCoord 1
		 gWidthd2, 	-gHeightd2 ,	0.0f,	1.0f, 1.0f,  	// TexCoord 2
		 gWidthd2, 	gHeightd2, 	0.0f,	1.0f, 0.0f		// TexCoord 3
	};

	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	// Use the program object
	glUseProgram ( gProObject );

	// Load the vertex position
	glVertexAttribPointer ( gShaderPosition, 3, GL_FLOAT,
						   GL_FALSE, 5 * sizeof(GLfloat), vVertices );
	glEnableVertexAttribArray ( gShaderPosition );

	// Load the texture coordinate
	glVertexAttribPointer ( gShaderTexCoord, 2, GL_FLOAT,
						   GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );
	glEnableVertexAttribArray ( gShaderTexCoord );

	//glUniform1i ( gColorFlag, 0 );
	// Bind the base map
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, gMainTexture );
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glBindBuffer(GL_ARRAY_BUFFER, gBufferData );

	glUniformMatrix4fv( gvpMatrix, 1, GL_FALSE, (GLfloat *)&matrixTrans );

	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
	//glDisableClientState(GL_VERTEX_ARRAY);
	return;
}

void GlesFlush()
{
	glFlush();
}

int GlesInitDisplay()
{
	LOGWHERE();
    const EGLint attribs[] =
    {
    	EGL_SURFACE_TYPE,   EGL_PBUFFER_BIT,
		//EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		//EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 16,
		EGL_BUFFER_SIZE, 32,
		EGL_STENCIL_SIZE, 8,
		EGL_NONE
    };

    EGLint numConfigs;
    EGLint format;
    EGLint width;
    EGLint height;
    EGLint contextAtt[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    eglBindAPI(EGL_OPENGL_ES_API);

	gDisplay = eglGetDisplay( EGL_DEFAULT_DISPLAY );
	eglInitialize( gDisplay, 0, 0 );
	eglChooseConfig( gDisplay, attribs, &config, 1, &numConfigs );
	eglGetConfigAttrib( gDisplay, config, EGL_NATIVE_VISUAL_ID, &format );
	ANativeWindow_setBuffersGeometry( gANativeWindow, 0, 0, format);

	gSurface = eglCreateWindowSurface( gDisplay, config, gANativeWindow, NULL);
	gContext = eglCreateContext( gDisplay, config, EGL_NO_CONTEXT, contextAtt);
	gShareContext = eglCreateContext( gDisplay, config, gContext, contextAtt);

	return 0;

}

int GlesDrawEachFrame()
{
	static float fr = 0.0f;
	fr += 0.1;
	if( fr > 1.0 )
		fr = 0.0;
	LOGE("Line:%d,%f", __LINE__, fr );

}

int FlushBuffer()
{
	eglSwapBuffers( gDisplay, gSurface);
}

int GlesTermDisplay()
{
	if( gDisplay != EGL_NO_DISPLAY )
	{
		eglMakeCurrent( gDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
		if( gContext != EGL_NO_CONTEXT )
		{
			eglDestroyContext( gDisplay, gContext );
		}
		if( gSurface != EGL_NO_SURFACE )
		{
			eglDestroySurface( gDisplay, gSurface );
		}
		eglTerminate( gDisplay );
	}
}

void MakeCurrent( bool b )
{
	if( b )
	{
		if (eglMakeCurrent(gDisplay, gSurface, gSurface, gContext) == EGL_FALSE)
		{
			LOGE("Unable to eglMakeCurrent");
		}
	}
	else
	{
		if (eglMakeCurrent(gDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) == EGL_FALSE)
		{
			LOGWHEREMSG("Release MakeCurrent Error");
		}
	}
	return;
}

void UsePrograme()
{
	glUseProgram( gProObject );
}

