/**
 * @file Image.h
 * @author Michael Tan
 *
 * Class to preload an image into
 *
 * Allows the game to preload images to an object
 */

#ifndef PROJECT1_IMAGE_H
#define PROJECT1_IMAGE_H

#include <vector>
#include <memory>
#include <map>
#include <wx/graphics.h>


/**
 * Class to preload an image into
 */
class Image {
private:
    /// The item image
    std::shared_ptr<wxImage> mItemImage;

    /// Map that stores wxString and
    /// smart pointer to corresponding wxBitmap
    std::map<wxString, std::shared_ptr<wxBitmap>> mImageBitmapMap;

    /// Folder in which images are contained
    const std::wstring mFolder = L"images/";

public:
    Image();

    /**
     * Get Image Bitmap from filename
     * @param filename wxString representing filename
     * @return smart pointer to wxBitmap object
     */
    std::shared_ptr<wxBitmap> GetImageBitmap(wxString filename);
};

#endif //PROJECT1_IMAGE_H