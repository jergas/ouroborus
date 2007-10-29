#ifndef Dimension_H
#define Dimension_H

///This type of objects represents a dimension; in the cellular automata the possible coordinates in the dimensions are finite and discrete. 
/**
* This type of objects represents an axe in the "picture"; the dimensions can be normalized, 
* forming ring, or can be with limits looking like a strand. 
*/

class Dimension {

    /**the maxLimit variable is the size of the dimension, is the maximum number of coordinates 
    * alluded in this axe, if you use a bigger coordinate and the dimension is normalized, 
    * you finish with a coordinate inside the maxLimit variable (normalization), if isn’t normalized 
    * then the coordinate don’t exists in this dimension.  
    */
    int maxLimit;
    /**if this variable is true then the dimension coordinates form a ring, if don’t forms a strand, 
    * the coordinates have a max limit, without them the coordinates don’t exist in this dimension.  
    */
    bool normalized;
    
    public:
    
    /**
    * The constructor, creates a object, with a given 
    * size (100 default) and type of limits (default with limits)
    */
    Dimension(int size=100, bool normalized=false): maxLimit(size), normalized(normalized){}
    
    /// The copy-constructor:
    Dimension(const Dimension& d): maxLimit(d.maxLimit), normalized(d.normalized){}
    
    /** 
    * Overwrite the = operator to avoid problems when you
    *forget initialize whit the constructor  
    */
    Dimension& operator=(const Dimension& d) {
        maxLimit = d.maxLimit;
        normalized = d.normalized;
        return *this;
    }   
    
	/// the destructor
    ~Dimension(){}    

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //   ACAESTOY:    
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    
    //-----------get set methods --------------------------
    ///Return the number of alluded  coordinates in this finite, discrete dimension object.
    inline int getSize(){return maxLimit;}
    ///Set the number of alluded coordinates in this finite, discrete dimension object.
    inline void setSize(int dsize){maxLimit = dsize;}
    /** This method return if the dimension is normalized or not, the normalization implies
    * if the dimension have limits or not, if not (return true) the coordinates are forming 
    * a ring, no matter how big the coordinate you can choose the coordinates in this dimension 
    * always exist, if isn’t normalized, the dimension have limits, and if you choose a 
    * coordinate bigger than the maxLimit variable the coordinate will don’t exist in this dimension*/
    inline bool getNormalized(){return normalized;}  
    /**With this method you can change the normalization of the dimension, if is set true, then no 
    * matter how big the coordinates you choose, is always gone exist in this dimension object, if
    * set false, and you choose a coordinate bigger than the maxLimit variable the coordinate it 
    * will by out of range */
    inline void setNormalized(bool normal){normalized = normal;}
    //-----------get set methods --------------------------
    
    /**
    * This method is to know if a coordinate
    * is outside of limits, returns true is the coordinate is 
    * out and false other way
    */
    inline bool isOutOfBounds(int coordinate){    
    
		//If the dimension is normalized there is no limits    
		if(normalized)
			return false;
		//if not normalized
		else{
		//and the coordinate  is to big or to small
		//is outside of limits
			if( (0 <= coordinate)&&(coordinate < maxLimit) )
                return false;                               
			else
                return true;
		}
	}//---------isOutOfBounds(int coordinate)------------------
   
    /**
    * this method is to return the “real” coordinate in the dimension, in 
    * base of the input, only has sense to call it if the dimension
    * is normalized, but sometimes you want generic code and call 
    * it anyway, so you have to call isOutOfBounds(int coordinate) 
    * method before call this method to avoid a bugs.
    */
    inline int getPos(int coordinate){
                //if the coordinate is normalized
		if(normalized){
			//and the coordinate is not in the limits
			if(! ((0<= coordinate) && (coordinate < maxLimit)) ){
				if(0 > coordinate){
					/*if the coordinate is negative move
					one time the dimension to the left 
					and try again the function */
					coordinate = getPos(coordinate += maxLimit);
					return coordinate; 
				}                
				else{                
					/*if the coordinate is bigger than the
					limits move one time the dimension to 
					the right and try again the function*/
					coordinate = getPos(coordinate -= maxLimit);                       
					return coordinate;                     
				}
			}    
			else {//if the coordinate is in between boundary's
				return coordinate;
			}                
		}
		//not normalized
		else{ 
			return coordinate;
		}
	}//-------------------getPos(int coordinate)----------------      
};
#endif //Dimension_H
