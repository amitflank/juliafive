#include "NumberGrid.h"


NumberGrid::NumberGrid(): mHeight(300), mWidth(400),
mMax(255),mGrid_vals(mHeight * mWidth, 0){
}

NumberGrid::NumberGrid(const int& height, const int& width): mHeight(height),
mWidth(width), mMax(255),mGrid_vals(mHeight * mWidth, 0){
}

NumberGrid::~NumberGrid(){}

void NumberGrid::calculateAllNumbers( ){
  int cols = getWidth();
  int rows = getHeight();
  int num = 0;

  for(int row = 0; row < rows; row++){
    for(int col = 0; col < cols; col++){
        num = calculateNumber(row, col);
        setNumber(row, col, num);
    }
  }
}

int NumberGrid::getHeight() const{
  return mHeight;
}

int NumberGrid::getWidth() const{
  return mWidth;
}

int NumberGrid::getMaxNumber() const{
  return mMax;
}

void NumberGrid::setGridSize(const int& height, const int& width){
  if(height >= 2 && width >= 2){
    mGrid_vals.resize(height * width);
    mHeight = height;
    mWidth = width;
  }
}

void NumberGrid::setMaxNumber(const int& number){
  if(number >= 0){
    mMax = number;
  }
}

const std::vector<int>& NumberGrid::getNumbers() const{
  return mGrid_vals;
}

int NumberGrid::index(const int& row, const int& column) const{
  return row * getWidth() + column;
}

bool NumberGrid::indexValid(const int& row, const int& column) const{
  bool validRow = row >= 0 && row <  getHeight();
  bool validCol = column >= 0 && column <  getWidth();
  return validRow && validCol;
}

bool NumberGrid::numberValid(const int& number) const{
  bool nonNeg = number >= 0;
  bool nonOverMax = number <= getMaxNumber();
  return nonNeg && nonOverMax;
}

int NumberGrid::getNumber(const int& row, const int& column) const{
  if(indexValid(row, column)){
    int idx = index(row, column);
    return getNumbers()[idx];
  }
  return -1;
}

void NumberGrid::setNumber(const int& row, const int& column, const int& number){
  if(numberValid(number) && indexValid(row, column)){
    int idx = index(row, column);
    mGrid_vals[idx] = number;
  }
}

void NumberGrid::setPixel(int row, int col, PPM& ppm) const{
  int num = getNumber(row, col);
  if(num == 0){
    ppm.setPixel(row, col, 0, 0, 0);
  }
  else if(num == getMaxNumber()){
    ppm.setPixel(row, col, 63, 31, 31);
  }
  else if(num % 8 == 0){
    ppm.setPixel(row, col, 63, 63, 63);
  }
  else if(num % 8 == 1){
    ppm.setPixel(row, col, 63, 31, 31);
  }
  else if(num % 8 == 2){
    ppm.setPixel(row, col, 63, 63, 31);
  }
  else if(num % 8 == 3){
    ppm.setPixel(row, col, 31, 63, 31);
  }
  else if(num % 8 == 4){
    ppm.setPixel(row, col, 0, 0, 0);
  }
  else if(num % 8 == 5){
    ppm.setPixel(row, col, 31, 63, 63);
  }
  else if(num % 8 == 6){
    ppm.setPixel(row, col, 31, 31, 63);
  }
  else {
    ppm.setPixel(row, col, 63, 31, 63);
  }

}
void NumberGrid::setPPM(PPM& ppm) const{
  int width = getWidth();
  int height = getHeight();
  ppm.setMetaData(width, height, 63);
  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      setPixel(row, col, ppm);
    }
  }
}

void NumberGrid::setPixelFromColor(int row, int col, Color c, PPM& ppm) const{
  ppm.setPixel(row, col, c.getRed(), c.getGreen(), c.getBlue());
}

void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors ) const{
  if (colors.getNumberOfColors() > 2) {
    int height = getHeight();
    int width = getWidth();

    ppm.setWidth(width);
    ppm.setHeight(height);
    ppm.setMaxColorValue(colors.getMaxChannelValue());

    for(unsigned int z = 0; z < colors.getNumberOfColors() ; z++){
      std::cout << colors[z] <<std::endl;

    }

    for(int row = 0; row < height; row++){
      for(int col = 0; col < width; col++){

        if (getNumber(row, col) == getMaxNumber()){
          setPixelFromColor(row, col, colors[colors.getNumberOfColors() - 1], ppm);

        }
        else if(getNumber(row, col) == 0){
            //std::cout << "row " << row << " col " << col <<std::endl;
            setPixelFromColor(row, col, colors[colors.getNumberOfColors() - 2], ppm);
        }
        else{
            setPixelFromColor(row, col, colors[getNumber(row, col) % (colors.getNumberOfColors() - 2)], ppm);
            
        }
      }
    }
  }
}
