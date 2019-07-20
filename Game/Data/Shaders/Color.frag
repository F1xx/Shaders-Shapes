varying vec4 v_Color;

void main()
{
	vec4 color = v_Color / 255.0;
    gl_FragColor = color;
}
