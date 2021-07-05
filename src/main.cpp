#include "image.hh"

int main(int argc, char *argv[]) 
{
    Image im(255,255);
    im.SetToTestImage();
    im.Write("test.ppm");
    return 0;
}
