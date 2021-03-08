
var foo = new p5.Speech(); // speech synthesis object
foo.onLoad = loaded; // it's a property not a method
foo.interrupt = true;

var voices = ['Victoria', 'Alex', 'Princess', 'Pipe Organ'];
var phrases = ['Yes', 'No', 'Maybe', 'Never'];

function setup(){
  createCanvas(windowWidth, windowHeight);
}

function draw()
{
}

function mousePressed()
{
  foo.setVoice(random(voices));
  foo.speak(random(phrases));
}

function loaded()
{
  foo.listVoices();

}
