varying vec2 v_texcoord;
varying vec4 v_pos;



void main()
{

    v_pos = gl_Vertex;

    /* multiply each vertex with the ModelView Matrix and
       Projection Matrix */

    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

}