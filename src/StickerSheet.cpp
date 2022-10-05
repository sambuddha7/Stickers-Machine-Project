#include "StickerSheet.h"
#include "Image.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;
using namespace cs225;
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = picture;
    max_ = max;
}
void StickerSheet::changeMaxStickers(unsigned max) {
    if (max < vect_image_.size() ) {
        unsigned i = 0;
        while (i <= vect_image_.size() - max) {
            removeSticker(vect_image_.size() - 1);
            ++i;
        }
    }
    max_ = max;
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (vect_image_.size() < max_) {
        vect_image_.push_back(&sticker);
        vector<unsigned> p = {x, y};
        map_.push_back(p);
        return vect_image_.size() - 1;
    }
    return -1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < vect_image_.size() && index >= 0) {
        vector<unsigned> p = {x, y};
        map_[index] = p;
        return true;
    }
    return false;
}
void StickerSheet::removeSticker(unsigned index) {
    if (index < vect_image_.size() && index >= 0) {
        if (index == vect_image_.size() - 1) {
            map_.pop_back();
            vect_image_.pop_back();
        } 
        else {
            map_.erase(map_.begin() + index);
            vect_image_.erase(vect_image_.begin() + index);
        }
    }
}
Image* StickerSheet::getSticker(unsigned index) {
    if (index < vect_image_.size() && index >= 0) {
        return vect_image_[index];
    }
    return NULL;
}
Image StickerSheet::render() const {
    unsigned max_width = base_.width();
    unsigned max_height = base_.height();
    Image out = base_;
    for (unsigned i = 0;i < vect_image_.size(); ++i) {
        unsigned x = map_.at(i).at(0) + vect_image_[i]->width();
        unsigned y = map_.at(i).at(1) + vect_image_[i]->height();
        if (x > max_width) max_width = x;
        if (y > max_height) max_height = y;
        out.resize(max_width, max_height);
        Image sticker = *vect_image_[i];
        unsigned mx = map_.at(i).at(0);
        unsigned ny = map_.at(i).at(1);
        for (unsigned j = mx; j < mx + sticker.width(); ++j) {
            for (unsigned k = ny; k < ny + sticker.height(); ++k) {
                HSLAPixel& pixel = sticker.getPixel(j - mx, k - ny);
                HSLAPixel& iter = out.getPixel(j, k);
                if (pixel.a != 0) {
                    iter = pixel;
                }
            }
        }
       
    }
    return out;
}