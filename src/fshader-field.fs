
uniform sampler2D field_tex;

varying vec2 v_texcoord;

varying vec4 v_pos;




void main()
{
    
    gl_FragColor = texture2D(field_tex, v_texcoord);
}