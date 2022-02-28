#version 460 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT{
	vec2 pos;
	vec2 uv;
} vs_out;

void main() {
	vs_out.pos = aPos;
	vs_out.uv = aUV;
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, -1.0f, 1.0f);
}


#type - delim

#version 460 core

out vec4 out_color;
uniform sampler2D tex[8];
uniform int texId;

in VS_OUT{
	vec2 pos;
	vec2 uv;
} vs_in;

void main() {
	vec4 color;
	color = texture(tex[texId], vs_in.uv);
	if (color.a < 0.01)
		discard;
	/*out_color = vec4(1.0, 1.0, 1.0, 1.0);*/
	out_color = vec4(vec3(color), 1.0);
}

