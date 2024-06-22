# BBGL
BareBones Graphics Library is just a small library im making which gives you the bare minimum to make rendering projects

# installation
1. download or clone the project
2. insert it in your project
3. add bbgl.cpp and graphic_buffers.cpp to your makefile

# usage

1. declare the needed variables
    ```cpp
    BBGL *bbgl;
    void draw();
    void update();
    ```

2. fill the update and draw functions
    ```cpp
    void draw() {
        /** This i where you draw stuff **/
        return;
    }

    void update() {
        /** This i where you do logic stuff **/
        return;
    }
    ```

3. create the BBGLOPTIONS object
    ```cpp
    BBGLOPTIONS bbglOptions;
    bbglOptions.windowOptions.maxHeight = 1024;
    bbglOptions.windowOptions.maxWidth = 1024;
    bbglOptions.windowOptions.allowResize = true;
    ```

4. create the bbgl object
    ```cpp
    int main() {
        bbgl = new BBGL(bbglOptions);
        bbgl->update = update;
        bbgl->draw = draw;
        bbgl->start();
        std::cout << "GoodBye World!" << std::endl;
        return 0;
    }
    ```

5. change pixel data of the window

    ```cpp
    bbgl->buffs->set_pixel(x, y, RGB(255,255,255));
    ```
    you can also use safe_set_pixel to prevent crashes but it is a bit slower
    ```cpp
    bbgl->buffs->safe_set_pixel(x, y, RGB(255,255,255));
    ```

Note: Everything after bbgl->start() will only be called after the window is closed.

# limitation

1. resizing

    For now BBGL does not support resizing the window although this will come later.

2. OS

    BBGL is completely dependent on the Windows API for now althought this will be changed in later updates.

# contribution

You are welcome to post issues or pull requests in this repository.\
It would be greatly appreciated to get a Mac and Linux implementation.