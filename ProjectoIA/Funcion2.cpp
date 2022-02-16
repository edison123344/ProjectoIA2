/**#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include "Cabecera.h"
using namespace cv;
using namespace std;
int h = 235;
int IndexOfBiggestContour;
int hMin = 33, sMin = 255, vMin = 255;
int hMax = 142, sMax = 139, vMax = 158;
int findBiggestContour(vector<vector<Point> > contours);
void functionTrackHSV(int, void*)
{
}
double huMoments[7] = {
0.198131,0.00257448,4.40244e-05,0.000217498,-1.94848e-08,2.98142e-06,-8.56171e-09,
};


double distanciaEuclidea(double momentosHu[7]) {
    double d = 0;
    for (int i = 0; i < 7; i++) {
        d += (momentosHu[i] - huMoments[i]) * (momentosHu[i] - huMoments[i]);
    }

    return sqrt(d);
}
int Detector2::inicio2()
{
    Funcion f = Funcion();

    VideoCapture video = VideoCapture(0);


    if (video.isOpened()) {
        Mat frame;
        Mat frameAux;
        Mat roi_image;
        Mat grayROI;
        Mat dif;
        Mat anterior;
        Mat th;
        double huMoments[7];
        Moments momentosRaw;

        double cx = 0, cy = 0;
        double dis = 0;
        //prosesamiento de la imagen
        Point p1(1000, 84);
        // cordenadas
        Point p2(650, 450);
        namedWindow("Video Original", WINDOW_AUTOSIZE);
        namedWindow("Modificacion", 0);
        createTrackbar("hMin", "Modificacion", &hMin, 180, functionTrackHSV, NULL);
        createTrackbar("sMin", "Modificacion", &sMin, 255, functionTrackHSV, NULL);
        createTrackbar("vMin", "Modificacion", &vMin, 255, functionTrackHSV, NULL);

        createTrackbar("hMax", "Modificacion", &hMax, 180, functionTrackHSV, NULL);
        createTrackbar("sMax", "Modificacion", &sMax, 255, functionTrackHSV, NULL);
        createTrackbar("vMax", "Modificacion", &vMax, 255, functionTrackHSV, NULL);
        createTrackbar("h", "Modificacion", &h, 255, functionTrackHSV, NULL);

        cv::Rect roi_rect;
        roi_rect.x = 650;
        roi_rect.y = 84;
        roi_rect.width = 350;
        roi_rect.height = 350;

        while (3 == 3) {
            video >> frame;
            if (frame.empty()) {
                break;
            }
            //rescalado video
            resize(frame, frame, Size(), 1.6, 1.5);
            //voltedo de imagen
            flip(frame, frame, 1);
            //sona de interes representada en el frame
            rectangle(frame, p1, p2, Scalar(255, 0, 0), 2);
            //copia de frame
            frameAux = frame.clone();
            //dibujado de la sona de interes 
            roi_image = frame(roi_rect);
            //creacion de una imagen gray
            cvtColor(roi_image, grayROI, COLOR_BGR2GRAY);

            //if (anterior.empty()) {
             //  anterior = grayROI.clone();
              //  cvtColor(roi_image, anterior, COLOR_BGR2GRAY);
            //}

            //absdiff(  anterior, grayROI, dif);

            inRange(grayROI, Scalar(hMin, sMin, vMin), Scalar(hMax, sMax, vMax), th);

            threshold(th, th, h, 255, THRESH_BINARY);


            momentosRaw = moments(th, true);

            cx = momentosRaw.m10 / momentosRaw.m00;
            cy = momentosRaw.m01 / momentosRaw.m00;

            //cout << "Area: " << momentosRaw.m00 << endl;

            HuMoments(momentosRaw, huMoments);


            vector<Vec4i> hierarchy;
            vector<vector<Point> > contours_hull;
            Mat Erode(Size(640, 420), CV_8UC1);
            cv::erode(th, Erode, cv::Mat(), cv::Point(-1, -1));
            Mat Dialate(Size(640, 420), CV_8UC1);
            cv::dilate(Erode, Dialate, cv::Mat(), cv::Point(-1, -1), 2);
            findContours(Dialate.clone(), contours_hull, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0)); // CV_CHAIN_APPROX_SIMPLE

            if (contours_hull.size() > 0)
            {
                //Encuentre el objeto de casco convexo para cada contorno
                vector<vector<Point> >hull(contours_hull.size());
                //guarda los puntos de defectos para cada contorno
                vector<vector<Vec4i>> defects(contours_hull.size());

                vector<vector<int> > hullsI(contours_hull.size());

                //encuentra el mayor contorno
                IndexOfBiggestContour = findBiggestContour(contours_hull);

                Point2f rect_points[4];
                vector<RotatedRect> minRect(contours_hull.size());

                vector<vector<Point> > contours_poly(contours_hull.size());
                vector<Rect> boundRect(contours_hull.size());


                try {
                    for (int i = 0; i < contours_hull.size(); i++)
                    {
                        convexHull(Mat(contours_hull[i]), hull[i], false);
                        convexHull(Mat(contours_hull[i]), hullsI[i], false);
                        convexityDefects(Mat(contours_hull[i]), hullsI[i], defects[i]);

                        if (IndexOfBiggestContour == i)
                        {
                            minRect[i] = minAreaRect(Mat(contours_hull[i]));

                            drawContours(roi_image, contours_hull, IndexOfBiggestContour, CV_RGB(255, 255, 255), 2, 8, hierarchy, 0, Point());
                            drawContours(roi_image, hull, IndexOfBiggestContour, CV_RGB(255, 0, 0), 2, 8, hierarchy, 0, Point());

                            approxPolyDP(Mat(contours_hull[i]), contours_poly[i], 3, true);
                            boundRect[i] = boundingRect(Mat(contours_poly[i]));

                            rectangle(roi_image, boundRect[i].tl(), boundRect[i].br(), CV_RGB(0, 0, 0), 2, 8, 0);

                            Point2f rect_points[4];
                            minRect[i].points(rect_points);

                            for (int j = 0; j < 4; j++)
                            {
                                line(roi_image, rect_points[j], rect_points[(j + 1) % 4], CV_RGB(255, 255, 0), 2, 8);
                            }

                        }
                    }
                }
                catch (Exception ex)
                {
                    //std::cout << "errror!!!" << std::endl;
                }

                for (int i = 0; i < contours_hull.size(); i++)
                {
                    size_t count = contours_hull[i].size();
                    //std::cout << "contador : " << count << std::endl;
                    if (count < 300)
                        continue;

                    vector<Vec4i>::iterator d = defects[i].begin();

                    while (d != defects[i].end()) {
                        Vec4i& v = (*d);
                        if (IndexOfBiggestContour == i) {
                            if (momentosRaw.m00 > 100) {

                                dis = distanciaEuclidea(huMoments);


                                int startidx = v[0];
                                Point ptStart(contours_hull[i][startidx]); // punto del contorno donde comienza el defecto
                                int endidx = v[1];
                                Point ptEnd(contours_hull[i][endidx]); // punto del contorno donde termina el defecto
                                int faridx = v[2];
                                Point ptFar(contours_hull[i][faridx]); // el más alejado del punto convexo del casco dentro del defecto
                                float depth = v[3] / 256; // distancia entre el punto más lejano y el casco convexo

                                if (depth > 4 && depth < 130)
                                {
                                    line(roi_image, ptStart, ptFar, CV_RGB(0, 255, 0), 2);
                                    line(roi_image, ptEnd, ptFar, CV_RGB(0, 255, 0), 2);
                                    circle(roi_image, ptStart, 4, Scalar(100, 0, 255), 2);
                                    //cout <<"punto1::" << startidx <<"punto2::" << endidx << "punto3::"<<faridx << endl;
                                    if (dis <= 0.03) {
                                        circle(roi_image, Point(cx, cy), 3, Scalar(10, 10, 200), 3);
                                        //modificacion de pociciones de la mano
                                        if (startidx >= 588 && endidx >= 622 && faridx >= 600) {
                                            //punto1::588punto2::622punto3::600                        
                                            cout << "mano abierta" << endl;
                                            // f.apcion1();
                                        }
                                        if (startidx >= 240 && endidx == 328 && faridx >= 301) {

                                            //punto1::240punto2::328punto3::301
                                            cout << "l" << endl;
                                            //f.apcion2();
                                        }
                                        if (startidx >= 303 && endidx == 409 && faridx >= 344) {
                                            // punto1::303punto2::409punto3::344

                                            cout << "dos dedos arriva menique y anular" << endl;
                                            // f.apcion3();
                                        }
                                        if (startidx >= 217 && endidx == 251 && faridx >= 234) {
                                            //punto1::217punto2::251punto3::234
                                            cout << " menique arriva" << endl;
                                            // f.apcion4();
                                        }
                                        if (startidx >= 304 && endidx == 381 && faridx >= 349) {
                                            //punto1::304punto2::381punto3::349
                                            cout << "like" << endl;
                                            // f.apcion5();
                                        }
                                    }

                                }
                                /**if (dis > 0.03) {
                                    circle(roi_image, Point(cx, cy), 3, Scalar(10, 100, 100), 3);
                                    //parte2
                                    if (startidx == 321 && endidx == 323 && faridx <= 322) {
                                        //punto1::207punto2::209punto3::208
                                        //punto1::321punto2::323punto3::322
                                        cout << "dedo uno" << endl;
                                        // f.apcion6();
                                    }
                                    if (startidx == 398 && endidx == 400 && faridx >= 399) {
                                        //punto1::398punto2::400punto3::399
                                        cout << "rock" << endl;
                                        // f.apcion7();
                                    }
                                    if (startidx >= 275 && endidx == 380 && faridx == 345) {
                                        //punto1::275punto2::380punto3::345
                                        cout << "pistola" << endl;
                                        //f.apcion8();
                                    }
                                    if (startidx == 373 && endidx == 401 && faridx == 380) {
                                        //punto1::373punto2::401punto3::380
                                        cout << "dos  dedos" << endl;
                                        // f.apcion9();
                                    }

                                    if (startidx >= 209 && endidx == 0 && faridx >= 339) {
                                        // punto1::209punto2::0punto3::339
                                        cout << "puno" << endl;
                                        //f.apcion10();

                                    }
                                }
                            }

                        }
                        d++;
                    }
                }
            }
            //resultados
            //imagen original
            imshow("Video Original", frame);
            //imshow("roi image", roi_image);
            //imshow("roi image gray", grayROI);
            imshow("roi image dif", th);
            //imshow("roi image anterior", anterior);


            if (waitKey(23) == 27) {
                break;
            }

        }
        video.release();
        destroyAllWindows();
    }
    return 0;
}


int findBiggestContour(vector<vector<Point> > contours)
{
    int indexOfBiggestContour = -1;
    int sizeOfBiggestContour = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contours[i].size() > sizeOfBiggestContour) {
            sizeOfBiggestContour = contours[i].size();
            indexOfBiggestContour = i;
        }
    }
    return indexOfBiggestContour;
}
*/