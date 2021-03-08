var synth;

synth = new Tone.PolySynth({
  // "volume": -10,
  "envelope": {
    "attack": 0.1,
    "decay": 0.05,
    "sustain": 0.2,
    "release": 0.03,
  },
  "oscillator": {
          "type": "sine"
        }
  }).toDestination();

var pattern = new Tone.Pattern(function(time, note){
  synth.triggerAttackRelease(note, "16n");
}, [["C4","G4"], ["D4", "F#3"], "E4", "A3"], "upDown");
	//https://tonejs.github.io/docs/r12/CtrlPattern

pattern.interval = "4n";

function setup(){
  createCanvas(windowWidth, windowHeight);
  Tone.Transport.bpm.value = 120;
  Tone.Transport.start();
  pattern.start(0);
}

function keyPressed()
{
  if(key=='s') pattern.stop();
  if(key=='g') pattern.start(0);
}
