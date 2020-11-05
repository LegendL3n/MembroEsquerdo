#pragma once

#include <psmoveapi.h>

namespace Palette {
    class HSV;

    // Hue, Saturation, Lightness
    class HSV {
    public:
        double h;       // angle in degrees
        double s;       // a fraction between 0 and 1
        double v;       // a fraction between 0 and 1

        HSV(double h, double s, double v) {
            this->h = h;
            this->s = s;
            this->v = v;
        }

        RGB toRGB();
    };


    RGB HSV::toRGB() {
        double hh, p, q, t, ff;
        long i;
        Palette::HSV in = *this;
        RGB out;

        if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
            out.r = in.v;
            out.g = in.v;
            out.b = in.v;
            return out;
        }

        hh = in.h;

        if (hh >= 360.0) hh = 0.0;

        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = in.v * (1.0 - in.s);
        q = in.v * (1.0 - (in.s * ff));
        t = in.v * (1.0 - (in.s * (1.0 - ff)));

        switch (i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
        }
        return out;
    }
}
