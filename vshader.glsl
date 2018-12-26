#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

attribute vec4 a_position;
attribute vec3 a_color;

varying vec4 v_color;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    v_color = vec4(a_color, 0.5f);
}
