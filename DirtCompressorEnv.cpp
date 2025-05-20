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

PluginLoad(DirtCompressorUGens) {
    ft = inTable;
    registerUnit<DirtCompressorEnv>(ft, "DirtCompressorEnv");
}
