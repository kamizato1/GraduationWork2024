#pragma once
#include"MapBase.h"

#define TILE_TYPE_NUM 28
#define TILE_NUM 60

class TownMap : public MapBase
{
private: 

    char town_map_data[TILE_NUM][TILE_NUM][3] =
    {
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "31", "31", "31", "91", "91", "31", "91", "91", "91", "91", "H1", "H1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "31", "01", "01", "01", "01", "01", "31", "31", "91", "91", "H1", "H1", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "91", "01", "01", "01", "01", "01", "01", "31", "31", "91", "H1", "H1", "91", "D1", "E1", "E1", "D1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "D1", "91", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "91", "91", "31", "31", "31", "31", "31", "31", "31", "91", "H1", "H1", "91", "D1", "Q1", "R1", "D1", "P1", "P1", "P1", "D1", "61", "61", "61", "61", "61", "D1", "91", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "91", "91", "91", "91", "91", "31", "31", "31", "31", "31", "H1", "H1", "01", "D1", "61", "N1", "D1", "61", "61", "61", "D1", "61", "64", "O1", "O1", "61", "D1", "01", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "E1", "E1", "E1", "E1", "E1", "D1", "D1", "D1", "31", "H1", "H1", "01", "D1", "61", "O1", "D1", "P1", "P1", "61", "E1", "61", "62", "N1", "N1", "61", "D1", "01", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "P1", "P1", "P1", "P1", "P1", "D1", "D1", "D1", "31", "H1", "H1", "01", "D1", "61", "61", "E1", "61", "61", "61", "61", "61", "61", "O1", "O1", "61", "D1", "01", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "61", "61", "61", "61", "61", "D1", "D1", "D1", "31", "H1", "H1", "01", "D1", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "D1", "01", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "N1", "O1", "61", "61", "61", "D1", "D1", "D1", "31", "H1", "H1", "01", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "61", "E1", "E1", "E1", "E1", "01", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "61", "61", "61", "64", "61", "D1", "M1", "D1", "31", "H1", "H1", "01", "01", "01", "01", "01", "01", "01", "01", "01", "01", "61", "01", "01", "01", "01", "01", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "E1", "E1", "E1", "E1", "N1", "E1", "E1", "E1", "E1", "31", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "61", "H1", "H1", "H1", "H1", "H1", "H1", "H1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "91", "31", "31", "01", "61", "01", "31", "31", "31", "31", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "61", "I1", "I1", "I1", "I1", "I1", "I1", "I1", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "01", "01", "01", "01", "91", "91", "31", "91", "91", "01", "01", "01", "91", "01", "01", "01", "61", "61", "61", "01", "01", "01", "01", "01", "01", "01", "31", "31", "31", "01", "01", "01", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "01", "01", "91", "91", "91", "C1", "C1", "C1", "31", "91", "91", "91", "91", "01", "91", "01", "61", "61", "61", "01", "01", "01", "01", "01", "31", "31", "91", "91", "91", "91", "91", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "01", "01", "91", "91", "C1", "C1", "C1", "C1", "C1", "C1", "C1", "C1", "31", "01", "01", "01", "61", "61", "61", "01", "31", "31", "31", "31", "31", "31", "91", "91", "91", "91", "91", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "01", "91", "91", "C1", "C1", "C1", "C1", "C1", "C1", "C1", "C1", "C1", "C1", "91", "01", "01", "61", "61", "61", "01", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "01", "91", "91", "C1", "C1", "31", "C1", "C1", "C1", "C1", "C1", "C1", "C1", "91", "01", "01", "61", "61", "61", "01", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "C1", "C1", "C1", "91", "01", "01", "61", "61", "61", "01", "91", "D1", "D1", "D1", "D1", "D1", "D1", "D1", "D1", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "91", "91", "91", "91", "01", "91", "91", "01", "91", "91", "C1", "91", "01", "01", "01", "61", "61", "61", "01", "01", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "D1", "E1", "E1", "E1", "D1", "D1", "01", "01", "01", "31", "01", "01", "01", "01", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "N1", "61", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "E1", "P1", "P1", "P1", "E1", "D1", "01", "01", "01", "01", "08", "01", "01", "31", "61", "61", "61", "01", "D1", "D1", "D1", "61", "61", "61", "61", "N1", "63", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "61", "61", "61", "61", "61", "D1", "01", "01", "01", "01", "01", "01", "31", "31", "61", "61", "61", "01", "D1", "L1", "D1", "61", "61", "61", "61", "N1", "61", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "61", "61", "61", "O1", "61", "E1", "E1", "E1", "01", "01", "01", "31", "31", "31", "61", "61", "61", "01", "E1", "D1", "E1", "E1", "E1", "61", "E1", "E1", "E1", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "61", "61", "N1", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "61", "01", "91", "D1", "Q1", "R1", "61", "61", "61", "Q1", "R1", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "61", "O1", "61", "69", "61", "E1", "E1", "D1", "01", "01", "01", "01", "31", "31", "61", "61", "61", "91", "91", "D1", "Q1", "R1", "61", "61", "61", "Q1", "R1", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "61", "61", "61", "61", "61", "61", "61", "D1", "31", "01", "01", "01", "01", "31", "61", "61", "61", "91", "91", "D1", "Q1", "R1", "61", "61", "61", "Q1", "R1", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "D1", "61", "61", "61", "61", "61", "61", "61", "D1", "31", "01", "01", "01", "01", "31", "61", "61", "61", "91", "91", "D1", "D1", "D1", "D1", "D1", "D1", "D1", "D1", "D1", "D1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "31", "31", "01", "01", "01", "01", "61", "61", "61", "31", "91", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "E1", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "31", "01", "01", "01", "61", "61", "61", "31", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "91", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" },
        { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" }
    };

    TILE tile[TILE_NUM][TILE_NUM];
    
    //クラス
    class NpcBase* npc[10];
    class Message* message;

    VECTOR2_I player_start_location;
    VECTOR2_I player_start_location_index;

    //画像
    int tile_image[TILE_TYPE_NUM];

    int npc_image[252];

    int bright_value;

    //関数
    void SetMap()override;//フィールドを生成
    void SetMessage();
    bool CheckHitObject(VECTOR2_I character_location_index, int npc_index);

public:
    TownMap(class Player* player);
    ~TownMap();
    void Initialize()override;

    void SetRevival();

    GAME_SCENE_TYPE Update(float delta_time)override;//戻り値あるよ！
    void Draw() const override;
};