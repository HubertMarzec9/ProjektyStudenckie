#include "nonlinearfilterimageprocessor.h"
#include <iostream>

void NonlinearFilterImageProcessor::process(const QImage &src, QImage &dst) {
  borderImg = QImage(src.width()+2*n,src.height()+2*n,QImage::Format_ARGB32);
  border(src, borderImg, n);

  if(isMedianMode)
    medianFilter(borderImg, dst, n);

  if(isBilatrealMode)
    bilateralFilter(borderImg, dst, n);
}

void NonlinearFilterImageProcessor::setKernelSize(int size) {
  n = size;
}

void NonlinearFilterImageProcessor::setMin() {
  isMedianMode = false;
  isBilatrealMode = false;
}

void NonlinearFilterImageProcessor::setMax() {
  isMedianMode = false;
  isBilatrealMode = false;
}

void NonlinearFilterImageProcessor::setMedian() {
  isMedianMode = true;
  isBilatrealMode = false;
}

void NonlinearFilterImageProcessor::setBilateral() {
  isMedianMode = false;
  isBilatrealMode = true;
}

uchar getMedian(const int* ctr, int size){
  size /= 2;
  for(int i = 0; i <= 255; i++){
      size -= ctr[i];
      if(size <= 0) return i;
    }
  return 0;
}

void NonlinearFilterImageProcessor::medianFilter(const QImage& srcWithBorder, QImage& dst, int r){

  int W = srcWithBorder.width(); int number_pixels = (2*r+1)*(2*r+1);

  for(int y = 0; y < dst.height(); y++){
      QRgb* pixSrc = (QRgb*) srcWithBorder.scanLine((y+r));
      QRgb* pixDst = (QRgb*) dst.scanLine(y);
      int* R_ctr = new int[256]{};
      int* G_ctr = new int[256]{};
      int* B_ctr = new int[256]{};
      for(int iy = -r; iy <= r; iy++){
          for(int ix = -r; ix <= r; ix++){
              int pixPos = r+ix + iy*W;
              R_ctr[qRed(pixSrc[pixPos])]++;
              G_ctr[qGreen(pixSrc[pixPos])]++;
              B_ctr[qBlue(pixSrc[pixPos])]++;
            }
        }

      uchar R = getMedian(R_ctr, number_pixels );
      uchar G = getMedian(G_ctr, number_pixels );
      uchar B = getMedian(B_ctr, number_pixels );

      pixDst[0] = qRgb(R, G, B);

      for(int x = 1; x < dst.width(); x++){
          for(int iy = -r; iy <= r; iy++){
              int pixPos = (x-1)+iy*W;
              R_ctr[qRed(pixSrc[pixPos])]--;
              G_ctr[qGreen(pixSrc[pixPos])]--;
              B_ctr[qBlue(pixSrc[pixPos])]--;
            }
          for(int iy = -r; iy <= r; iy++){
              int pixPos = x+2*r + iy*W;
              R_ctr[qRed(pixSrc[pixPos])]++;
              G_ctr[qGreen(pixSrc[pixPos])]++;
              B_ctr[qBlue(pixSrc[pixPos])]++;
            }

          uchar R = getMedian(R_ctr, number_pixels );
          uchar G = getMedian(G_ctr, number_pixels );
          uchar B = getMedian(B_ctr, number_pixels );
          pixDst[x] = qRgb(R, G, B);

        }
      delete[] R_ctr;
      delete[] G_ctr;
      delete[] B_ctr;
    }
}

void NonlinearFilterImageProcessor::border(const QImage& originalImage,QImage& border,int n)
{
  for(int y =0 ;y<originalImage.height();y++)
    {
      memcpy(border.scanLine(y+n)+n*4,originalImage.scanLine(y),originalImage.width()*4);
    }
  for(int y=0 ;y<n;y++){
      memcpy(border.scanLine(n-y-1)+n*4,originalImage.scanLine(y),originalImage.width()*4);
    }
  for(int y=originalImage.height()-1;y>=originalImage.height()-n;y--)
    {
      memcpy(border.scanLine(originalImage.height()*2-y+n-1)+n*4,originalImage.scanLine(y),originalImage.width()*4);
    }
  for(int y=0;y<originalImage.height()+2*n;y++){
      QRgb* pixel_b=(QRgb*)border.scanLine(y);
      QRgb* pixel=pixel_b;
      pixel=pixel+n*2;
      for(int i=0;i<n;i++)
        {
          pixel_b[i]=pixel[-i];
        }
      pixel_b=pixel_b+originalImage.width()+n*2-1;
      pixel=pixel_b-n*2+1;
      for(int i=0;i<n;i++)
        {
          pixel_b[-i]=pixel[i];
        }
    }
}

double NonlinearFilterImageProcessor::weight(int i, int j, int center_i, int center_j, double sigma_color, double sigma_space, QImage& src, int color_diff)
{
  int space_diff = (i - center_i) * (i - center_i) + (j - center_j) * (j - center_j);
  double color_weight = exp(-color_diff * color_diff / (2 * sigma_color * sigma_color));
  double space_weight = exp(-space_diff / (2 * sigma_space * sigma_space));

  return color_weight * space_weight;
}

QRgb NonlinearFilterImageProcessor::filteredPixelValue(double sum_r, double weight_sum_r, double sum_g,double weight_sum_g, double sum_b, double weight_sum_b)
{
  int r = (sum_r / weight_sum_r + 0.5);
  int g = (sum_g / weight_sum_g + 0.5);
  int b = (sum_b / weight_sum_b + 0.5);
    return qRgb(qBound(0, r, 255), qBound(0, g, 255), qBound(0, b, 255));
}

void NonlinearFilterImageProcessor::bilateralFilter(QImage &src, QImage &dst, int kernel_size){
  int height = dst.height() - 1;
  int width = dst.width() - 1;
  double sum_r;
  double weight_sum_r;
  double sum_g;
  double weight_sum_g;
  double sum_b;
  double weight_sum_b;
  int x,y, color_diff;
  double w;
  QRgb dst_pixel,src_pixel;
  const double sigma_color_fixed = 20;
  const double sigma_space_fixed = 50;

  for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
        {
          sum_r = 0;
          weight_sum_r = 0;
          sum_g = 0;
          weight_sum_g = 0;
          sum_b = 0;
          weight_sum_b = 0;

          for (int ki = -(kernel_size/2); ki <= (kernel_size/2); ki++)
            {
              for (int kj = -(kernel_size/2); kj <= (kernel_size/2); kj++)
                {
                  x = i + ki;
                  y = j + kj;

                  if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                      src_pixel = src.pixel(x, y);
                      if (i >= 0 && i < height && j >= 0 && j < width)
                      {
                          dst_pixel = src.pixel(i, j);
                          color_diff = qRed(src_pixel) - qRed(dst_pixel);
                          w = weight(x, y, i, j, sigma_color_fixed, sigma_space_fixed, src, color_diff);
                          sum_r += w * qRed(src_pixel);
                          weight_sum_r += w;

                          sum_g += w * qGreen(src_pixel);
                          weight_sum_g += w;

                          sum_b += w * qBlue(src_pixel);
                          weight_sum_b += w;
                      }
                    }
                }
            }

          if (i >= 0 && i < height && j >= 0 && j < width)
            dst.setPixel(i, j, filteredPixelValue(sum_r, weight_sum_r, sum_g, weight_sum_g, sum_b, weight_sum_b));
        }
    }
}
