#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;




// ==========================================
//  CLASSES (づ￣ 3￣)づ
// ==========================================

class Coordinates{
    public:
        float x, y;

        Coordinates(float user_x = 0, float user_y = 0){
            x = user_x;
            y = user_y;
        }

        double distance(Coordinates p){return sqrt( pow(x-p.x, 2) + pow(y-p.y, 2) );} // a method to find a distance in a coordinate system between two points

        void translate(int dx, int dy){ x += dx; y += dy;} // a method to translate or move shapes according to the input

        void scale(int factor, bool sign){ // a method to scale shapes by multiplying or dividing their sides
            if (sign){x *= factor; y *= factor;}
            else {x /= factor; y /= factor;}
        }

        string display(){return "X=" + to_string(x) + ", Y=" + to_string(y);} // a method to display the information about the shapes

};

// ------------------------------------------

class shape{
    public:
        int num_sides;
        Coordinates center;
        shape(int user_sides, Coordinates user_c){
            num_sides = user_sides; 
            center = user_c;
            }

        
        // pure virtual functions
        virtual double getArea() = 0;
        virtual double getPerimeter() = 0;
        virtual void translate(int dx, int dy) = 0;
        virtual void scale(int factor, bool sign) = 0;
        virtual string display() = 0;

};

// ------------------------------------------

class Rectangle: public shape{
    public:
        float width, length;
        Coordinates center;
        Rectangle(float w, float l, Coordinates c): shape(4, c){width = w, length = l; center = c;}

        virtual double getArea(){return width * length;} // get the area of the rectangle

        virtual double getPerimeter(){return 2 * width + 2 * length;} // get the perimeter of the rectangle 

        void translate(int dx, int dy){shape::center.translate(dx, dy);} // translate the rectange 

        void scale(int factor, bool sign){ // scale the rectangle
            if (!sign){width /= factor; length /= factor;}
            else if (sign){width *= factor; length *= factor;}
            else {cout << "Invalid sign for scaling";}
        }

        string display(){return "Rectangle\nCenter coordinates: " + shape::center.display() + // display shape information
            "\nLenth: " + to_string(length) + "\nWidth: " + to_string(width) + 
            "\nArea: " + to_string(getArea()) + 
            "\nPerimeter: " + to_string(getPerimeter()) + "\n\n";}
    
};

// ------------------------------------------

class Square: public shape{
    public:
        float side;
        Coordinates center;
        Square(float s, Coordinates c): shape(4, c){side = s; center = c;}

        double getArea(){return side * side;} //get the area of the square

        double getPerimeter(){return 4 * side;} // get the perimeter of the square

        void translate(int dx, int dy){shape::center.translate(dx, dy);} // translate the square

        void scale(int factor, bool sign){ // scale the square
            if (sign == 0){side /= factor;}
            else if (sign == 1){side *= factor;}
            else {cout << "Invalid sign for scaling";}
        }

        string display(){return "Square\nCenter coordinates: " + shape::center.display() + // display shape information
            "\nSide: " + to_string(side) + 
            "\nArea: " + to_string(getArea()) + 
            "\nPerimeter: " + to_string(getPerimeter()) + "\n\n";}

    


};

// ------------------------------------------

class Circle: public shape{
    public:
    float radius;
    Coordinates center;
    Circle(float r, Coordinates c): shape(1, c){radius = r; center = c;}

    double getArea(){return M_PI * pow(radius, 2);} //get the area of the circle

    double getPerimeter(){return 2 * M_PI * radius;} // get the perimeter of the circle

    void translate(int dx, int dy){return shape::center.translate(dx, dy);} // translate the circle 

    void scale(int factor, bool sign){ // scale the circle
        if (!sign){radius /= factor;}
        else if (sign){radius *= factor;}
        else {cout << "Invalid sign for scaling";}
    }
    
    string display(){return "Circle\nCenter coordinates: " + shape::center.display() + // display shape information
            "\nRadius: " + to_string(radius) + 
            "\nArea: " + to_string(getArea()) + 
            "\nPerimeter: " + to_string(getPerimeter()) + "\n\n";}

};

// ------------------------------------------

class Triangle: public shape{
    public:
        Coordinates V1;
        Coordinates V2;
        Coordinates V3;


        Triangle(Coordinates input1, Coordinates input2, Coordinates input3): shape(3, V1){
            V1 = input1;
            V2 = input2;
            V3 = input3;
            shape::center.x = (V1.x + V2.x + V3.x)/3;
            shape::center.y = (V1.y + V2.y + V3.y)/3;
        }
        
        
        double getArea(){ // get the area of the triangle
            double s = Triangle::getPerimeter()/2;
            return sqrt( s * ( s - V1.distance(V2) ) * ( s - V2.distance(V3) ) * (s - V3.distance(V1) ));
        }

        double getPerimeter(){return V1.distance(V2) + V2.distance(V3) + V3.distance(V1);} // get the perimeter of the triangle

        void scale(int factor, bool sign){ // scale the triangle
            if (!sign){
                V1.scale(factor, sign);
                V2.scale(factor, sign);
                V3.scale(factor, sign);
                shape::center.x = (V1.x + V2.x + V3.x)/3;
                shape::center.y = (V1.y + V2.y + V3.y)/3;
            }
            else if (sign){
                V1.scale(factor, sign);
                V2.scale(factor, sign);
                V3.scale(factor, sign);
                shape::center.x = (V1.x + V2.x + V3.x)/3;
                shape::center.y = (V1.y + V2.y + V3.y)/3;
            }
        }

        void translate(int dx, int dy){ // translate the triangle
            V1.translate(dx, dy);
            V3.translate(dx, dy);
            V2.translate(dx, dy);
            shape::center.translate(dx, dy);
        }

        string display(){return "Triangle\nPoints Coordinates: " + V1.display() + " | " + V2.display() + " | " + V3.display() + "\nCenter: " + shape::center.display() + // display shape information
        "\nArea: " + to_string(getArea()) + 
        "\nPerimeter: " + to_string(getPerimeter()) + "\n\n";}
         
};

// ------------------------------------------

class  ShapeManagement{
    public:
    bool play = true; // mainloop stopper
    int mainloop_user; // user switch case choose
    vector<shape*> L; // pointer vector, which contains the addresses of the created shapes

    ShapeManagement(){}

    void mainloop(){
        
        while (play){
            cout << "\nShape Management Menu\n---------------------------\n" << endl;

            cout << "1.Add a shape " << endl;
            cout << "2.Remove a shape by position " << endl;
            cout << "3.Get information about a shape by position " << endl;
            cout << "4.Area and perimeter of a shape by position " << endl;
            cout << "5.Display information of all of the shapes " << endl;
            cout << "6.Translate all the shapes " << endl;
            cout << "7.Scale all the shapes " << endl;
            cout << "0.Quit program\n" << endl;

            cout << "---------------------------\n" << endl;\

            cout << ">> ";
            cin >> mainloop_user;
            cout << endl;

            if (cin.fail()){ // "If" to prevent error with the infinite loop 
                cin.clear(); // Cleans the input
                cin.ignore(); // Ignores wrong type input 
                cout << "Unexpected input\nPlease try again\n" << endl;
            }

            else{
                double user_x, user_y;
                
                switch(mainloop_user){
                    case 0: // Exit program
                        play = false;
                        break;
                    
                    case 1: // Add a shape
                        int user_shapeChoose;

                        cout << "\nChoose one of the given shapes to create: \n" << endl;
                        cout << "1. Rectangle\n2. Square\n3. Cirlce\n4. Triangle\n\n>> ";
                        cin >> user_shapeChoose;

                        if (user_shapeChoose == 1){         // create a rectangle
                            float user_width, user_lenth;
                            cout << "Write down the coordinates of the center of the shape to create it using space (x y)\n>> ";
                            cin >> user_x >> user_y;
                            cout << "Enter width and lenth using space (width lenth)\n>> ";
                            cin  >> user_width >> user_lenth;
                            cout << "\n";

                            L.push_back(new Rectangle(user_width, user_lenth, Coordinates(user_x, user_y))); // add a created shape to the vector

                            cout << "\nThe shape was successfully added" << endl;
                        }   

                        else if (user_shapeChoose == 2){    // create a square
                            float user_side;
                            cout << "Write down the coordinates of the center of the shape to create it using space (x y)\n>> ";
                            cin >> user_x >> user_y;
                            cout << "Enter the side value\n>> ";
                            cin >> user_side;
                            cout << "\n";

                            L.push_back(new Square(user_side, Coordinates(user_x, user_y))); // add a created shape to the vector

                            cout << "\nThe shape was successfully added" << endl;
                        }

                        else if (user_shapeChoose == 3){    // create a circle
                                float user_radius;
                                cout << "Write down the coordinates of the center of the shape to create it using space (x y)\n>> ";
                                cin >> user_x >> user_y;
                                cout << "Enter the radius value\n>> ";
                                cin >> user_radius;
                                cout << "\n";

                                L.push_back(new Circle(user_radius, Coordinates(user_x, user_y))); // add a created shape to the vector

                            cout << "\nThe shape was successfully added" << endl;
                        }

                        else if (user_shapeChoose == 4){    // create a triangle
                                double x1, x2, x3, y1, y2, y3;
                                cout << "Write down the coordinates of the points of the shape to create it using space (x y)\nEnter first point\n>> ";
                                cin >> x1 >> y1;
                                cout << "Enter the second point\n>> ";
                                cin >> x2 >> y2;
                                cout << "Enter the third point\n>> ";
                                cin >> x3 >> y3;
                                cout << "\n";

                                L.push_back(new Triangle(Coordinates(x1, y1), Coordinates(x2, y2), Coordinates(x3, y3))); // add a created shape to the vector

                            cout << "\nThe shape was successfully added" << endl;
                        }
  
                        else {cout << "Wrong input. Please try again." << endl;}    // wrong input

                        break;


                    case 2: // Remove a shape by position                        
                        cout << "Enter the position of the shape to remoce it (x y)\n>> ";
                        cin >> user_x >> user_y; 

                        for (int i = 0; i < L.size(); i++){
                            if ((L[i]->center.x == user_x) && (L[i]->center.y == user_y)){
                                L.erase(L.begin()+i);
                                cout << "\nThe shape was removed successfully" << endl;
                            }
                        }

                        
                        break;

                    
                    case 3: // Get information about a shape by position
                        cout << "Enter shape position (write down the coordinates using space (x y)) to display information about it\n>> ";
                        cin >> user_x >> user_y;
                        
                        for (int i = 0; i < L.size(); i++){
                            if ((L[i]->center.x == user_x) && (L[i]->center.y == user_y)){cout << L[i]->display() << "\n" << endl;}
                        }
                        
                        break;

                    
                    case 4: // Area and perimeter of a shape by position
                        cout << "Enter the shape position using space (x y):\n>> ";
                        cin >> user_x >> user_y;
                        for (int i = 0; i < L.size(); i++){
                            if ((L[i]->center.x == user_x) && (L[i]->center.y == user_y)){
                                cout << "\nArea: " + to_string(L[i]->getArea()) + "\nPerimeter: " + to_string(L[i]->getPerimeter()) << endl; 
                            }
                        }

                        break;


                    case 5: // Display information of all of the shapes
                        if (L.size() == 0){cout << "There are no created shapes" << endl;}
                        for (int i = 0; i < L.size(); i++){
                            cout << L[i]->display() << endl;
                        }
                        
                        
                        break;

                    case 6: // Translate all the shapes
                        cout << "Enter by which coordinates you wish to translate the shapes\n Enter coordinates using space (x y)\n>> ";
                        cin >> user_x >> user_y;
                        
                        for (int i = 0; i < L.size(); i++){
                            L[i]->translate(user_x, user_y);
                        }

                        cout << "\nAll shapes were translated successfully" << endl;
                        
                        break;


                    case 7: // Scale all the shapes
                        int user_factor;
                        bool sign;
                        cout << "Enter how much do you want to scale shapes\n>> ";
                        cin >> user_factor;
                        cout << "divide (0) | multiply (1)\n>> ";
                        cin >> sign;

                        for (int i = 0; i < L.size(); i++){
                            L[i]->scale(user_factor, sign);
                        }
                       
                        cout << "\nAll shapes were scaled successfully" << endl;
                        
                        break;


                    default: // Unexpected input error
                        cout << "Unexpected input\nPlease try again\n" << endl;
                        break;
 
                }
            }
      
       }

    } 
};


// ==========================================
//  MAIN FUNCTION <( _ _ )>
// ==========================================

int main(){
    ShapeManagement mainTool;
    mainTool.mainloop(); // interaction menu starter
}