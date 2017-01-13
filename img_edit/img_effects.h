#ifndef IMG_EFFECTS_H
#define IMG_EFFECTS_H

bool toGray(QImage &img_orig);
void GrayGaussBlur(QImage &img);
void GrayBlur(QImage &img);
void GrayDivision(QImage &img_to_process, QImage image_divisor, int intensity);
void GrayDivision(QImage &img_to_process, int intensity);

int Gray_from_RGB(QRgb color);
int * Chain(QImage img);
int * EnergyChain(QImage img);
int * LessEnergyWay(QImage img);

void ClockwiseRotation(QImage &img_orig);
void CounterClockwiseRotation(QImage &img_orig);

int LiqudScale(QImage &img_orig, int new_width);
int DeleteOneChain(QImage &img_orig);
int DeleteTwoChains(QImage &img_orig);

void HorizontalMirror(QImage &img_orig);
void VerticalMirror(QImage &img_orig);

#endif // IMG_EFFECTS_H
