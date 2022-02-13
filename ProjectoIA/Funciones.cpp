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
    string comando = "notepad C:\\Users\\ediosn\\Pictures\\archivo.txt";
    system(comando.c_str());
}
void Funcion::apcion3() {
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "OmenCV" << endl;
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
    archivo << "Opcion1" << "\n" << endl;
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
    archivo << "Opcion3" << "\n" << endl;
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
    archivo << "Opcion4" << "\n" << endl;
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
    archivo << "Opcion5" << "\n" << endl;
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
    archivo << "Opcion6" << "\n" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion9() {
    string nombreArchivo = "C:/Users/ediosn/Pictures/archivo.txt";
    ofstream archivo;
    // Abrimos el archivo
    archivo.open(nombreArchivo.c_str(), fstream::out);
    // escritura
    archivo << "Opcion7" << "\n" << endl;
    // Finalmente lo cerramos
    archivo.close();
    cout << "Escrito correctamente";
}
void Funcion::apcion10() {
    system("EXIT");
    cout << "Escrito correctamente";
}