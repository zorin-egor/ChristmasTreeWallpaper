#ifndef LIFEWALLPAPERTREE_RENDER_H
#define LIFEWALLPAPERTREE_RENDER_H

class Render {

public:
    virtual void render() = 0;
    virtual bool getVisible() = 0;
    virtual void setVisible(bool visible) = 0;
    virtual ~Render(){

    };
};

#endif //LIFEWALLPAPERTREE_RENDER_H
