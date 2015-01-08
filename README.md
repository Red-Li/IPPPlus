C++ wrapper for Intel Integrated Performance Primitives(IPP)
===========

Naming Standard
-------------

Support Features
-------------

* Automatic tranlate C++ navitve type to Ipp types

    > std::is_same(ipp::get<int8_t>::type, Ipp8s);    
    > std::is_same(ipp::get<char>::type, Ipp8s); //int8_t and char are not always the same      
    > std::is_same(ipp::get<uint8_t>::type, Ipp8u);         
    > std::is_same(ipp::get<std::complex<float> >::type, Ipp32fc);        

* Automatic function dispath depend on parameter type

    > uint8_t *buf1 = ipp::malloc<uint8_t>(1024);   
    > uint8_t *buf2 = ipp::malloc<uint8_t>(1024);    
    > ipp::and_const(buf1, uint8_t(0x3), buf2, 1023);  //same as ippsAndC_8u(...)    

    > unsigned int *buf1 = ipp::malloc<unsigned int>(1024);    
    > unsigned int *buf2 = ipp::malloc<unsigned int>(1024);    
    > ipp::and_const(buf1, unsigned int(0x3), buf2, 1023);  //same as ippsAndC_32u(...)   

* Extend some original IPP function to support more types

    > int8_t *buf1 = ipp::malloc<int8_t>(1024);
    > int8_t *buf2 = ipp::malloc<int8_t>(1024);
    > ipp::and_const(buf1, int8_t(0x3), buf2, 1023);  //actually, ippsAndC_8s(...) is not supported

* Re-write some context based IPP function as C++ class to make it easy to use
    
    > ipp::rand_gauss<float> gas(0, 0.1, 0);    
    > float *buf = ipp::malloc<float>(1024);      
    > gas.generate(buf, 1024);      

    > typedef ipp::win<float> win;  
    > win w(win::HAMMING, 1024);  
    > w.mul(src, dst, 1024);  


Tutorial
--------

This is a header only C++ library and the only dependence is Intel Integrated Performance Primitives(IPP)
 
- Build Test

    > mkdir build && cd build     
    > export IPPROOT=/root/directory/of/intel/ipp/direcotry      
    > cmake ..    
    > .....       


- CMake

    > export IPPROOT=/root/directory/of/intel/ipp/direcotry       
    > include(IPPPlus)


