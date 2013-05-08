#ifndef TILEMAP_HPP
#define TILEMAP_HPP
class Tilemap{
public:
    // Variables
    typedef short TileType; /// -----
    typedef map<int,TileType> RowType; /// -----
    typedef map<int,RowType> MapType; /// -----
    MapType Tiles; /// -----
    //sf::Image Texture;
    // Constructor
    Tilemap(); /// -----
    // Functions
    void Render(int X,int Y,int Rows,int Columns)const; /// -----
    // Operators
    TileType& operator()(int Row,int Column); /// -----
};
#endif // TILEMAP_HPP
