// EnvelopeADSR.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "EnvelopeADSR.h"

int main()
{
	EnvelopeADSR env;

	env.setADSR(20, 20, 0.5, 20);

	for (int j = 0; j < 3; j++) {
		env.gateOn();
		for (int i = 0; i < 100; i++) {
			float amp = env.tick();
			long count = env.getCount();
			int state = env.getState();
			printf("%ld\t%d\t%f\n", count, state, amp);
		}
		env.gateOff();
		for (int i = 0; i < 100; i++) {
			float amp = env.tick();
			long count = env.getCount();
			int state = env.getState();
			printf("%ld\t%d\t%f\n", count, state, amp);
		}
	}

    return 0;
}

