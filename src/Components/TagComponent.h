#ifndef INC_2DGAMEENGINE_TAGCOMPONENT_H
#define INC_2DGAMEENGINE_TAGCOMPONENT_H

enum class Tag {
  None,
  Player,
  Enemy,
  Projectile,
  Obstacle,
  UIElement
};

struct TagComponent {
  Tag tag;

  TagComponent(Tag tag = Tag::None) : tag(tag) {}
};

#endif // INC_2DGAMEENGINE_TAGCOMPONENT_H
