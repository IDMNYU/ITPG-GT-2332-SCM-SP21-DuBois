#version 120

uniform sampler2DRect tex0;

uniform float blurX;
uniform float blurY;

varying vec2 texCoordVarying;

// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/

void main()
{
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

	color += 0.000229 * texture2DRect(tex0, texCoordVarying + vec2(blurX * -4.0, 0.0));
	color += 0.005977 * texture2DRect(tex0, texCoordVarying + vec2(blurX * -3.0, 0.0));
	color += 0.060598 * texture2DRect(tex0, texCoordVarying + vec2(blurX * -2.0, 0.0));
	color += 0.241732 * texture2DRect(tex0, texCoordVarying + vec2(blurX * -1.0, 0.0));

	color += 0.000229 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurY * -4.0));
	color += 0.005977 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurY * -3.0));
	color += 0.060598 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurY * -2.0));
	color += 0.241732 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurY * -1.0));


	color += 0.382928 * texture2DRect(tex0, texCoordVarying + vec2(0.0, 0));

	color += 0.241732 * texture2DRect(tex0, texCoordVarying + vec2(blurX * 1.0, 0.0));
	color += 0.060598 * texture2DRect(tex0, texCoordVarying + vec2(blurX * 2.0, 0.0));
	color += 0.005977 * texture2DRect(tex0, texCoordVarying + vec2(blurX * 3.0, 0.0));
	color += 0.000229 * texture2DRect(tex0, texCoordVarying + vec2(blurX * 4.0, 0.0));

	color += 0.241732 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurY * 1.0));
	color += 0.060598 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurY * 2.0));
	color += 0.005977 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurY * 3.0));
	color += 0.000229 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurY * 4.0));
    
    gl_FragColor = color;
}
