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

uniform float LB;
uniform float LC;
uniform float RB;
uniform float RT;
uniform float CC;
uniform float LT;
uniform float CT;
uniform float RC;
uniform float CB;
uniform sampler2D tin1;

uniform vec2 dim; // IMPORTANT -> you need to set this: this is the pixel size of the texture you're processing
varying vec2 v_texcoord;

void main() {
	vec4 in1 = texture2D(tin1, v_texcoord);
	vec2 norm = v_texcoord;

	vec2 expr_8 = (1.0 / dim);
	vec2 mul_37 = (expr_8 * vec2(0.0, 0.0));
	vec2 add_36 = (mul_37 + norm);
	vec4 nearest_38 = (texture2D(tin1, jit_wrap1(add_36)));
	vec4 mul_35 = (nearest_38 * CC);
	vec2 mul_13 = (expr_8 * vec2(0.0, -1.0));
	vec2 add_12 = (mul_13 + norm);
	vec4 nearest_14 = (texture2D(tin1, jit_wrap1(add_12)));
	vec4 mul_11 = (nearest_14 * CT);
	vec2 mul_7 = (expr_8 * vec2(-1.0, -1.0));
	vec2 add_6 = (mul_7 + norm);
	vec4 nearest_10 = (texture2D(tin1, jit_wrap1(add_6)));
	vec4 mul_5 = (nearest_10 * LT);
	vec2 mul_3 = (expr_8 * vec2(1.0, -1.0));
	vec2 add_2 = (mul_3 + norm);
	vec4 nearest_4 = (texture2D(tin1, jit_wrap1(add_2)));
	vec4 mul_1 = (nearest_4 * RT);
	vec2 mul_25 = (expr_8 * vec2(0.0, 1.0));
	vec2 add_24 = (mul_25 + norm);
	vec4 nearest_26 = (texture2D(tin1, jit_wrap1(add_24)));
	vec4 mul_23 = (nearest_26 * CB);
	vec2 mul_21 = (expr_8 * vec2(-1.0, 1.0));
	vec2 add_20 = (mul_21 + norm);
	vec4 nearest_22 = (texture2D(tin1, jit_wrap1(add_20)));
	vec4 mul_19 = (nearest_22 * LB);
	vec2 mul_17 = (expr_8 * vec2(1.0, 1.0));
	vec2 add_16 = (mul_17 + norm);
	vec4 nearest_18 = (texture2D(tin1, jit_wrap1(add_16)));
	vec4 mul_15 = (nearest_18 * RB);
	vec2 mul_29 = (expr_8 * vec2(1.0, 0.0));
	vec2 add_28 = (mul_29 + norm);
	vec4 nearest_30 = (texture2D(tin1, jit_wrap1(add_28)));
	vec4 mul_27 = (nearest_30 * RC);
	vec2 mul_33 = (expr_8 * vec2(-1.0, 0.0));
	vec2 add_32 = (mul_33 + norm);
	vec4 nearest_34 = (texture2D(tin1, jit_wrap1(add_32)));
	vec4 mul_31 = (nearest_34 * LC);
	vec4 mul_51 = (((((((((mul_31 + mul_27) + mul_15) + mul_19) + mul_23) + mul_1) + mul_5) + mul_11) + mul_35) * 1.0);
	float swiz_56 = (mul_51.r);
	float swiz_57 = (mul_51.g);
	float swiz_58 = (mul_51.b);
	vec4 vec_48 = (vec4(swiz_56, swiz_57, swiz_58, 1.0));
	gl_FragColor = vec_48;
}
