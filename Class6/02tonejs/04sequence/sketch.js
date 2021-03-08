
// sequencer stuff:
var ncols = 21; // how many 'steps' in the sequence
var nrows = 21; // how many 'rows' (pitches) in the sequence
var cstep, rstep; // pixel size for drawing
var thestuff; // array to store on/off data for sequence
var curstep; // what 'step' are we on?

var t; // tone.js object to access conversion functions
var keys; // polyphonic synthesizer

var notes; // array of notes = nrows
var basenote = 50; // MIDI pitch of lowest note
// scales to build 'notes' array:
//var scalepat = [2, 2, 1, 2, 2, 2, 1]; // major scale
var scalepat = [3, 2, 2, 3, 2]; // pentatonic scale

// p5.js + tone.js setup:
function setup() {

  // graphics:
  createCanvas(800, 600);
  noLoop();
  cstep = width/ncols;
  rstep = height/nrows;

  fillerup(); // set up 'thestuff' with a sequence of random values

  // fill up 'notes' with a scale:
  notes = new Array(nrows);
  var sptr = 0;
  notes[0] = basenote;
  for(var j = 1;j<notes.length;j++)
  {
    notes[j] = notes[j-1]+scalepat[sptr];
    sptr = (sptr+1) % scalepat.length;
  }

  // tone.js setup:

  //t = new Tone();

  // reverb:
  var freeverb = new Tone.Freeverb(0.8, 10000).toDestination();
  freeverb.wet.value = 0.25;

  // synthesizer:
  keys = new Tone.PolySynth(Tone.SimpleSynth).connect(freeverb);
  keys.set({maxPolyphony: nrows});

  // timecode 'clock' array for sequencer:
  var tc = new Array(ncols);
  for(var k = 0;k<tc.length;k++)
  {
    tc[k] = k;
  }

  // sequencer:
  Tone.Transport.bpm.value = 120;
  Tone.Transport.start();
  var theloop = new Tone.Sequence(sequenceStep, tc, "16n");
  theloop.start();

}

// calls every step in the sequence (tone.js):
function sequenceStep(time, step)
{
  curstep = step;
  var n = [];
  for(var i = 0;i<nrows;i++)
  {
    if(thestuff[step][i])
    {
      n.push(Tone.Midi(notes[nrows-1-i]).toFrequency());
    }
  }
  keys.triggerAttackRelease(n, "4n", time, random(0.1, 0.2));
  redraw();
}

// draws every frame (p5.js):
function draw() {
  background(0);
  for(var i = 0;i<ncols;i++)
  {
    if(i==curstep) fill(255, 0, 0); else fill(255);
    for(var j = 0;j<nrows;j++)
    {
      if(thestuff[i][j]) rect(i*cstep, j*rstep, cstep, rstep);
    }
  }

}

function mouseClicked()
{
  let c = floor(mouseX/width*ncols);
  let r = floor(mouseY/height*nrows);
  thestuff[c][r] = !thestuff[c][r];

}

function keyPressed()
{
  if(key==' ') fillerup();
  if(key=='c') blank();
}

// fill up 'thestuff' with random values for use as the sequence:
function fillerup()
{
  blank()

  for(var i = 0;i<thestuff.length;i++)
  {
    for(var j = 0;j<thestuff[i].length;j++)
    {
      thestuff[i][j] = random()>0.9;
    }
  }
}

function blank() {
  thestuff = new Array(ncols);
  for(var i = 0;i<thestuff.length;i++)
  {
    thestuff[i] = new Array(nrows);
  }
}
