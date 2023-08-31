#include <iostream>
#include <windows.h>
#include <time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Ballon.h"
#include "Score.h"

using namespace std;
using namespace cv;

int main()
{
	// Initialisation de la fen�tre
	namedWindow("Jeu du ballon", WINDOW_AUTOSIZE);
	
	Mat image;
	VideoCapture cap;
	cap.set(CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CAP_PROP_FRAME_HEIGHT, 480);
	cap.open(0);

	cap >> image;

	vector<Scalar> colors = {
		Scalar(0, 0, 255),
		Scalar(0, 255, 0),
		Scalar(255, 0, 0),
		Scalar(255, 255, 0),
		Scalar(255, 0, 255),
		Scalar(0, 255, 255),
	};

	srand(time(NULL));

	Score score{ 0 };

	int step = -5;
	
	Ballon* b = new Ballon{
				Point(rand() % image.cols, image.rows),
				25,
				colors[rand() % colors.size()]
	};
	
	while (1) {
		try {

			// Si la touche x est appuyer sortir du programme
			if (GetAsyncKeyState('X')) break;

			cap >> image;

			Mat hsv;
			cvtColor(image, hsv, COLOR_BGR2HSV);
			Mat1b masqueVert;
			inRange(hsv, Scalar(66, 40, 40), Scalar(86, 255, 255), masqueVert);
			vector<vector<Point>> c;
			findContours(masqueVert, c, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			if (c.size() > 0) {
				// Trouver le plus grand contour
				int max = 0;
				for (int i = 1; i < c.size(); i++) {
					if (contourArea(c[i]) > contourArea(c[max])) {
						max = i;
					}
				}

				// Trouver le centre du contour
				Moments m = moments(c[max]);
				Point centre(m.m10 / m.m00, m.m01 / m.m00);
			
				// Pointeur
				circle(image, Point(centre.x, centre.y), 5, Scalar(0, 0, 255), -1);

				if (b->isHit(Point(centre.x, centre.y))) {
					score.incremente();
					b = new Ballon{
						Point(rand() % image.cols, image.rows),
						10 + rand() % 40,
						colors[rand() % colors.size()]
					};

					if (score.value() % 3 == 0) {
						step -= 5;
					}

				}
			}

			putText(image, score.toString(), Point(image.cols - 75, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);

			b->draw(image);

			b->deplaceY(step);

			if (b->center().y < 0) break;

			auto contours = b->getContour(image);

			imshow("Jeu du ballon", image);
			
			waitKey(33);
		}
		catch (Exception& e) {
			cout << e.what() << endl;
		}
	}

	cap >> image;

	putText(image, "GAME OVER", Point(100, 100), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 2);
	putText(image, "Score : " + score.toString(), Point(100, 200), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 2);

	imshow("Jeu du ballon", image);

	waitKey(0);

	destroyAllWindows();
	
	return 0;
}