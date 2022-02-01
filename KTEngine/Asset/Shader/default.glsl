#version 460 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;


out VS_OUT{
	vec2 pos;
	vec2 uv;
} vs_out;

void main() {
	vs_out.pos = aPos;
	vs_out.uv = aUV;
	// -1.0 to 1.0
	gl_Position = vec4(aPos.x, aPos.y, 0.9f, 1.0f);
}


#type - delim

#version 460 core

out vec4 out_color;
uniform float u_Time;
uniform sampler2D tex;
in VS_OUT{
	vec2 pos;
	vec2 uv;
} vs_in;

void main() {
	vec3 tex_c = texture(tex, vs_in.uv).rgb;
	float time = cos(u_Time) * 0.5f + 0.5f;
	out_color = vec4(tex_c, 1.0f);
}

