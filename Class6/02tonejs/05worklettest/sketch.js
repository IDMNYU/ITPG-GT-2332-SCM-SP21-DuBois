
var context;
var noiseNode, noiseVol;

var running = 0;

// audioworklet blob loader code:
const addAudioWorkletModule = url => fetch(url)
  .then(response => response.text()
    .then((text) => {
      const oUrl = URL.createObjectURL(new Blob([text], { type: 'text/javascript' }));
      return context.audioWorklet.addModule(oUrl);
    }));

const start = async () => {
  if (noiseNode) {
    return;
  }
  if (!context) {
    context = new AudioContext();
    await addAudioWorkletModule('./noise-processor.js');
    Tone.context = context;
  }
  // this worklet is output-only so it must be told how many channels to generate
  noiseNode = new AudioWorkletNode(context, 'noise-processor', {
    outputChannelCount: [context.destination.channelCount]
  });
  noiseNode.connect(context.destination);
  noiseVol = noiseNode.parameters.get('amplitude');
};

function setup(){
  createCanvas(800, 600);
  start();
}

function draw()
{
  background(0);
  fill(255);
  ellipse(mouseX, mouseY, 20, 20);
  if(running) {
    let vol = constrain((1.0-(mouseY/height))*.05, 0., 1.);
    noiseVol.value = vol;
    // noiseVol.setValueAtTime(1.0-(mouseY/height), context.currentTime);
    // noiseVol.linearRampToValueAtTime(1.0-(mouseY/height), context.currentTime+0.25);
  }
  else {
    noiseVol.value = 0;
  }
}

function keyPressed()
{
  if(key==' ')
  {
    running = !running;
  }
}
