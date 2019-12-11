#ifndef _COLOR_H_
#define _COLOR_H_


class Color{
  public:
    Color();
    Color(const int& red, const int& green, const int& blue);
    int getRed( ) const;
    int getGreen( ) const;
    int getBlue( );
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

#endif
