var synth, amp, s1, s2;

amp = new Tone.Gain(0).toDestination();
synth = new Tone.Oscillator(440, "sine").connect(amp);
s1 = new Tone.Signal({
  value: 440,
  units: "frequency"
}).connect(synth.frequency);

s2 = new Tone.Signal(0).connect(amp.gain);

function setup(){
  createCanvas(windowWidth, windowHeight);
  synth.start();
}

function draw()
{
  let f = map(mouseX, 0, width, 200, 800);
  s1.rampTo(f, 0.05);
  let a = map(mouseY, 0, height, .1, 0);
  console.log(a);
  //synth.volume.value = a;
  s2.rampTo(a, 0.05);
  //s2.rampTo(0, 0);
}
