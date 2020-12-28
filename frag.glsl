#version 120

uniform float EPSILON = 0.25;
uniform float GAMMA = 0.2;
uniform float FORCE = 0.6;
uniform float B = -0.3;

varying vec2 texCoord;

// complex library
vec2 cmul(vec2 a, vec2 b)
{
	return vec2(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y);
}

float cabs2(vec2 z)
{
	return z.x * z.x + z.y * z.y;
}

float cabs(vec2 z)
{
	return sqrt(cabs2(z));
}

vec2 cexp(vec2 z)
{
	return exp(z.x) * vec2(cos(z.y), sin(z.y));
}

float classicMandel(vec2 c)
{
	vec2 z = vec2(0);
	for (int i = 0; i < 255; i++)
		if (cabs2(z) > 4.0)
			return float(i) / 255.0;
		else
			z = cmul(z, z) + c;
	return 1.0;
}

vec2 conj(vec2 z)
{
	return vec2(z.x, -z.y);
}

vec2 cdiv(vec2 a, vec2 b)
{
	return cmul(a, conj(b)) / cabs2(b);
}

// diff mandelbrot part

vec2 nextXiNu(vec2 lambda, vec2 xiNu, vec2 prevXiNu)
{
	float d = xiNu.x - xiNu.y;
	float d2 = d * d;
	vec2 xiNu2 = xiNu * xiNu;
	return lambda - xiNu2 - B * prevXiNu + EPSILON * d2;
}

float nextY(vec2 lambda, vec2 xiNu, float t, float y, float prevY)
{
	float y2 = y * y;
	float ymNu = y - xiNu.y;
	float ymNu2 = ymNu * ymNu;

	float nom = y2 - y * (2 + GAMMA) + lambda.x + prevY - EPSILON * ymNu2 - FORCE * cos(t);
	float den = -(1 + GAMMA);
	return nom / den;
}

float diffMandelbrot(vec2 lambda)
{
	float pY = 0;
	float y = 0;
	vec2 pXiNu = vec2(0);
	vec2 xiNu = vec2(0);
	float delta = 1.0 / 128.0;
	for (float i = 0; i < 1.0; i += delta)
	{
		if (y > 2.5)
			return i;
		float nY = nextY(lambda, xiNu, i, y, pY);
		vec2 nXiNu = nextXiNu(lambda, xiNu, pXiNu);
		pXiNu = xiNu;
		xiNu = nXiNu;
		pY = y;
		y = nY;
	}
	return 1.0;
}

vec2 nextX(vec2 lambda, vec2 x)
{
	vec2 x2 = x * x;
	float xm = x.x - x.y;
	float xm2 = xm * xm;
	return lambda - x2 + vec2(EPSILON * xm2);
}

float simpleMandelbrot(vec2 lambda)
{
	vec2 x = vec2(0);
	float delta = 1.0 / 256.0;
	for (float i = 0; i < 1.0; i += delta)
	{
		vec2 x2 = x * x;
		if (x2.x + x2.y > 16)
			return i;
		vec2 nx = nextX(lambda, x);
		x = nx;
	}
	return 1.0;
}

void main(void)
{
	vec2 c = texCoord * 2.0;
	float m;
	// m = classicMandel(c);
	// m = diffMandelbrot(c);
	m = simpleMandelbrot(c);
	gl_FragColor = vec4(m / 2.0, 0.0, m, 1.0);
}
