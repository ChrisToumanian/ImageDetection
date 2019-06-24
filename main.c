#include "bitmap.c"

#define ROW 10
#define COLUMN 10
#define THRESHOLD 51

unsigned char image[ROW][COLUMN];
int test;

void createImage()
{
  for (int x = 0; x < ROW; x++)
    for (int y = 0; y < COLUMN; y++)
      image[x][y] = 255;

  image[7][6] = 50;
  image[7][7] = 28;
  image[7][8] = 19;
  image[8][6] = 0;
  image[8][7] = 5;
  image[8][6] = 34;
  image[9][7] = 24;
  image[9][6] = 17;
  image[2][2] = 40;
  image[3][2] = 2;
  image[2][3] = 12;
  image[3][3] = 23;
}

void printImage()
{
  for (int y = 0; y < COLUMN; y++)
  {
    for (int x = 0; x < ROW; x++)
    {
      printf("%03i%s", image[x][y], ", ");
    }
    printf("\n");
  }
}

void printCoordinateOnImage(int xPos, int yPos)
{
  printf("\n");
  for (int y = 0; y < COLUMN; y++)
  {
    for (int x = 0; x < ROW; x++)
    {
      if (x == xPos && y == yPos) printf("XXX, ");
      else printf("000, ");
    }
    printf("\n");
  }
  printf("\n");
}

void findBlobCenter(unsigned char x, unsigned char y)
{
  int leftX = 0;
  int rightX = 0;
  int downY = 0;
  int upY = 0;
  int i;
  int width;
  int height;
  float offsetX;
  float offsetY;
  float xCoord;
  float yCoord;

  // Find dark pixels to the right
  for (i = x + 1; i < ROW; i++)
  {
    if (image[i][y] < THRESHOLD) rightX++;
    else break;
  }

  // Find dark pixels to the left
  for (i = x - 1; i > 0; i--)
  {
    if (image[i][y] < THRESHOLD) leftX++;
    else break;
  }

  // Find dark pixels downward
  for (i = y + 1; i < COLUMN; i++)
  {
    if (image[x][i] < THRESHOLD) downY++;
    else break;
  }

  // Find dark pixels upward
  for (i = y - 1; i > 0; i--)
  {
    if (image[x][i] < THRESHOLD) upY++;
    else break;
  }

  // Calculate dimensions
  width = rightX + leftX + 1;
  height = downY + upY + 1;

  // Calculate offset from coordinates
  offsetX = (float) (rightX - leftX) / 2;
  offsetY = (float) (downY - upY) / 2;
  xCoord = x + offsetX;
  yCoord = y + offsetY;

  printf("%.2f%s%.2f", xCoord, ", ", yCoord);
  printf("%s%i%s%i%s", " (", width, " x ", height, ")\n");
  printCoordinateOnImage(xCoord, yCoord);
}

void findBlobs()
{
  for (int x = 0; x < ROW; x++)
    for (int y = 0; y < COLUMN; y++)
      if (image[x][y] < THRESHOLD) findBlobCenter(x, y);
}

int main()
{
  printf("Image Data:\n");
  createImage();
  printImage();
  printf("\nCoordinates:\n");
  findBlobs();
  printf("\n");
  test = 2;
  saveImageBitmap("image.bmp", ROW, COLUMN, image);
  
  return 0;
}
