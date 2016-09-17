#ifndef ITEMS_H
#define ITEMS_H



// base  class for a bunch of different items like food and tools
class Item {
public:
  std::string name;
  int weight;
  char shortcut;

  Item(std::string name_, int weight_, char shortcut_=' ') : name(name_), weight(weight_), shortcut(shortcut_)
  {}


};

class FoodItem : public Item {

public:
  FoodItem(std::string name_,  int weight_, char shortcut_=' ') : Item(name_, weight_, shortcut_)
  {
    
  }



};


std::vector<FoodItem> foodTypes = {
  FoodItem("Blueberry", 1),
  FoodItem("The Blackberry", 1),
  FoodItem("Frog", 2),
  FoodItem("Acorns", 1),
  FoodItem("Mouse", 2)
};



#endif
