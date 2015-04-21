varying vec2 v_texcoord;
varying vec4 v_pos;



void main()
{

    v_pos = gl_Vertex;
    
    v_texcoord.x = min(max((v_pos.y - 20.0)/480.0, 0.0),1.0);
    v_texcoord.y = min(max((v_pos.x - 125.0)/200.0, 0.0), 1.0);

    /* multiply each vertex with the ModelView Matrix and
       Projection Matrix */

    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

}