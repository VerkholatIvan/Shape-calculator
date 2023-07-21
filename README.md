# Shape-calculator

The code consists of 7 classes, of which there are three base classes: “Coordinates”, “shape”
and “ShapeManagement”. The “shape” class has 4 derived classes

![uml_C++_Final_2](https://github.com/VerkholatIvan/Shape-calculator/assets/123458146/6f71f67c-4b94-4dae-81fd-348ed95249eb)


Each class has its own function: <br>
 &nbsp; • Coordinates – one of the base classes, which contains a constructor for user 
coordinates inputs, and some additional methods, which can be universal in certain 
cases. For example, the function “distance” can count the distance between points on 
the virtual graph, or “display” to show the coordinates of the center of the given shape. <br>
&nbsp; • Shape – second base class, which contains pure virtual functions for the derived classes. <br>
&nbsp; • Rectangle – a derived class, which contains the methods for finding the area and 
perimeter, scaling the figure, and translating it, for this exact shape. <br>
&nbsp; • Square – class similar to “Rectangle” and “Circle” other derived shape classes, but this 
one contains methods exactly for square. <br>
&nbsp; • Circle – class similar to “Rectangle” and “Square” other derived shape classes, but this 
one contains methods exactly for circle. <br>
&nbsp; • Triangle – class, which is similar to the previous classes with its functions, but is the 
most complex among them, because it contains not the sides of the values, but the point 
coordinates and distance between them. <br>
&nbsp; • ShapeManagement – class with a main loop, which allows the user to interact with the 
program menu by calling the method called “void mainloop()”. <br>
