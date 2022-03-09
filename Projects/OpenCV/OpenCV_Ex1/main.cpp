#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
  // *Display image*

  // Set path for image
  std::string path = "../OpenCV_Ex1/imgs/legoHouse.jpg";

  // Create image object in color
  Mat img_color = imread(path, 1);

  // Display image in color
  imshow("Color", img_color);

  // Create image object in grayscale
  Mat img_grayscale = imread(path, 1);

  // Display image in grayscale
  imshow("Grayscale", img_grayscale);

  // Save grayscale image
  imwrite("../OpenCV_Ex1/imgs/legoHouse_grayscale.jpg", img_grayscale);

  // Wait for a keystroke before moving on
  waitKey(0);
  // Destroy all windows
  destroyAllWindows();

  // *Rotate image*
  // Create image object in color for rotating
  Mat img_rotated = img_color;

  // Different ways of rotating below
  cv::rotate(img_color, img_rotated, cv::ROTATE_90_COUNTERCLOCKWISE);

  // Display rotated image
  imshow("Rotated", img_rotated);

  // Display image in color
  imshow("Color", img_color);

  // Wait for a keystroke before moving on
  waitKey(0);
  // Destroy all windows
  destroyAllWindows();

  // Save rotated image
  imwrite("../OpenCV_Ex1/imgs/legoHouse_rotated.jpg", img_rotated);

  // Re-assign for different ways to rotate
  Mat img_transposed_flipped = img_color;

  // Rotate by transposing and flipping
  cv::transpose(img_color, img_transposed_flipped);
  cv::flip(img_transposed_flipped, img_transposed_flipped, 0);

  // Display rotated image
  imshow("Transposed and Flipped", img_transposed_flipped);

  // Display image in color
  imshow("Color", img_color);

  // Wait for a keystroke before moving on
  waitKey(0);
  // Destroy all windows
  destroyAllWindows();

  // Re-re-assign for different ways to rotate
  Mat img_rotated_SPA(img_color.cols, img_color.rows, img_color.type());

  CV_Assert(img_color.type() == CV_8UC3);

  // Transpose image using SPA (Authored by Thorbjoern Mosekjaer Iversen @ SDU Robotics)
  for(int i=0; i<img_color.rows; i++){
      for(int j=0; j<img_color.cols; j++){
          img_rotated_SPA.at<Vec3b>(j,i) = img_color.at<Vec3b>(i,j);
      }
  }

  // Flip image
  cv::flip(img_rotated_SPA, img_rotated_SPA, 0);

  imshow("Rotated w/ single pixel access",img_rotated_SPA);

  // Display image in color
  imshow("Color", img_color);

  // Wait for a keystroke before moving on
  waitKey(0);
  // Destroy all windows
  destroyAllWindows();

  // *Color segmenting*

  return 0;
}
