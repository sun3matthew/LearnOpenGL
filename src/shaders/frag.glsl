#version 410 core

out vec4 fragColor;  // The output color of the fragment
in vec2 fragCoord;   // The coordinates of the current fragment (pixel)

uniform float iTime; // The time uniform
uniform vec3 iResolution; // The resolution of the screen (x, y, and optional z)
uniform vec4 iMouse; // The mouse position (x, y, click, and optional z)

// This scene is taken from my second tutorial about shader coding,
// which introduces the concept of raymarching as well as some useful
// transforms and space-bending techniques.
// 
//     Mouse interactive!
//                            Video URL: https://youtu.be/khblXafu7iA

// 2D rotation function
mat2 rot2D(float a) {
    return mat2(cos(a), -sin(a), sin(a), cos(a));
}

// Custom gradient - https://iquilezles.org/articles/palettes/
vec3 palette(float t) {
    return .5+.5*cos(6.28318*(t+vec3(.3,.416,.557)));
}

// Octahedron SDF - https://iquilezles.org/articles/distfunctions/
// float sdOctahedron(vec3 p, float s) {
//     p = abs(p);
//     return (p.x+p.y+p.z-s)*0.57735027;
// }

  float de(vec3 p){
    p=mod(p,2.)-1.;
    p=abs(p)-1.;
    if(p.x < p.z)p.xz=p.zx;
    if(p.y < p.z)p.yz=p.zy;
    if(p.x < p.y)p.xy=p.yx;
    float s=1.;
    for(int i=0;i<10;i++){
      float r2=2./clamp(dot(p,p),.1,1.);
      p=abs(p)*r2-vec3(.6,.6,3.5);
      s*=r2;
    }
    return length(p)/s;
  }
// Scene distance
float map(vec3 p) {
    p.z += iTime * .4; // Forward movement
    
    // Space repetition
    p.xy = fract(p.xy) - .5;     // spacing: 1
    p.z =  mod(p.z, .25) - .125; // spacing: .25
    
    // return sdOctahedron(p, .15); // Octahedron
    return de(p); // Custom SDF
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    vec2 uv = (fragCoord * 2. - iResolution.xy) / iResolution.y;
    vec2  m = (iMouse.xy * 2. - iResolution.xy) / iResolution.y;
    
    // Default circular motion if mouse not clicked
    if (iMouse.z <= 0.) m = vec2(cos(iTime*.2), sin(iTime*.2));

    // Initialization
    vec3 ro = vec3(0, 0, -3);         // ray origin
    vec3 rd = normalize(vec3(uv, 1)); // ray direction
    vec3 col = vec3(0);               // final pixel color

    float t = 0.; // total distance travelled

    int i; // Raymarching
    for (i = 0; i < 80; i++) {
        vec3 p = ro + rd * t; // position along the ray
        
        p.xy *= rot2D(t*.15 * m.x);     // rotate ray around z-axis

        p.y += sin(t*(m.y+1.)*.5)*.35;  // wiggle ray

        float d = map(p);     // current distance to the scene

        t += d;               // "march" the ray

        if (d < .001 || t > 100.) break; // early stop
    }

    // Coloring
    col = palette(t*.04 + float(i)*.005);

    fragColor = vec4(col, 1);
}

void main()
{
    mainImage(fragColor, fragCoord);  // Call the mainImage function
}
