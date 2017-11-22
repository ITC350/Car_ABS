//
//  dcmotor.hpp
//  Car_ABS
//
//  Created by <author> on 18/11/2017.
//
//

#ifndef dcmotor_hpp
#define dcmotor_hpp



class dcmotor {
private:
  const int dc_has=10;
  const int dc_ret1=11;
  const int dc_ret2=12;
public:
    dcmotor();
    ~dcmotor();
    void Forward();
    void Backward();
    void Accelerator();
protected:

};


#endif /* dcmotor_hpp */
