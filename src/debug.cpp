/********************************************************************************
*********************************************************************************
	3KSC: A fighting game
    Copyright (C) 2018  Chaotic Games

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*********************************************************************************
*********************************************************************************/

#include "../headers/debug.hpp"

#include <GL/gl.h>
#include <GL/glut.h>

void Debug::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
    //set up vertex array
    GLfloat glverts[16]; //allow for polygons up to 8 vertices
    glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
    glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays
    
    //fill in vertex positions as directed by Box2D
    for (int i = 0; i < vertexCount; i++) {
        glverts[i*2]   = vertices[i].x;
        glverts[i*2+1] = vertices[i].y;
    }
    
    //draw solid area
    glColor4f( color.r, color.g, color.b, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
  
    //draw lines
    glLineWidth(3); //fat lines
    glColor4f( 1, 0, 1, 1 ); //purple
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}
