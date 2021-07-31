#include "image.hh"
#include "camera.hh"

int main(int argc, char *argv[]) 
{
    const auto aspect_ratio = 16.0/9.0;
    const int width = 400;
    Image im(width,width/aspect_ratio);
    Camera cam(aspect_ratio);
    //im.SetToTestImage();
    cam.Render(im);
    im.Write("test.ppm");
    return 0;
}
