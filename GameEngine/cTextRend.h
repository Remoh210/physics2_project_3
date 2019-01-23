//#pragma once
//#include <string>
//#include <map>
//#include <vector>
//#include <glad\glad.h>
//#include <GLFW\glfw3.h>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//
//class cTextRend {
//
//public:
//	cTextRend();
//	bool init();
//	void renderText(const char *text, float x, float y, float sx, float sy);
//
//private:
//
//
//	GLboolean init_gl();
//
//	// Init FreeType stuff
//	GLboolean initfreetype();
//
//
//
//	// Render the FreeType text
//	
//
//	GLuint mvertex_shader;                              // Vertex Shader name
//	GLuint mfragment_shader;                            // Fragment Shader name
//	GLuint mprogramm;                                   // The Shader Program    
//	GLuint mvao;                                        // Vertex array object    
//	GLuint mdp_vbo;                                     // Vertex buffer object
//	GLint attribute_coord;                              // Attribute coordinate
//	GLint uniform_tex;                                  // Uniform texture
//	GLint uniform_color;                                // Unifor color
//	const char* mvs_text;                               // Vertex shader text
//	const char* mfs_text;                               // Fragment shader text
//	FT_Library mft;                                     // The FreeType font
//	FT_Face mface;                                      // The FreeType face
//	std::vector<std::wstring> m_vecStringsToDraw;       // The strings to be drawn  
//														// Current state of the localization
//
//	// Point struct to draw the box on screen
//	struct point
//	{
//		GLfloat x;
//		GLfloat y;
//		GLfloat s;
//		GLfloat t;
//	};
//};