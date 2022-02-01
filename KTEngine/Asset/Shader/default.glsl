#version 460 core

layout(location = 0) in vec3 aPos;


out VS_OUT{
	vec3 pos;

} vs_out;

void main() {
	vs_out.pos = aPos;

	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}


#type - delim

#version 460 core

out vec4 out_color;
uniform float u_Time;
in VS_OUT{
	vec3 pos;
} vs_in;

void main() {
	float time = cos(u_Time) * 0.5f + 0.5f;
	out_color = vec4(0.0f, time, 1 - time, 1.0f);
}

