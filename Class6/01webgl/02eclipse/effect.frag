precision mediump float;

#define hypot(x, y) sqrt(x*x+y*y)
#define xor(x, y)	((!(x&&y))&&(x||y))
#define sinh(x)		(0.5*(exp(x) - exp(-x)))
#define cosh(x)		(0.5*(exp(x) + exp(-x)))
#define tanh(x)		((sinh(x))/(cosh(x)))
#define asinh(x)	(log(x) + sqrt(x*x+1.))
#define acosh(x)	(log(x) + sqrt(x*x-1.))
#define atanh(x)	(0.5*log((1.+x)/(1.-x)))
#define trunc(x)	(vec4(x.r > 0. ? floor(x.r) : ceil(x.r), x.g > 0. ? floor(x.g) : ceil(x.g), x.b > 0. ? floor(x.b) : ceil(x.b), x.a > 0. ? floor(x.a) : ceil(x.a)))

vec2 jit_wrap1(vec2 v) {
	return mod(v, 1.);
}

vec2 jit_clamp1(vec2 v) {
	return clamp(v, 0., 1.);
}

vec2 jit_mirror1(vec2 v) {
	return 1.-abs((mod(v, 2.)-1.));
}

uniform float yfreq;
uniform float xfreq;
uniform sampler2D tin1;


varying vec2 v_texcoord;






void main() {
	vec4 in1 = texture2D(tin1, v_texcoord);
	vec2 norm = v_texcoord;




	float swiz_15 = (norm.r);
	float mul_12 = (swiz_15 * xfreq);
	float mod_4 = (mod(mul_12, 1.0));
	float floor_6 = (floor(mul_12));
	float div_11 = (floor_6 / xfreq);
	float swiz_14 = (norm.g);
	float mul_10 = (swiz_14 * yfreq);
	float mod_3 = (mod(mul_10, 1.0));
	vec2 vec_2 = (vec2(mod_4, mod_3));
	vec4 sample_5 = (texture2D(tin1, jit_wrap1(vec_2)));
	float floor_7 = (floor(mul_10));
	float div_9 = (floor_7 / xfreq);
	vec2 vec_8 = (vec2(div_11, div_9));
	vec4 sample_13 = (texture2D(tin1, jit_wrap1(vec_8)));
	vec4 mul_1 = (sample_5 * sample_13);
	gl_FragColor = mul_1;
}
