// this sketch shows how to use texture coordinates to create a fly's eye mosaic effect

// this stuff is from here:
// https://github.com/aferriss/p5jsShaderExamples

// the shader variable
let theshader;

// the image variable - live video capture
let capture;

function preload(){
  // load the shader
  theshader = loadShader('effect.vert', 'effect.frag');
}

function setup() {
  // shaders require WEBGL mode to work
  createCanvas(windowWidth, windowHeight, WEBGL);
  noStroke();
  capture = createCapture(VIDEO);
  //capture.size(320,240);

}

function draw() {

  // shader() sets the active shader with our shader
  shader(theshader);

  // send the image and the resolution to the shader
  theshader.setUniform('tex0', capture);
  theshader.setUniform('resolution', [capture.width, capture.height]);
  theshader.setUniform('mouseX', mouseX/width*50);

  // rect gives us some geometry on the screen
  rect(0,0,capture.width, capture.height);


}

function windowResized(){
  resizeCanvas(windowWidth, windowHeight);
}
