// this sketch shows how to use texture coordinates to create a fly's eye mosaic effect

// this stuff is from here:
// https://github.com/aferriss/p5jsShaderExamples

// the shader variable
let theshader;

// the image variable
let img;

function preload(){
  // load the shader
  theshader = loadShader('effect.vert', 'effect.frag');
  img = loadImage('cat.jpg');
}

function setup() {
  // shaders require WEBGL mode to work
  createCanvas(windowWidth, windowHeight, WEBGL);
  noStroke();

}

function draw() {

  // shader() sets the active shader with our shader
  shader(theshader);

  // send the image and the resolution to the shader
  theshader.setUniform('tex0', img);
  theshader.setUniform('resolution', [img.width, img.height]);
  theshader.setUniform('mouseX', mouseX/width*50);

  // rect gives us some geometry on the screen
  rect(0,0,img.width, img.height);


}

function windowResized(){
  resizeCanvas(windowWidth, windowHeight);
}
