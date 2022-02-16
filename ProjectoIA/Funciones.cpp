#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include "Cabecera.h"
using namespace cv;
using namespace std;



void Funcion::apcion1() {
    VideoCapture cap("C:/Users/ediosn/Documents/video.mp4");
    if (!cap.isOpened())
    {
        cout << "no abrio el archivo. \n";
    }
    double fps = cap.get(CAP_PROP_FPS);
    namedWindow("Video", WINDOW_AUTOSIZE);
    while (1)
    {
        Mat frame;
        if (!cap.read(frame))
        {
            cout << "\n nose abrio el video. \n";
            break;
        }
        imshow("Video", frame);
        if (waitKey(33) == 'a')
        {
            break;
        }
    }
}
void Funcion::apcion2() {

    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "l" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion3() {
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "dos dedos arriva" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion4() {
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "menique arriva" << "\n" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion5() {
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "like" << "\n" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion6() {
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "dedo uno" << "\n" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion7() {
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "rock" << "\n" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion8() {
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "pistola" << "\n" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion9() {
    //string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "dos dedos" << "\n" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";

}
void Funcion::apcion10() {

    char cadena[128];
    ifstream fe("C:/Users/ediosn/Pictures/archivo.txt");
    while (!fe.eof()) {
        fe >> cadena;
        cout << cadena << endl;
    }
    fe.close();
}