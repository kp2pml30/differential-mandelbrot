#version 120

uniform float EPSILON = 0.25;
uniform float GAMMA = 0.2;
uniform float FORCE = 0.6;
uniform float B = -0.3;

varying vec2 texCoord;

vec4 getdiff(vec2 lambda, vec4 where, float t0)
{
	/*
		 x1' = z1
		 x2' = z2
		 z1' = ...
		 z2' = ...
	 */
	float fwt = FORCE * cos(B * t0);
	float xd = where.x - where.y;
	float xd2 = xd * xd;
	vec2 where2 = where.xy * where.xy;
	vec2 z12 = -GAMMA * where.zw - lambda + where2 + vec2(EPSILON * xd2 + fwt);
	return vec4(where.zw, z12);
}

vec4 euler(vec2 lambda, vec4 start, float t0, float dt)
{
	vec4 res = getdiff(lambda, start, t0);
	res *= dt;
	return res;
}

vec4 rungeKutta(vec2 lambda, vec4 start, float t0, float dt)
{
	vec4 k1 = getdiff(lambda, start, t0);
	vec4 k2 = getdiff(lambda, start + k1 * (dt / 2), t0 + dt / 2);
	vec4 k3 = getdiff(lambda, start + k2 * (dt / 2), t0 + dt / 2);
	vec4 k4 = getdiff(lambda, start + k3 * dt, t0 + dt);
	k2 *= 2;
	k3 *= 2;
	k1 += k2;
	k1 += k3;
	k1 += k4;
	k1 /= 6;
	return k1;
}

float hardMandelbrot(vec2 lambda)
{
	vec4 x = vec4(0);
	float delta = 1.0 / 256.0;
	for (float i = 0; i < 1.0; i += delta)
	{
		vec2 x2 = x.xy * x.xy;
		if (x2.x + x2.y > 16)
			return i;
		// vec4 nx = euler(lambda, x, i * 256.0, 1);
		vec4 nx = rungeKutta(lambda, x, i * 256.0, 1);
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
	m = hardMandelbrot(c);
	gl_FragColor = vec4(m / 2.0, 0.0, m, 1.0);
}
