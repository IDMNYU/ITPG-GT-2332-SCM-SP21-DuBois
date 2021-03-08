// this sketch shows how to use texture coordinates to create a fly's eye mosaic effect


// the shader variable
let theshader;

// the image variable
let capture;

let ck = [[0,0,0],
          [0,1,0],
          [0,0,0]];

// convolution kernel greatest hits:

ck = [[1.0,0.0,1.0],
      [0.0,-4.0,0.0],
      [1.0,0.0,2.0]];

ck = [[0.0,-1.0,0.0],
      [-1.0,4.0,-1.0],
      [0.0,-1.0,0.0]];

ck = [[1.0/16.0,2.0/16.0,1.0/16.0],
      [2.0/16.0,4.0/16.0,2.0/16.0],
      [1.0/16.0,2.0/16.0,1.0/16.0]];

function preload(){
  // load the shader
  theshader = loadShader('effect.vert', 'effect.frag');
}

function setup() {
  // shaders require WEBGL mode to work
  createCanvas(windowWidth, windowHeight, WEBGL);
  noStroke();
  capture = createCapture(VIDEO);

}

function draw() {


  // shader() sets the active shader with our shader
  shader(theshader);

  // send the image and the resolution to the shader
  theshader.setUniform('tin1', capture);
  theshader.setUniform('dim', [capture.width, capture.height]);
  theshader.setUniform('LT', ck[0][0]);
  theshader.setUniform('CT', ck[0][1]);
  theshader.setUniform('RT', ck[0][2]);
  theshader.setUniform('LC', ck[1][0]);
  theshader.setUniform('CC', ck[1][1]);
  theshader.setUniform('RC', ck[1][2]);
  theshader.setUniform('LB', ck[2][0]);
  theshader.setUniform('CB', ck[2][1]);
  theshader.setUniform('RB', ck[2][2]);

  // rect gives us some geometry on the screen
  rect(0,0,capture.width, capture.height);


}

function windowResized(){
  resizeCanvas(windowWidth, windowHeight);
}
