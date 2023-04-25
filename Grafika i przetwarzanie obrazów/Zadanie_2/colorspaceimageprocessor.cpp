#include "colorspaceimageprocessor.h"

#include <cmath>
#include <QColor>
#include <iostream>

void ColorspaceImageProcessor::process(const QImage &src, QImage &dst) {
  const QRgb *src_data = reinterpret_cast<const QRgb*>(src.bits());
  QRgb *dst_data = reinterpret_cast<QRgb*>(dst.bits());
  int sizeInBytes = dst.sizeInBytes()/4;
  QRgb tmp;
  for(int i=0; i<sizeInBytes; i++){
      tmp = src_data[i];
      tmp = fromRGB(tmp);
      if(flaga == 0 || flaga ==1)
        tmp = processOffset(tmp);
      if(flaga == 2)
        tmp = processOfflab (tmp);
      tmp = toRGB(tmp);
      dst_data[i] = tmp;
    }
}

void ColorspaceImageProcessor::setOffset(int c0, int c1, int c2) {
  offset[0] = c0;
  offset[1] = c1;
  offset[2] = c2;
}

QRgb ColorspaceImageProcessor::processOffset(QRgb val) {
  int r = (qRed(val)+offset[0])%256;
  int g = std::clamp(qGreen(val)+offset[1], 0, 255);
  int b = std::clamp(qBlue(val)+offset[2], 0, 255);
  return qRgba(r,g,b,qAlpha(val));
}

QRgb ColorspaceImageProcessor::processOfflab(QRgb val)
{
    int r=std::clamp(qRed(val)+offset[0], 0, 255);
    int g=std::clamp(qGreen(val)+offset[1], 0, 255);
    int b=std::clamp(qBlue(val)+offset[2], 0, 255);
    return  qRgba(r,g,b,qAlpha(val));
}

void ColorspaceImageProcessor::setRgbMode(){
  flaga = 0;
  toRGB = fromRGB = [](QRgb val){return val;};
}

void ColorspaceImageProcessor::setHslMode(){
  flaga = 1;
  toRGB = hslToRgb;
  fromRGB = rgbToHsl;
}

void ColorspaceImageProcessor::setClabMode(){
  flaga =2;
  toRGB = clabToRgb;
  fromRGB = rgbToClab;
}

double ColorspaceImageProcessor::f_inverse(double t){
  if (t > 6.0 / 29.0) {
      return t * t * t;
    } else {
      return 3.0 * pow(6.0 / 29.0, 2) * (t - 4.0 / 29.0);
    }
}

double ColorspaceImageProcessor::funkcjaHelp(double k){
  if (k > pow(6.0 / 29.0, 3.0)) {
      return pow(k, 1.0 / 3.0);
    } else {
      return (1.0 / 3.0) * pow(29.0 / 6.0, 2.0) * k + (4.0 / 29.0);
    }
}

QRgb ColorspaceImageProcessor::clabToRgb(QRgb val) {
  float l,a,b;
    float rgb[3];
    l=(float)qRed(val)/2.55f;
    a=(float)qGreen(val)-128.f;
    b=(float)qBlue(val)-128.f;
    float xyz[3],fx,fy,fz;
    float Q=6.f/29.f;

    fx=(l+16)/116+a/500;
    fy=(l+16)/116;
    fz=(l+16)/116-b/200;
    if(fx>Q)
        fx=pow(fx,3);
    else
        fx=3*Q*Q*(fx-4.f/29.f);
    if(fy>Q)
        fy=pow(fy,3);
    else
        fy=3*Q*Q*(fy-4.f/29.f);
    if(fz>Q)
        fz=pow(fz,3);
    else
        fz=3*Q*Q*(fz-4.f/29.f);

    xyz[0]=fx*0.9505f;
    xyz[1]=fy;
    xyz[2]=fz*1.0891f;

    rgb[0]=xyz[0]*3.2404542f -xyz[1]*1.5371385f -xyz[2]*0.4985314f;
    rgb[1]=-xyz[0]*0.9692660f +xyz[1]* 1.8760108f + xyz[2]*0.0415560f;
    rgb[2]=xyz[0]*0.0556434f -xyz[1]*0.2040259f +xyz[2]* 1.0572252f;
    for(int i=0;i<2;i++)
    {
        if(rgb[i]> 0.0031308f)
            rgb[i] =(float) pow((rgb[i] * 1.055f) ,1.f/2.4f)-0.055f;
        else
            rgb[i] *= 12.92f;
    }
    int clampedr,clampedg,clampedb;
    rgb[0]*=255;
    rgb[1]*=255;
    rgb[2]*=255;
    clampedr=std::clamp((int)rgb[0], 0, 255);
    clampedg=std::clamp((int)rgb[1], 0, 255);
    clampedb=std::clamp((int)rgb[2], 0, 255);
    return qRgba(clampedr,clampedg,clampedb,qAlpha(val));
}

QRgb ColorspaceImageProcessor::rgbToClab(QRgb val)
{
  float rgb[3];
     rgb[0]=(float)qRed(val)/255.f;
     rgb[1]=(float)qGreen(val)/255.f;
     rgb[2]=(float)qBlue(val)/255.f;
     for(int i=0;i<2;i++)
     {
         if(rgb[i]> 0.04045f)
             rgb[i] =(float) pow(((rgb[i] + 0.055f) / 1.055f) ,2.4f);
         else
             rgb[i] /= 12.92f;
     }
     float xyz[3];
     xyz[0]=(rgb[0]*0.4124f+rgb[1]*0.3576f+rgb[2]*0.1805f)/0.9505f;//dzielenie to odnośnik do punktu bieli D65
     xyz[1]=(rgb[0]*0.2126f+rgb[1]*0.7152f+rgb[2]*0.0722f)/1.f; //macierz srgb
     xyz[2]=(rgb[0]*0.0193f+rgb[1]*0.1192f+rgb[2]*0.9505f)/1.0891f;
     float l,a,b,fx,fy,fz;
     float Q=6.f/29.f;

     if(xyz[0]>Q*Q*Q)
         fx=pow(xyz[0],1.f/3.f);
     else
         fx=xyz[0]/(3*Q*Q)+4.f/29.f;
     if(xyz[1]>Q*Q*Q)
         fy=pow(xyz[1],1.f/3.f);
     else
         fy=xyz[1]/(3*Q*Q)+4.f/29.f;
     if(xyz[2]>Q*Q*Q)
         fz=pow(xyz[2],1.f/3.f);
     else
         fz=xyz[2]/(3*Q*Q)+4.f/29.f;

     l=(116.f*fy)-16.f;
     a=500.f*(fx-fy);
     b=200.f*(fy-fz);

     l*=2.55f;
     a+=128.f;
     b+=128.f;

     int clampedl,clampeda,clampedb;

     clampedl=std::clamp((int)l, 0, 255);
     clampeda=std::clamp((int)a, 0, 255);
     clampedb=std::clamp((int)b, 0, 255);
     return qRgba(clampedl,clampeda,clampedb,qAlpha(val));
}

QRgb ColorspaceImageProcessor::rgbToHsl(QRgb val){
  double r = qRed(val) / 255.0;
  double g = qGreen(val) / 255.0;
  double b = qBlue(val) / 255.0;

  double h, s, l;

  double min = std::min(r, std::min(g, b));
  double max = std::max(r, std::max(g, b));
  double delta = max - min;

  l = (max + min) / 2.0;

  if (delta == 0)
    {
      h = s = 0; // achromatic
    }
  else
    {
      s = l > 0.5 ? delta / (2 - max - min) : delta / (max + min);

      if (max == r)
        {
          h = (g - b) / delta + (g < b ? 6 : 0);
        }
      else if (max == g)
        {
          h = (b - r) / delta + 2;
        }
      else
        {
          h = (r - g) / delta + 4;
        }

      h /= 6;
    }

  return qRgb(h * 255, s * 255, l * 255);
}

QRgb ColorspaceImageProcessor::hslToRgb(QRgb val){
  double h = qRed(val) / 255.0;
  double s = qGreen(val) / 255.0;
  double l = qBlue(val) / 255.0;

  double r, g, b;

  if (s == 0)
    {
      r = g = b = l;
    }
  else
    {
      double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
      double p = 2 * l - q;
      r = hueToRgb(p, q, h + 1.0 / 3.0);
      g = hueToRgb(p, q, h);
      b = hueToRgb(p, q, h - 1.0 / 3.0);
    }
  r = std::clamp(r, 0.0, 255.0);
  g = std::clamp(g, 0.0, 255.0);
  b = std::clamp(b, 0.0, 255.0);
  return qRgb(r*255, g*255, b*255);
}

double ColorspaceImageProcessor::hueToRgb(double p, double q, double t)
{
  if (t < 0) t += 1;
  if (t > 1) t -= 1;
  if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
  if (t < 1.0 / 2.0) return q;
  if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
  return p;
}
