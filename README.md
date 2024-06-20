# rvo2_ros
Optimal Reciprocal Collision Avoidance for ROS

# Setup

### 1. Download this repository into your workspace:
```bash
cd ~/catkin_ws/src
git clone https://github.com/hrjp/rvo2_ros.git
```

### 2. Add the following entry to the CMakeLists.txt of the package where you want to include rvo2_ros:

```cmake
# CMakeList.txt

find_package(catkin REQUIRED COMPONENTS
  
  ....

  rvo2_ros
)
```
### 3. Include it in your source file:


```cpp
// XXXX.cpp
...

#include <rvo2_ros/RVO.h>

...


```

## ROS node example
--> https://github.com/hrjp/rvo2_ros/blob/main/src/example/agent_viz.cpp

# Reference
* Optimal Reciprocal Collision Avoidance   
    https://gamma.cs.unc.edu/RVO2/
    
* RVO2 - Github   
    https://github.com/snape/RVO2.git