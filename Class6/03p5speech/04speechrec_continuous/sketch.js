
var foo = new p5.SpeechRec('en-US'); // speech recognition object (will prompt for mic access)
foo.onResult = showResult; // bind callback function to trigger when speech is recognized
foo.continuous = true;
foo.interimResults = true;

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
  foo.setVoice(random(voices));
  foo.speak(random(phrases));
}

function showResult()
{
  textSize((foo.resultConfidence * 32) + 9);
  var mostrecentword = foo.resultString.split(' ').pop();
  var bg = 'black';
  if(mostrecentword.indexOf("black")!==-1) { bg = 'black'; }
  if(mostrecentword.indexOf("red")!==-1) { bg = 'red'; }
  if(mostrecentword.indexOf("green")!==-1) { bg = 'green'; }
  if(mostrecentword.indexOf("blue")!==-1) { bg = 'blue'; }
  if(mostrecentword.indexOf("yellow")!==-1) { bg = 'yellow'; }
	if(mostrecentword.indexOf("purple")!==-1) { bg = 'purple'; }
  background(bg);
  fill(255);
  text(foo.resultString, 20, height/2); // log the result

}
