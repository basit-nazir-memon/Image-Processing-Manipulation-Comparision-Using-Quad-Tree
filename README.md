# Image to Quad Tree Processing(Conversion, Reconstruction), Manipulation, and Comparision

The Image to Quad Tree Processing(Conversion, Reconstruction), Manipulation, and Comparision project is a console-based program written in C++ that reads an image, converts it into a quad tree representation, and then reconstructs the image from the quad tree. It also provides a mechanism to compare the original image with the generated image.

## Description

The program utilizes the quad tree data structure, where each internal node represents a quadrant in a two-dimensional space, and each leaf node represents a pixel in the image. The quad tree is constructed by recursively dividing the image into four quadrants until each quadrant contains only one pixel.

The project consists of the following steps:

1. Reading the Image: The program reads an image file in a supported format (e.g., JPEG, PNG) using the OpenCV library.

2. Quad Tree Conversion: The program converts the image into a quad tree by recursively dividing the image into quadrants and creating nodes for each quadrant.

3. Image Reconstruction: The program reconstructs the image from the quad tree by traversing the tree and assigning colors to the corresponding pixels.

4. Image Comparison: The program compares the original image with the generated image to measure the accuracy of the quad tree-based reconstruction. It may use metrics such as Mean Squared Error (MSE) or Structural Similarity Index (SSIM).

## Prerequisites

- C++ compiler
- OpenCV library (already included in the project)

## Getting Started

1. Clone the repository:

   ```shell
   git clone https://github.com/basit-nazir-memon/Image-Processing-Manipulation-Comparision-Using-Quad-Tree.git
   ```

2. Open the project in your preferred C++ development environment (e.g., Visual Studio, Code::Blocks).

3. Build the project to compile the source code.

## Usage

1. Run the compiled executable or debug the project in your development environment.

2. Provide the path to the image file when prompted by the program.

3. The program will convert the image into a quad tree representation and reconstruct the image from the quad tree.

4. After the reconstruction, the program may display or save the generated image.

5. The program will also provide a comparison between the original image and the generated image, using a suitable metric to evaluate the reconstruction accuracy.

6. Follow the instructions on the console to navigate through the program and view the results.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgments

- [OpenCV Library](https://opencv.org/) - Used for image processing and manipulation
