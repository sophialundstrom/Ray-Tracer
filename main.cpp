#include <vector>
#include "Disc.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Triangle.h"
#include "Box.h"
#include <memory>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main()
{
	const unsigned int width = 512, height = 512;
	const int channels = 3;
	const double lightRange = 330.0;
	double lightFactor = 1;
	double basecolor[3] = { 255, 255 , 255 };

	uint8_t* imageData = new uint8_t[width * height * channels];
	std::vector<std::unique_ptr<Shape>> shapes;

	Disc disc(Vector3D(255.0, 0.0, 0.0), Vector3D(width / 3.0 + 100, height / 2.0, 200), Vector3D(2, 0, -1), 100.0f);

	Sphere sphere(Vector3D(0.0, 255.0, 0.0), Vector3D(width / 2, height / 2, 200), 50.0f);

	Plane plane(Vector3D(0.0, 0.0, 255.0), Vector3D(0.0, 0.0, 1.0), Vector3D(0.0, 0.0, 300.0));

	Triangle triangle(Vector3D(0.0, 0.0, 255.0), Vector3D(200.0, height / 2, 250.0), Vector3D(150.0, 400.0, 100.0), Vector3D(400.0, 100.0, 200.0));

	Box box(Vector3D(50.0, 50.0, 50.0), Vector3D(350, 250, 200.0), Vector3D(50.0, 100.0, 200.0), Vector3D(45.0, 60.0, 30.0));

	//shapes.push_back(std::make_unique<Disc>(disc));
	shapes.push_back(std::make_unique<Sphere>(sphere));
	shapes.push_back(std::make_unique<Plane>(plane));
	shapes.push_back(std::make_unique<Triangle>(triangle));
	shapes.push_back(std::make_unique<Box>(box));

	for (unsigned int h = 0; h < height; ++h)
	{
		for (unsigned int w = 0; w < width; ++w)
		{
			Ray ray({ static_cast<float>(w), static_cast<float>(h), 0 }, { 0, 0, 1 });
			int currentPixel = (h * width + w) * channels;
			double currentClosest = std::numeric_limits<double>::max();

			imageData[currentPixel + 0] = basecolor[0];
			imageData[currentPixel + 1] = basecolor[1];
			imageData[currentPixel + 2] = basecolor[2];

			for (auto& shape : shapes)
			{
				double t = 0;
				if (shape->Intersection(ray, t) && t < currentClosest)
				{
					const Vector3D& color = shape->GetColor();

					lightFactor = 1 - (t / lightRange);
					
					lightFactor = lightFactor > 1 ? 1 : lightFactor;
					lightFactor = lightFactor < 0 ? 0 : lightFactor;

					imageData[currentPixel + 0] = static_cast<uint8_t>(color.GetX() * lightFactor);
					imageData[currentPixel + 1] = static_cast<uint8_t>(color.GetY() * lightFactor);
					imageData[currentPixel + 2] = static_cast<uint8_t>(color.GetZ() * lightFactor);
					currentClosest = t;
				}
			}
		}
	}

	stbi_write_jpg("Rendering.jpg", width, height, channels, imageData, 100);
	delete[] imageData;

	return 0;
}