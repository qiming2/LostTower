#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aUV;

out VS_OUT{
	vec3 pos;
	vec3 color;
	vec2 uv;
} vs_out;

void main() {
	vs_out.pos = aPos;
	vs_out.color = aColor;
	vs_out.uv = aUV;
	gl_Position = vec4(aPos, 1.0);
}


#type-delim

#version 460 core

out vec4 out_color;
in VS_OUT{
	vec3 pos;
	vec3 color;
	vec2 uv;
} vs_in;

void main() {
	out_color = vec4(vs_in.color, 1.0);
}

