
var foo = new p5.Speech(); // speech synthesis object
foo.onLoad = loaded; // it's a property not a method

function setup(){
  createCanvas(windowWidth, windowHeight);
}

function draw()
{
}

function loaded()
{
  foo.listVoices();
  foo.setVoice('Victoria');
  foo.setRate(1.);
  foo.setPitch(1.);
  foo.setLang('en-US'); // BCP-47
  foo.speak('hi there');
  foo.setVoice('Google UK English Female');
  foo.setRate(1.);
  foo.setPitch(1.);
  foo.setLang('en-GB'); // BCP-47
  foo.speak('whats happening');
  foo.setVoice('Google français');
  foo.setRate(1.);
  foo.setPitch(1.);
  foo.setLang('fr-FR'); // BCP-47
  foo.speak('how are you today');

}
