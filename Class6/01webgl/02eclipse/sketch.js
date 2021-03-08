// this sketch shows how to use texture coordinates to create a fly's eye mosaic effect


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
  theshader.setUniform('tin1', img);
  theshader.setUniform('xfreq', floor(mouseX/width*50));
  theshader.setUniform('yfreq', floor(mouseY/height*50));

  // rect gives us some geometry on the screen
  rect(0,0,img.width, img.height);


}

function windowResized(){
  resizeCanvas(windowWidth, windowHeight);
}
