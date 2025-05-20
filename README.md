# DirtCompressor

the compressor from [Dirt](https://github.com/tidalcycles/Dirt/blob/071fd88b3e004a11215afd11b718e92d3ab44d18/audio.c#L770-L777), implemented as a SuperCollider plugin.

## installation

build:

```shell
mkdir build
cd build
cmake .. -DSC_PATH=/path/to/supercollider-source
make
```

then copy `DirtCompressor.sc` and `DirtCompressorEnv.scx` into your SuperCollider extensions folder. (on some operating systems, it might be just `DirtCompressorEnv` without the extension?)

TODO: CI, precompiled builds

## usage as master effect

for SuperDirt, etc:

```supercollider
(
Ndef(\dirtComp, { |amount=1, speed=50|
	var in, max, env;
	in = In.ar(0, ~dirt.numChannels);

	ReplaceOut.ar(0, amount.linlin(0, 1, in, DirtCompressor.ar(in, speed)));
}).play(
	group: RootNode(Server.default),
	addAction: \addToTail
);
)

// can also tune the parameters
Ndef(\dirtComp).set(\amount, 1);
Ndef(\dirtComp).set(\speed, 200);
```
