attribute vec4 a_Position;
attribute vec4 a_Color;

varying vec4 v_Color;

uniform vec2 u_Offset;
uniform vec2 u_Center;

uniform vec2 u_Translation;
uniform float u_Scale;
uniform float u_Rotation;
uniform float u_CameraScale;

//Rotates about the object's center
vec2 Rotate(float radians)
{
	float s = sin(radians);
	float c = cos(radians);

	float tempx = a_Position.x - u_Center.x;
	float tempy = a_Position.y - u_Center.y;

	float newx = tempx * c - tempy * s;
	float newy = tempx * s + tempy * c;

	return vec2(newx + u_Center.x, newy + u_Center.y);
}

void main()
{
	v_Color = a_Color;

	vec4 objectpos = a_Position;
		
	objectpos.w /= u_Scale / u_CameraScale; //Scale

	if(u_Rotation != 0.0) //only rotate if the object is actually rotated since sin/cos is heavy
	{
		objectpos.xy = Rotate(u_Rotation); //Rotate
	}

	objectpos.xy += u_Offset; //translate to where the are
	objectpos.xy += (u_Translation * -1.0); //translate to camera
	objectpos.xy += 300.0; //Move back to the center of the screen
	objectpos.xy += vec2(1.0/60.0, 1.0/60.0); //projection 

	//convert to 0-600xy coordinates
	objectpos.xy = ((objectpos.xy / 300.0) - 1.0);

	//pls gib me matrix

	gl_Position = objectpos;
}
