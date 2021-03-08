// in this sketch we're going to send the webcam to the shader, and then invert it's colors

// the shader variable
let camShader;

// the camera variable
let cam;
let pupImg;

function preload(){
  // load the shader
  camShader = loadShader('effect.vert', 'effect.frag');

  pupImg = loadImage('dog.jpg');
}

function setup() {
  // shaders require WEBGL mode to work
  createCanvas(windowWidth, windowHeight, WEBGL);
  noStroke();

  // initialize the webcam at the window size
  cam = createCapture(VIDEO);
  cam.size(windowWidth, windowHeight);

  // hide the html element that createCapture adds to the screen
  cam.hide();

}

function draw() {  
  // shader() sets the active shader with our shader
  shader(camShader);

  // lets just send the cam to our shader as a uniform
  camShader.setUniform('tex0', cam);
  camShader.setUniform('tex1', pupImg);

  camShader.setUniform('amt', map(mouseX, 0, width, 0, 0.2));
  // rect gives us some geometry on the screen
  rect(0,0,width, height);
}

function windowResized(){
  resizeCanvas(windowWidth, windowHeight);
}