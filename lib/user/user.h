/* User interaction functions, including display and status LED controls */

#ifndef USER_H
#define USER_H

/* ====================  Display Functions  ==================== */

/* ====================  LED Functions  ==================== */

/* ====================  Button Functions  ==================== */
namespace Button {
    class Button {
    public:
        Button(void);

        int init(void);
        int deinit(void);
    };
}

#endif  // USER_H