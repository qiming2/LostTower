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
uniform vec2 u_Resolution;
uniform sampler2D tex;
in VS_OUT{
	vec2 pos;
	vec2 uv;
} vs_in;

#define line_width 0.03
#define t u_Time
#define r u_Resolution.xy
#define fragCoord gl_FragCoord
float plot(float pc, float y) {
	// line width param
	
	return smoothstep(pc - line_width, pc, y) - smoothstep(pc, pc + line_width, y);
}

void main() {
	//float w_h_ratio = u_Resolution.x / u_Resolution.y;
	//float x = gl_FragCoord.x / u_Resolution.x;
	//float y = gl_FragCoord.y / u_Resolution.y;
	////float y_limit = smoothstep(0.5 - 0.5 / w_h_ratio, 0.5 + 0.5 / w_h_ratio, x);
	////float y_limit = mod(sin((u_Time + x * 3.1415926) * 2) * 0.5 + 0.5, 0.5);
	//float x2 = x * x;
	//float x4 = x2 * x2;
	//float x6 = x4 * x2;

	//float fa = (4.0 / 9.0);
	//float fb = (17.0 / 9.0);
	//float fc = (22.0 / 9.0);

	//float y_limit = 1 - sqrt(1 - x * x);
	////float y_limit = abs(sin((u_Time + x ) * 2));
	////float y_limit = sin((u_Time * x * 100)) ;
	//	//discard;
	//vec3 tex_c = texture(tex, vs_in.uv).rgb;
	////float time = cos(u_Time) * 0.5f + 0.5f;
	//// Draw a smoothstep func
	//float pct = plot(y_limit, y);
	//out_color = vec4(0.0, 1.0, 1.0, 1.0) * (1.0 - pct) + pct * vec4(tex_c, 1.0f);
	////out_color = vec4(vec2(x, y), 0.0, 1.0);

	vec3 c;
	float l, z = t;
	for (int i = 0; i < 3; i++) {
		vec2 uv, p = fragCoord.xy / r;
		uv = p;
		p -= .5;
		p.x *= r.x / r.y;
		z += .10;
		l = length(p);
		uv += p / l * (sin(z) + 1.0) * abs(sin(l * 9.0 - z - z));
		l *= mix(1., 0.1 * sin(z * l * 0.1) * 0.5 + 0.5, cos(z) * 0.5 + 0.5);
		c[i] = .01 / length(mod(uv, 1.) - .5);
	}
	out_color = vec4(c / l, 1.0);
}

