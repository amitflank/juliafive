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
int Color::getBlue( ) const { return mBlue; }

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
  if (value >= 0){
    mRed = value;
  }
}
void Color::setGreen(const int& value){
  if(value >= 0){
    mGreen = value;
  }
}
void Color::setBlue(const int& value){
  if (value >= 0){
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
  int inv_red =  max_color_value - getRed();
  int inv_green = max_color_value - getGreen();
  int inv_blue = max_color_value - getBlue();

  bool valid_val = (inv_red >= 0) && (inv_blue >= 0) && (inv_green >= 0);

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
  os << color.getRed() << ':' << color.getGreen() << ":" << color.getBlue();
  return os;
}

ColorTable::ColorTable(const size_t& num_color){
  for(unsigned int i = 0; i < num_color; i ++){
    mColors.push_back(Color());
  }
  error_Col();
}

void ColorTable::error_Col(){
  Color ec( -1, -1, -1 );
  c = ec;
}

size_t ColorTable::getNumberOfColors() const{
  return mColors.size();
}

void ColorTable::setNumberOfColors(const size_t& num_color){
  mColors.resize(num_color);
}

const Color& ColorTable::operator[](const int& i) const{
  if ((unsigned int) i >= getNumberOfColors() || (i < 0)){
    return c;
  }
  else{
    return mColors[i];
  }
}

Color& ColorTable::operator[](const int& i){
  if ((unsigned int) i >= getNumberOfColors() || (i < 0)){
    error_Col();
    return c;
  }
  else{
    return mColors[i];
  }
}

void ColorTable::setRandomColor(const int& max_color_value, const size_t& position){
  if (position < getNumberOfColors() && max_color_value >= 0){

    int red  = 0;
    int blue = 0;
    int green = 0;

    if (max_color_value != 0){
      red = rand() % max_color_value;
      green = rand() % max_color_value;
      blue = rand() % max_color_value;
    }

    mColors[position].setRed(red);
    mColors[position].setGreen(green);
    mColors[position].setBlue(blue);
  }
}

bool ColorTable::valid_pos(size_t pos){
  if (pos < getNumberOfColors()){
    return true;
  }
  return false;
}

int ColorTable::get_color_grad(int init_color, int col_diff, int pos_diff, int idx){
  if (pos_diff == 0){
    return init_color;
  }
  else{
    return init_color + idx * col_diff / pos_diff;
  }
}
void ColorTable::insertGradient(const Color& color1, const Color& color2, const size_t& position1, const size_t& position2){
  bool legal_rel_pos = position1 < position2;
  bool use_gradient = valid_pos(position1) && valid_pos(position2) && legal_rel_pos;

  if(use_gradient){
    int red_diff = color2.getRed() - color1.getRed();
    int green_diff = color2.getGreen() - color1.getGreen();
    int blue_diff = color2.getBlue() - color1.getBlue();

    int pos_diff = position2 - position1;

    for (unsigned int i = position1; i <= position2; i++){
      mColors[i].setRed(get_color_grad(color1.getRed(), red_diff, pos_diff, i - position1));
      mColors[i].setGreen(get_color_grad(color1.getGreen(), green_diff, pos_diff, i - position1));
      mColors[i].setBlue(get_color_grad(color1.getBlue(), blue_diff, pos_diff, i - position1));
    }
  }
}


int ColorTable::getMaxChannelValue( ) const{
  int max_val = 0;
  for(unsigned int i = 0; i < getNumberOfColors(); i ++){

    if (mColors[i].getRed() > max_val){
      max_val = mColors[i].getRed();
    }
    if(mColors[i].getGreen() > max_val){
      max_val = mColors[i].getGreen();
    }

    if(mColors[i].getBlue() > max_val){
      max_val = mColors[i].getBlue();
    }
  }
  return max_val;
}
