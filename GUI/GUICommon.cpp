#include "GUICommon.h"



Size adjustSizeToMargins(const Size& s , const Margins& margin){
    return {s.width - margin.left - margin.right , s.height - margin.top - margin.bottom};
}

Size horizontalSizeByStretchFactor(const Size& totalSize , int segments , int stretch){
    const float segmentW = totalSize.width / segments;

    return { segmentW * stretch , totalSize.height};
}

bool intersection(const Rect& rect1 , const Rect& rect2){
    return rect1.x + rect1.s.width > rect2.x && rect1.x < rect2.x + rect2.s.width &&
        rect1.y + rect1.s.height > rect2.y && rect1.y < rect2.y + rect2.s.height ;
}


void logSize(Size s){
    std::cout << "033\[32m" << "[SIZE]" << "033\[0m \n";
    std::cout << "Width: " << s.width << " Height: " << s.height;
}



