
uniform sampler2D field_tex

varying vec2 v_texcoord;

varying vec4 v_pos;




void main()
{
    v_texcoord.x = min(max((v_pos.y + 240.0)/480.0, 0.0),1.0);
    v_texcoord.y = min(max((v_pos.x + 100.0)/200.0, 0.0), 1.0);
    
    gl_FragColor = texture2D(marbi_tex, v_texcoord);
}