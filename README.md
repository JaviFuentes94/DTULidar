# DTULidar

The objective of this project is to build a rudimentary lidar that is able to scan rooms or objects with reasonable accuracy. It operates autonomously when started and collect a range distnace that is send to a PC through a custom protocol. There the processed data can be viewed as a 3D point plot using PCL. The system will use 2 motors, that allow scanner to rotate around its own axis (azimuth) and another motor to allow it to scan the elevation plane. It can be setup for up to 360 degrees rotation on the azimuth and 180 degrees on the elevation plane and thereby be able to capture data points in all three dimensions.


The general overview with the device working
![alt-text](https://github.com/JaviFuentes94/DTULidar/blob/master/Media/overview.gif)

The final prototype
![alt-text](https://github.com/JaviFuentes94/DTULidar/blob/master/Media/Lidar1.jpg)

The output visualization using PCL

![alt-text](https://github.com/JaviFuentes94/DTULidar/blob/master/Media/results2.gif)

## Getting Started
This project is just for inspiration, as finding the exact parts that we used would be difficult. However, if you are interested here you can find a schematic of all the hardware:

![alt-text](https://github.com/JaviFuentes94/DTULidar/blob/master/Media/schematic.jpg)


### Prerequisites

In order to run the application you need:
* Eigen (for the coordinate transformations)
* PCL - Point Cloud Library (for the visualization)

## Authors

* **Christoph Weiser** [chrische-xx](https://github.com/chrische-xx)

* **Javier Fuentes Alonso** [JaviFuentes94](https://github.com/JaviFuentes94)

* **Szymon Kowalewski** [szymonkowalewski](https://github.com/szymonkowalewski)

* **Mads Duncan Cronquist Larsen** [MadsDuncan](https://github.com/MadsDuncan)


## Acknowledgments

* Thanks to DTU for providing the hardware used for this project
