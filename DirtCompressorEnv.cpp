#include "SC_PlugIn.hpp"

static InterfaceTable *ft;

struct DirtCompressorEnv : public SCUnit {
public:
    DirtCompressorEnv() {
        set_calc_function<DirtCompressorEnv, &DirtCompressorEnv::next>();
        next(1);
    }

private:
    float env = 0.0f;

    void next(int inNumSamples) {
        const float* inbuf = in(0);
        const float speed = in0(1);
        float* outbuf = out(0);

        for(int i = 0; i < inNumSamples; i++) {
            float in_samp = inbuf[i];
            env += speed * sampleDur();
            float in_env_abs = fabs(in_samp * env);
            if(in_env_abs > 1.0f) {
                env /= in_env_abs;
            }
            outbuf[i] = env;
        }
    }
};

struct DirtCompressorMax : public SCUnit {
public:
    DirtCompressorMax() {
        set_calc_function<DirtCompressorMax, &DirtCompressorMax::next>();
        // numChannels = in0(0);
        next(1);
    }
    
private:
    void next(int inNumSamples) {
        int numChannels = in0(0);
        float* outbuf = out(0);
        
        for(int i = 0; i < inNumSamples; i++) {
            float max = 0.0f;
            for(int j = 0; j < numChannels; j++) {
                float in_samp = in(1+j)[i];
                if(fabsf(in_samp) > max) {
                    max = in_samp;
                }
            }

            outbuf[i] = max;
        }
    }
};

PluginLoad(DirtCompressorUGens) {
    ft = inTable;
    registerUnit<DirtCompressorEnv>(ft, "DirtCompressorEnv");
    registerUnit<DirtCompressorMax>(ft, "DirtCompressorMax");
}
