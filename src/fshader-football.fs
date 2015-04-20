
uniform sampler2D football_tex;

varying vec2 v_texcoord;



void main()
{

    gl_FragColor = texture2D(football_tex, v_texcoord);
}