DirtCompressorEnv : UGen {
    *ar { |in, speed=50.0|
        ^this.multiNew('audio', in, speed);
    }

    checkInputs {
		if(inputs[0].rate != 'audio') {
			^"input % is not audio rate".format(0).throw;
		};
		if(inputs[1].rate != 'control') {
			^"input % is not audio rate".format(1).throw;
		};
        ^this.checkValidInputs;
    }
}

DirtCompressor {
	*ar { |in, speed=50.0|
		var envIn;
		envIn = switch(in.size,
			0, { in },
			1, { in[0] },
			{ Select.ar(ArrayMax.ar(in.abs)[1], in) }
		);
		^in * DirtCompressorEnv.ar(envIn, speed);
	}
}