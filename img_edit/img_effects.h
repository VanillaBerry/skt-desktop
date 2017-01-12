#ifndef IMG_EFFECTS_H
#define IMG_EFFECTS_H

bool toGray(QImage &img_orig);
void GrayGaussBlur(QImage &img);
void GrayBlur(QImage &img);
void GrayDivision(QImage &img_to_process, QImage image_divisor, int intensity);
void GrayDivision(QImage &img_to_process, int intensity);

int Gray_from_RGB(QRgb color);

#endif // IMG_EFFECTS_H
