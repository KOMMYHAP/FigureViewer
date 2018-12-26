#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

varying vec4 v_color;

void main()
{
    // Set fragment color
    gl_FragColor = v_color;
}