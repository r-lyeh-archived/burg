# burg

- Burg is a simple linear predictor (C++11).
- Burg is tiny. Header-only.
- Burg is BOOST licensed.

## API
```c++
ns burg {
template<typename T>
void expand( std::vector<T> &values, unsigned new_values, unsigned quality=8 /*[4..11]*/ ); 
}
```

### Possible output
```c++
Expression (i) = i
value[ 128 ] = 127.999999 (vs expected 128.000000)
value[ 129 ] = 128.999997 (vs expected 129.000000)
value[ 130 ] = 129.999988 (vs expected 130.000000)
value[ 131 ] = 130.999968 (vs expected 131.000000)
Error: 0.000000

Expression (i) = i * i
value[ 128 ] = 16384.000437 (vs expected 16384.000000)
value[ 129 ] = 16641.003241 (vs expected 16641.000000)
value[ 130 ] = 16900.013824 (vs expected 16900.000000)
value[ 131 ] = 17161.044372 (vs expected 17161.000000)
Error: 0.002171

Expression (i) = i * i * i
value[ 128 ] = 2097151.944476 (vs expected 2097152.000000)
value[ 129 ] = 2146688.569397 (vs expected 2146689.000000)
value[ 130 ] = 2196998.120943 (vs expected 2197000.000000)
value[ 131 ] = 2248084.926147 (vs expected 2248091.000000)
Error: 40.611054

Expression (i) = i * i - sin(i)
value[ 128 ] = 16383.279961 (vs expected 16383.278962)
value[ 129 ] = 16641.201242 (vs expected 16641.193473)
value[ 130 ] = 16900.958472 (vs expected 16900.930106)
value[ 131 ] = 17161.872759 (vs expected 17161.811603)
Error: 0.004606

Expression (i) = sin(i)
value[ 128 ] = 0.721038 (vs expected 0.721038)
value[ 129 ] = -0.193473 (vs expected -0.193473)
value[ 130 ] = -0.930106 (vs expected -0.930106)
value[ 131 ] = -0.811603 (vs expected -0.811603)
Error: 0.000000

Expression (i) = cos( i * 0.01 ) + 0.75 * cos( i * 0.03 ) + 0.5 * cos( i * 0.05 ) + 0.25 * cos( i * 0.11 )
value[ 128 ] = 0.223191 (vs expected 0.223191)
value[ 129 ] = 0.197302 (vs expected 0.197301)
value[ 130 ] = 0.170816 (vs expected 0.170815)
value[ 131 ] = 0.144063 (vs expected 0.144061)
Error: 0.000000
```
