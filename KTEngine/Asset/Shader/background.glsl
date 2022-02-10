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
	gl_Position = vec4(aPos.x, aPos.y, 0.99f, 1.0f);
}


#type - delim

#version 460 core

out vec4 out_color;
uniform sampler2D tex;

in VS_OUT{
	vec2 pos;
	vec2 uv;
} vs_in;

void main() {
	vec3 color = texture(tex, vs_in.uv).rgb;
	out_color = vec4(color, 1.0);
}
