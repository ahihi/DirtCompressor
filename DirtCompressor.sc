DirtCompressorEnv : UGen {
    *ar { |in, speed=50.0|
        ^this.multiNew('audio', in, speed);
    }

    checkInputs {
		if(inputs[0].rate != 'audio') {
			^"input % is not audio rate".format(0).throw;
		};
		if(inputs[1].rate != 'control') {
			^"input % is not control rate".format(1).throw;
		};
        ^this.checkValidInputs;
    }
}

DirtCompressorMax : UGen {
    *ar { |in|
		if(in.isCollection.not) {
			in = [in];
		};
		[in.size, in].postln;
        ^this.new1('audio', in.size, *in);
    }

    checkInputs {
		if(inputs[0].rate != 'control') { // TODO: how to do ir?
			^"input % is not control rate".format(0).throw;
		};
		if(inputs[1].rate != 'audio') {
			^"input % is not audio rate".format(1).throw;
		};
        ^this.checkValidInputs;
    }
}

DirtCompressor {
	*ar { |in, speed=50.0, bugCompatible=false|
		var envIn;
		envIn = switch(in.size,
			0, { in },
			1, { in[0] },
			{
				if(bugCompatible) {
					DirtCompressorMax.ar(in)
				} {
					Select.ar(ArrayMax.ar(in.abs)[1], in)
				}
			}
		);
		^in * DirtCompressorEnv.ar(envIn, speed) * 0.2;
	}
}