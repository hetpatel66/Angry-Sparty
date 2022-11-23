/**
 * @file Image.cpp
 * @author Michael Tan
 */

#include "pch.h"
#include "Image.h"
#include <string>
#include <vector>

using namespace std;

/// Vector of every possible image in the program
const vector<std::string> Images{ "background1.png", "debrisGlass_1.png", "debrisStone_1.png", "elementExplosive039.png",
                                  "elementExplosive041.png", "elementMetal002.png", "elementMetal013.png", "elementMetal029.png",
                                  "elementStone047.png", "elementWood015.png", "elementWood031.png", "flagGreen.png", "foeM.png",
                                  "foeM2.png", "foeN.png", "foeO.png", "goalposts.png", "goalposts-front.png", "gruff-sparty.png",
                                  "helmet-sparty.png", "sand.png", "slingshot.png", "slingshot-front.png"};

Image::Image() {
    for (auto &inVec : Images){
        auto temp_filename = wxString(inVec);
        auto temp_name = mFolder + temp_filename;
        auto temp_image = make_shared<wxImage>(temp_name, wxBITMAP_TYPE_ANY);
        auto temp_bitmap = make_shared<wxBitmap>(*mItemImage);
        mImageBitmapMap.insert({temp_filename,temp_bitmap});  //std::map<wxString, std::shared_ptr<wxBitmap>> mImageBitmapMap;
    }
}

std::shared_ptr<wxBitmap> Image::GetImageBitmap(wxString filename){
    return mImageBitmapMap[filename];
}

