#pragma once
#include <unordered_map>
#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/XKBlib.h>
    #include <X11/keysym.h>
    #include <unistd.h>
#elif __APPLE__
    #include <ApplicationServices/ApplicationServices.h>
#elif __APPLE__
    #include <Carbon/Carbon.h>
#endif

struct KeyCode {
    // Letters
    static constexpr int A = 'A';
    static constexpr int B = 'B';
    static constexpr int C = 'C';
    static constexpr int D = 'D';
    static constexpr int E = 'E';
    static constexpr int F = 'F';
    static constexpr int G = 'G';
    static constexpr int H = 'H';
    static constexpr int I = 'I';
    static constexpr int J = 'J';
    static constexpr int K = 'K';
    static constexpr int L = 'L';
    static constexpr int M = 'M';
    static constexpr int N = 'N';
    static constexpr int O = 'O';
    static constexpr int P = 'P';
    static constexpr int Q = 'Q';
    static constexpr int R = 'R';
    static constexpr int S = 'S';
    static constexpr int T = 'T';
    static constexpr int U = 'U';
    static constexpr int V = 'V';
    static constexpr int W = 'W';
    static constexpr int X = 'X';
    static constexpr int Y = 'Y';
    static constexpr int Z = 'Z';

    // Numbers
    static constexpr int Num0 = '0';
    static constexpr int Num1 = '1';
    static constexpr int Num2 = '2';
    static constexpr int Num3 = '3';
    static constexpr int Num4 = '4';
    static constexpr int Num5 = '5';
    static constexpr int Num6 = '6';
    static constexpr int Num7 = '7';
    static constexpr int Num8 = '8';
    static constexpr int Num9 = '9';

    // Function Keys
#ifdef _WIN32
    static constexpr int F1 = VK_F1;
    static constexpr int F2 = VK_F2;
    static constexpr int F3 = VK_F3;
    static constexpr int F4 = VK_F4;
    static constexpr int F5 = VK_F5;
    static constexpr int F6 = VK_F6;
    static constexpr int F7 = VK_F7;
    static constexpr int F8 = VK_F8;
    static constexpr int F9 = VK_F9;
    static constexpr int F10 = VK_F10;
    static constexpr int F11 = VK_F11;
    static constexpr int F12 = VK_F12;
    static constexpr int F13 = VK_F13;
    static constexpr int F14 = VK_F14;
    static constexpr int F15 = VK_F15;
    static constexpr int F16 = VK_F16;
    static constexpr int F17 = VK_F17;
    static constexpr int F18 = VK_F18;
    static constexpr int F19 = VK_F19;
    static constexpr int F20 = VK_F20;
    static constexpr int F21 = VK_F21;
    static constexpr int F22 = VK_F22;
    static constexpr int F23 = VK_F23;
    static constexpr int F24 = VK_F24;

    // Special Keys#
    static constexpr int LeftShift = VK_LSHIFT;
    static constexpr int RightShift = VK_RSHIFT;
    static constexpr int LeftCtrl = VK_LCONTROL;
    static constexpr int RightCtrl = VK_RCONTROL;
    static constexpr int LeftAlt = VK_LMENU;
    static constexpr int RightAlt = VK_RMENU;
    static constexpr int CapsLock = VK_CAPITAL;

    // Navigation keys
    static constexpr int Enter = VK_RETURN;
    static constexpr int Backspace = VK_BACK;
    static constexpr int Tab = VK_TAB;
    static constexpr int Escape = VK_ESCAPE;
    static constexpr int Space = VK_SPACE;
    static constexpr int Insert = VK_INSERT;
    static constexpr int Delete = VK_DELETE;
    static constexpr int Home = VK_HOME;
    static constexpr int End = VK_END;
    static constexpr int PageUp = VK_PRIOR;
    static constexpr int PageDown = VK_NEXT;

    // Arrow keys
    static constexpr int LeftArrow = VK_LEFT;
    static constexpr int RightArrow = VK_RIGHT;
    static constexpr int UpArrow = VK_UP;
    static constexpr int DownArrow = VK_DOWN;

    static constexpr int Numpad0 = VK_NUMPAD0;
    static constexpr int Numpad1 = VK_NUMPAD1;
    static constexpr int Numpad2 = VK_NUMPAD2;
    static constexpr int Numpad3 = VK_NUMPAD3;
    static constexpr int Numpad4 = VK_NUMPAD4;
    static constexpr int Numpad5 = VK_NUMPAD5;
    static constexpr int Numpad6 = VK_NUMPAD6;
    static constexpr int Numpad7 = VK_NUMPAD7;
    static constexpr int Numpad8 = VK_NUMPAD8;
    static constexpr int Numpad9 = VK_NUMPAD9;

    static constexpr int NumpadAdd = VK_ADD;
    static constexpr int NumpadSubtract = VK_SUBTRACT;
    static constexpr int NumpadMultiply = VK_MULTIPLY;
    static constexpr int NumpadDivide = VK_DIVIDE;
    static constexpr int NumpadDecimal = VK_DECIMAL;
    static constexpr int NumLock = VK_NUMLOCK;

    static constexpr int PrintScreen = VK_SNAPSHOT;
    static constexpr int ScrollLock = VK_SCROLL;
    static constexpr int Pause = VK_PAUSE;
    static constexpr int Menu = VK_APPS;
    // Mouse Buttons
    static constexpr int MouseLeft = VK_LBUTTON;
    static constexpr int MouseRight = VK_RBUTTON;
    static constexpr int MouseMiddle = VK_MBUTTON;
    static constexpr int MouseX1 = VK_XBUTTON1;
    static constexpr int MouseX2 = VK_XBUTTON2;

#elif __linux__
    static constexpr int F1 = XK_F1;
    static constexpr int F2 = XK_F2;
    static constexpr int F3 = XK_F3;
    static constexpr int F4 = XK_F4;
    static constexpr int F5 = XK_F5;
    static constexpr int F6 = XK_F6;
    static constexpr int F7 = XK_F7;
    static constexpr int F8 = XK_F8;
    static constexpr int F9 = XK_F9;
    static constexpr int F10 = XK_F10;
    static constexpr int F11 = XK_F11;
    static constexpr int F13 = XK_F13;
    static constexpr int F14 = XK_F14;
    static constexpr int F15 = XK_F15;
    static constexpr int F16 = XK_F16;
    static constexpr int F17 = XK_F17;
    static constexpr int F18 = XK_F18;
    static constexpr int F19 = XK_F19;
    static constexpr int F20 = XK_F20;
    static constexpr int F21 = XK_F21;
    static constexpr int F22 = XK_F22;
    static constexpr int F23 = XK_F23;
    static constexpr int F24 = XK_F24;
    static constexpr int F25 = XK_F25;
    static constexpr int F26 = XK_F26;
    static constexpr int F27 = XK_F27;
    static constexpr int F28 = XK_F28;
    static constexpr int F29 = XK_F29;
    static constexpr int F30 = XK_F30;
    static constexpr int F31 = XK_F31;
    static constexpr int F32 = XK_F32;
    static constexpr int F33 = XK_F33;
    static constexpr int F34 = XK_F34;
    static constexpr int F35 = XK_F35;

    static constexpr int LeftShift = XK_Shift_L;
    static constexpr int RightShift = XK_Shift_R;
    static constexpr int LeftCtrl = XK_Control_L;
    static constexpr int RightCtrl = XK_Control_R;
    static constexpr int LeftAlt = XK_Alt_L;
    static constexpr int RightAlt = XK_Alt_R;
    static constexpr int CapsLock = XK_Caps_Lock;

    static constexpr int Enter = XK_Return;
    static constexpr int Backspace = XK_BackSpace;
    static constexpr int Tab = XK_Tab;
    static constexpr int Escape = XK_Escape;
    static constexpr int Space = XK_space;
    static constexpr int Insert = XK_Insert;
    static constexpr int Delete = XK_Delete;
    static constexpr int Home = XK_Home;
    static constexpr int End = XK_End;
    static constexpr int PageUp = XK_Page_Up;
    static constexpr int PageDown = XK_Page_Down;

    static constexpr int LeftArrow = XK_Left;
    static constexpr int RightArrow = XK_Right;
    static constexpr int UpArrow = XK_Up;
    static constexpr int DownArrow = XK_Down;

    static constexpr int NumLock = XK_Num_Lock;
    static constexpr int ScrollLock = XK_Scroll_Lock;
    static constexpr int Pause = XK_Pause;
    static constexpr int PrintScreen = XK_Print;

    // Mouse Buttons (X11 button mappings)
    static constexpr int MouseLeft = 1;
    static constexpr int MouseMiddle = 2;
    static constexpr int MouseRight = 3;
    static constexpr int MouseScrollUp = 4;
    static constexpr int MouseScrollDown = 5;
    static constexpr int MouseX1 = 8;
    static constexpr int MouseX2 = 9;

#elif __APPLE__
    static constexpr int F1 = kVK_F1;
    static constexpr int F2 = kVK_F2;
    static constexpr int F3 = kVK_F3;
    static constexpr int F4 = kVK_F4;
    static constexpr int F5 = kVK_F5;
    static constexpr int F6 = kVK_F6;
    static constexpr int F7 = kVK_F7;
    static constexpr int F8 = kVK_F8;
    static constexpr int F9 = kVK_F9;
    static constexpr int F10 = kVK_F10;
    static constexpr int F11 = kVK_F11;
    static constexpr int F12 = kVK_F12;

    static constexpr int LeftShift = kVK_Shift;
    static constexpr int RightShift = kVK_RightShift;
    static constexpr int LeftCtrl = kVK_Control;
    static constexpr int RightCtrl = kVK_RightControl;
    static constexpr int LeftAlt = kVK_Option;
    static constexpr int RightAlt = kVK_RightOption;
    static constexpr int CapsLock = kVK_CapsLock;

    static constexpr int Enter = kVK_Return;
    static constexpr int Backspace = kVK_Delete;
    static constexpr int Tab = kVK_Tab;
    static constexpr int Escape = kVK_Escape;
    static constexpr int Space = kVK_Space;
    static constexpr int Insert = 0x72; // Help key = Insert
    static constexpr int Delete = kVK_ForwardDelete;
    static constexpr int Home = kVK_Home;
    static constexpr int End = kVK_End;
    static constexpr int PageUp = kVK_PageUp;
    static constexpr int PageDown = kVK_PageDown;

    static constexpr int LeftArrow = kVK_LeftArrow;
    static constexpr int RightArrow = kVK_RightArrow;
    static constexpr int UpArrow = kVK_UpArrow;
    static constexpr int DownArrow = kVK_DownArrow;

    // Mouse Buttons (macOS uses CGEvent)
    static constexpr int MouseLeft = 0;  // kCGMouseButtonLeft
    static constexpr int MouseRight = 1; // kCGMouseButtonRight
    static constexpr int MouseMiddle = 2;
#endif
};

class Input {
private:
static bool mouseLocked;
static inline std::unordered_map<int, bool> prevKeyStates;
public:
    // Check if a keyboard key is currently down
    static bool GetKeyDown(int key) {
        return isKeyHeldDown(key);
    }
    static bool GetKeyPressed(int key) {
        bool currentlyDown = isKeyHeldDown(key);
        bool wasDown = false;

        auto it = prevKeyStates.find(key);
        if (it != prevKeyStates.end()) {
            wasDown = it->second;
        }

        // Update the stored state
        prevKeyStates[key] = currentlyDown;

        // Return true only if currently down, but was not down previously
        return currentlyDown && !wasDown;
    }
    static void LockMouseToCenter(bool hideCursor = false) {
        lockCenter(hideCursor);
    }

    // Check if a mouse button is pressed
    static bool GetMouseButtonDown(int button) {
        return isMouseButtonPressed(button);
    }

    // Get mouse position (x, y)
    static void GetMousePosition(int& x, int& y) {
        getMousePosition(x, y);
    }

private:
    // ------------------------
    // Windows Implementation
    // ------------------------
#ifdef _WIN32
    static void lockCenter(bool hideCursor){
        HWND hwnd = GetActiveWindow();
        if (!hwnd) return;

        RECT rect;
        GetClientRect(hwnd, &rect);
        ShowCursor(!hideCursor);
        POINT center;
        center.x = (rect.right - rect.left) / 2;
        center.y = (rect.bottom - rect.top) / 2;

        ClientToScreen(hwnd, &center);
        SetCursorPos(center.x, center.y);
    }
    static bool isKeyHeldDown(int key) {
        return GetAsyncKeyState(key) & 0x8000;
    }

    static bool isMouseButtonPressed(int button) {
        return (GetAsyncKeyState(button) & 0x8000) != 0;
        
    }

    static void getMousePosition(int& x, int& y) {
        POINT p;
        GetCursorPos(&p);
        x = p.x;
        y = p.y;
    }

    // ------------------------
    // Linux (X11) Implementation
    // ------------------------
#elif __linux__
    static void lockCenter(bool hideCursor){
        Display* display = XOpenDisplay(nullptr);
        if (!display) return;

        Window root = DefaultRootWindow(display);
        int screen = DefaultScreen(display);
        int width = DisplayWidth(display, screen);
        int height = DisplayHeight(display, screen);

        int centerX = width / 2;
        int centerY = height / 2;

        XWarpPointer(display, None, root, 0, 0, 0, 0, centerX, centerY);
        XFlush(display);
        XCloseDisplay(display);
    }
    static bool isKeyPressed(KeyCode key){
        bool currentlyDown = isKeyHeldDown(key);
        bool wasDown = false;

        auto it = prevKeyStates.find(key);
        if (it != prevKeyStates.end()) {
            wasDown = it->second;
        }

        // Update the stored state
        prevKeyStates[key] = currentlyDown;

        // Return true only if currently down, but was not down previously
        return currentlyDown && !wasDown;
    }
    static bool isKeyHeldDown(KeyCode key) {
        Display* display = XOpenDisplay(nullptr);
        if (!display) return false;

        char keys[32];
        XQueryKeymap(display, keys);
        KeyCode kc = XKeysymToKeycode(display, key);
        bool pressed = (keys[kc / 8] & (1 << (kc % 8))) != 0;

        XCloseDisplay(display);
        return pressed;
    }

    static bool isMouseButtonPressed(KeyCode button) {
        Display* display = XOpenDisplay(nullptr);
        if (!display) return false;

        Window root, child;
        int root_x, root_y, win_x, win_y;
        unsigned int mask;
        bool pressed = false;

        XQueryPointer(display, DefaultRootWindow(display), &root, &child, &root_x, &root_y, &win_x, &win_y, &mask);
        if (button == 0) pressed = mask & Button1Mask; // Left Click
        if (button == 1) pressed = mask & Button3Mask; // Right Click
        if (button == 2) pressed = mask & Button2Mask; // Middle Click

        XCloseDisplay(display);
        return pressed;
    }

    static void getMousePosition(int& x, int& y) {
        Display* display = XOpenDisplay(nullptr);
        if (!display) return;

        Window root, child;
        int root_x, root_y, win_x, win_y;
        unsigned int mask;

        XQueryPointer(display, DefaultRootWindow(display), &root, &child, &root_x, &root_y, &win_x, &win_y, &mask);
        x = root_x;
        y = root_y;

        XCloseDisplay(display);
    }

    // ------------------------
    // macOS Implementation
    // ------------------------
#elif __APPLE__
    static void lockCenter(bool hideCursor){
        CGSize screenSize = CGDisplayBounds(CGMainDisplayID()).size;
        CGPoint center = CGPointMake(screenSize.width / 2, screenSize.height / 2);

        if (hideCursor)
            CGDisplayHideCursor(kCGDirectMainDisplay);
        else
            CGDisplayShowCursor(kCGDirectMainDisplay);

        CGWarpMouseCursorPosition(center);
        CGAssociateMouseAndMouseCursorPosition(true);
    }
    static bool isKeyHeldDown(KeyCode key) {
        CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState);
        return (flags & key) != 0;
    }
    static bool isKeyPressed(KeyCode key){
        bool currentlyDown = isKeyHeldDown(key);
        bool wasDown = false;

        auto it = prevKeyStates.find(key);
        if (it != prevKeyStates.end()) {
            wasDown = it->second;
        }

        // Update the stored state
        prevKeyStates[key] = currentlyDown;

        // Return true only if currently down, but was not down previously
        return currentlyDown && !wasDown;
    }

    static bool isMouseButtonPressed(KeyCode button) {
        CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState);
        if (button == 0) return flags & kCGEventLeftMouseDown;   // Left Click
        if (button == 1) return flags & kCGEventRightMouseDown;  // Right Click
        if (button == 2) return flags & kCGEventOtherMouseDown;  // Middle Click
        return false;
    }

    static void getMousePosition(int& x, int& y) {
        CGPoint point = CGEventGetLocation(CGEventCreate(nullptr));
        x = static_cast<int>(point.x);
        y = static_cast<int>(point.y);
    }
#endif
};

//std::unordered_map<int, bool> Input::prevKeyStates;