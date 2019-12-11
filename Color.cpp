#include "ColorTable.h"

Color::Color(){
  mRed = 0;
  mGreen = 0;
  mBlue = 0;
}

Color::Color(const int& red, const int& green, const int& blue){
  mRed = red;
  mGreen = green;
  mBlue = blue;
}

int Color::getRed( ) const { return mRed; }
int Color::getGreen( ) const { return mGreen; }
int Color::getBlue( ) { return mBlue; }

int Color::getChannel(const int& channel) const{
  if (channel == 0){
    return getRed();
  }
  else if(channel == 1){
    return getGreen();
  }

  else if(channel == 2){
    return getBlue();
  }
  else{
    return -1;
  }
}

void Color::setRed(const int& value){
  if (value > 0){
    mRed = value;
  }
}
void Color::setGreen(const int& value){
  if(value > 0){
    mGreen = value;
  }
}
void Color::setBlue(const int& value){
  if (value > 0){
    mBlue = value;
  }
}

void Color::setChannel(const int& channel, const int& value){
    if (channel == 0){
      return setRed(value);
    }
    else if(channel == 1){
      return setGreen(value);
    }

    else if(channel == 2){
      return setBlue(value);
    }
    else{
      int a = 1;
      a++;
    }
}

void Color::invert(const int& max_color_value){
  int inv_red =  max_color_value; - getRed();
  int inv_green = max_color_value - getGreen();
  int inv_blue = max_color_value - getBlue();

  bool valid_val = (inv_red > 0) && (inv_blue > 0) && (inv_green > 0);

  if (valid_val){
    setRed(inv_red);
    setGreen(inv_green);
    setBlue(inv_blue);
  }
}

bool Color::operator==(const Color& rhs) const{
  bool same_red = (rhs.getRed() == getRed());
  bool same_green = (rhs.getGreen() == getGreen());
  bool same_blue = (rhs.getBlue() == getBlue());

  return same_red && same_blue && same_green;
}

std::ostream& operator<<(std::ostream& os, const Color& color){
  os << color.getRed() << ':' << color.getGreen() << ":" << color.getBlue() << std::endl;
  return os;
}
