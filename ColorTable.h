#ifndef _COLOR_TABLE_H_
#define _COLOR_TABLE_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Color{
  public:
    Color();
    Color(const int& red, const int& green, const int& blue);
    int getRed( ) const;
    int getGreen( ) const;
    int getBlue( ) const;
    int getChannel(const int& channel) const;
    void setRed(const int& value);
    void setGreen(const int& value);
    void setBlue(const int& value );
    void setChannel(const int& channel, const int& value);
    void invert(const int& max_color_value);
    bool operator==(const Color& rhs) const;


  private:
    int mRed;
    int mGreen;
    int mBlue;
};

std::ostream& operator<<(std::ostream& os, const Color& color);

class ColorTable{
  public:
    ColorTable(const size_t& num_color);
    size_t getNumberOfColors( ) const;
    void setNumberOfColors(const size_t& num_color);
    const Color& operator[](const int& i) const;
    Color& operator[](const int& i);
    void setRandomColor(const int& max_color_value, const size_t& position);
    void insertGradient(const Color& color1, const Color& color2, const size_t& position1, const size_t& position2);
    int getMaxChannelValue( ) const;

  private:
    Color c;
    void error_Col();
    int get_color_grad(int init_color, int col_diff, int pos_diff, int idx);
    bool valid_pos(size_t pos);
    std::vector<Color> mColors;
};
#endif
