#ifdef GL_ES
precision mediump float;
#endif

#define LOW_QUALITY


uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float randomNumber1;
uniform float randomNumber2;
uniform float randomNumber3;
uniform float randomNumber4;
uniform float randomNumber5;
//uniform float brightness;


vec2 random2(vec2 st){
    
    st = vec2( dot(st,vec2(randomNumber1,randomNumber2)),
              dot(st,vec2(randomNumber3,randomNumber4)) );
    return -1.0 + 2.0*fract(sin(st)*randomNumber5);
}

float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);
    
    vec2 u = f*f*(3.0-2.0*f);
    return mix( mix( dot( random2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                     dot( random2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( random2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                     dot( random2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

mat2 rotate2d(float _angle){
   return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}
float speed = 1.;
//float speed = 1.5 - (brightness)/255;

vec2 center = vec2(1.65*u_resolution.y/u_resolution.x, 0.5);



float shape(vec2 st, float radius) {
    st = center-st;
    float r = length(st)*2.;
    float a = atan(st.y,st.x);
    float m = abs(mod(a+u_time*2.,3.14*2.0))/5.;
    float f = radius;
    //m += noise(st+u_time*0.1)*.5;
    //a *= 1.+abs(atan(u_time*0.2))*.1;
    //a *= 1.+noise(st+u_time*0.1)*0.1;
    f += cos(a*800.)*noise(st+u_time*speed)*.3;
    f += (sin(noise(st+u_time*speed)*1.)*0.05);
   // f += cos(sin(cos(st)*3)+u_time)*sin(100*st);
    return 1.-smoothstep(f,f+0.15,r);
}


float shapeBorder(vec2 st, float radius, float width) {
    return shape(st,radius)-shape(st,radius-width);
}
float circle(vec2 st, float radius) {
    st = center-st;
    float r = length(st)*2.;
    float a = atan(st.y,st.x);
    float f = radius;
  f += (sin(noise(st+u_time*0.2)*1.)*.01);
    return 1-smoothstep(f,f+0.015,r);
}




void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.y;
    vec3 color =1- vec3(1.0) * shapeBorder(st,0.6,1.0);
    vec3 color1 = vec3(1.0) * circle(st,0.62);
    
    gl_FragColor = vec4(1.0- (color + color1), 1.0);
}
