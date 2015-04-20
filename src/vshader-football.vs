varying vec2 v_texcoord;
varying vec4 v_pos;



void main()
{

    v_pos = gl_Vertex;


    v_texcoord.x = (gl_Normal.x + 1) / 2.0;
    if(gl_Normal.y < 0) {
        v_texcoord.y = (-gl_Normal.z + 1) / 2.0;

    }
    else {
        v_texcoord.y = (glNormal.z + 1) / 2.0;
    }

   /* multiply each vertex with the ModelView Matrix and
       Projection Matrix */

    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

}