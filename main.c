#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int main() {
    // Open a connection to the X server
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Failed to open display\n");
        return 1;
    }

    // Create a window
    Window root = DefaultRootWindow(display);
    Window window = XCreateSimpleWindow(display, root, 0, 0, 800, 600, 0, 0, 0);

    // Set up the required events
    XSelectInput(display, root, SubstructureNotifyMask | SubstructureRedirectMask);

    // Set window border width
    unsigned int border_width = 2;
    XSetWindowBorderWidth(display, window, border_width);

    // Set window background color
    XSetWindowBackground(display, window, BlackPixel(display, DefaultScreen(display)));

    // Map the window
    XMapWindow(display, window);

    // Event loop
    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == MapNotify)
            break;
    }

    // Main loop
    while (1) {
        XNextEvent(display, &event);
        
        // Handle events
        switch (event.type) {
            case ConfigureNotify:
                // Handle window resize events here
                break;
            case ButtonPress:
                // Handle button press events here
                if (event.xbutton.button == Button1) {
                    // Perform actions on left mouse button press
                    printf("Left mouse button pressed\n");
                } else if (event.xbutton.button == Button3) {
                    // Perform actions on right mouse button press
                    printf("Right mouse button pressed\n");
                }
                break;
            case KeyPress:
                // Handle key press events here
                if (event.xkey.keycode == XKeysymToKeycode(display, XK_Escape)) {
                    // Perform actions on Escape key press
                    printf("Escape key pressed\n");
                    // Exit the compositor
                    XDestroyWindow(display, window);
                    XCloseDisplay(display);
                    return 0;
                }
                break;
            default:
                break;
        }
    }

    // Clean up and exit
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
