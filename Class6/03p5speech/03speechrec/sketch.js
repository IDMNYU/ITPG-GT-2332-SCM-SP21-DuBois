
var foo = new p5.SpeechRec('en-US'); // speech recognition object (will prompt for mic access)
foo.onResult = showResult; // bind callback function to trigger when speech is recognized

function setup(){
  createCanvas(windowWidth, windowHeight);

  foo.start(); // start listening
  textSize(48);
}

function draw()
{
}

function mousePressed()
{
}

function showResult()
{
  background(0);
  fill(255);
  text(foo.resultString, 20, height/2); // log the result

}
