//
//  LoadModel.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef LoadModel_hpp
#define LoadModel_hpp

#include "Utils.h"


class LoadModel {
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    
    
public:
    void loadModel();
    const std::vector<Vertex>& GetVertices() const;
    const std::vector<uint32_t>& GetIndices() const;
    
};

#endif /* LoadModel_hpp */
