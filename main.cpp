#include <opencv2/highgui.hpp>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "stdlib.h"
#include <unistd.h>

using namespace cv;
using namespace std;


int main() {

    int i = 0;

    VideoCapture cap;
    Mat imgDiff, imagen, imgActual, imgAnterior;

    if(!cap.open(0))
		cout << "No se puede acceder a la webcam." << endl;

    // para trabajar con una matriz pequeña
    cap.set(3, 512);
    cap.set(4, 288);
    
    while(true)
	{	
		
        int difference = 0;
		cap >> imagen;
		
        // leemos el primer frame
        cap.read(imgAnterior);
        cvtColor(imgAnterior, imgAnterior, COLOR_BGR2GRAY);
        GaussianBlur(imgAnterior, imgAnterior, Size(21, 21), 0);
        sleep(.2);

        // leemos el segundo frame
        cap.read(imgActual);
        cvtColor(imgActual, imgActual, COLOR_BGR2GRAY);
        GaussianBlur(imgActual, imgActual, Size(21, 21), 0);

        // comparamos los frames y lo guardamos en imgDiff
        absdiff(imgAnterior, imgActual, imgDiff);

        // calculamos la diferencia
        difference = countNonZero(imgDiff);
        printf("Diferencia: %d\n", difference);

        // si la diferencia es mayor a la referencia entonces existe movimiento
        if (difference > 35000) {
            putText(imagen, "MOVIMIENTO DETECTADO", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
        } else {
            putText(imagen, "TODO TRANQUI", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,255,0),2);            
        }

        cv::namedWindow( "Deteccion de movimiento", cv::WINDOW_AUTOSIZE );
        imshow("Deteccion de movimiento", imagen);
        
        waitKey(33);
	}

  return 0;
}

// g++ `pkg-config --cflags opencv` -o PROGRAMA main.cpp `pkg-config --libs opencv` && ./PROGRAMA