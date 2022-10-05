#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("../alma.png");
  
  StickerSheet sheet(alma,5);
  Image p;
  p.readFromFile("../bow1.png");
  Image c;
  c.readFromFile("../The_Weeknd.png");
  Image x;
  x.readFromFile("../ariana.png");
  x.scale(0.25);
  c.scale(0.18);
  sheet.addSticker(c, 370, 10);
  sheet.addSticker(p, 35, 400);
  sheet.addSticker(x, 600, 400);
  Image out = sheet.render();
  out.writeToFile("../myimage.png");
  return 0;
}
