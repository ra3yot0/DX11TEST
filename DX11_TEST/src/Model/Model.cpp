#include "../../include/Model/HeaderApp.hpp"

Model::Model() 
{
    numIdx = 0U;
    posX = 0.f;
    posY = 0.f;
    posZ = 0.f;
    degX = 0.f;
    degY = 0.f;
    degZ = 0.f;
    sclX = 1.f;
    sclY = 1.f;
    sclZ = 1.f;
    colR = 1.f;
    colG = 1.f;
    colB = 1.f;
    colA = 1.f;
    pVBuffer = nullptr;
    pIBuffer = nullptr;
}