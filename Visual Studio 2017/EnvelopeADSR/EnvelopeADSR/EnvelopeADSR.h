/*
 * ADSR Type Envelope Class
 *
 * 2018.06.28
 *
 */
 
#ifndef _ENVELOPE_ADSR_H_
#define _ENVELOPE_ADSR_H_

class EnvelopeADSR
{
private:
	enum EnvelopeState {
		ST_ATTACK,
		ST_DECAY,
		ST_SUSTAIN,
		ST_RELEASE
	};

public:
	EnvelopeADSR()
	{
		count = 0;
		amplitude = 0;
		setADSR(0, 0, 0.0f, 0);
	}
	
	void setADSR(int _attack, int _decay, float _sustain, int _release)
	{
		attack = _attack;
		decay = _decay;
		sustain = _sustain;
		release = _release;

		if (attack != 0) {
			attackRatio = 1.0f / attack;
		} 
		else {
			attackRatio = 0.0f;
		}
		if (decay != 0) {
			decayRatio = -(1.0f - sustain) / decay;
		}
		else {
			decayRatio = 0.0f;
		}
		if (release != 0) {
			releaseRatio = -sustain / release;
		}
		else {
			releaseRatio = 0.0f;
		}
	}
	
	void gateOn()
	{
		isGateOn = true;
		count = 0;
		amplitude = 0.0f;
		state = ST_ATTACK;
	}

	void gateOff()
	{
		isGateOn = false;
		state = ST_RELEASE;
	}

	float getAmplitude()
	{
		return amplitude;
	}

	long getCount()
	{
		return count;
	}

	int getState()
	{
		return state;
	}
	
	float tick()
	{
		float currentAmplitude = amplitude;

		switch (state) {
		case ST_ATTACK:
			amplitude += attackRatio;
			break;
		case ST_DECAY:
			amplitude += decayRatio;
			break;
		case ST_SUSTAIN:
			// do nothing
			break;
		case ST_RELEASE:
			amplitude += releaseRatio;
			if (amplitude < 0.0f) {
				amplitude = 0.0f;
			}
			break;
		}
		
		count++;
		if (count < attack) {
			state = ST_ATTACK;
		} else if (count < attack + decay) {
			state = ST_DECAY;
		} else if (isGateOn) {
			state = ST_SUSTAIN;
		}
		
		return currentAmplitude;
	}

private:
	int attack;
	int decay;
	float sustain;
	int release;
	
	float attackRatio;
	float decayRatio;
	float releaseRatio;
	
	long count;
	bool isGateOn;
	EnvelopeState state;
	
	float amplitude;
};

#endif //_ENVELOPE_ADSR_H_
