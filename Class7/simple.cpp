#include "simple.h"

namespace simple {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	DCBlock __m_dcblock_20;
	DCBlock __m_dcblock_18;
	Delay m_delay_5;
	Delay m_delay_6;
	Delta __m_delta_13;
	Delta __m_delta_8;
	Phasor __m_phasor_7;
	Phasor __m_phasor_12;
	Rate __m_rate_17;
	Rate __m_rate_19;
	int __exception;
	int vectorsize;
	t_sample samplerate;
	t_sample m_knob_3;
	t_sample m_knob_4;
	t_sample __m_slide_14;
	t_sample m_cv_2;
	t_sample m_cv_1;
	t_sample __m_slide_9;
	t_sample samples_to_seconds;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_cv_1 = ((int)0);
		m_cv_2 = ((int)0);
		m_knob_3 = ((int)0);
		m_knob_4 = ((int)0);
		m_delay_5.reset("m_delay_5", ((int)10000));
		m_delay_6.reset("m_delay_6", ((int)10000));
		samples_to_seconds = (1 / samplerate);
		__m_phasor_7.reset(0);
		__m_delta_8.reset(0);
		__m_slide_9 = 0;
		__m_phasor_12.reset(0);
		__m_delta_13.reset(0);
		__m_slide_14 = 0;
		__m_rate_17.reset();
		__m_dcblock_18.reset();
		__m_rate_19.reset();
		__m_dcblock_20.reset();
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample mul_39 = ((m_knob_3 + m_cv_2) * ((int)10));
		t_sample triangle_30 = triangle(mul_39, ((t_sample)0.12));
		t_sample mul_29 = (triangle_30 * ((int)100));
		samples_to_seconds = (1 / samplerate);
		t_sample mul_41 = ((m_knob_4 + m_cv_1) * ((int)10));
		t_sample triangle_32 = triangle(mul_41, ((t_sample)0.1));
		t_sample mul_31 = (triangle_32 * ((int)100));
		t_sample iup_10 = (1 / maximum(1, abs(((int)1))));
		t_sample idown_11 = (1 / maximum(1, abs(mul_31)));
		t_sample iup_15 = (1 / maximum(1, abs(((int)1))));
		t_sample idown_16 = (1 / maximum(1, abs(mul_29)));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample phasor_40 = __m_phasor_7(mul_39, samples_to_seconds);
			t_sample delta_37 = __m_delta_8(phasor_40);
			int lt_36 = (delta_37 < ((int)0));
			__m_slide_9 = fixdenorm((__m_slide_9 + (((lt_36 > __m_slide_9) ? iup_10 : idown_11) * (lt_36 - __m_slide_9))));
			t_sample slide_34 = __m_slide_9;
			t_sample phasor_42 = __m_phasor_12(mul_41, samples_to_seconds);
			t_sample delta_38 = __m_delta_13(phasor_42);
			int lt_35 = (delta_38 < ((int)0));
			__m_slide_14 = fixdenorm((__m_slide_14 + (((lt_35 > __m_slide_14) ? iup_15 : idown_16) * (lt_35 - __m_slide_14))));
			t_sample slide_33 = __m_slide_14;
			t_sample rate_13 = __m_rate_17.perform_off(phasor_42, ((int)10));
			t_sample mul_11 = (rate_13 * ((int)10));
			t_sample round_15 = round(mul_11);
			t_sample mul_19 = (round_15 * ((int)110));
			t_sample rdiv_20 = safediv(((int)1), mul_19);
			t_sample mul_22 = (rdiv_20 * samplerate);
			t_sample tap_24 = m_delay_5.read_linear(mul_22);
			t_sample dcblock_9 = __m_dcblock_18(tap_24);
			t_sample out2 = (dcblock_9 + in2);
			t_sample mul_21 = (tap_24 * ((t_sample)0.99));
			t_sample rate_14 = __m_rate_19.perform_off(phasor_40, ((int)10));
			t_sample mul_12 = (rate_14 * ((int)10));
			t_sample round_16 = round(mul_12);
			t_sample mul_17 = (round_16 * ((int)110));
			t_sample rdiv_18 = safediv(((int)1), mul_17);
			t_sample mul_26 = (rdiv_18 * samplerate);
			t_sample tap_28 = m_delay_6.read_linear(mul_26);
			t_sample dcblock_10 = __m_dcblock_20(tap_28);
			t_sample out1 = (dcblock_10 + in1);
			t_sample mul_25 = (tap_28 * ((t_sample)0.99));
			m_delay_5.write((mul_21 + slide_33));
			m_delay_6.write((mul_25 + slide_34));
			m_delay_5.step();
			m_delay_6.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_cv2(t_param _value) {
		m_cv_1 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv1(t_param _value) {
		m_cv_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 4; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_cv1(value); break;
		case 1: self->set_cv2(value); break;
		case 2: self->set_knob1(value); break;
		case 3: self->set_knob2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_cv_2; break;
		case 1: *value = self->m_cv_1; break;
		case 2: *value = self->m_knob_3; break;
		case 3: *value = self->m_knob_4; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_cv_2")
	pi = self->__commonstate.params + 0;
	pi->name = "cv1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_cv_1")
	pi = self->__commonstate.params + 1;
	pi->name = "cv2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob_3")
	pi = self->__commonstate.params + 2;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob_4")
	pi = self->__commonstate.params + 3;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // simple::
