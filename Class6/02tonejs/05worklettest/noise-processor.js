
registerProcessor('noise-processor', class extends AudioWorkletProcessor {
  static get parameterDescriptors() {
    return [{name: 'amplitude', defaultValue: 0.05, minValue: 0, maxValue: 1}];
  }
  process(inputs, outputs, parameters) {
    const amplitude = parameters.amplitude;
    for (let c = 0; c < outputs[0].length; c++) { // channels
      for (let i = 0; i < outputs[0][0].length; i++) { // samples
        const r = Math.random()*2-1;
        outputs[0][c][i] = r*amplitude; // first dim of array is output devices
      }
    }

    return true;
  }
});
