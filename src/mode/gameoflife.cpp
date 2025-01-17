#include "mode/gameoflife.h"

uint8_t GameOfLife::countNeighbours(int row, int col)
{
  int i, j;
  int count = 0;
  for (i = row - 1; i <= row + 1; i++)
  {
    for (j = col - 1; j <= col + 1; j++)
    {
      count += this->buffer[i * 16 + j];
    }
  }
  count -= this->buffer[row * 16 + col];
  return count;
};

uint8_t GameOfLife::updateCell(int row, int col)
{
  uint8_t total = this->countNeighbours(row, col);
  if (total > 4 || total < 3)
  {
    return 0;
  }
  else if (this->buffer[row * 16 + col] == 0 && total == 3)
  {
    return 1;
  }
  else
  {
    return this->buffer[row * 16 + col];
  }
};

void GameOfLife::setup()
{
  memset(previous, 0, ROWS * COLS);
  for (int i = 0; i < ROWS * COLS; i++)
  {
    this->buffer[i] = (random(20)) ? 1 : 0;
  }
  Screen.setRenderBuffer(this->buffer);
  this->next();
};

void GameOfLife::next()
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      this->buffer[i * 16 + j] = this->updateCell(i, j);
      Screen.setPixelAtIndex(i * 16 + j, this->buffer[i * 16 + j]);
    }
  }
}

void GameOfLife::loop()
{
  this->next();

  if (memcmp(this->previous, this->buffer, sizeof(this->previous)) == 0)
  {
    this->setup();
    delay(1000);
  }

  for (int i = 0; i < ROWS * COLS; i++)
  {
    this->previous[i] = this->buffer[i];
  }
  delay(300);
};
