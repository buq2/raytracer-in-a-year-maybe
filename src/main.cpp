#include "image.hh"
#include "camera.hh"

int main(int argc, char *argv[]) 
{
    const auto aspect_ratio = 16.0/9.0;
    const int width = 400;
    Image im(width,static_cast<int>(width/aspect_ratio));
    Camera cam(aspect_ratio);
    //im.SetToTestImage();
    ObjectList objects;
    objects.emplace_back(new Sphere(Vec3(0.0,0.0,-1.0),0.5));
    objects.emplace_back(new Sphere(Vec3(0.5,0.0,-1.0),0.7));
    
    cam.Render(im, objects);
    im.Write("test.ppm");
    return 0;
}
