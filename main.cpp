#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>


typedef unsigned int uint;
int map[4][4];

//生成随机0-3的随机数
uint randNum() {
    return (rand() % 4);
}

// 在地图上添加一个数字
int addNum() {
    uint x = randNum();
    uint y = randNum();
    int ex = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!map[i][j]) {
                ex = 0;
            }
        }
    }
    // 增加不了，返回0
    if (ex) {
        return 0;
    }


    while (map[x][y]) {
        x = randNum();
        y = randNum();
    }
    map[x][y] = 2;
    return 1;
}

// 根据数字大小获取颜色
int getColorForNumber(int num) {
    switch (num) {
        case 2: return RGB(238, 228, 218);
        case 4: return RGB(237, 224, 200);
        case 8: return RGB(242, 177, 121);
        case 16: return RGB(245, 149, 99);
        case 32: return RGB(246, 124, 95);

        case 64: return RGB(246, 94, 59);
        case 128: return RGB(237, 207, 114);
        case 256: return RGB(237, 200, 80);
        case 512: return RGB(247, 120, 70);
        case 1024: return RGB(237, 197, 63);
        default: return RGB(237, 194, 46);
    }
}

// 绘制游戏界面
void draw() {
    cleardevice();

    // 背景
    setfillcolor(WHITE);
    solidrectangle(0, 0, 600, 600);


    // 绘制数字
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (map[i][j]) {
                // 根据数字大小设置不同的颜色
                int num = map[i][j];
                int color = getColorForNumber(num);
                setfillcolor(color);
                solidrectangle(150 * j + 10, 150 * i + 10, 150 * j + 140, 150 * i + 140);

                char ch[10];
                sprintf(ch, "%d", map[i][j]);

                if (num <= 8) {
                    setcolor(RGB(119, 110, 101)); // 文字颜色
                } else {
                    setcolor(RGB(249, 246, 242)); //白色
                }
                setbkmode(TRANSPARENT);
                settextstyle(75, 0, _T("宋体"));
                int textWidth = textwidth(ch);
                int textHeight = textheight(ch);
                outtextxy(150 * j + (150 - textWidth) / 2, 150 * i + (150 - textHeight) / 2, ch);
            } else {
                setfillcolor(RGB(238, 228, 218));
                solidrectangle(150 * j + 10, 150 * i + 10, 150 * j + 140, 150 * i + 140);
            }
        }
    }
}

// 向左移动所有数字
void moveLeft() {
    //全部移动到贴墙边
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = i;
            int y = j;
            if (map[i][j]) {
                while (y - 1 >= 0) {
                    if (map[x][y - 1]) {
                        break;
                    }
                    map[x][y - 1] = map[x][y];
                    map[x][y] = 0;

                    y--;
                }
            }
        }
    }
    // 合并
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (map[i][j]) {
                if (map[i][j] == map[i][j + 1]) {
                    map[i][j] += map[i][j + 1];
                    map[i][j + 1] = 0;
                }
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = i;
            int y = j;
            if (map[i][j]) {
                while (y - 1 >= 0) {
                    if (map[x][y - 1]) {
                        break;
                    }
                    map[x][y - 1] = map[x][y];
                    map[x][y] = 0;

                    y--;
                }
            }
        }
    }
}

// 向上移动所有数字
void moveUp() {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            int x = i;
            int y = j;
            if (map[i][j]) {
                while (x - 1 >= 0) {
                    if (map[x - 1][y]) {
                        break;
                    }
                    map[x - 1][y] = map[x][y];
                    map[x][y] = 0;

                    x--;
                }
            }
        }
    }

    // 合并
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (map[i][j]) {
                if (map[i][j] == map[i + 1][j]) {
                    map[i][j] += map[i + 1][j];
                    map[i + 1][j] = 0;
                }
            } else {
                break;
            }
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            int x = i;
            int y = j;
            if (map[i][j]) {
                while (x - 1 >= 0) {
                    if (map[x - 1][y]) {
                        break;
                    }
                    map[x - 1][y] = map[x][y];
                    map[x][y] = 0;

                    x--;
                }
            }
        }
    }
}

// 向右移动所有数字
void moveRight() {
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            int x = i;
            int y = j;
            if (map[i][j]) {
                while (y + 1 <= 3) {
                    if (map[x][y + 1]) {
                        break;
                    }
                    map[x][y + 1] = map[x][y];
                    map[x][y] = 0;

                    y++;
                }
            }
        }
    }
    // 合并
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (map[i][j]) {
                if (map[i][j] == map[i][j - 1]) {
                    map[i][j] += map[i][j - 1];
                    map[i][j - 1] = 0;
                }
            } else {
                break;
            }
        }
    }

    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            int x = i;
            int y = j;
            if (map[i][j]) {
                while (y + 1 <= 3) {
                    if (map[x][y + 1]) {
                        break;
                    }
                    map[x][y + 1] = map[x][y];
                    map[x][y] = 0;

                    y++;
                }
            }
        }
    }
}

// 向下移动所有数字
void moveDown() {
    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 4; j++) {
            int x = i;
            int y = j;
            if (map[i][j]) {
                while (x + 1 <= 3) {
                    if (map[x + 1][y]) {
                        break;
                    }
                    map[x + 1][y] = map[x][y];
                    map[x][y] = 0;

                    x++;
                }
            }
        }
    }

    //合并
    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 4; j++) {
            if (map[i][j]) {
                if (map[i][j] == map[i - 1][j]) {
                    map[i][j] += map[i - 1][j];
                    map[i - 1][j] = 0;
                }
            } else {
                break;
            }
        }
    }


    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 4; j++) {
            int x = i;
            int y = j;
            if (map[i][j]) {
                while (x + 1 <= 3) {
                    if (map[x + 1][y]) {
                        break;
                    }
                    map[x + 1][y] = map[x][y];
                    map[x][y] = 0;

                    x++;
                }
            }
        }
    }
}

// 检查地图是否有变化
int isAdd(int temp[4][4]) {
    int state = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!map[i][j]) {
                state = 0; // 有空state = 0
            }
            if (temp[i][j] == map[i][j]) {
                continue;
            } else {
                return 0;
            }
        }
    }

    // 如果有一个0都会返回1，否则全不为0返回0
    if (state) {
        return 0;
    } else {
        return 1;
    }
}

// 检查游戏是否结束
int isEnd() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (map[i][j] == map[i][j + 1]) {
                return 0;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (map[i][j] == map[i + 1][j]) {
                return 0;
            }
        }
    }

    return 1;
}


int main() {
    // 初始化图片
    initgraph(600, 600);
    // 初始化随机数种子
    srand(time(NULL));

    //初始化两个数字
    addNum();
    addNum();


    while (1) {
        draw();

        int temp[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[i][j] = map[i][j];
            }
        }


        char dir = _getch();
        switch (dir) {
            case 'w': moveUp();
                break;
            case 's': moveDown();
                break;
            case 'a': moveLeft();
                break;
            case 'd': moveRight();
                break;
            default: continue;;
        }


        if (isAdd(temp)) {
            continue;
        }


        if (!addNum() && isEnd()) {
            setcolor(BLACK);
            char ch[] = "游戏结束！";
            int textWidth = textwidth(ch);
            int textHeight = textheight(ch);

            // 计算文本的居中位置
            int centerX = 600 / 2 - textWidth / 2;
            int centerY = 600 / 2 - textHeight / 2;

            // 输出居中文本
            outtextxy(centerX, centerY - 50, ch);
            outtextxy(centerX, centerY + 50, _T("回车退出！"));


            getchar();
            break;
        }
    }

    cleardevice();
    return 0;
}
