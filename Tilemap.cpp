#include "main.hpp"
Tilemap::Tilemap():Tiles(){}

void Tilemap::Render(int RowStart,int ColumnStart,int NumberOfRows,int NumberOfColumns)const{
    if(NumberOfRows<=0||NumberOfColumns<=0)return; /// -----
    int RowEnd=RowStart+NumberOfRows; /// -----
    int ColumnEnd=ColumnStart+NumberOfColumns; /// -----
    int CurrentRow=RowStart; /// -----
    int CurrentColumn; /// -----
    const MapType::const_iterator TilesEnd=Tiles.cend(); /// -----
    MapType::const_iterator RowIterator=Tiles.find(RowStart); /// -----
    while(CurrentRow<RowEnd){
        if(RowIterator==TilesEnd){
            // Invalid row iterator, get a new one.
            RowIterator=Tiles.find(++CurrentRow); /// -----
        }else{
            // Valid row iterator, get the column iterator now.
            const RowType& Row=RowIterator->second; /// -----
            RowType::const_iterator ColumnIterator=Row.find(CurrentColumn=ColumnStart); /// -----
            const RowType::const_iterator TilesRowEnd=Row.cend(); /// -----
            while(CurrentColumn<ColumnEnd){
                if(ColumnIterator==TilesRowEnd){
                    // Invalid column iterator, get a new one.
                    ColumnIterator=Row.find(++CurrentColumn); /// -----
                }else{
                    // Valid column iterator, get the tile value now.
                    const short& TileValue=ColumnIterator->second; /// -----
                    /** Draw Tile **/
                    // Move on to the next column.
                    CurrentColumn=(++ColumnIterator==TilesRowEnd?ColumnEnd:ColumnIterator->first); /// -----
                }
            }
            // Move on to the next row.
            CurrentRow=(++RowIterator==TilesEnd?RowEnd:RowIterator->first); /// -----
        }
    }
}

Tilemap::TileType& Tilemap::operator()(int Row,int Column){
    return Tiles[Row][Column]; /// -----
}
