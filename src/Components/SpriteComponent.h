#ifndef INC_2DGAMEENGINE_SPRITECOMPONENT_H
#define INC_2DGAMEENGINE_SPRITECOMPONENT_H


struct SpriteComponent {
    int width;
    int height;

    SpriteComponent(int width = 0, int height = 0) {
        this->width = width;
        this->height = height;
    };
};


#endif //INC_2DGAMEENGINE_SPRITECOMPONENT_H