#include "Image.h"
#include <iostream>
using namespace cs225;
    void Image::lighten() {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (pixel.l >= 0.9) pixel.l = 1;
                else pixel.l += 0.1;
            }
        }
    }
    void Image::lighten(double amount) {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (pixel.l + amount >= 1) pixel.l = 1;
                else pixel.l += amount;
            }
        }
    }
    void Image::darken() {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (pixel.l <= 0.1) pixel.l = 0;
                else pixel.l -= 0.1;
            }
        }
    }
    void Image::darken(double amount) {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (pixel.l - amount <= 0) pixel.l = 0;
                else pixel.l -= amount;
            }
        }
    }
    void Image::saturate() {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (pixel.s >= 0.9) pixel.s = 1;
                else pixel.s += 0.1;
            }
        }
    }
    void Image::saturate(double amount) {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (pixel.s + amount >= 1) pixel.s = 1;
                else pixel.s += amount;
            }
        }
    }
    void Image::desaturate() {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (pixel.s <= 0.1) pixel.s = 0;
                else pixel.s -= 0.1;
            }
        }

    }
    void Image::desaturate(double amount) {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (pixel.s - amount <= 0) pixel.s = 0;
                else pixel.s -= amount;
            }
        }

    }
    void Image::greyscale() {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                pixel.s = 0;
            }
        }
    }
    void Image::rotateColor(double degrees) {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if (degrees >= 0) {
                    pixel.h += degrees;
                    int H = int(pixel.h);
                    H = H % 360;
                    pixel.h = double(H);
                } else {
                    pixel.h += degrees;
                    int H = int(pixel.h);
                    H = H % 360;
                    if (H < 0) pixel.h = double(360 + H);
                    else pixel.h = double(H);
                }
                
            }
        }
    }
    void Image::illinify() {
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                HSLAPixel &pixel = this->getPixel(j, i);
                if ((pixel.h < 114 && pixel.h >=0) || (pixel.h >= 293 && pixel.h <= 360)) {
                    pixel.h = 11;
                } else {
                    pixel.h = 216;
                }
            }
        }
    }
    void Image::scale(double factor) {
        if (factor == 1.0) return;
        PNG og_png = PNG(*this);
        unsigned int nw = width() * factor;
        unsigned int nh = height() * factor;
        resize(nw, nh);
        for (unsigned int i = 0; i < height(); ++i) {
            for (unsigned int j = 0; j < width(); ++j) {
                getPixel(j, i) = og_png.getPixel(j / factor, i/ factor);
            }
        }

    }
    void Image::scale(unsigned w, unsigned h) {
        double width_factor = double(double(w) / width());
        double height_factor = double(double(h) / height());
        scale(std::min(width_factor, height_factor));
    }